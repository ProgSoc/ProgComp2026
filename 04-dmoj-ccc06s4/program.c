#include <stdio.h>
#include <stdbool.h>

int table[100][100];

bool isGroup(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        bool isIdentity = true;
        for (int j = 0; j < n; j++) {
            if (table[i][j] != j || table[j][i] != j) {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity) {
            for (int j = 0; j < n; j++) {
                bool hasInverse = false;
                for (int k = 0; k < n; k++) {
                    if (table[j][k] == i && table[k][j] == i) {
                        hasInverse = true;
                        break;
                    }
                }
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
    return false;
}

int main(void) {
    int n;
    scanf("%d", &n);

    while (n != 0) {
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