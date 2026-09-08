import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;

public class program {
    static final long base = 1_000_000_007;

    // The recursive formulation of repeated squaring is too slow for Java,
    // so the iterative one is used here instead.
    static long pow(long a, long b) {
        long result = 1;
        while (b > 0) {
            if ((b & 1) != 0) {
                result = (result * a) % base;
            }
            a = (a * a) % base;
            b >>= 1;
        }
        return result;
    }

    // Conducting a full Gauss-Jordan elimination in Java takes too long.
    // Instead, a Gaussian elimination is conducted with a slightly less simple back-substitution step.
    // Additionally, the matrix `a` represents the full augmented one rather than just the coefficients.
    static long[] gaussianElimination(long[][] a) {
        int n = a.length, m = a[0].length - 1;

        // We keep track of the rows each pivot is found at. `-1` is the sentinel value for no pivot present.
        int[] pivots = new int[m];
        Arrays.fill(pivots, -1);

        int lastPivot = -1;
        // Move through each column step by step.
        for (int step = 0; step < m; ++step) {
            // First, we find the pivot row, only looking beyond the previous one.
            int pivot = -1;
            for (int row = lastPivot + 1; row < n; ++row) {
                if (a[row][step] != 0) {
                    pivot = row;
                    break;
                }
            }
            // If no pivot is found, we move to the next column.
            if (pivot == -1) {
                continue;
            }

            // Otherwise, we record which row the pivot was found for the column `step`.
            pivots[step] = pivot;
            lastPivot = pivot;

            // Computing modular inverses in this loop is too slow for Java.
            // Instead, we multiply the relation by the pivot's value
            // to conduct the step un-normalised.
            long denom = a[pivot][step];

            // We then eliminate only the rows below the current one.
            for (int row = pivot + 1; row < n; ++row) {
                long factor = a[row][step];

                // We skip elimination if our current element is zero, since that is trivially a no-op.
                if (factor == 0) {
                    continue;
                }

                for (int col = step; col < m + 1; ++col) {
                    // We eliminate without normalising the original row.
                    // This prevents doing relatively expensive modular exponentiation within the loop.
                    long value = (denom * a[row][col] - factor * a[pivot][col]) % base;
                    // Since the `%` operator is the remainder and not the mathematical modulo,
                    // we correct its value in case it is negative.
                    if (value < 0) {
                        value += base;
                    }
                    a[row][col] = value;
                }
            }
        }

        // Check for any inconsistencies.
        // If an all-zero coefficient row is matched with a non-zero answer, there is no solution.
        for (int row = 0; row < n; ++row) {
            boolean allZero = true;
            for (int col = 0; col < m; ++col) {
                if (a[row][col] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (allZero && a[row][m] != 0) {
                return new long[0];
            }
        }

        long[] solution = new long[m];

        // Back-substitution step after the Gaussian elimination.
        for (int step = m - 1; step >= 0; --step) {
            if (pivots[step] == -1) {
                // If the row we are considering has no pivot,
                // it is a free variable which we can assign to zero.
                solution[step] = 0;
            } else {
                int pivot = pivots[step];
                // First, we find the target value for our pivot row.
                long value = a[pivot][m];
                for (int col = step + 1; col < m; ++col) {
                    // Then, we subtract the contributions of the coefficients to the right.
                    value = (value - a[pivot][col] * solution[col]) % base;
                    // Keep within the modulo bound here.
                    if (value < 0) {
                        value += base;
                    }
                }
                // Now we divide by the pivot's coefficient using modular inverse.
                value = (value * pow(a[pivot][step], base - 2)) % base;
                solution[step] = value;
            }
        }

        return solution;
    }

    public static void main(String[] args) {
        // A `BufferedReader` and `StringTokenizer` are required to read the input quickly enough.
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());
            long[][] a = new long[n][m+1];
            for (int i = 0; i < n; ++i) {
                st = new StringTokenizer(br.readLine());
                for (int j = 0; j < m + 1; ++j) {
                    a[i][j] = Long.parseLong(st.nextToken());
                }
            }

            long[] solution = gaussianElimination(a);
            if (solution.length == 0) {
                // If an empty array is outputted, no solution exists.
                System.out.println(-1);
            } else {
                for (long element : solution) {
                    System.out.print(element + " ");
                }
                System.out.println();
            }
        } catch (IOException err) {
            System.err.println("Input reading failed.");
        }
    }
}
