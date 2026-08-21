# To prevent TLE, it is better to precompute the possible rooms any value can map to beforehand.

def dfs(grid, m, n):
    # Precompute the traversal graph,
    # such that `adj[v]` returns the list of all rooms that can be reached
    # from a room that has the value `v` in it.
    adj = {}
    for row in range(m):
        for col in range(n):
            key = (row + 1) * (col + 1)
            adj[key] = adj.get(key, [])
            adj[key].append((row + 1, col + 1))
    # We start in the room (1, 1).
    stack = [(1, 1)]
    # There are `m * n` rooms,
    # so we have a list of size `m * n` to keep track of whether we have visited a room or not.
    # It is encoded such that a room (i, j) has been visited if index `(i - 1) * n + (j - 1)` is True.
    seen = [True] + [False] * (m * n - 1)
    # We then conduct the depth-first search here (a breadth-first search can work as well).
    while stack:
        r, c = stack.pop()
        for row, col in adj.get(grid[r-1][c-1], []):
            # The indexing rule for the `seen` list as above.
            if not seen[(row - 1) * n + (col - 1)]:
                # We keep the 1-based indexing of rooms in the stack.
                stack.append((row, col))
                seen[(row - 1) * n + (col - 1)] = True
                if ((row, col) == (m, n)):
                    break
    # We are able to escape the labyrinth if the final room (corresponding to the room (m, n)) is visited.
    return seen[-1]

# Take in the number of rows and columns, then the grid itself.
m = int(input())
n = int(input())
grid = [[int(x) for x in input().split()] for _ in range(m)]
print('yes' if dfs(grid, m, n) else 'no')
