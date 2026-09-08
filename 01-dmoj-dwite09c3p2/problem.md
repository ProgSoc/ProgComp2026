# Fibonacci Sunflowers

You have a florist friend who is particularly obsessed with the number of petals on sunflowers. They have noticed that the number of petals on almost every sunflower that comes through their shop is a member of the same sequence of integers, which they had studiously taken note of over time. You have long since given up convincing them that maybe there are better ways to use one's time.

Upon taking a look at the noted sequence of integers, you realise they are almost all members of the Fibonacci sequence. This has led them to have taken interest in this sequence, and declare that sunflowers are intrinsically linked to the sequence. However, both of you can't get past the fact that some of the sunflowers don't line up with the Fibonacci sequence, and in their frustration, your friend declares that all values that aren't exactly a Fibonacci number must have been miscounts, and that the records must be corrected to reflect this fact.

Thus, your task is to round some integers to the nearest Fibonacci number. If an integer is equally distant from two different Fibonacci numbers, you are to select the larger one.

Formally, the Fibonacci sequence is made up of integers $F(n)$ where $n \ge 0$ is an integer, such that
* $F(0) = 0$,
* $F(1) = 1$, and
* $F(n) = F(n-1) + F(n-2)$ for $n \ge 2$.

*Note for Python users: Please select the `Python 3` option instead of the `PyPy 3` option for this question.*

### Input

Your input will consist of five lines. Each line $i$ (where $1 \le i \le 5$) consists of a single integer $0 \le n_i \le 10^9$.

### Output

Output five lines, with each line $i$ containing a single integer corresponding to the Fibonacci number closest to $n_i$.

### Example

#### Sample Input 1

```
1
2
4
22
1000000000
```

#### Sample Output 1

```
1
2
5
21
1134903170
```
