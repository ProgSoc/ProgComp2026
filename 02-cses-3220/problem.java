import java.io.*;

public class problem {
    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));

        // n is the window count, k is the window size
        in.nextToken(); long n = (long) in.nval;
        in.nextToken(); long k = (long) in.nval;

        // generator parameters, x is x_1, and each term following that is
        // x_i = (a * x_{i-1} + b) % c
        in.nextToken(); long x = (long) in.nval;
        in.nextToken(); long a = (long) in.nval;
        in.nextToken(); long b = (long) in.nval;
        in.nextToken(); long c = (long) in.nval;

        // we only need to remember the last k generated values at once
        int kk = (int) k;
        long[] window = new long[kk];
        long xi = x;
        long windowSum = 0;

        // generating x_1 to x_k and filling the first window, window_sum
        // accumulates the sum as we go
        window[0] = xi;
        windowSum += xi;
        for (long i = 2; i <= k; i++) {
            xi = (a * xi + b) % c;
            window[(int) i - 1] = xi;
            windowSum += xi;
        }

        // sum holds the running xor of all window sums, starting with w_1
        long sum = windowSum;

        // pos tracks the index of the oldest element in the current window,
        // the one that gets thrown out when the window slides forward by one
        int pos = 0;
        for (long i = k + 1; i <= n; i++) {
            // slide the window forward by one, remove the oldest element's
            // value from the running sum
            windowSum -= window[pos];
            // generate the next term in the sequence
            xi = (a * xi + b) % c;
            // overwrite the oldest slot with the new term and add it to the
            // running sum so window_sum is the sum of the new window in o(1)
            window[pos] = xi;
            windowSum += xi;
            // move pos forward, wrapping around so it points at the next
            // element that will become the oldest once the window slides again
            pos = (int) ((pos + 1) % k);
            // xor this window's sum into the running passcode total
            sum ^= windowSum;
        }

        System.out.println(sum);
    }
}