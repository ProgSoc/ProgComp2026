#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100000

int cars[MAX_N];
int carsTop;
int branch[MAX_N];
int branchTop;

bool possible(int n) {
    branchTop = 0;

    for (int lake = 1; lake <= n; lake++) {
        if (branchTop > 0 && branch[branchTop - 1] == lake) {
            branchTop--;
        } else if (carsTop > 0 && cars[carsTop - 1] == lake) {
            carsTop--;
        } else {
            while (carsTop > 0 && cars[carsTop - 1] != lake) {
                branch[branchTop] = cars[carsTop - 1];
                branchTop++;
                carsTop--;
            }
            if (carsTop == 0) {
                return false;
            } else {
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