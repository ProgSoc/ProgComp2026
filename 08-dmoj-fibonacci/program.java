import java.io.*;

public class program {

    // a 2x2 matrix, used to represent the fibonacci transformation
    static long[][] matmul(long[][] a, long[][] b, long base) {
        long[][] ans = new long[2][2];
        // standard matrix multiplication, ans[i][j] is the dot product
        // of row i from a and column j from b
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % base;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long n = Long.parseLong(br.readLine().trim());

        // x is the accumulated result, starts as the identity matrix
        // since multiplying by it does nothing, the standard starting
        // point for binary exponentiation
        long[][] x = {{1, 0}, {0, 1}};

        // f is the fibonacci transformation matrix, [[0,1],[1,1]],
        // raising f to the n-th power gives a matrix whose entries are
        // consecutive fibonacci numbers, f^n = [[F(n-1),F(n)],[F(n),F(n+1)]]
        long[][] f = {{0, 1}, {1, 1}};

        long base = 1_000_000_007L;

        // binary exponentiation, computes f^n by repeated squaring
        // instead of n separate multiplications, this brings the
        // complexity down from o(n) to o(log n), essential given n can
        // be up to 10^19
        while (n != 0) {
            // if the current bit of n is set, fold the current power of
            // f into the result
            if ((n & 1) != 0) {
                x = matmul(x, f, base);
            }
            // square f each iteration, so it always represents f raised
            // to the next power of two
            f = matmul(f, f, base);
            n >>= 1;
        }

        // x now holds f^n, and since f^n = [[F(n-1),F(n)],[F(n),F(n+1)]],
        // the value we want, F(n), sits at position [0][1]
        System.out.println(x[0][1]);
    }
}