import java.lang.Comparable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.stream.IntStream;

// Record class used as a pair of integers representing a weighted edge in the graph over which Dijkstra's algorithm is conducted.
record Edge(int v, int t) {}

// The element of the min-heap during Dijkstra's algorithm.
record Item(int cost, int u) implements Comparable<Item> {
    @Override
    public int compareTo(Item other) {
        return Integer.compare(this.cost(), other.cost());
    }
}

// Two instances of Dijkstra's algorithm for the single-source shortest path (SSSP) problem are executed:
// one from the source and one from the destination.
// For any node in the graph, adding up the cost of the shortest path from either end (City 0 or City N-1)
// gives the total cost of the shortest path through that node.
public class program {
    // Conducts Dijkstra's algorithm (with adjacency list encoding of the graph) from a given source.
    static int[] sssp(List<List<Edge>> graph, int source) {
        // Initialise the "shortest distance" array.
        int[] dist = new int[graph.size()];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        // The traversal frontier is initialised with our source node and a cost of zero.
        // A min-heap is used (`PriorityQueue` by default is a min-heap).
        PriorityQueue<Item> open = new PriorityQueue<>();
        open.add(new Item(0, source));

        // We keep iterating while our traversal frontier is not empty,
        // since we want to find the shortest path to *all points*.
        Item top;
        while ((top = open.poll()) != null) {
            int cost = top.cost(), u = top.u();
            for (Edge e : graph.get(u)) {
                int v = e.v(), t = e.t();
                int newCost = cost + t;
                // Edge relaxation.
                if (newCost < dist[v]) {
                    dist[v] = newCost;
                    open.add(new Item(newCost, v));
                }
            }
        }

        return dist;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        List<List<Edge>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; ++i) {
            graph.add(new ArrayList<Edge>());
        }

        // We take in the graph and represent it in an adjacency list format.
        for (int i = 0; i < m; ++i) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int t = sc.nextInt();

            graph.get(a).add(new Edge(b, t));
            graph.get(b).add(new Edge(a, t));
        }

        // We conduct the two Dijkstra's instances.
        int[] cost = sssp(graph, 0);
        int[] cost_end = sssp(graph, n-1);

        // We then add distance arrays element-wise and output the maximum value.
        int ans = IntStream.range(0, n)
            .map(i -> cost[i] + cost_end[i])
            .max()
            .orElse(0);

        System.out.println(ans);

        sc.close();
    }
}
