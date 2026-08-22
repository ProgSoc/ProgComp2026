#include <stdio.h>
int main (void) {
    int n;
    // setting the number of fibonacci numbers to be computed capped at 45
    // as F(45) is  1,134,903,170 which is just over the bounds of 10^9 so this 
    // will cover the numbers between (0 <= n <= 10^9) as per problem spec
    int fib[46];
    // the base values of the fibbonaci numbers
    fib[0] = 0;
    fib[1] = 1;
    // precomputing the fib numbers fromm 0 - 45
    for (int i = 2; i < 46; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    // processing 5 inputs at a time
    for (int i = 0; i < 5; ++i) {
        scanf("%d", &n);
        int high_idx = 0;
        //find the smallest fib number that is >= n, looping through to find the 
        // first fib number that is big enough to reach or pass n
        while (high_idx < 46 && fib[high_idx] < n) {
            high_idx ++;
        }
        int high = fib[high_idx];
        //finding the largest fib number that is <= n
        // same pattern as the loop above but this time starting at the largest value
        // working down to find the first fib which is smaller than n
        int low_idx = 45;
        while (low_idx >= 0 && fib[low_idx] > n) {
            low_idx --;
        }
        int low = fib[low_idx];
        // n is now between the two bounds that we set earlier
        // comparing the two distances and choosing which one is the smaller one
        // ties will automatically go to the larger fib number which is why we use the
        // < instead of <= to avoid ties
        // if the given number is a fib number itself (low == high) then it will just 
        // pprint the high which is n itself
        if (n - low < high - n) {
            printf("%d\n", low);
        } else {
            printf("%d\n", high);
        }
    }

    return 0;
}