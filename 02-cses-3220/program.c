#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, k;
    unsigned long long x, a, b, c;

    scanf("%d %d", &n, &k);
    scanf("%llu %llu %llu %llu", &x, &a, &b, &c);

    unsigned long long *window = malloc((size_t)k * sizeof(unsigned long long));
    unsigned long long xi = x, sum = 0, window_sum = 0;

    window[0] = xi;
    window_sum += xi;
    for (int i = 2; i <= k; ++i) {
        xi = (a * xi + b) % c;
        window[i - 1] = xi;
        window_sum += xi;
    }

    sum = window_sum;

    int pos = 0; 
    for (int i = k + 1; i <= n; ++i) {
        window_sum -= window[pos];
        xi = (a * xi + b) % c;
        window[pos] = xi;
        window_sum += xi;
        pos = (pos + 1) % k;
        sum ^= window_sum;
    }

    free(window);

    printf("%llu\n", sum);

    return 0;
}