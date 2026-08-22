import java.io.*;
import java.util.*;

public class problem {
    static int[] parent;
    static int[] setSize;

    // standard path compressed find, follows parent pointers to the
    // root of x's set, flattening the path along the way
    static int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    // merges the sets containing x and y, using union by size so the
    // smaller set is always attached under the larger one
    static void union(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (setSize[x] < setSize[y]) {
                int temp = x;
                x = y;
                y = temp;
            }
            parent[y] = x;
            setSize[x] += setSize[y];
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        // process exactly 5 workdays, resetting all state at the start
        // of each one since no portals persist overnight
        for (int day = 0; day < 5; day++) {
            int n = Integer.parseInt(br.readLine().trim());

            // maps a city name to its assigned integer id, reset fresh
            // every day, using java's built in hashmap instead of a
            // manual hash table since java doesn't need the manual
            // approach the c version used
            HashMap<String, Integer> idOf = new HashMap<>();

            // at most 2 new cities can be introduced per line
            parent = new int[2 * n + 5];
            setSize = new int[2 * n + 5];
            int nextId = 0;

            for (int line = 0; line < n; line++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                String type = st.nextToken();
                String a = st.nextToken();
                String b = st.nextToken();

                // resolve both city names to integer ids, registering
                // either one as new if this is the first time it's seen
                Integer idA = idOf.get(a);
                if (idA == null) {
                    idA = nextId++;
                    idOf.put(a, idA);
                    parent[idA] = idA;
                    setSize[idA] = 1;
                }
                Integer idB = idOf.get(b);
                if (idB == null) {
                    idB = nextId++;
                    idOf.put(b, idB);
                    parent[idB] = idB;
                    setSize[idB] = 1;
                }

                if (type.equals("p")) {
                    // portal activation, merge the two cities' sets
                    union(idA, idB);
                } else {
                    // delivery query, cities are reachable from each
                    // other if and only if they belong to the same set
                    if (find(idA) == find(idB)) {
                        sb.append("connected\n");
                    } else {
                        sb.append("not connected\n");
                    }
                }
            }
        }

        System.out.print(sb);
    }
}