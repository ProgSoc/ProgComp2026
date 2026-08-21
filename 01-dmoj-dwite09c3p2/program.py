# The input bound is 10^9,
# so we calculate Fibonacci numbers up until the first one that exceeds the bound.
fibonacci = [0, 1]
while fibonacci[-1] < 10 ** 9:
    fibonacci.append(fibonacci[-2] + fibonacci[-1])

for _ in range(5):
    n = int(input())
    # `low` is the largest Fibonacci number less than or equal to `n`.
    # `high` is the smallest Fibonacci number greater than or equal to `n`.
    low, high = 0, 0
    for fib_num in fibonacci:
        # If we are searching in ascending order,
        # the last Fibonacci number less than or equal to `n` is `low`,
        # and the first Fibonacci number greater than or equal to `n` is `high`.
        if fib_num <= n:
            low = fib_num
        if high == 0 and fib_num >= n:
            high = fib_num
    # Print the lower Fibonacci number only if its difference from `n` is less than that of the higher one.
    print(low if n - low < high - n else high)
