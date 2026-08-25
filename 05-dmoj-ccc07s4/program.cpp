#include <iostream>
#include <vector>

// The waterpark can be considered as a graph with `n` points (numbered `1` to `n`),
// such that the graph has a directed edge from `i` to `j`
// if there is a slide that goes from `i` to `j` and `i < j`.
// The numbering of the points already imposes a topological ordering,
// so all we need to do is solve the subproblem of how many paths there are to node `i`
// sequentially from `i = 1` to `i = n`. The subproblem for a node `i` depends on values for `1` to `i-1`.
int calc(std::vector<std::vector<bool>>& adj) {
    int n = adj.size();
    std::vector<int> paths(n, 0);

    // The base case. By definition, there is one way to reach the very first node.
    paths[0] = 1;

    for (int i = 1; i < n; ++i) {
        // We then iterate over every previous node.
        for (int src = 0; src < i; ++src) {
            // If that previous node directly connects to the current one,
            // then the number of ways you can reach that node is added to our current count.
            if (adj[src][i]) {
                paths[i] += paths[src];
            }
        }
    }

    // The last element of `paths` is the `n`-th node.
    return paths.back();
}

int main() {
    // First we take in the number of points.
    int n;
    std::cin >> n;

    // The graph can be easily inputted and represented in adjacency matrix form.
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));

    int x, y;
    std::cin >> x >> y;
    // We keep taking in pairs (edges) until the sentinel values `0 0` are given.
    while (x != 0 && y != 0) {
        // Since the nodes are numbered in the problem input from `1` to `n`,
        // we convert these to zero-based indices to allow the usage of an adjacency matrix.
        adj[x-1][y-1] = true;
        std::cin >> x >> y;
    }

    // Finally, we output the number of paths to the final node.
    std::cout << calc(adj) << '\n';

    return 0;
}
