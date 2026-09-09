#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BASE 1000000007LL

// The maximum size of the augmented matrix is 500 rows and 501 columns.
long long a[500][501];

// Repeated squaring for modular exponentiation.
long long modpow(long long a, long long b) {
    if (b == 0) {
        return 1;
    } else if (b == 1) {
        return a;
    }
    long long tmp = modpow(a, b/2);
    long long result = (tmp * tmp) % BASE;
    return b % 2 == 0 ? result : (a * result) % BASE;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m+1; ++j) {
            scanf("%lld", &a[i][j]);
        }
    }

    int* pivots = malloc(m * sizeof(long long));
    for (int i = 0; i < m; ++i) {
        pivots[i] = -1;
    }

    // It is fast enough to conduct Gauss-Jordan elimination in C.
    int last_pivot = -1;
    for (int step = 0; step < m; ++step) {
        // Move through each column (`step`) and find the first non-zero pivot row after the previous.
        int pivot = -1;
        for (int row = last_pivot + 1; row < n; ++row) {
            if (a[row][step] != 0) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) {
            continue;
        }

        // Record the row number of the pivot chosen this time.
        pivots[step] = pivot;
        last_pivot = pivot;

        // Normalise the current row by taking the modular inverse (using Fermat's little theorem).
        long long inverse = modpow(a[pivot][step], BASE - 2);
        for (int i = 0; i < m + 1; ++i) {
            a[pivot][i] = (a[pivot][i] * inverse) % BASE;
        }

        // Then, eliminate all other rows.
        for (int row = 0; row < n; ++row) {
            if (row == pivot) {
                continue;
            }

            // The addition of `BASE` at each step is to prevent the result from being negative.
            long long factor = a[row][step];
            for (int col = 0; col < m + 1; ++col) {
                a[row][col] = (a[row][col] - (a[pivot][col] * factor) % BASE + BASE) % BASE;
            }
        }
    }

    // Check for inconsistencies.
    // If any completely zero row is matched with a zero last column, then there is no solution.
    for (int i = 0; i < n; ++i) {
        bool all_zero = true;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero && a[i][m] != 0) {
            printf("-1\n");
            return 0;
        }
    }

    // Otherwise, loop through all the pivot rows for each column.
    // Since we conducted Gauss-Jordan elimination,
    // the values of each coefficient is exactly the vector at the end of the augmented matrix.
    // If a particular column has no pivot, then that is a free variable which we set to 0.
    // Otherwise, we output the corresponding element in the resultant vector.
    for (int i = 0; i < m; ++i) {
        if (pivots[i] == -1) {
            printf("0 ");
        } else {
            printf("%lld ", a[pivots[i]][m]);
        }
    }
    printf("\n");

    return 0;
}
