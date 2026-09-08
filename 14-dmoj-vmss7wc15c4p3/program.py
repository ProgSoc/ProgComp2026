import heapq

# To see what the shortest distances are while also passing through some particular node,
# we perform two instances of Dijkstra's algorithm for the single-source shortest path (SSSP) problem:
# one from the source and one from the destination.
# These two shortest distances to reach the node when summed up give the shortest complete path
# passing through that node. From there, we just need to find the maximum value.

# Conducts Dijkstra's algorithm (with adjacency list encoding of the graph) from a given source.
def sssp(graph, source):
    # Initialise our "shortest distance" array.
    dist = [float('inf')] * len(graph)
    # Naturally, we start with a distance of zero at our source.
    dist[source] = 0

    # We initialise our traversal frontier with the tuple of (cost, node).
    open = [(0, source)]
    while open:
        # The traversal frontier is a priority queue implemented as a min-heap (binary heap).
        # Priority queue operations are managed by `heapq`.
        cost, u = heapq.heappop(open)
        for v, t in graph[u]:
            new_cost = cost + t
            # Edge relaxation.
            if new_cost < dist[v]:
                dist[v] = new_cost
                heapq.heappush(open, (new_cost, v))
    return dist

n, m = list(map(int, input().split()))
# Take in the graph and represent it in adjacency list format via a dictionary.
graph = {}
for _ in range(m):
    a, b, t = list(map(int, input().split()))
    graph[a] = graph.get(a, [])
    graph[a].append((b, t))
    graph[b] = graph.get(b, [])
    graph[b].append((a, t))

# Add the two `dist` arrays element-wise and find the maximum value.
print(max(start + end for start, end in zip(sssp(graph, 0), sssp(graph, n-1))))
