#include <stdio.h>
#include <stdbool.h>
// table[i][j] stores i * j using 0-indexed elements (element values are
// shifted down by 1 from the input, which uses 1-indexed labels).
int table[100][100];

// checks whether the operator defined in `table` (over n elements) forms a valid group
bool isGroup(int n) {
    // associativity check: (i*j)*k must equal i*(j*k) for all i, j, k

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    // if it fails there's no point looking for an identity at all
                    return false;
                }
            }
        }
    }
    // try each element i as a candidate identity
    for (int i = 0; i < n; i++) {
        // i is a valid identity only if i*j == j*i == j for every j
        bool isIdentity = true;
        for (int j = 0; j < n; j++) {
            if (table[i][j] != j || table[j][i] != j) {
                isIdentity = false;
                break;
            }
        }
        // only check inverses if i actually passed as an identity candidate above
        if (isIdentity) {
            // every element j must have some inverse k such that
            // j*k == k*j == i (the identity)
            for (int j = 0; j < n; j++) {
                bool hasInverse = false;
                for (int k = 0; k < n; k++) {
                    if (table[j][k] == i && table[k][j] == i) {
                        hasInverse = true;
                        break;
                    }
                }
                // if even one element has no inverse, i doesn't lead to
                // a valid group, reuse isIdentity as a flag to say so
                if (!hasInverse) {
                    isIdentity = false;
                    break;
                }
            }
        }
        if (isIdentity) {
            return true;
        }
    }
    // no candidate satisfied both the identity and inverse conditions
    return false;
}

int main(void) {
    int n;
    scanf("%d", &n);

    // keep processing tablets until the sentinel n == 0 is reached
    while (n != 0) {
        // read the table, converting from the input's 1-indexed element
        // labels down to 0-indexed values to match the array
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int element;
                scanf("%d", &element);
                table[i][j] = element - 1;
            }
        }

        if (isGroup(n)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }

        scanf("%d", &n);
    }

    return 0;
}