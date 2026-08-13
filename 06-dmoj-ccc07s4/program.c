#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10000

bool adj[MAX_N][MAX_N];
long long paths[MAX_N];

long long calc(int n) {
    paths[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int src = 0; src < i; src++) {
            if (adj[src][i]) {
                paths[i] += paths[src];
            }
        }
    }
    return paths[n - 1];
}

int main(void) {
    int n;
    scanf("%d", &n);

    int x, y;
    scanf("%d %d", &x, &y);
    while (x != 0 && y != 0) {
        adj[x - 1][y - 1] = true;
        scanf("%d %d", &x, &y);
    }

    printf("%lld\n", calc(n));

    return 0;
}