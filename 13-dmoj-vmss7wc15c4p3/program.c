#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_M 1000
#define MAX_N 1000
#define MAX_VALUE 1000000

int grid[MAX_M][MAX_N];
bool seen[MAX_M * MAX_N];

int countArr[MAX_VALUE + 2];
int cum[MAX_VALUE + 2];
int cursor[MAX_VALUE + 2];
int adjRow[MAX_M * MAX_N];
int adjCol[MAX_M * MAX_N];

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

int main(void) {
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int v = i * j;
            if (v <= MAX_VALUE) {
                countArr[v]++;
            }
        }
    }

    cum[1] = 0;
    for (int v = 1; v <= MAX_VALUE; v++) {
        cum[v + 1] = cum[v] + countArr[v];
        cursor[v] = cum[v];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int v = i * j;
            if (v <= MAX_VALUE) {
                int pos = cursor[v];
                adjRow[pos] = i - 1;
                adjCol[pos] = j - 1;
                cursor[v]++;
            }
        }
    }

    stackCapacity = 1024;
    stack = malloc(stackCapacity * sizeof(Pos));
    stackSize = 0;

    pushStack(0, 0);
    seen[0] = true;

    while (stackSize > 0) {
        Pos cur = popStack();
        int r = cur.row;
        int c = cur.col;
        int v = grid[r][c];

        for (int idx = cum[v]; idx < cum[v + 1]; idx++) {
            int row = adjRow[idx];
            int col = adjCol[idx];
            int flatIdx = row * n + col;
            if (!seen[flatIdx]) {
                seen[flatIdx] = true;
                pushStack(row, col);
            }
        }
    }

    if (seen[m * n - 1]) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    free(stack);
    return 0;
}