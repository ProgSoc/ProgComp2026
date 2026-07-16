#include <iostream>
#include <vector>

bool isGroup(std::vector<std::vector<int>>& table) {
    int n = table.size();
    // Check for associativity.
    // Every triple must be checked, and this is doable despite being cubic time since `n <= 100`.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                // We return early (i.e., know it cannot be a group) if at any point,
                // we find a triplet such that `(i.j).k != i.(j.k)`.
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }

    // Check for an identity (and the inverse property).
    for (int i = 0; i < n; ++i) {
        // For every element, we first check if it an identity element.
        // That is, for some element `i`, we check if `j.i = j` and `i.j = j`
        // for all elements `j`, where `.` is the group operator.
        bool isIdentity = true;
        for (int j = 0; j < n; ++j) {
            if (table[i][j] != j || table[j][i] != j) {
                isIdentity = false;
                break;
            }
        }
        // If the element is a candidate for an identity,
        // we check the inverse property using this as the inverse.
        if (isIdentity) {
            for (int j = 0; j < n; ++j) {
                bool hasInverse = false;
                // For every element `j`, we look for an element `k` (the inverse)
                // such that `j.k = k.j = i`. We return early (successfully) if we find one.
                for (int k = 0; k < n; ++k) {
                    if (table[j][k] == i && table[k][j] == i) {
                        hasInverse = true;
                        break;
                    }
                }
                // If we did not manage to find an inverse,
                // then our current candidate `i` cannot be an identity.
                if (!hasInverse) {
                    isIdentity = false;
                    break;
                }
            }
        }
        // If we have found an element that satisfies the identity property
        // and allows the existence of an inverse element for all elements of the group,
        // then we can return now and safely say this is a group.
        if (isIdentity) {
            return true;
        }
    }
    return false;
}

int main() {
    // Every test case starts with the number of elements in the group.
    int n;
    std::cin >> n;
    // We keep taking in grids until `n` hits zero.
    while (n != 0) {
        // We take in a 2D-vector of size `n` in both dimensions.
        std::vector<std::vector<int>> table(n, std::vector<int>(n));
        for (auto& row : table) {
            for (auto& element : row) {
                std::cin >> element;
                // Since the integers are in the range [1..n],
                // we decrement them to map them to [0..n-1]
                // to allow each integer to be usable as an index of the table.
                --element;
            }
        }
        // Finally, we output whether the table satisfies the group property.
        std::cout << (isGroup(table) ? "yes\n" : "no\n");
        // We grab the size of the next test case to update for the next test case.
        std::cin >> n;
    }
    return 0;
}
