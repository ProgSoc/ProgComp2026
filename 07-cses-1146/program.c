#include <stdio.h>
#include <stdlib.h>

struct adjNode{
    int v;
    struct adjNode *next;
};

struct adjNode *edges[10000];
long long dp[10000];
int main () {
    int number = 0;
    scanf("%d", &number);

    for (int i = 0; i <= number; i++) {
        edges[i] = NULL;
    }
    int x, y;
    while (scanf("%d %d", &x, &y) == 2) {
        if (x == 0 && y == 0) {
            break;
        }
        struct adjNode *newNode = malloc(sizeof(struct adjNode));
        newNode->v = y;
        newNode->next = edges[x];
        edges[x] = newNode;
    }
    dp[number] = 1;
    
    for (int i = number - 1; i >= 1; i--) {
        for (struct adjNode *curr = edges[i]; curr != NULL; curr = curr->next) {
            dp[i] += dp[curr->v];
        }
    }
    printf("%lld\n", dp[1]);
    return 0;
}