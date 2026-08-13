import sys
from collections import defaultdict

def solve():
    data = sys.stdin.buffer.read().split()
    idx = 0
    m = int(data[idx]); idx += 1
    n = int(data[idx]); idx += 1
    grid = [int(x) for x in data[idx:idx + m * n]]

    reachable = defaultdict(list)
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            v = i * j
            if v <= 1_000_000:
                reachable[v].append((i - 1, j - 1))
            else:
                break

    visited = bytearray(m * n)
    stack = [0]
    target = m * n - 1

    while stack:
        pos = stack.pop()
        if visited[pos]:
            continue
        if pos == target:
            print("yes")
            return
        visited[pos] = 1

        value = grid[pos]
        for (r, c) in reachable.get(value, ()):
            npos = r * n + c
            if not visited[npos]:
                stack.append(npos)

    print("no")

solve()