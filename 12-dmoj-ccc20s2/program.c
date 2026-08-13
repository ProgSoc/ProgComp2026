#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_M 1000
#define MAX_N 1000
#define MAX_VALUE 1000000

int grid[MAX_M][MAX_N];
bool visited[MAX_M][MAX_N];
int *factors[MAX_VALUE + 1];
int factorCount[MAX_VALUE + 1];

typedef struct {
    int row;
    int col;
} Pos;

Pos *stack;
int stackSize;
int stackCapacity;

void pushStack(int row, int col) {
    if (stackSize == stackCapacity) {
        stackCapacity *= 2;
        stack = realloc(stack, stackCapacity * sizeof(Pos));
    }
    stack[stackSize].row = row;
    stack[stackSize].col = col;
    stackSize++;
}

Pos popStack(void) {
    stackSize--;
    return stack[stackSize];
}

bool dfs(int m, int n) {
    stackCapacity = 1024;
    stack = malloc(stackCapacity * sizeof(Pos));
    stackSize = 0;
    pushStack(0, 0);

    bool found = false;

    while (stackSize > 0) {
        Pos cur = popStack();
        int row = cur.row;
        int col = cur.col;

        if (visited[row][col]) {
            continue;
        }

        if (row == m - 1 && col == n - 1) {
            found = true;
            break;
        }

        visited[row][col] = true;

        int value = grid[row][col];

        if (factors[value] == NULL) {
            int count = 0;
            for (int factor = 1; factor <= m; factor++) {
                if (value % factor == 0) {
                    count++;
                }
            }

            factors[value] = malloc(count * sizeof(int));
            factorCount[value] = count;

            int idx = 0;
            for (int factor = 1; factor <= m; factor++) {
                if (value % factor == 0) {
                    factors[value][idx] = factor;
                    idx++;
                }
            }
        }

        for (int k = 0; k < factorCount[value]; k++) {
            int factor = factors[value][k];
            int new_row = factor - 1;
            int new_col = value / factor - 1;
            if (new_row < m && new_col < n) {
                if (!visited[new_row][new_col]) {
                    pushStack(new_row, new_col);
                }
            }
        }
    }

    free(stack);
    return found;
}

int main(void) {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    if (dfs(m, n)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}