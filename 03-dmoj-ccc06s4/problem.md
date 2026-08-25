# Alien Groups

You and your friend have stumbled upon some seemingly extraterrestrial engravings. These engravings are marked on upon stone tablets and are strangely arranged in a square grid, with many symbols repeatedly showing up. Since your friend is actually a mathematician, they quickly spot that these engravings are actually tables defining the behaviour of an operator under a set of elements, since every grid is an $n$ by $n$ grid of symbols, and there are always exactly $n$ unique symbols on each tablet. Excited with their discovery, they want to know whether these tables correspond to a *group*, as this could be evidence of a super-intelligent alien species attempting to communicate with us via mathematics. You're convinced this isn't the case, so you set out to verify this conjecture for all the stone tablets you see.

Your friend has helpfully translated all these grids into an easily interpretable format, in that every unique alien symbol has been assigned a specific integer from the range $1$ to $n$ inclusive, where $n$ is the number of unique symbols in the grid (which is the same as the number of rows and number of columns in the grid). Your task is to take a series of such converted grids, and determine whether each grid given to you defines the operator of a group.

Formally, consider a group $G$ and its operator $\times$. The operator must abide by the following properties:
* **Closed:** For all elements $x$ and $y$ in $G$, $x \times y$ must also be in $G$.
* **Associativity:** For all elements $x$, $y$, and $z$ in $G$, $x \times (y \times z) = (x \times y) \times z$.
* **Identity:** The group $G$ has an "identity element" (let us call this $i$) such that for all elements $x$ in $G$, $x \times i = i \times x = x$.
* **Inverse:** For every element $x$ in $G$, there is some element $y$ in $G$ such that $x \times y = y \times x = i$ (where $i$ is the identity element as above).

An example of a finite group is the integers modulo $10$, with the group operator being addition (modulo $10$). In this case, the group has the elements $0, 1, 2, 3, 4, 5, 6, 7, 8, 9$. Addition modulo $10$ always stays within this set of elements, and is naturally associative. The identity element is $0$, and the inverse for any element $x \neq 0$ would be $10 - x$ (the inverse for $0$ is $0$ itself).

### Input

Your input will consist of a series of test cases (each corresponding to a single tablet), and ends with a particular sentinel value. Specifically, each test case begins with an integer $0 \le n_i \le 100$, which is the size of the finite group engraved on tablet $i$. When given an integer $n_i = 0$, the program should terminate. It is guaranteed that the last line of input is always a line containing $0$.

Following the single line containing the integer $n_i$, there will be $n_i$ rows of input, each containing $n_i$ space-separated integers, and defining a finite group operator over the integers from $1$ to $n_i$ inclusive. Each integer that appears will thus always be in the aforementioned range. The $q$-th integer on the $p$-th line of this sequence is the value of $p \times q$, where $\times$ is the operator of the given group.

Note that if an identity element exists, it is not necessarily $1$.

### Output

For every test case (that is, every group being provided to the program), output a single line containing `yes` if the given operator definition forms a valid group, or `no` otherwise.

### Example

#### Sample Input 1
```
2
1 2
2 1
6
1 2 3 4 5 6
2 1 5 6 3 4
3 6 1 5 4 2
4 5 6 1 2 3
5 4 2 3 6 1
6 3 4 2 1 5
0
```

#### Sample Output 1
```
yes
yes
```

#### Explanation 1
There are two test cases.

In the first test case, the operator $\times$ behaves as follows:
* $1 \times 1 = 1$,
* $1 \times 2 = 2$,
* $2 \times 1 = 2$,
* $2 \times 2 = 1$.

It satisfies **associativity** since:
* $(1 \times 1) \times 1 = 1 \times 1 = 1$ and $1 \times (1 \times 1) = 1 \times 1 = 1$.
* $(1 \times 1) \times 2 = 1 \times 2 = 2$ and $1 \times (1 \times 2) = 1 \times 2 = 2$.
* $(1 \times 2) \times 1 = 2 \times 1 = 2$ and $1 \times (2 \times 1) = 1 \times 2 = 2$.
* $(1 \times 2) \times 2 = 2 \times 2 = 1$ and $1 \times (2 \times 2) = 1 \times 1 = 1$.
* $(2 \times 1) \times 1 = 2 \times 1 = 2$ and $2 \times (1 \times 1) = 2 \times 1 = 2$.
* $(2 \times 1) \times 2 = 2 \times 2 = 1$ and $2 \times (1 \times 2) = 2 \times 2 = 1$.
* $(2 \times 2) \times 1 = 1 \times 1 = 1$ and $2 \times (2 \times 1) = 2 \times 2 = 1$.
* $(2 \times 2) \times 2 = 1 \times 2 = 2$ and $2 \times (2 \times 2) = 2 \times 1 = 2$.

The **identity** element is $1$ since $1 \times x = x \times 1 = x$ when $x = 1$ and $x = 2$.

The **inverse** element of $1$ is $1$ ($1 \times 1 = 1$), and the inverse element of $2$ is $2$ ($2 \times 2 = 1$).

In the second test case, the operator also satisfies associativity, the existence of an identity element (it is again $1$ in this case), and the existence of inverse elements (for $1$, $2$, $3$, $4$, $5$, and $6$, they are $1$, $2$, $3$, $4$, $6$, and $5$ respectively).

#### Sample Input 2
```
7
1 2 3 4 5 6 7
2 1 1 1 1 1 1
3 1 1 1 1 1 1
4 1 1 1 1 1 1
5 1 1 1 1 1 1
6 1 1 1 1 1 1
7 1 1 1 1 1 1
3
1 2 3
3 1 2
3 1 2
0
```

#### Sample Output 2
```
no
no
```

#### Explanation 2

In the first test case, $(3 \times 2) \times 2 = 1 \times 2 = 2$, but $3 \times (2 \times 2) = 3 \times 1 = 3$. This violates the associativity rule.

In the second test case, there is no identity element.
* $1$ cannot be the identity since $2 \times 1 = 3 \neq 2$.
* $2$ cannot be the identity since $2 \times 1 = 3 \neq 1$.
* $3$ cannot be the identity since $1 \times 3 = 3 \neq 1$.
