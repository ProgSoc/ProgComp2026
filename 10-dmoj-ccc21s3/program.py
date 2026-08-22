people = [list(map(int, input().split())) for _ in range(int(input()))]

# Function to calculate the total walking times of everyone if you choose
# to place the food truck at position `c` along the line.
cost = lambda c: sum(w * max(0, abs(p - c) - d) for p, w, d in people)

# Over all possible values of `c`, `cost()` is a unimodal function.
# We can conduct a binary search and check whether the middle and its next index form an upward or downward slope.
# `low` and `high` form the inclusive interval on which the search is conducted.
# If it is upward, we exclude the higher value (`mid + 1`) from the next searching interval.
# If it is downward, we exclude the lower value (`mid`) from the next searching interval.
low, high = min(x[0] for x in people), max(x[0] for x in people)
while low < high:
    mid = (low + high) // 2
    c1, c2 = cost(mid), cost(mid + 1)
    if c1 < c2:
        high = mid
    elif c1 > c2:
        low = mid + 1
    else:
        low = high = mid

print(cost(low))
