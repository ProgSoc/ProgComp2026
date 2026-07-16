#include <iostream>
#include <utility>
#include <vector>

// The concept behind this is simply to conduct a depth-first search
// over the grid with the traversal rules as described.
// That is, when in a position `(x, y)` (where `1 <= x, y`)
// that has an associated value `v`, we can only travel to positions
// `(xi, yi)` such that `xi * yi = v`.

bool dfs(std::vector<std::vector<int>>& grid, int m, int n) {
    // To save time, we record the list of factors every time we compute it for some value,
    // so that repeat numbers in a grid do not take up unnecessary time.
    // This is required to ensure TLE doesn't happen.
    // Every value is a positive integer <= 1000000, hence we can pre-allocate this.
    std::vector<std::vector<int>> factors(1'000'000);

    // We keep track of nodes we have already visited,
    // such that `visited[i-1][j-1] = true` if we have already expanded the node `(i, j)`.
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n));

    // For depth-first search, a stack is used for the frontier.
    std::vector<std::pair<int, int>> stack {};
    stack.push_back({ 0, 0 });

    while (!stack.empty()) {
        // We take the first node off the top of the stack.
        auto [row, col] = stack.back();
        stack.pop_back();

        // If we have already visited it, we do not process it anymore.
        if (visited[row][col]) {
            continue;
        }

        // The destination is `(m, n)`, which is represented by `[m-1][n-1]` due to zero-indexing.
        // If we reach it, then it is possible to reach `(m, n)` from `(1, 1)` with our traversal rules.
        if (row == m-1 && col == n-1) {
            return true;
        }

        // If we get to this point, we are now processing node `(i, j)`.
        // Hence, we mark it as visited.
        visited[row][col] = true;

        int value = grid[row][col];
        // If we have not yet computed the factors for the value we currently see,
        // we do that now and store it in our `factors` hashmap.
        if (factors[value - 1].empty()) {
            // We also only consider the pairs `(x, y)` where `x * y = value` such that `1 <= x <= m`,
            // since other values would be out of bounds of the grid (when considering their x-coordinate).
            for (int factor = 1; factor <= m; ++factor) {
                if (value % factor == 0) {
                    factors[value - 1].push_back(factor);
                }
            }
        }

        // Then, for all the factors for the value we currently are considering,
        // we add them to the traversal frontier if they represent a point in bounds.
        for (int factor : factors[value - 1]) {
            int new_row = factor - 1;
            int new_col = value / factor - 1;
            if (new_row < m && new_col < n) {
                if (!visited[new_row][new_col]) {
                    stack.push_back({ new_row, new_col });
                }
            }
        }
    }

    // If we exhaust the search but do not ever hit the early return,
    // then it is impossible to reach `(m, n)` from `(1, 1)` given our traversal rules.
    return false;
}

int main() {
    // We first take in the dimensions of the grid.
    int m, n;
    std::cin >> m >> n;

    // We can then represent all values in the grid by a 2D vector of dimensions `m x n`.
    // We directly input these values.
    std::vector<std::vector<int>> grid(m, std::vector<int>(n));
    for (auto& row : grid) {
        for (auto& square : row) {
            std::cin >> square;
        }
    }

    // We conduct the search, and output whether it reached the end state or not.
    std::cout << (dfs(grid, m, n) ? "yes\n" : "no\n");
    return 0;
}
