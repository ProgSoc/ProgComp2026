import java.io.*;
import java.util.*;

public class problem {

    // computes p(n, k): the k-th permutation (1-indexed) of [1..n] in
    // lexicographical order, using the factorial number system
    static long[] getP(int n, long k) {
        long[] p = new long[n];
        // numbers holds the values not yet placed into the permutation,
        // kept in ascending order
        List<Long> numbers = new ArrayList<>();
        for (long i = 0; i < n; i++) {
            numbers.add(i + 1);
        }

        // factorial starts at (n-1)!, since with n numbers remaining,
        // fixing the first one leaves (n-1)! ways to arrange the rest
        long factorial = 1;
        long factor = n - 1;
        for (long i = 1; i <= n - 1; i++) {
            factorial *= i;
        }

        // convert k from 1-indexed to 0-indexed, easier for the arithmetic
        k--;

        // build the permutation one position at a time
        for (int i = 0; i < n - 1; i++) {
            // k_i is the index within the remaining numbers of the value
            // that belongs at this position
            int kI = (int) (k / factorial);
            p[i] = numbers.get(kI);
            numbers.remove(kI);

            // k is now the rank within the block we picked
            k = k % factorial;
            // shrink the factorial to match the smaller remaining problem
            factorial /= factor;
            factor--;
        }

        // only one number is left after n-1 picks, it must go last
        p[n - 1] = numbers.get(0);
        return p;
    }

    // computes k such that p(n, k) equals the given permutation p, the
    // inverse of getP, using the same factorial number system
    static long getK(int n, long[] p) {
        List<Long> numbers = new ArrayList<>();
        for (long i = 0; i < n; i++) {
            numbers.add(i + 1);
        }

        long factorial = 1;
        long factor = n - 1;
        for (long i = 1; i <= n - 1; i++) {
            factorial *= i;
        }

        // start k at 1 since the final answer is 1-indexed
        long k = 1;

        for (int i = 0; i < n - 1; i++) {
            // find where p[i] currently sits among the remaining numbers
            int idx = numbers.indexOf(p[i]);

            // each skipped candidate accounts for a full block of
            // factorial permutations, add that many to k
            k += idx * factorial;

            numbers.remove(idx);
            factorial /= factor;
            factor--;
        }

        return k;
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        StringBuilder sb = new StringBuilder();

        in.nextToken();
        int t = (int) in.nval;

        while (t-- > 0) {
            in.nextToken();
            int type = (int) in.nval;
            in.nextToken();
            int n = (int) in.nval;

            if (type == 1) {
                // type 1: given n and k, output the permutation p(n, k)
                in.nextToken();
                long k = (long) in.nval;

                long[] p = getP(n, k);
                for (int i = 0; i < n; i++) {
                    if (i > 0) {
                        sb.append(" ");
                    }
                    sb.append(p[i]);
                }
                sb.append("\n");
            } else {
                // type 2: given n and the permutation itself, output its rank k
                long[] p = new long[n];
                for (int i = 0; i < n; i++) {
                    in.nextToken();
                    p[i] = (long) in.nval;
                }
                sb.append(getK(n, p)).append("\n");
            }
        }

        System.out.print(sb);
    }
}