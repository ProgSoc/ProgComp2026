#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

// Whenever one position is chosen, there is a cost based on distance on a line
// calculated from and aggregated over a series of points.
// Since the cost increases linearly (generally) with the distance between the chosen point and a friend on the line,
// moving too far left or right will increase the total number of steps needed.
// The optimal answer is somewhere in the middle, and the cost landscape forms a unimodal function
// with the lowest number being somewhere in the middle.

// If we choose point `c`, for a given position `p[i]` with an associated walking cost `w[i]` and a hearing radius of `d[i]`,
// the number of seconds required to walk in order to hear the music is:
// * If `|p[i] - c| <= d[i]`, then `0`.
// * Otherwise, `(|p[i] - c| - d[i]) * w[i]`. The distance required is `|p[i] - c| - d[i]`, with the multiplier being `w[i]`.
long long cost(long long c, std::vector<long long>& p, std::vector<long long>& w, std::vector<long long>& d) {
    long long total = 0;
    for (std::size_t i = 0; i < p.size(); ++i) {
        // Distance to target (start at p[i], end at c), and subtract the extra tolerance from d[i].
        long long distance = std::llabs(p[i] - c) - d[i];
        // This line accounts for both cases. If `distance` is negative, then no walking is needed.
        total += w[i] * std::max(distance, 0ll);
    }
    return total;
}

int main() {
    // First, we input `n`, the number of friends in the line.
    int n;
    std::cin >> n;

    // Next, we input their positions `p[i]`, walking speeds `w[i]`, and tolerances `d[i]` one friend at a time.
    std::vector<long long> p(n), w(n), d(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i] >> w[i] >> d[i];
    }

    // With the property that the `cost()` function is unimodal in its first parameter,
    // we conduct a ternary search. Even though computing `cost()` is O(n),
    // it is only called at maximum `2 * log_3(n) + 3` times overall, making the overall algorithm still O(n log n).
    // We know specifically that this unimodal function has a minimum which we need to find.
    long long low = *std::min_element(p.begin(), p.end());
    long long high = *std::max_element(p.begin(), p.end());
    while (high - low > 2) {
        long long m1 = low + (high - low) / 3;
        long long m2 = high - (high - low) / 3;
        if (cost(m1, p, w, d) <= cost(m2, p, w, d)) {
            // In this case, we know that `cost()` increases from `m2` and above,
            // so `m2` is our new upper bound (since we are finding the minimum).
            high = m2;
        } else {
            // In this case, we know that `cost()` increases from `m1` and below,
            // so `m1` is our new lower bound (since we are finding the minimum).
            low = m1;
        }
    }
    // Over final window, we find the lowest value for `cost` and output it.
    long long ans = cost(low, p, w, d);
    for (long long i = low + 1; i <= high; ++i) {
        ans = std::min(ans, cost(i, p, w, d));
    }
    std::cout << ans << '\n';
    return 0;
}
