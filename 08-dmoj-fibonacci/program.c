#include <stdio.h>

typedef unsigned long long ull;
// a 2x2 matrix, used to represent the fibonacci transformation
typedef struct {
    ull m[2][2];
} Matrix;

// multiplies two 2x2 matrices together, reducing every entry modulo
// base to keep values from overflowing as n grows large
Matrix matmul(Matrix a, Matrix b, ull base) {
    Matrix ans;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ans.m[i][j] = 0;
        }
    }
    // standard matrix multiplication, ans[i][j] is the dot product of
    // row i from a and column j from b
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

    // x is the accumulated result, starts as the identity matrix since
    // multiplying by it does nothing, this is the standard starting
    // point for binary exponentiation
    Matrix x;
    x.m[0][0] = 1;
    x.m[0][1] = 0;
    x.m[1][0] = 0;
    x.m[1][1] = 1;

      // f is the fibonacci transformation matrix, [[0,1],[1,1]]
    // raising f to the n-th power gives a matrix whose entries are
    // consecutive fibonacci numbers, specifically f^n = [[F(n-1),F(n)],[F(n),F(n+1)]]
    Matrix f;
    f.m[0][0] = 0;
    f.m[0][1] = 1;
    f.m[1][0] = 1;
    f.m[1][1] = 1;

    ull base = 1000000007ull;
    // binary exponentiation, computes f^n by repeated squaring instead
    // of n separate multiplications, this is what brings the complexity
    // down from O(n) to O(log n), essential given n can be up to 10^19
    while (n) {
        // if the current bit of n is set, fold the current power of f
        // (which represents 2^(current bit position)) into the result
        if (n & 1) {
            x = matmul(x, f, base);
        }
        // square f each iteration, so it always represents f raised to
        // the next power of two
        f = matmul(f, f, base);
        n >>= 1;
    }
    // x now holds f^n, and since f^n = [[F(n-1),F(n)],[F(n),F(n+1)]],
    // the value we want, F(n), sits at position [0][1]
    printf("%llu\n", x.m[0][1]);

    return 0;
}