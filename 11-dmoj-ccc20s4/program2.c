// this is for stadium seating using sliding window 
#include <stdio.h>
#include <string.h>

int n;
char seats[1000002];
int i, j;
int p[3], q[3][3];
int minswaps = 999999999;

int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    return b;
}

int window_swaps(void) {
    static int _q[3][3], z, s;
    memcpy(_q, q, sizeof q);
    s = 0;
    z = min(_q[1][0], _q[0][1]); _q[1][0] -= z; _q[0][1] -= z; s += z;
    z = min(_q[2][0], _q[0][2]); _q[2][0] -= z; _q[0][2] -= z; s += z;
    z = min(_q[1][2], _q[2][1]); _q[1][2] -= z; _q[2][1] -= z; s += z;
    s += _q[1][0] * 2;
    s += _q[0][1] * 2;
    return s;
}

void proc(void) {
    for (j = i = 0; i < 3; i++) {
        for (; j <= p[i]; j++) {
            q[(int)seats[j]][i]++;
        }
    }
    for (i = 0; i < n; i++) {
        minswaps = min(minswaps, window_swaps());
        for (j = 0; j < 3; j++) {
            if (++p[j] == n) {
                p[j] = 0;
            }
        }
        q[(int)seats[p[0]]][0]++; q[(int)seats[p[0]]][1]--;
        q[(int)seats[p[1]]][1]++; q[(int)seats[p[1]]][2]--;
        q[(int)seats[p[2]]][2]++; q[(int)seats[p[2]]][0]--;
    }
}

int main(void) {
    for (; (seats[n] = getchar() - 'A') != '\n' - 'A'; n++) {
        p[(int)seats[n]]++;
    }
    p[1] += p[0];
    p[2] += p[1];
    p[0]--; p[1]--; p[2]--;

    proc();

    memset(p, 0, sizeof p);
    memset(q, 0, sizeof q);

    for (i = 0; i < n; i++) {
        if (seats[i] == 1) {
            seats[i] = 2;
        } else if (seats[i] == 2) {
            seats[i] = 1;
        }
        p[(int)seats[i]]++;
    }
    p[1] += p[0];
    p[2] += p[1];
    p[0]--; p[1]--; p[2]--;

    proc();

    printf("%d\n", minswaps);
    return 0;
} 