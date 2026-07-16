#include <iostream>

int main() {
    unsigned long long n, sum = 0;
    std::cin >> n;
    int d = -1;
    while (n >> ++d) {
        // We consider the problem of finding the number of 1 bits from values [0..n] at a certain bit position `d`
        // (equivalent since 0 trivially contributes no bits in all cases).
        // `d` refers to the number of spaces from the least significant (right-most) bit.
        // The pattern at position `d` as `n` increases by 1 repeats as follows: (1 << d) instances of 0, followed by (1 << d) instances of 1.
        //
        // Thus, our task is broken down into two portions:
        // 1. Determining how many blocks of 1 in position `d` we have seen before the number `n`.
        // 2. Determining at which position within our current block of 1 the number `n` is in (or whether it is not in such a block).
        //
        // Portion 1:
        // Since we are counting blocks of 1 bits at position `d`, every time we move out of such a block, the number is incremented by 1.
        // All less significant bits will have been flushed to 0 as well, while the more significant digit (to the left) has been incremented by 1.
        // Hence, we only need to interpret the bits to the left of position `d` as a number to find the number of times we have exited a 1-block at `d`.
        // This gives us the value `n >> (d+1)` or equivalently `(n >> d) >> 1`.
        // Also, each such block contains `1 << d` numbers, hence the number of 1s in position `d` before our current block is `(n >> (d+1)) * (1 << d)`.
        // This can alternatively be written as `(n >> (d+1)) << d`.
        //
        // Portion 2:
        // If we are not in a 1-block at position `d`, then position `d` will have a value of `0`,
        // and our aforementioned counting will have covered all previous 1-bit occurrences in position `d`.
        // If we are in a 1-block at position `d`, we can find out how far within it we are by interpreting the less significant bits as a number.
        // We need to add 1 to it since the first number within the 1-block will be marked with an all-zero set of bits.
        // This gives the value `1 + (n & ((1 << d) - 1))` to add 1 to the number of the last `d` bits (via the mask `(1 << d) - 1`).
        // We only count this number if position `d` is a 1-bit, hence the value we actually add is `((n >> d) & 1) * (1 + (n & ((1 << d) - 1)))`.
        //
        // This gives the final result as follows (`1ull` is used everywhere to prevent implicit casting and overflow).
        sum += ((n >> (d+1ull)) << d) + ((n >> d) & 1ull) * (1ull + (n & ((1ull << d) - 1ull)));
    }
    std::cout << sum << '\n';
    return 0;
}
