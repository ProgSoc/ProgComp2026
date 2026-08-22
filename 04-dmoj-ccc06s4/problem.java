import java.io.*;

public class problem {
    static int[][] table = new int[100][100];

    // checks whether the operator defined in table (over n elements)
    // forms a valid group
    static boolean isGroup(int n) {
        // associativity check: (i*j)*k must equal i*(j*k) for all i, j, k
        // this is the most expensive check, done first so we can bail
        // early before looking for an identity at all
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (table[table[i][j]][k] != table[i][table[j][k]]) {
                        return false;
                    }
                }
            }
        }

        // try each element i as a candidate identity
        for (int i = 0; i < n; i++) {
            // i is a valid identity only if i*j == j*i == j for every j
            boolean isIdentity = true;
            for (int j = 0; j < n; j++) {
                if (table[i][j] != j || table[j][i] != j) {
                    isIdentity = false;
                    break;
                }
            }

            // only bother checking inverses if i passed as an identity
            // candidate above
            if (isIdentity) {
                // every element j must have some inverse k such that
                // j*k == k*j == i (the identity)
                for (int j = 0; j < n; j++) {
                    boolean hasInverse = false;
                    for (int k = 0; k < n; k++) {
                        if (table[j][k] == i && table[k][j] == i) {
                            hasInverse = true;
                            break;
                        }
                    }
                    // if even one element has no inverse, i doesn't lead
                    // to a valid group, reuse isIdentity as a flag to say so
                    if (!hasInverse) {
                        isIdentity = false;
                        break;
                    }
                }
            }

            // a group has at most one identity, so as soon as we find an
            // i that passes both checks, every axiom holds
            if (isIdentity) {
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        StringBuilder sb = new StringBuilder();

        in.nextToken();
        int n = (int) in.nval;

        // keep processing tablets until the sentinel n == 0 is reached
        while (n != 0) {
            // read the table, converting from the input's 1-indexed
            // element labels down to 0-indexed values to match the array
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    in.nextToken();
                    table[i][j] = (int) in.nval - 1;
                }
            }

            sb.append(isGroup(n) ? "yes" : "no").append("\n");

            in.nextToken();
            n = (int) in.nval;
        }

        System.out.print(sb);
    }
}