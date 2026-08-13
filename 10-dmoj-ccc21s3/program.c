#include <stdio.h>
#include <stdlib.h>

#define MAX 200000

long long P[MAX], W[MAX], D[MAX];
int number;

long long cost(long long c) {
    long long total = 0;
    for (int i = 0; i < number; i++) {
        long long distance = P[i] - c;
        if (distance < 0) {
            distance = -distance;
        }
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

    long long lo = 0;
    long long hi = 1000000000LL;

    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        if (cost(m1) <= cost(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

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