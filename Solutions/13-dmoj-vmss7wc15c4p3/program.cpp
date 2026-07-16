#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// This problem can be solved by solving the single-source shortest paths (SSSP) problem twice:
// one from the starting city (City 0), and one from the destination city (City N-1).
// This is because for any City `i`, the shortest path from City 0 to City N-1 that passes through City `i`
// must be decomposable into two components: a path from City 0 to City `i`, and a path from City `i` to City N-1.
// For the total path to be the shortest possible, both components must also be the shortest possible.
// Hence, solving SSSP from both ends finds these two components, and all we need to do is add them together.

// Solves SSSP using Dijkstra's.
std::vector<int> sssp(std::vector<std::vector<std::pair<int, int>>>& graph, int source) {
    // Each item in our traversal frontier is a pair weighted on cost first
    // (here the lexicographical comparison automatically defined by `std::pair` is used).
    // Hence, the first element is the cost taken to get to that node, while the second element is the node itself.
    using Item = std::pair<int, int>;

    // Dijkstra's requires keeping track of the shortest distance to a particular node found currently.
    std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());
    // We start off with having zero distance from the source.
    dist[source] = 0;

    // The traversal frontier, which is a min-heap so the smallest cost is always explored first.
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> open {};

    // We start at the source with zero accumulated cost.
    open.push({ 0, source });

    while (!open.empty()) {
        auto [cost, u] = open.top();
        open.pop();

        // For every node that can be reached, we find the cost it would take to reach that node
        // as a result of using the current traversal we are considering.
        // If this is better than our previous records for that node,
        // only then do we consider adding this traversal to the frontier we keep track of,
        // while also updating our knowledge of the shortest paths.
        for (auto [v, t] : graph[u]) {
            int new_cost = cost + t;
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                open.push({ new_cost, v });
            }
        }
    }

    // Since we need to solve SSSP for all possible nodes rather than just for one destination,
    // we return the entire `dist` vector.
    return dist;
}

int main() {
    // First, we take in the number of nodes (`n`) and number of edges (`m`).
    int n, m;
    std::cin >> n >> m;

    // We store the graph in adjacency list manner,
    // where `graph[u]` stores a vector of pairs `(v, cost)`,
    // such that `u` has a directed edge to `v` weighted by `cost`.
    std::vector<std::vector<std::pair<int, int>>> graph(n);

    // We take in the information about the graph, which has `m` lines (since there are `m` edges).
    int a, b, t;
    while (m--) {
        std::cin >> a >> b >> t;
        graph[a].push_back({ b, t });
        graph[b].push_back({ a, t });
    }

    // Conduct the two executions of Dijkstra's algorithm: one from `0` and one from `N-1`.
    std::vector<int> cost = sssp(graph, 0);
    std::vector<int> cost_end = sssp(graph, n-1);

    // We add the costs to reach all values together to assemble the cost associated with the shortest path
    // through all nodes `i` for `0 <= i < n`.
    for (int i = 0; i < n; ++i) {
        cost[i] += cost_end[i];
    }

    // We then output the maximum cost from these.
    std::cout << *std::max_element(cost.begin(), cost.end()) << '\n';
    return 0;
}
