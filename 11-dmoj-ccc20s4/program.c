#include <stdio.h>
#include <string.h>

#define MAXN 1000005
// this is the prefix sums version that i cleaned up 
char s[MAXN];
char doubled[2 * MAXN];
int pA[2 * MAXN], pB[2 * MAXN], pC[2 * MAXN];
int N, cA, cB, cC;
int *prefixes[3];
int counts[3];

// all 6 possible orderings of which faction's block comes first,
// second, and third going clockwise around the circle
int perms[6][3] = {
    {0, 1, 2}, {0, 2, 1},
    {1, 0, 2}, {1, 2, 0},
    {2, 0, 1}, {2, 1, 0}
};
// returns the count of a given faction within seats [l, r] inclusive,
// using a prefix sum array for O(1) range queries
// note, this does not guard against l > r, so callers must ensure the
// range passed in is always valid, unlike the query function in the
// getPrefix rewrite of this solution
int prefixQuery(int *prefix, int l, int r) {
    int left = 0;
    if (l > 0) {
        left = prefix[l - 1];
    }
    return prefix[r] - left;
}
// for a fixed ordering where groupA's block comes immediately before
// groupB's block (with the third, unnamed group filling the rest),
// finds the minimum swaps needed across every possible starting
// position of groupA's block around the circle
long long solve(int groupA, int groupB) {
    long long ans = (long long)N + 1;
    int *prefixA = prefixes[groupA];
    int *prefixB = prefixes[groupB];
    int sizeA = counts[groupA];
    int sizeB = counts[groupB];

    // slide the starting position of groupA's block across every seat,
    // using the doubled string so the block can wrap past the end
    for (int start = 0; start < N; start++) {
        int aRight = start + sizeA - 1;
        int bLeft = start + sizeA;
        int bRight = bLeft + sizeB - 1;
        // count children who don't belong in groupA's section but are
        // currently sitting there, and likewise for groupB's section
        int wrongInA = sizeA - prefixQuery(prefixA, start, aRight);
        int wrongInB = sizeB - prefixQuery(prefixB, bLeft, bRight);
        // count how many groupA children are misplaced into groupB's
        // section, and vice versa, since swapping one of each directly
        // fixes both at once, resolving two "wrong" seats in a single
        // swap wherever this overlap exists
        int aCharsInB = prefixQuery(prefixA, bLeft, bRight);
        int bCharsInA = prefixQuery(prefixB, start, aRight);

        int swappable;
        if (bCharsInA < aCharsInB) {
            swappable = bCharsInA;
        } else {
            swappable = aCharsInB;
        }
        // each direct swap resolves two wrong seats at once instead of
        // needing two separate swaps, so subtract the swappable count
        // once from the total wrong count
        long long cost = wrongInA + wrongInB - swappable;
        if (cost < ans) {
            ans = cost;
        }
    }
    return ans;
}

int main() {
    scanf("%s", s);
    N = strlen(s);
    // build a doubled copy of the string so any block of consecutive
    // seats, including ones that wrap past the last seat back to the
    // first, can be read as one contiguous slice
    for (int i = 0; i < N; i++) {
        doubled[i] = s[i];
        doubled[i + N] = s[i];
    }

    cA = 0; cB = 0; cC = 0;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'A') {
            cA++;
        } else if (s[i] == 'B') {
            cB++;
        } else {
            cC++;
        }
    }

    prefixes[0] = pA; prefixes[1] = pB; prefixes[2] = pC;
    counts[0] = cA; counts[1] = cB; counts[2] = cC;
    // build prefix sum arrays over the doubled string, one per faction,
    // so any range query can be answered in O(1) later
    pA[0] = (doubled[0] == 'A');
    pB[0] = (doubled[0] == 'B');
    pC[0] = (doubled[0] == 'C');
    for (int i = 1; i < 2 * N; i++) {
        pA[i] = pA[i - 1] + (doubled[i] == 'A');
        pB[i] = pB[i - 1] + (doubled[i] == 'B');
        pC[i] = pC[i - 1] + (doubled[i] == 'C');
    }
    // try every possible ordering of the three faction blocks around
    // the circle, keeping the best (minimum) result across all of them
    long long ans = (long long)N + 1;
    for (int p = 0; p < 6; p++) {
        long long val = solve(perms[p][0], perms[p][1]);
        if (val < ans) {
            ans = val;
        }
    }

    printf("%lld\n", ans);
    return 0;
}