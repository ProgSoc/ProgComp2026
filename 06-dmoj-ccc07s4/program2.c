#include <stdio.h>
#include <stdlib.h>
// this is the same slippery slide problem quesiton (accidentally put it in 07)
// but this uses an adjacency list version instead

// each adjNode represents one outgoing slide, v is the destination
// station, next points to the next slide out of the same source station
struct adjNode{
    int v;
    struct adjNode *next;
};
// edges[x] is the head of a linked list of all stations directly
// reachable from station x via a single slide
struct adjNode *edges[10000];
// dp[i] will hold the number of distinct paths from station i to the
// final station (number), filled in working backwards from the end
long long dp[10000];
int main () {
    int number = 0;
    scanf("%d", &number);
    // explicitly initialise every adjacency list head to NULL, since
    // global arrays of pointers are zero-initialised in c but being
    // explicit here avoids relying on that behaviour
    for (int i = 0; i <= number; i++) {
        edges[i] = NULL;
    }
    // read slide connections until the 0 0 sentinel is reached, using
    // a linked list per source station instead of a full n by n matrix
    // avoids the O(n^2) memory blowup from the earlier matrix version
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
    // base case, there's exactly one way to be at the final station,
    // the "empty path" of already being there
    dp[number] = 1;
    // work backwards from the final station down to station 1, since
    // slides only go from lower numbered stations to higher numbered
    // ones, by the time we reach station i every station reachable
    // from it has already had its own dp value finalised
    for (int i = number - 1; i >= 1; i--) {
        for (struct adjNode *curr = edges[i]; curr != NULL; curr = curr->next) {
            dp[i] += dp[curr->v];
        }
    }
    printf("%lld\n", dp[1]);
    return 0;
}