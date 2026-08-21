from collections import deque

n, k = list(map(int, input().split()))
x, a, b, c = list(map(int, input().split()))

# Initialise the generator input and the window with `x`.
xi = x
window = deque([xi])
window_sum = xi

# Calculate the first window of size `k`.
for i in range(2, k+1):
    # This generates the next input `x_i` from the previous value of `x_i`.
    xi = (a * xi + b) % c
    window.append(xi)
    window_sum += xi

# The first window we have seen thus contributes the first number to the final `sum`.
sum = window_sum

for i in range(k+1, n+1):
    # The new generator input `x_i` is generated from the previous, and the window sum is incremented.
    xi = (a * xi + b) % c
    window_sum += xi

    # We move to the next window by removing from the left and adding the new element to the right.
    # We also remove the contribution of the removed element (on the left) from the window sum.
    window_sum -= window.popleft()
    window.append(xi)

    # Update the `sum` by XOR'ing with the current window sum.
    sum ^= window_sum

# Output the final XOR sum.
print(sum)
