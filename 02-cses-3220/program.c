#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // starting variables (unsinged long long to take in the size constraints)
    int n, k;
    unsigned long long x, a, b, c;
    // getting the passcode creation parameters 
    // n is the window count, k is the window size
    scanf("%d %d", &n, &k);
    // getting generator parameters where x is x_1, 
    // and each term following that is x_i = (a * x_{i-1} + b) % c
    scanf("%llu %llu %llu %llu", &x, &a, &b, &c);
    //mallocing for memory since we only need the current window
    unsigned long long *window = malloc((size_t)k * sizeof(unsigned long long));
    unsigned long long xi = x, sum = 0, window_sum = 0;

    // generating x_1 to x_k and filling the first window
    // window_sum accumulates the sum as we  go
    window[0] = xi;
    window_sum += xi;
    for (int i = 2; i <= k; ++i) {
        xi = (a * xi + b) % c;
        window[i - 1] = xi;
        window_sum += xi;
    }
    // sum holds the XOR of all the window sums
    sum = window_sum;
    // starting off with w_1 calculating the sum of the first window
    // pos tracks the index of the oldest element in the current window
    // (the one that gets thrown out when the window slides forward by one)
    int pos = 0; 
    for (int i = k + 1; i <= n; ++i) {
        // slides the window by one position
        // removese the oldest element's value from the running sum
        window_sum -= window[pos];
        // generate the next term in the sequence 
        xi = (a * xi + b) % c;
        // overwrite the oldest slot with the new term
        window[pos] = xi;
        // add it to the running sum os the window sum is the sum of the window in o(1)
        window_sum += xi;
        // move the pos forward by wrapping it around os it points at the next element
        // that will become the oldest once the window slids again
        pos = (pos + 1) % k;
        // XOR the window sum into the running passcode total
        sum ^= window_sum;
    }
    // free memory
    free(window);
    // print result
    printf("%llu\n", sum);

    return 0;
}