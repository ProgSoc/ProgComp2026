# Fibonacci's Homework

Everybody remembers the story of Carl Friedrich Gauss in his primary school days:
one day his teacher wanted to keep the students in his maths class busy,
and so he asked them all to sum up the integers from $1$ to $100$.
To his amazement, Gauss got the solution much faster than he had expected,
through a formula we now all use to this day.

Now, you suddenly find yourself in a similar situation.
You have just been given a conceptually simple piece of homework,
only this time it's not quite as simple as adding all positive integers up until a certain number.

Instead, your teacher gives you an integer $N$.
Your task is to find the $N$-th Fibonacci number
(modulo $10^9 + 7$, since your teacher is still considerate about how many digits you may have to write for your solution).

Formally, the Fibonacci sequence is made up of integers $F(n)$ where $n \ge 0$ is an integer, such that
* $F(0) = 0$,
* $F(1) = 1$, and
* $F(n) = F(n-1) + F(n-2)$ for $n \ge 2$,

where $F(n)$ represents the $n$-th Fibonacci number.

### Input

Your input consists of a single integer $N$ ($1 \le N \le 10^{19}$),
the integer given to you by your teacher.

### Output

Your output is a single integer, which is the value of $F(N)$ modulo $10^9 + 7$.

### Example

#### Sample Input 1
```
4
```

#### Sample Output 1
```
3
```

#### Explanation 1
We start with base cases $F(0) = 0$ and $F(1) = 1$.
* $F(2) = F(0) + F(1) = 0 + 1 = 1$,
* $F(3) = F(1) + F(2) = 1 + 1 = 2$, and
* $F(4) = F(2) + F(3) = 1 + 2 = 3$.

Since $3$ modulo $10^9 + 7$ is still $3$, the solution is $3$.

#### Sample Input 2
```
26
```

#### Sample Output 2
```
121393
```

#### Explanation 2
After much calculation, we find that $F(26) = 121393$.
Again, this is less than $10^9 + 7$, so the modulo operation keeps it unchanged.
