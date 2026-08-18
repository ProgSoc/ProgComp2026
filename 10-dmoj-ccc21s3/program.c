#include <stdio.h>
#include <stdlib.h>

#define MAX 200000

long long P[MAX], W[MAX], D[MAX];
int number;
// computes the total walking time if the food truck is parked at
// position c, summing over every concert-goer
long long cost(long long c) {
    long long total = 0;
    for (int i = 0; i < number; i++) {
        // distance from this concert-goer's current position to the
        // truck, always taken as positive regardless of direction
        long long distance = P[i] - c;
        if (distance < 0) {
            distance = -distance;
        }
        // the concert-goer only needs to walk enough to bring
        // themselves within range D[i] of the truck, if they're
        // already within range this comes out negative, which we
        // clamp to 0 since they don't need to walk at all
        long long walk = distance - D[i];
        if (walk < 0) {
            walk = 0;
        }
        total += walk * W[i];
    }
    return total;
}

int main() {
    scanf("%d", &number);
    for (int i = 0; i < number; i++) {
        scanf("%lld %lld %lld", &P[i], &W[i], &D[i]);
    }
    // search bounds cover every possible position along the line,
    // positions are guaranteed to be within [0, 10^9] as per the spec

    long long lo = 0;
    long long hi = 1000000000LL;
    // ternary search relies on cost(c) being unimodal, decreasing then
    // increasing as c moves away from the optimal spot, which holds
    // here since total walking time only gets worse the further the
    // truck is parked from the "centre of mass" of everyone's ranges

    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        // whichever third has the lower cost tells us which side the
        // minimum can't be on, so we shrink the search range away from
        // the worse third each iteration
        if (cost(m1) <= cost(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

    // once the range has shrunk down small enough, just brute force
    // check every remaining integer position directly, this avoids any
    // subtle off by one issues from ternary search alone on integer
    // domains, where the shrinking loop can't always narrow down to a
    // single exact point
    long long ans = cost(lo);
    for (long long c = lo; c <= hi; c++) {
        long long val = cost(c);
        if (val < ans) {
            ans = val;
        }
    }

    printf("%lld\n", ans);
    return 0;
}