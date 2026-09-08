n, m = list(map(int, input().split()))
a = [list(map(int, input().split())) for _ in range(n)]

base = 10**9 + 7

# Conducting a full Gauss-Jordan elimination is too slow for Python.
# Instead, a Gaussian elimination is conducted with the suitable back-substitution step.

# We keep track of which row each column's pivot is found at.
# This is later used to store the actual values deduced from the back-substitution step.
pivots = [-1] * m

last_pivot = -1
for step in range(m):
    # First, we find the pivot row for our current column,
    # such that the pivot row is below the previous one.
    pivot = -1
    for row in range(last_pivot + 1, n):
        if a[row][step] != 0:
            pivot = row
            break
    if pivot == -1:
        continue

    # Then, we record the row of our current pivot.
    pivots[step] = pivot
    last_pivot = pivot

    # Next, we normalise the current row using the modular inverse,
    # which is achieved via modular exponentiation natively through the `pow` function.
    inverse = pow(a[pivot][step], base - 2, base)
    for col in range(step, m + 1):
        a[pivot][col] = (a[pivot][col] * inverse) % base

    # Finally, we eliminate the rows below our current one.
    for row in range(pivot + 1, n):
        factor = a[row][step]

        # If the factor is 0, then no further computation needs to be done since the operation is a no-op.
        if factor == 0:
            continue

        for col in range(step, m + 1):
            a[row][col] = (a[row][col] - a[pivot][col] * factor) % base

# Check for any inconsistencies.
# If there is a row where all coefficients are zero but the target is non-zero, then there is no solution.
for row in range(n):
    if all(a[row][col] == 0 for col in range(m)) and a[row][m] != 0:
        print(-1)
        exit()

# Back substitution to find the solutions.
for step in range(m - 1, -1, -1):
    # If a column `step` does not have a pivot,
    # this column is a free variable and we set it to 0.
    if pivots[step] == -1:
        pivots[step] = 0
    else:
        # Otherwise, we find the corresponding value in the final column.
        pivot = pivots[step]
        value = a[pivot][m]
        # Then, subtract the values contributed by the other variables in the same row.
        # We only consider `col` from higher than `step` since only those ones are non-zero.
        for col in range(step + 1, m):
            value = (value - a[pivot][col] * pivots[col]) % base
        pivots[step] = value

print(*pivots)
