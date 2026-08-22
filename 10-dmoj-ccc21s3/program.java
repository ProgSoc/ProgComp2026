import java.io.*;

public class program {
    static long[] P, W, D;
    static int number;

    // computes the total walking time if the food truck is parked at
    // position c, summing over every concert-goer
    static long cost(long c) {
        long total = 0;
        for (int i = 0; i < number; i++) {
            // distance from this concert-goer's current position to the
            // truck, always taken as positive regardless of direction
            long distance = Math.abs(P[i] - c);
            // the concert-goer only needs to walk enough to bring
            // themselves within range D[i] of the truck, if they're
            // already within range this comes out negative, clamp to 0
            long walk = distance - D[i];
            if (walk < 0) {
                walk = 0;
            }
            total += walk * W[i];
        }
        return total;
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));

        in.nextToken();
        number = (int) in.nval;
        P = new long[number];
        W = new long[number];
        D = new long[number];

        for (int i = 0; i < number; i++) {
            in.nextToken(); P[i] = (long) in.nval;
            in.nextToken(); W[i] = (long) in.nval;
            in.nextToken(); D[i] = (long) in.nval;
        }

        // search bounds cover every possible position along the line,
        // positions are guaranteed to be within [0, 10^9] as per spec
        long lo = 0;
        long hi = 1_000_000_000L;

        // ternary search relies on cost(c) being unimodal, decreasing
        // then increasing as c moves away from the optimal spot
        while (hi - lo > 2) {
            long m1 = lo + (hi - lo) / 3;
            long m2 = hi - (hi - lo) / 3;
            // whichever third has the lower cost tells us which side
            // the minimum can't be on, so shrink away from the worse third
            if (cost(m1) <= cost(m2)) {
                hi = m2;
            } else {
                lo = m1;
            }
        }

        // once the range has shrunk down small enough, brute force
        // check every remaining integer position directly, this avoids
        // off by one issues from ternary search alone on integer domains
        long ans = cost(lo);
        for (long c = lo; c <= hi; c++) {
            long val = cost(c);
            if (val < ans) {
                ans = val;
            }
        }

        System.out.println(ans);
    }
}