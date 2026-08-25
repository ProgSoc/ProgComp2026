# Maths Homework

It's 1 am and you're currently helping your sibling with their maths homework. While they seem to have zoomed through most of it, they're currently stuck on a section about combinatorics. Upon closer inspection, you find to your horror that their teacher has set them a single question with many sub-questions, each demanding one of two tasks.

Specifically, this question concerns itself with permutations of positive integers. Let $p(n, k)$ define the $k$-th permutation of the integers from $1$ to $n$ inclusive, when ranked in ascending lexicographical order. For example, $p(3, 1) = [1, 2, 3]$, $p(3, 2) = [1, 3, 2]$, and $p(3, 6) = [3, 2, 1]$.

Every sub-question is either Type 1 or Type 2.
* Type 1 sub-questions provide the integers $n$ and $k$, and ask for the permutation $p(n, k)$.
* Type 2 sub-questions provide the integer $n$ and the permutation $p(n, k)$, and ask for the integer $k$.

Your sibling has gotten so fed up with their maths homework that they have stormed out of their room, leaving you staring at their homework in disbelief. (Why are there so many sub-questions?!) However, you also know that your sibling doesn't get along with their maths teacher, so you think it's best that they complete tonight's homework in time. Working it all out by hand sounds like a pain though, so you get the brilliant idea of writing a program to do the homework.

### Input

The first line contains a single integer $t$ ($1 \le t \le 10^3$), the number of sub-questions your sibling's maths homework has set.

The next $t$ lines each contain the sub-question and the provided information for that sub-question. For every line $i$ ($1 \le i \le t$):
* If the sub-question is Type 1, it will contain three space-separated integers.
  * The first integer will be $1$, indicating its type.
  * The second integer will be $n_i$, the number of integers in the required permutation.
  * The third integer will be $k_i$, the rank (when counting in ascending lexicographical order starting from $1$) of the required permutation.
* If the sub-question is Type 2, it will contain $n_i + 2$ space-separated integers.
  * The first integer will be $2$, indicating its type.
  * The second integer will be $n_i$, the number of integers in the provided permutation.
  * The next $n_i$ space-separated integers will form the permutation $p(n_i, k_i)$ in the provided order, where $k_i$ is the integer you need to find.

In all cases, $1 \le n_i \le 20$, and $1 \le k_i \le n_i!$.

### Output

Output $t$ lines, with the format of each line $i$ depending on the type of sub-question given in line $i$.
* If the sub-question is Type 1 with provided parameters $n_i$ and $k_i$, then your output will be $n_i$ space-separated integers such that they form the permutation $p(n_i, k_i)$.
* If the sub-question is Type 2 with provided parameters $n_i$ and $p(n_i, k_i)$, then your output will be a single integer: $k_i$.

### Example

#### Sample Input 1
```
6
1 4 1
1 4 2
2 4 1 2 3 4
2 4 1 2 4 3
1 5 42
2 5 2 4 5 3 1
```

#### Sample Output 1
```
1 2 3 4
1 2 4 3
1
2
2 4 5 3 1
42
```

#### Explanation 1
We have 6 sub-questions in this example. Explanations for each line are as follows.

1. $n_1 = 4$ and $k_1 = 1$. $p(4, 1) = [1, 2, 3, 4]$.
2. $n_2 = 4$ and $k_2 = 2$. $p(4, 2) = [1, 2, 4, 3]$.
3. $n_3 = 4$ and $p(4, k_3) = [1, 2, 3, 4]$. $k_3 = 1$.
4. $n_4 = 4$ and $p(4, k_4) = [1, 2, 4, 3]$. $k_4 = 2$.
5. $n_5 = 5$ and $k_5 = 42$. $p(5, 42) = [2, 4, 5, 3, 1]$.
6. $n_6 = 5$ and $p(5, k_6) = [2, 4, 5, 3, 1]$. $k_6 = 42$.
