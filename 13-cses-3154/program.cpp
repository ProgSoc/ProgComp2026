#include <algorithm>
#include <iostream>
#include <vector>

constexpr long long int BASE = 1'000'000'007;

typedef std::vector<std::vector<long long int>> Matrix;
typedef std::vector<long long int> Vector;

// Repeated squaring for modular exponentiation.
long long pow(long long a, long long b) {
    if (b == 0) {
        return 1;
    } else if (b == 1) {
        return a;
    }
    long long tmp = pow(a, b/2);
    long long result = (tmp * tmp) % BASE;
    return b % 2 == 0 ? result : (a * result) % BASE;
}

// Conducts Gauss-Jordan elimination to solve for the system of linear equations.
Vector gauss_jordan(Matrix a, Vector b) {
    // Finds the modular inverse of a given integer by Fermat's Little Theorem, since `10^9 + 7` is prime.
    auto inv = [](auto x) {
        return pow(x, BASE - 2) % BASE;
    };

    int n = a.size(), m = a[0].size();

    // Every element of the solution vector corresponds to a pivot or a zero column (sentinel value -1).
    Vector solution(m, -1);

    // We move down in row along the columns (`step`) when finding pivots.
    int last_pivot = -1;
    for (int step = 0; step < m; ++step) {
        // In our current column and record the row at which we found the first potential non-zero pivot element.
        int pivot = -1;
        for (int row = last_pivot + 1; row < n; ++row) {
            if (a[row][step] != 0) {
                pivot = row;
                break;
            }
        }
        // If none were found, we continue with the Gauss-Jordan elimination,
        // but this column has no pivot.
        if (pivot == -1) {
            continue;
        }

        // We record the position of our pivot in the solution vector for back-substitution later.
        solution[step] = pivot;
        // We also record it so the next pivot we look for is past this row.
        last_pivot = pivot;

        // Next, we normalise the row of our pivot using the modular inverse.
        // This is done for both the unaugmented coefficient matrix (A) and the target vector (b).
        int inverse = inv(a[pivot][step]);
        for (int i = 0; i < m; ++i) {
            a[pivot][i] = (a[pivot][i] * inverse) % BASE;
        }
        b[pivot] = (b[pivot] * inverse) % BASE;

        // Finally, we eliminate all other rows using our current pivot row.
        // In this implementation, we use Gauss-Jordan elimination, hence we also eliminate the rows above us.
        // This makes the back-substitution step easier in this case.
        for (int row = 0; row < n; ++row) {
            if (row == pivot) {
                continue;
            }
            int factor = a[row][step];
            // The addition of `BASE` right after the modulo is to make sure it stays positive
            // since the `%` operator in C++ is a remainder and not a strict mathematical modulo.
            for (int col = 0; col < m; ++col) {
                a[row][col] = (a[row][col] - (a[pivot][col] * factor) % BASE + BASE) % BASE;
            }
            b[row] = (b[row] - (b[pivot] * factor) % BASE + BASE) % BASE;
        }
    }

    // Check for inconsistencies in any of the zero rows.
    // If there are, return an empty vector indicating no solution.
    for (int i = 0; i < n; ++i) {
        bool all_zero = std::all_of(a[i].begin(), a[i].end(), [](auto x) { return x == 0; });
        if (all_zero && b[i] != 0) {
            return {};
        }
    }

    // Since everything is normalised, the back-substitution step just involves taking the value
    // in the vector `b` corresponding to the row we are concerned with.
    // If a particular row of our solution vector had no pivot, then that is a free variable which we assign zero.
    for (int i = 0; i < m; ++i) {
        solution[i] = solution[i] == -1 ? 0 : b[solution[i]];
    }
    return pivots;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Matrix a(n, Vector(m));
    Vector b(n);
    for (int i = 0; i < n; ++i) {
        for (auto& cell : a[i]) {
            std::cin >> cell;
        }
        std::cin >> b[i];
    }

    Vector vec = gauss_jordan(a, b);

    // The function `gauss_jordan` returns an empty vector if no solution exists.
    if (vec.size() == 0) {
        std::cout << -1 << '\n';
    } else {
        for (auto element : vec) {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
