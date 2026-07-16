#include <iostream>
#include <queue>

int main() {
    // Only take in two lines of input at the very start.
    int n, k;
    unsigned long long x, a, b, c;

    std::cin >> n >> k;
    std::cin >> x >> a >> b >> c;

    // `xi` is the variable containing the element from the generator's input.
    // `sum` is the final answer to be outputted, while
    // `window_sum` is the sum of values within the `k`-size window.
    unsigned long long xi = x, sum = 0, window_sum = 0;

    // The window needs to be a FIFO structure as we move through the generator's input.
    std::queue<unsigned long long> window {};
    // We then initialise the window with the first `k` values of the generator's input.
    window.push(xi);
    window_sum += xi;
    std::cout << "x1 " << xi << '\n';
    for (int i = 2; i <= k; ++i) {
        // Generate the next input `x_i` from `x_{i-1}`, and add to window.
        xi = (a * xi + b) % c;
        window.push(xi);
        window_sum += xi;
        std::cout << "x" << i << ' ' << xi << '\n';
    }

    // The initial value of the final output starts with the first window's sum value.
    sum = window_sum;

    // We have consumed values `x_1` to `x_k`, so now we iterate over `x_{k+1}` to `x_n`.
    for (int i = k + 1; i <= n; ++i) {
        // To efficiently update the current window sum,
        // we subtract the contribution of the first element of the window (and remove that element).
        window_sum -= window.front();
        window.pop();
        // Generate the next input `x_i` from `x_{i-1}`, and add to window.
        xi = (a * xi + b) % c;
        window.push(xi);
        // Also then update the current window sum by adding the new element.
        window_sum += xi;
        // Finally, update the final output `sum` by XOR'ing.
        sum ^= window_sum;
    }

    // Output the final XOR sum.
    std::cout << sum << '\n';

    return 0;
}
