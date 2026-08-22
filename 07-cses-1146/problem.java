import java.io.*;

public class problem {

    // counts the total number of 1 bits across all numbers from 0 to n
    static long countBits(long n) {
        // base case, only the number 0 exists in this range, and it
        // contributes no 1 bits at all
        if (n == 0) {
            return 0;
        }

        // find the highest set bit of n, d is its position and half is
        // the value of that bit on its own (i.e. 2^d)
        int d = 0;
        while ((1L << (d + 1)) <= n) {
            d++;
        }
        long half = 1L << d;

        // numbers from 0 to half - 1 don't have bit d set, so this range
        // contributes nothing at bit d, but still needs its own bits
        // counted recursively
        long lowerHalfCount = countBits(half - 1);

        // numbers from half to n all have bit d set, that's (n - half + 1)
        // numbers each contributing exactly one 1 bit at position d alone
        long highHalfBitD = n - half + 1;

        // the remaining bits (below position d) of numbers from half to
        // n are the same as the bits of numbers from 0 to (n - half), so
        // recurse on that smaller remainder
        long highHalfLowerBits = countBits(n - half);

        return lowerHalfCount + highHalfBitD + highHalfLowerBits;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long n = Long.parseLong(br.readLine().trim());
        System.out.println(countBits(n));
    }
}