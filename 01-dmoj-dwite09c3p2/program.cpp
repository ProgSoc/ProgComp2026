#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    // Needs only to store one integer at a time,
    // since we can input -> calculate -> output on the fly.
    int n;

    // Store lookup tables for Fibonacci numbers.
    // Only F(46) at maximum is needed since that is the first one above 10^9.
    std::vector<int> fib(46);
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 46; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    for (int i = 0; i < 5; ++i) {
        std::cin >> n;
        // Finds first Fibonacci number not greater than `n`.
        int low = *std::lower_bound(fib.rbegin(), fib.rend(), n, std::greater<int> {});
        // Finds first Fibonacci number not less than `n`.
        int high = *std::lower_bound(fib.begin(), fib.end(), n);
        if (n - low < high - n) {
            // Here, the distance to `low` is less than the distance to `high`.
            std::cout << low << '\n';
        } else {
            // Here, the opposite is true. This means the equal case takes this higher value.
            std::cout << high << '\n';
        }
    }
}
