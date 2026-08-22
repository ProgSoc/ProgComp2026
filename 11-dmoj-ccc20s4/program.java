import java.util.Scanner;

// To prevent TLE, stack-allocated variables are used rather than using arrays to store them.
public class program {
    // Helper method to count the number of times a letter occurs in a string `s`.
    static int count(String s, char letter) {
        return (int)s.chars().filter(c -> c == (int)letter).count();
    }

    static int getMinSwaps(String s, String order) {
        // Variables for the letters in the `order` argument are extracted out.
        char l1 = order.charAt(0), l2 = order.charAt(1), l3 = order.charAt(2);

        // Variables containing the counts of the 1st, 2nd, and 3rd letters (numbered as they appear in `order`).
        int c1 = count(s, l1);
        int c2 = count(s, l2);
        int c3 = count(s, l3);

        // The variables named in the format `dij` refer to the number of instances where
        // the `i`-th letter should appear in the target configuration but the `j`-th letter appears in the actual string.
        int d12 = count(s.substring(0, c1), l2);
        int d13 = count(s.substring(0, c1), l3);
        int d21 = count(s.substring(c1, c1 + c2), l1);
        int d23 = count(s.substring(c1, c1 + c2), l3);
        int d31 = count(s.substring(c1 + c2, c1 + c2 + c3), l1);
        int d32 = count(s.substring(c1 + c2, c1 + c2 + c3), l2);

        int n = s.length();
        // The string has maximum length `10^6`, hence this is a reasonable upper bound for all cases.
        int minSwaps = 2000000;

        for (int i = 0; i < n; ++i) {
            // Count the number of mismatches that can be corrected by swapping two (matching) out-of-place letters.
            int swap2 = Math.min(d12, d21) + Math.min(d13, d31) + Math.min(d23, d32);
            // The remaining mismtaches are corrected by conducting two swaps to permute three incorrect letters.
            int swap3 = Math.max(d12, d21) - Math.min(d12, d21);
            int totalSwaps = swap2 + 2 * swap3;

            minSwaps = Math.min(minSwaps, totalSwaps);

            // When moving to the next rotation,
            // we keep track of which character no longer overlaps with each contiguous stretch in the target configuration.
            char leaving1 = s.charAt(i % n);
            char leaving2 = s.charAt((c1 + i) % n);
            char leaving3 = s.charAt((c1 + c2 + i) % n);

            // Similarly, we keep track of the characters that enter such stretches.
            char entering1 = s.charAt((c1 + i) % n);
            char entering2 = s.charAt((c1 + c2 + i) % n);
            char entering3 = s.charAt((c1 + c2 + c3 + i) % n);

            // We decrement the difference/mismatch variables accordingly.
            if (leaving1 == l2) { --d12; } else if (leaving1 == l3) { --d13; }
            if (leaving2 == l1) { --d21; } else if (leaving2 == l3) { --d23; }
            if (leaving3 == l1) { --d31; } else if (leaving3 == l2) { --d32; }

            // We increment the difference/mismatch variables accordingly.
            if (entering1 == l2) { ++d12; } else if (entering1 == l3) { ++d13; }
            if (entering2 == l1) { ++d21; } else if (entering2 == l3) { ++d23; }
            if (entering3 == l1) { ++d31; } else if (entering3 == l2) { ++d32; }
        }

        return minSwaps;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        // The two possible target configurations have letters in the order of either A -> B -> C or A -> C -> B.
        int swaps1 = getMinSwaps(s, "ABC");
        int swaps2 = getMinSwaps(s, "ACB");
        System.out.println(Math.min(swaps1, swaps2));
        sc.close();
    }
}
