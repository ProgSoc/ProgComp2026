#include <stdio.h>
int main (void) {
    int n;
    int fib[46];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 46; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    for (int i = 0; i < 5; ++i) {
        scanf("%d", &n);
        int high_idx = 0;
        while (high_idx < 46 && fib[high_idx] < n) {
            high_idx ++;
        }
        int high = fib[high_idx];
        int low_idx = 45;
        while (low_idx >= 0 && fib[low_idx] > n) {
            low_idx --;
        }
        int low = fib[low_idx];

        if (n - low < high - n) {
            printf("%d\n", low);
        } else {
            printf("%d\n", high);
        }
    }

    return 0;
}