from functools import reduce

# For some permutation `p = [p1, p2, ..., pn]` such that `1 <= pi <= n`,
# there are `n` choices of integers to put for `p1`, `n-1` choices for `p2`, ..., and `1` choice for `pn`.
# If the `qi`-th lowest possible integer is chosen for every element `pi` in `p`,
# we would have selected the `k = 1 + (q1-1) * (n-1)! + (q2-1) * (n-2)! + ... + (qn-1) * (n-n)!`-th permutation.
# For example, if `q1 = q2 = ... = qn = 1`, then `p = [1, 2, ..., n]` and `k = 1`,
# meaning we have selected the `1`-st lowest permutation.
# In another example, if `q1 = n`, `q2 = n-1`, ..., `qn = 1`, then `p = [n, n-1, ..., 1]` and `k = n!`,
# meaning we have selected the `n!`-th lowest permutation (highest permutation).
# It is provable by induction that `n! = (n-1) * (n-1)! + (n-2) * (n-2)! + ... + 1 * 1! + 0 * 0!`.

# From `k`, return `p(n, k)`.
def get_p(n, k):
    # The permutation we will return.
    p = []
    # List of numbers not yet picked,
    # such that `numbers[i]` is the `i`-th lowest integer from the range `[1..n]` that has not been selected.
    numbers = list(range(1, n+1))

    # The first index involves finding the coefficient of `(n-1)!`, hence we start with that value first.
    factorial = reduce(lambda x, y: x * y, range(1, n), 1)
    # For the above math to work, we decrement `k` to map it to the `[0..n!-1]` range.
    k -= 1

    for i in range(n-1):
        # We select the `ki`-th lowest possible number for this slot.
        ki = k // factorial
        # We then remove the selected number from the list of choices for further iterations.
        p.append(numbers.pop(ki))
        # We reduce `k` by the modulo to ensure we always have a number in the `[1..n-1-i]` range.
        k %= factorial
        # Then reduce the factorial to move to the next slot.
        factorial //= n-1-i

    # The final choice is forced.
    p.append(numbers[0])
    return p

# From `p(n, k)`, return `k`.
def get_k(n, p):
    # Used to keep track of the possible numbers selectable at each stage.
    numbers = list(range(1, n+1))

    # The first coefficient to consider is `(n-1)!`.
    factorial = reduce(lambda x, y: x * y, range(1, n), 1)
    # Our computed value would be in the range `[0..n!-1]`,
    # so we add 1 to the initial value getting it to the required range `[1..n!]`.
    k = 1

    for i in range(n-1):
        # Out of the possible selected numbers, the `index`-th smallest integer was chosen.
        index = numbers.index(p[i])
        # Add this contribution to `k`.
        k += index * factorial
        # Remove the chosen number from the set of possibilities.
        numbers.pop(index)
        # Move to the next slot by removing the largest factor from the factorial.
        factorial //= n-1-i

    # We can always ignore the last element of `p` since that choice was forced.
    return k

t = int(input())
for _ in range(t):
    line = list(map(int, input().split()))
    # For every test case, if the first integer is 1, then we return `p` from `k`.
    if line[0] == 1:
        print(' '.join(map(str, get_p(line[1], line[2]))))
    elif line[0] == 2:
    # For every test case, if the first integer is 2, then we return `k` from `p`.
        print(get_k(line[1], line[2:]))
