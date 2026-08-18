#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100000
// cars holds the mountain top queue, cars[carsTop - 1] is always the
// next car free to move (either to the branch or straight to the lake)
int cars[MAX_N];
int carsTop;

// branch acts as a stack, cars can only enter and exit it in
// last-in-first-out order, matching the "cannot overtake" rule
int branch[MAX_N];
int branchTop;

// checks whether the cars can be sent to the lake in order 1 to n
bool possible(int n) {
    branchTop = 0;
    // lake tracks the next car number we need to send to the lake

    for (int lake = 1; lake <= n; lake++) {
        if (branchTop > 0 && branch[branchTop - 1] == lake) {
            // the car we need is already waiting at the top of the
            // branch, so just send it straight to the lake
            branchTop--;
        } else if (carsTop > 0 && cars[carsTop - 1] == lake) {
            // the car we need is right at the front of the mountain
            // top, so it can skip the branch entirely
            carsTop--;
        } else {
            // the car we need is neither at the front of the mountain
            // top nor the top of the branch, so we have to push cars
            // from the mountain top onto the branch until we either
            // find it or run out of cars to push
            while (carsTop > 0 && cars[carsTop - 1] != lake) {
                branch[branchTop] = cars[carsTop - 1];
                branchTop++;
                carsTop--;
            }
            if (carsTop == 0) {
                // ran out of cars to push and never found the one we
                // needed, so the required order is impossible
                return false;
            } else {
                // found the car we needed at the front of the mountain
                // top after pushing the others, send it to the lake
                carsTop--;
            }
        }
    }
    return true;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        // read the cars top to bottom as given, since cars[carsTop - 1]
        // needs to represent the car that's free to move first, we
        // fill the array in the same order it was given and treat the
        // last element read as the top of the "stack"
        for (int i = 0; i < n; i++) {
            scanf("%d", &cars[i]);
        }
        carsTop = n;

        if (possible(n)) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}