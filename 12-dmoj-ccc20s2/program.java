import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;

// Record class used as a pair of integers representing a room in the labyrinth.
record Room(int row, int col) {}

// To prevent TLE, it is better to precompute the possible rooms any value can map to beforehand.
public class program {
    static boolean dfs(int[][] grid, int m, int n) {
        // Precompute the traversal graph such that `adj.get(v)` returns all rooms that can be reached from a room with value `v`.
        HashMap<Integer, ArrayList<Room>> adj = new HashMap<>();
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                int value = (row + 1) * (col + 1);
                adj.computeIfAbsent(value, _ -> new ArrayList<Room>()).add(new Room(row + 1, col + 1));
            }
        }

        // We conduct a DFS (hence use a stack), and start with the room (1, 1).
        // A BFS can work here as well.
        Stack<Room> stack = new Stack<>();
        stack.push(new Room(1, 1));

        // An array of size `m * n` is used to keep track of whether we have visited a room or not.
        // If a room (i, j) has been visited, then index `(i - 1) * n + (j - 1)` is true.
        boolean[] seen = new boolean[m * n];
        seen[0] = true;
        Arrays.fill(seen, 1, m * n, false);

        // The search (in this case, the DFS) is conducted here.
        while (!stack.empty()) {
            Room room = stack.pop();
            int r = room.row(), c = room.col();
            for (Room newRoom : adj.getOrDefault(grid[r-1][c-1], new ArrayList<Room>())) {
                int row = newRoom.row(), col = newRoom.col();
                // We only expand the search if we have reached a room we haven't visited before.
                if (!seen[(row - 1) * n + (col - 1)]) {
                    stack.push(new Room(row, col));
                    seen[(row - 1) * n + (col - 1)] = true;
                    // If we reach our target, we exit early.
                    if (row == m && col == n) {
                        break;
                    }
                }
            }
        }
        // We are able to escape the labyrinth if the final room is visited after the search finishes.
        return seen[m * n - 1];
    }

    public static void main(String[] args) {
        // For this question, using a Scanner for the larger inputs is too slow.
        // A BufferedReader is used instead for faster input parsing.
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            int m = Integer.parseInt(br.readLine());
            int n = Integer.parseInt(br.readLine());
            int[][] grid = new int[m][];
            for (int i = 0; i < m; ++i) {
                grid[i] = Arrays.stream(br.readLine().split("\\s+"))
                    .mapToInt(Integer::parseInt)
                    .toArray();
            }
            System.out.println(dfs(grid, m, n) ? "yes" : "no");
        } catch (IOException err) {
            System.err.println("Input reading failed.");
        }
    }
}
