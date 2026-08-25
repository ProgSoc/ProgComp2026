from collections import defaultdict

n = int(input())
adj = defaultdict(list)

# We keep reading until the `0 0` pair is inputted.
while (pair := list(map(int, input().split()))) != [0, 0]:
    x, y = pair
    # Due to the way the stations are numbered,
    # we already have a topological ordering of the nodes in our graph.
    # Hence, we only need to record the edges pointing backward
    # (i.e., from a higher number to a lower number) to count the possible paths.
    adj[y-1].append(x-1)

# To start, there is one path to the first station.
paths = [1] + [0] * (n-1)
for i in range(1, n):
    # For every next station,
    # the number of ways to reach it is the sum of all the ways
    # you can reach previous stations that have a direct path to the current one.
    paths[i] = sum((paths[src] for src in adj[i]), 0)

print(paths[-1])
