#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10000

// adj[x][y] is true if there's a direct slide from station x to station y
// (0-indexed, so station 1 in the problem is index 0 here)
bool adj[MAX_N][MAX_N];
// paths[i] is the number of distinct ways to reach station i from station 0
long long paths[MAX_N];

// counts the number of distinct paths from station 0 to station n - 1
long long calc(int n) {
    // there's exactly one way to be at station 0, the starting point itself
    paths[0] = 1;
    // since the numbering is already a valid topological order, we can
    // process stations left to right and know every predecessor's path
    // count is already finalized by the time we reach it
    for (int i = 1; i < n; i++) {
        // sum the path counts of every earlier station that has a
        // direct slide into station i, this is the number of distinct
        // ways to arrive at station i
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

    // read slide connections until the 0 0 sentinel is reached, shifting
    // down to 0-indexed to match the array
    int x, y;
    scanf("%d %d", &x, &y);
    while (x != 0 && y != 0) {
        adj[x - 1][y - 1] = true;
        scanf("%d %d", &x, &y);
    }

    printf("%lld\n", calc(n));

    return 0;
}