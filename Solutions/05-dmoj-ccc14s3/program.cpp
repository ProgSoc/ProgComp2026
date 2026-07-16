#include <iostream>
#include <vector>

// To check if a given starting order of cars can match the required order at the end,
// we simulate the problem statement.
// Both the mountain top (vector `cars`) and the branch (vector `branch`) act like stacks,
// since the most recently added car is the first one to leave.
bool possible(std::vector<int>& cars) {
    std::vector<int> branch {};
    int n = cars.size();
    // Since the cars must reach the lake strictly in the order of `1` to `n`
    // with no cars skipped in between,
    // we check iteratively at step `i` whether it is possible for Car `i` to be moved down.
    for (int lake = 1; lake <= n; ++lake) {
        if (!branch.empty() && branch.back() == lake) {
            // If Car `i` is the first to leave the branch, it is possible.
            // We move Car `i` out of the branch by popping it off.
            branch.pop_back();
        } else if (!cars.empty() && cars.back() == lake) {
            // If Car `i` is the first to leave the mountain top (`cars`), it is possible.
            // We move Car `i` out of the mountain top by popping it off.
            cars.pop_back();
        } else {
            // If neither of the above is possible,
            // then we have the option to move some cars from the mountain top to the branch.
            // (We cannot do this the opposite way, however.)
            // The moment the car we desire is the first about to leave `cars`,
            // we can then add that to the lake.
            while (!cars.empty() && cars.back() != lake) {
                branch.push_back(cars.back());
                cars.pop_back();
            }
            // However, if we have emptied the entire mountain top and still have not found it,
            // then this arrangement makes it impossible to achieve our end state.
            // (In this case, the desired car is stuck somewhere in the middle of `branch`.)
            if (cars.empty()) {
                return false;
            } else {
                cars.pop_back();
            }
        }
    }
    // If we can get through all `n` cars without returning early, it must be possible.
    return true;
}

int main() {
    // The number of test cases.
    int t;
    std::cin >> t;

    while (t--) {
        // For each test case, we start with the number of cars.
        int n;
        std::cin >> n;

        // The cars are given in the format where the first is the top-most,
        // and the cars always leave the mountain top from the bottom first.
        // Hence, we can input the numbers directly into a vector which allows fast popping from the back.
        std::vector<int> cars(n);
        for (auto& car : cars) {
            std::cin >> car;
        }

        // For each test case, output whether it is possible or not as per above.
        std::cout << (possible(cars) ? "Y\n" : "N\n");
    }
    return 0;
}
