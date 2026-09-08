import java.util.Scanner;

public class program {
    // counts the total number of 1 bits across all numbers from 0 to n
    static long countBits(long n) {
        // base case, only the number 0 exists in this range, and it
        // contributes no 1 bits at all
        if (n == 0) {
            return 0;
        }

        // find the highest set bit of n, d is its position and
        // half is the value of that bit on its own (i.e. 2^d)
        int d = 0;
        while ((1L << (d + 1)) <= n) {
            d++;
        }
        long half = 1L << d;

        // numbers from 0 to half - 1 form a complete block of d-bit
        // numbers, and every bit position within a complete block is set
        // in exactly half the numbers, so the total 1-bits in this whole
        // block has a direct formula instead of needing recursion:
        // d positions, each set in (half / 2) of the numbers
        long lowerHalfCount = (long) d * (half >> 1);

        // numbers from half to n all have bit d set, that's (n - half + 1)
        // numbers each contributing exactly one 1 bit at position d alone
        long highHalfBitD = n - half + 1;

        // the remaining bits (below position d) of numbers from half to n
        // are the same as the bits of numbers from 0 to (n - half), and
        // since n - half is strictly smaller than half, this is now a
        // genuinely smaller subproblem, so recursing here (and only here)
        // keeps the recursion depth logarithmic instead of exponential
        long highHalfLowerBits = countBits(n - half);

        return lowerHalfCount + highHalfBitD + highHalfLowerBits;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();

        System.out.println(countBits(n));
    }
}