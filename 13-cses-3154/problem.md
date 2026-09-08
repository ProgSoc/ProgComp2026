# Locked In

Phew! You've just gotten out of the labyrinth from the previous question... Or have you? You seem to be one step away from fully exiting the eldritch being's lair, and you find yourself having to solve another puzzle to get out. This time, there's only *one* room, but that doesn't make this task any easier. On a big screen in front of you is a large matrix of integers, next to another column of integers. Below that, there's a panel on which you can enter a series of integers next to an ominous large button reading **"EJECT"**. In all cases, you notice that the screen and panel are only capable of displaying integers from $0$ to $10^9 + 6$ inclusive.

Upon further inspection, you realise this is another mathematical challenge! To escape *this* room, you'll have to solve the system of linear equations represented on the big screen, and enter any valid solution into the panel. If there is no solution to the system of equations, you'll need to press the "EJECT" button instead. You're not sure what will happen if you press the "EJECT" button when there is a valid solution, but this probably isn't the time to put that to the test.

After having jumped through so many portals earlier, you certainly don't trust yourself solving these equations by hand. You're going to need to write a program that takes in the integers on the big screen, and outputs a solution to the system of equations that they represent (or `-1` if there is no solution, in which case you will hit the "EJECT" button). Your solutions will also have to be modulo $10^9 + 7$ to make it possible for you to enter it into the panel.

Formally, you are presented with an integer matrix $A$ of $n$ rows and $m$ columns and an integer vector $b$ of $n$ rows, where $a_{i, j}$ is the element of $A$ in the $i$-th row and $j$-th column and $b_i$ is the element of $b$ in the $i$-th row. Your task is to find the sequence of integers $x_1, x_2, \dots, x_m$ such that $a_{i, 1} x_1 + a_{i, 2} x_2 + \dots + a_{i, m} x_m \equiv b_i \mod 10^9 + 7$ is true for all $1 \le i \le n$ (if such a solution exists).

*Note for Java users: To pass all test cases of this question, using a `Scanner` will be too slow in reading the entire input. Use a `BufferedReader` instead.*

### Input

The first line contains two space-separated integers: $n$ ($1 \le n \le 500$) and $m$ ($1 \le n \le 500$). These specify the dimensions of the matrix $A$ and the column vector $b$, such that $A \in \mathbb{Z}^{n \times m}$ has $n$ rows and $m$ columns, and $b \in \mathbb{Z}^n$ has $n$ rows.

The next $n$ lines contain $m+1$ space-separated integers, specifying the values contained in $A$ and $b$. Every Line $i$ ($1 \le i \le n$) contains the following integers (in order): $a_{i, 1}, a_{i, 2}, \dots, a_{i, m}, b_i$.

In all cases, $0 \le a_{i, j} < 10^9 + 7$, and $0 \le b_i < 10^9 + 7$.

### Output

Your output is a single line. If there is an assignment of integer values for $x_i$ such that $a_{i, 1} x_1 + a_{i, 2} x_2 + \dots + a_{i, m} x_m \equiv b_i \mod 10^9 + 7$ holds for all $1 \le i \le m$ and $0 \le x_i < 10^9 + 7$, then your output is the sequence of values (starting from $x_1$, to $x_2$, up until $x_m$) separated by spaces.

If there is no possible solution, then your output is a single line with `-1`.

### Example

#### Sample Input 1

```
3 3
5 0 2 12
3 1 0 5
1 1 1 2
```

#### Sample Output 1

```
2 1000000006 1
```

#### Explanation 1

The system of equations is as follows:
* $5 x_1 + 2 x_3 \equiv 12 \mod 10^9 + 7$,
* $3 x_1 + x_2 \equiv 5 \mod 10^9 + 7$, and
* $x_1 + x_2 + x_3 \equiv 2 \mod 10^9 + 7$.

The only solution for this system given our constraints is $x_1 = 2$, $x_2 = 10^9 + 6$, and $x_3 = 1$, since:
* $5 x_1 + 2 x_3 = 5 \times 2 + 2 \times 1 = 12$,
* $3 x_1 + x_2 = 3 \times 2 + 10^9 + 6 = 10^9 + 12 \equiv 5 \mod 10^9 + 7$, and
* $x_1 + x_2 + x_3 = 2 + 10^9 + 6 + 1 = 10^9 + 9 \equiv 2 \mod 10^9 + 7$.
