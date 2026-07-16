#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>

// The essence of the solution is to first identify a target configuration,
// then the number of swaps to get to that configuration.
// There are `n` configurations (for `n` total seats), and we find the minimum number of swaps out of those.
// The key then is to make the swap number calculation constant time,
// which is possible since we only have three types of characters to deal with.

// The key to counting swaps in constant time (assuming fixed number of possible letters)
// is that we only need a count of the occurrences for every possible `(i, j)`
// where `i` is the actual letter, and `j` is the target letter.
int count_swaps(std::array<std::array<int, 3>, 3>& matches) {
    // The `matches` matrix stores the number of occurrences of `(i, j)` at index `[i][j]`.
    // There are two main types of swap combos to consider:
    // * A single swap correcting two errors at once of the form `(x, y)` and `(y, x)`.
    // * Two swaps correcting three errors at once of the form `(x, y)`, `(y, z)`, and `(z, x)`.

    // The single swap essentially represents any 2-cycle possible over the set of letters.
    // We consider all possibilities here separately and then add them,
    // since a swap in one type cannot fix an error of another type.
    // There may be some errors left over that we can't resolve using this single swap,
    // hence the minimum of either order is taken at each step.
    int min_0_1 = std::min(matches[0][1], matches[1][0]); // Fixes errors of `(A, B)` and `(B, A)`.
    int min_0_2 = std::min(matches[0][2], matches[2][0]); // Fixes errors of `(A, C)` and `(C, A)`.
    int min_1_2 = std::min(matches[1][2], matches[2][1]); // Fixes errors of `(B, C)` and `(C, B)`.

    // After fixing all errors resolvable in one swap,
    // there are still potentially errors remaining only resolveable with the double-swap operation.
    // These errors must be of the form (`(A, B)`, `(B, C)`, `(C, A)`) or (`(A, C)`, `(C, B)`, `(B, A)`),
    // but at this point, we are considering the point where the other types of errors have been resolved.
    // Thus, there are either zero `(A, B)` or zero `(B, A)` errors (or both).
    // Whichever one is non-zero indicates the existence of only one of the above double-swap error forms.
    // Hence, the remaining number of `(A, B)` or `(B, A)` errors (whichever is higher)
    // is the number of double-swap operations we must do.
    int three_cycles = std::max(matches[0][1], matches[1][0]) - min_0_1;

    // Finally, we add them all together.
    return min_0_1 + min_0_2 + min_1_2 + 2 * three_cycles;
}

// Given the initial setting of the letter-matching matrix,
// the number of letters of each type, and the original string,
// we can calculate minimum number of swaps to reach any valid contiguous (circular) arrangement of letters.
int solve(std::array<std::array<int, 3>, 3> matches, std::array<std::size_t, 3>& count, std::string& s) {
    // `matches` is the matrix calculated by assuming the initial target structure of "A...AB...BC...C".
    // The other structures are considered for the indices `i > 0`,
    // where each next target structure is made by moving the right-most character to the left end.
    // That is, the next target considered is "CA...AB...BC..C".

    int ans = std::numeric_limits<int>::max();

    // First, we keep track of the indices within each letter type (A, B, then C)
    // that will be overwritten when the next shift (after the current arrangement) happens.
    std::array<std::size_t, 3> start_positions {};
    for (std::size_t i = 1; i < 3; ++i) {
        start_positions[i] = start_positions[i-1] + count[i-1];
    }

    // We then loop over every possible arrangement.
    for (std::size_t i = 0; i < s.size(); ++i) {
        // First, we count the number of swaps needed to reach our current target configuration.
        ans = std::min(ans, count_swaps(matches));

        // Next, we change the `matches` array to represent the matrix with the next target configuration.
        for (std::size_t old_target = 0; old_target < 3; ++old_target) {
            // For every letter type (represented by indices `0` to `2` inclusive),
            // if it is getting replaced in the next configuration, it gets replaced by the letter "behind" it.
            // That is, `0` is replaced with `2`, `1` is replaced with `0`, and `2` is replaced with `1`.
            std::size_t new_target = (old_target + 2) % 3;
            // We then need to find (from our string) the actual letter occupying that spot
            // corresponding to a change in the target configuration.
            int actual_letter = static_cast<int>(s[start_positions[old_target]] - 'A');
            // Finally, we update accordingly.
            --matches[actual_letter][old_target];
            ++matches[actual_letter][new_target];
        }
        // The next update positions will be one space forward from what we had this iteration
        // (modulo due to cyclical nature of shifting).
        for (std::size_t j = 0; j < 3; ++j) {
            start_positions[j] = (start_positions[j] + 1) % s.size();
        }
    }
    // By the end, we would have found the minimum number of swaps as per our update step at the start of each iteration.
    return ans;
}

// Here, we set up the initial values for the `solve` function.
int process(std::string& s) {
    // First, we find out how many of each letter is present in the string.
    // This will determine the structure of our target.
    std::array<std::size_t, 3> count {};
    for (char c : s) {
        int letter = static_cast<int>(c - 'A');
        ++count[letter];
    }
    // 2D matrix to represent each of the "actual vs. target" letter combinations,
    // given a specific string and its initial target configuration.
    std::array<std::array<int, 3>, 3> matches {};
    for (std::size_t i = 0; i < s.size(); ++i) {
        // First, we find the required letter for an index.
        std::size_t total = 0;
        int required = std::distance(count.begin(), std::find_if(count.begin(), count.end(), [&](std::size_t c) {
            return (total += c) > i;
        }));
        // Next, we find the actual letter.
        int letter = static_cast<int>(s[i] - 'A');
        // This occurrence gets tallied in the matrix like so.
        ++matches[letter][required];
    }
    // Finally, we return the solution as given by `solve()`.
    return solve(matches, count, s);
}

int main() {
    // We take a single input: the string `s`.
    std::string s;
    std::cin >> s;

    // There are two possible solutions. The first one is where the target is A followed by B followed by C.
    int solution1 = process(s);
    // The other possible solution is where the target is A followed by C followed by B.
    // That is equivalent to dealing with the same string where all Bs and Cs are swapped.
    for (char& c : s) {
        c = c == 'B' ? 'C' : c == 'C' ? 'B' : 'A';
    }
    int solution2 = process(s);

    // We return the minimum number of swaps after considering both solutions.
    std::cout << std::min(solution1, solution2) << '\n';
    return 0;
}
