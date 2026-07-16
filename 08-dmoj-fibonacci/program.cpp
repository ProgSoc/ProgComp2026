#include <array>
#include <iostream>

// Due to the input bounds of `n`, computing `Fib(n)` the traditional way
// leads to a O(n) solution, which is too long.
// Instead, this solution represents the recurrence relation as a matrix,
// where the next term is an application of the matrix via multiplication.
// This allows the usage of repeated squaring to achieve a O(log n) solution.

// We only need to define multiplication, so we can represent our matrix as a 2D-array.
template <std::size_t N>
using Matrix = std::array<std::array<unsigned long long, N>, N>;

// Matrix multiplication by this implementation is cubic in `N`,
// but `N = 2` since we are dealing with a second-order recurrence relation,
// hence it is completely feasible.
// Also, at every step, we modulo each operation by `base` to keep the numbers always within our range.
template <std::size_t N>
Matrix<N> matmul(Matrix<N>& a, Matrix<N>& b, unsigned long long base) {
    Matrix<N> ans {};
    // These operations represent the fomula such that, for two square matrices `A` and `B` of dimensions `n x n`,
    // if they multiply to give the matrix `C`, then `c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + ... + a[i][n-1] * b[n-1][j]`.
    // At each stage of addition, a modulo by `base` is conducted.
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            for (std::size_t k = 0; k < N; ++k) {
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % base;
            }
        }
    }
    return ans;
}

int main() {
    // A single number input `n` is given, such that our task is to output `Fib(n)`.
    unsigned long long n;
    std::cin >> n;

    // `x` is the matrix representing our current term (starts at the identity matrix).
    Matrix<2> x { std::array {1ull, 0ull}, std::array {0ull, 1ull} };

    // `f` is the recurrence relation matrix for the Fibonacci sequence.
    // Since `F(n) = F(n-1) + F(n-2)`, every update step is conceptually `(a, b) = (b, a+b)`,
    // yielding the following matrix since
    // [   b   ] = [ 0 1 ] [ a ]
    // [ a + b ]   [ 1 1 ] [ b ].
    Matrix<2> f { std::array {0ull, 1ull}, std::array {1ull, 1ull} };

    // Repeated squaring on the recurrence relation matrix `f`.
    unsigned long long base = 1'000'000'007;
    while (n) {
        if (n & 1) {
            x = matmul(x, f, base);
        }
        f = matmul(f, f, base);
        n >>= 1;
    }

    // Let our final matrix `x` be such that
    // [ x00 x01 ]
    // [ x10 x11 ].
    // To then find `Fib(n)` from this matrix, we multiply it by our initial values, which are `0` and `1`.
    // The first element is what we need, which is found by `x[0][0] * 0 + x[0][1] * 1`.
    // Hence, we just need to output `x[0][1]` as our answer.
    std::cout << x[0][1] << '\n';
    return 0;
}
