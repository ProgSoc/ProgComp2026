import java.io.*;
//import java.util.*;

public class program {
    static int[] cars;
    static int carsTop;
    static int[] branch;
    static int branchTop;

    // checks whether the cars can be sent to the lake in order 1 to n
    static boolean possible(int n) {
        branchTop = 0;

        // lake tracks the next car number we need to send to the lake
        for (int lake = 1; lake <= n; lake++) {
            if (branchTop > 0 && branch[branchTop - 1] == lake) {
                // the car we need is already waiting at the top of the
                // branch, so just send it straight to the lake
                branchTop--;
            } else if (carsTop > 0 && cars[carsTop - 1] == lake) {
                // the car we need is right at the front of the mountain
                // top, so it can skip the branch entirely
                carsTop--;
            } else {
                // the car we need is neither at the front of the mountain
                // top nor the top of the branch, so we have to push cars
                // from the mountain top onto the branch until we either
                // find it or run out of cars to push
                while (carsTop > 0 && cars[carsTop - 1] != lake) {
                    branch[branchTop] = cars[carsTop - 1];
                    branchTop++;
                    carsTop--;
                }
                if (carsTop == 0) {
                    // ran out of cars to push and never found the one we
                    // needed, so the required order is impossible
                    return false;
                } else {
                    // found the car we needed at the front of the mountain
                    // top after pushing the others, send it to the lake
                    carsTop--;
                }
            }
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        StringBuilder sb = new StringBuilder();

        in.nextToken();
        int t = (int) in.nval;

        while (t-- > 0) {
            in.nextToken();
            int n = (int) in.nval;

            // cars holds the mountain top queue, cars[carsTop - 1] is
            // always the next car free to move, read top to bottom as
            // given, since the last car read needs to be the top
            cars = new int[n];
            for (int i = 0; i < n; i++) {
                in.nextToken();
                cars[i] = (int) in.nval;
            }
            carsTop = n;

            // branch acts as a stack, cars can only enter and exit it in
            // last-in-first-out order, matching the "cannot overtake" rule
            branch = new int[n];

            sb.append(possible(n) ? "Y" : "N").append("\n");
        }

        System.out.print(sb);
    }
}