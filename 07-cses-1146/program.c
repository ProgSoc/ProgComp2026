#include <stdio.h>

// counts the total number of 1 bits across all numbers from 0 to n
unsigned long long count_bits(unsigned long long n) {
    // base case, only the number 0 exists in this range, and it
    // contributes no 1 bits at all
    if (n == 0) {
        return 0;
    }

    // find the highest set bit of n, d is its position and
    // half is the value of that bit on its own (i.e. 2^d)
    int d = 0;
    while ((1ull << (d + 1)) <= n) {
        d++;
    }
    unsigned long long half = 1ull << d;

    // numbers from 0 to half - 1 don't have bit d set, so this range
    // contributes nothing at bit d, but still needs its own bits
    // counted recursively, and since half - 1 has the same number of
    // bits below position d for every value up to half - 1, this
    // recursive count also equals the total contribution from bit d
    // downwards across one full block, used further below
    unsigned long long lower_half_count = count_bits(half - 1);

    // numbers from half to n all have bit d set, that's (n - half + 1)
    // numbers each contributing exactly one 1 bit at position d alone
    unsigned long long high_half_bit_d = n - half + 1;

    // the remaining bits (below position d) of numbers from half to n
    // are the same as the bits of numbers from 0 to (n - half), so
    // recurse on that smaller remainder
    unsigned long long high_half_lower_bits = count_bits(n - half);

    return lower_half_count + high_half_bit_d + high_half_lower_bits;
}

int main(void) {
    unsigned long long n;
    scanf("%llu", &n);

    printf("%llu\n", count_bits(n));
    return 0;
}