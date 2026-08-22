n = int(input())

# Function to define matrix multiplication for two `n x n` matrices (`a` and `b`), where each operation is modulo `base`.
# Every matrix is represented as a 2D list of `n` rows and `n` columns.
matmul = lambda a, b, base, n: [[sum(a[i][k] * b[k][j] for k in range(n)) % base for j in range(n)] for i in range(n)]

# Due to the bounds of this problem, the typical O(n) method of calculating F(n) is too slow.
# Using repeated squaring by representing the calculation of the next Fibonacci number as a matrix multiplication
# allows a O(log n) method which is fast enough.
base = 10 ** 9 + 7
# We start with the identity matrix (to accumulate the multiplications of the Fibonacci matrix).
x = [[1, 0], [0, 1]]
# The actual Fibonacci matrix. This maps (a, b) to (b, a+b) since
# [ 0 1 ] [a] = [  b  ]
# [ 1 1 ] [b] = [a + b]
f = [[0, 1], [1, 1]]

# Repeated squaring is used to make it so that `x = f^n`.
while n:
    if n & 1:
        x = matmul(x, f, base, 2)
    f = matmul(f, f, base, 2)
    n >>= 1

# Our starting terms are 0 and 1, so we conduct the multiplication
# [x00 x01] [0] = [x01]
# [x10 x11] [1] = [x11].
# The `n`-th term is the first element of the vector, hence we just return `x[0][1]`.

print(x[0][1])
