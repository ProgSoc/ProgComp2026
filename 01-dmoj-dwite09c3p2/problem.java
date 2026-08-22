import java.io.*;

public class problem {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        // setting the number of fibonacci numbers to be computed capped at 45
        // as f(45) is 1,134,903,170 which is just over the bounds of 10^9 so
        // this will cover the numbers between (0 <= n <= 10^9) as per spec
        long[] fib = new long[46];
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i < 46; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        for (int i = 0; i < 5; i++) {
            long n = Long.parseLong(br.readLine().trim());

            int highIdx = 0;
            while (highIdx < 46 && fib[highIdx] < n) {
                highIdx++;
            }
            long high = fib[highIdx];

            int lowIdx = 45;
            while (lowIdx >= 0 && fib[lowIdx] > n) {
                lowIdx--;
            }
            long low = fib[lowIdx];

            if (n - low < high - n) {
                sb.append(low).append("\n");
            } else {
                sb.append(high).append("\n");
            }
        }

        System.out.print(sb);
    }
}