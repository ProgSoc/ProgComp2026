#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Given the size constraints of this problem's input,
// conducting a BFS or a DFS at every query is too slow.
// Since we only care whether one point is connected to another,
// this can be modelled as an equivalence relation which can thus be captured by a disjoint set union.

// An implementation of a disjoint set union ranked by size.
// Ranking by height will also work.
struct DSU {
    std::vector<int> parent {};
    std::vector<int> size {};

    // Path compression during the search for the root (set representative).
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    // Union based on size (smaller size gets attached as a subtree of the bigger one).
    void union_sets(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (size[x] < size[y]) {
                std::swap(x, y);
            }
            parent[y] = x;
            size[x] += size[y];
        }
    }

    // Additional member function (outside of the typical DSU operations).
    // This allows adding an extra node when it is needed,
    // since that will be required during a possible query if a new city name is found.
    // Returns the index of the new element as well.
    int grow() {
        int new_num = parent.size();
        parent.push_back(new_num);
        size.push_back(1);
        return new_num;
    }
};

int main() {
    // There are five test cases.
    for (int t = 0; t < 5; ++t) {
        // For each test case, we have a distinct DSU and a list of names.
        // Since names of cities are passed as strings, we need to map them to integers
        // to be usable inside a DSU.
        DSU dsu {};
        std::unordered_map<std::string, int> names {};

        // The first line of a test case is the number of queries `n`.
        int n;
        std::cin >> n;
        while (n--) {
            // Each query starts with a single character (either "p" or "q"),
            // followed by two strings (city names `a` and `b`).
            std::string p, a, b;
            std::cin >> p >> a >> b;

            // First, we convert the strings to integers representing their index within a DSU.
            // If they do not yet exist, we assign them a new spot in the DSU, and record the new index.
            int i = names.contains(a) ? names[a] : (names[a] = dsu.grow());
            int j = names.contains(b) ? names[b] : (names[b] = dsu.grow());

            if (p == "p") {
                // If the first character is "p", we connect cities `i` and `j`.
                dsu.union_sets(i, j);
            } else if (p == "q") {
                // Otherwise, we return whether cities `i` and `j` are connected.
                std::cout << (dsu.find(i) == dsu.find(j) ? "connected" : "not connected") << '\n';
            }
        }
    }
    return 0;
}
