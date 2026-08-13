#include <stdio.h>
#include <string.h>

#define MAXN 1000005

char s[MAXN];
char doubled[2 * MAXN];
int pA[2 * MAXN], pB[2 * MAXN], pC[2 * MAXN];
int N, cA, cB, cC;
int *prefixes[3];
int counts[3];

int perms[6][3] = {
    {0, 1, 2}, {0, 2, 1},
    {1, 0, 2}, {1, 2, 0},
    {2, 0, 1}, {2, 1, 0}
};

int prefixQuery(int *prefix, int l, int r) {
    int left = 0;
    if (l > 0) {
        left = prefix[l - 1];
    }
    return prefix[r] - left;
}

long long solve(int groupA, int groupB) {
    long long ans = (long long)N + 1;
    int *prefixA = prefixes[groupA];
    int *prefixB = prefixes[groupB];
    int sizeA = counts[groupA];
    int sizeB = counts[groupB];

    for (int start = 0; start < N; start++) {
        int aRight = start + sizeA - 1;
        int bLeft = start + sizeA;
        int bRight = bLeft + sizeB - 1;

        int wrongInA = sizeA - prefixQuery(prefixA, start, aRight);
        int wrongInB = sizeB - prefixQuery(prefixB, bLeft, bRight);
        int aCharsInB = prefixQuery(prefixA, bLeft, bRight);
        int bCharsInA = prefixQuery(prefixB, start, aRight);

        int swappable;
        if (bCharsInA < aCharsInB) {
            swappable = bCharsInA;
        } else {
            swappable = aCharsInB;
        }

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

    pA[0] = (doubled[0] == 'A');
    pB[0] = (doubled[0] == 'B');
    pC[0] = (doubled[0] == 'C');
    for (int i = 1; i < 2 * N; i++) {
        pA[i] = pA[i - 1] + (doubled[i] == 'A');
        pB[i] = pB[i - 1] + (doubled[i] == 'B');
        pC[i] = pC[i - 1] + (doubled[i] == 'C');
    }

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