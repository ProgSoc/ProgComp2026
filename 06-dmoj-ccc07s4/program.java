import java.io.*;

public class program {
    static boolean[][] adj;
    static long[] paths;

    // counts the number of distinct paths from station 0 to station n - 1
    static long calc(int n) {
        // there's exactly one way to be at station 0, the starting point
        paths[0] = 1;

        // since the numbering is already a valid topological order, we
        // can process stations left to right and know every predecessor's
        // path count is already finalized by the time we reach it
        for (int i = 1; i < n; i++) {
            // sum the path counts of every earlier station that has a
            // direct slide into station i, this is the number of ways
            // to arrive at station i
            for (int src = 0; src < i; src++) {
                if (adj[src][i]) {
                    paths[i] += paths[src];
                }
            }
        }
        return paths[n - 1];
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));

        in.nextToken();
        int n = (int) in.nval;

        // adj[x][y] is true if there's a direct slide from station x to
        // station y (0-indexed, so station 1 in the problem is index 0)
        adj = new boolean[n][n];
        paths = new long[n];

        // read slide connections until the 0 0 sentinel is reached,
        // shifting down to 0-indexed to match the array
        in.nextToken(); int x = (int) in.nval;
        in.nextToken(); int y = (int) in.nval;
        while (x != 0 && y != 0) {
            adj[x - 1][y - 1] = true;
            in.nextToken(); x = (int) in.nval;
            in.nextToken(); y = (int) in.nval;
        }

        System.out.println(calc(n));
    }
}