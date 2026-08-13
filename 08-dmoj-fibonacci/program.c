#include <stdio.h>

typedef unsigned long long ull;

typedef struct {
    ull m[2][2];
} Matrix;

Matrix matmul(Matrix a, Matrix b, ull base) {
    Matrix ans;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ans.m[i][j] = 0;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j]) % base;
            }
        }
    }
    return ans;
}

int main(void) {
    ull n;
    scanf("%llu", &n);

    Matrix x;
    x.m[0][0] = 1;
    x.m[0][1] = 0;
    x.m[1][0] = 0;
    x.m[1][1] = 1;

    Matrix f;
    f.m[0][0] = 0;
    f.m[0][1] = 1;
    f.m[1][0] = 1;
    f.m[1][1] = 1;

    ull base = 1000000007ull;
    while (n) {
        if (n & 1) {
            x = matmul(x, f, base);
        }
        f = matmul(f, f, base);
        n >>= 1;
    }

    printf("%llu\n", x.m[0][1]);

    return 0;
}