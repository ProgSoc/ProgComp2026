# Mathematician's Labyrinth

Bad news! You've stumbled into the lair of an eldritch being who is obsessed with number theory.
When you come to your senses, you realise you've been placed in the corner of a rectangular grid of cells.
Every cell has a positive integer etched into a tablet in the centre,
as well as a button that can activate one or more portals.
These portals are the only way through which you can transport yourself from one cell to another,
and you are always free to choose which of the opened portals to step through each time.

The logic behind these portals elude you until you took the time to number all of the cells.
The grid you are in has $M$ rows and $N$ columns,
allowing you to refer to any cell uniquely by the pair $(r, c)$
where $r$ is the row number of the cell (any integer in the range $1, 2, \dots, M$)
and $c$ is the column number of the cell (any integer in the range $1, 2, \dots, N$).
Every cell contains a tablet in its centre,
and you realise that if you're in a cell that contains the integer $x$ in its centre tablet,
the portals that open will transport you to any other cell of the coordinate $(a, b)$ such that $a \times b = x$.

For example, if your current cell has the integer $6$ on its centre tablet
and you are in a grid containing $5$ rows and $6$ columns,
three portals will open up: one to the $(1, 6)$ cell, one to the $(2, 3)$ cell, and one to the $(3, 2)$ cell.
Note that even though $6 \times 1 = 6$, $(6, 1)$ is not a valid cell in a $5 \times 6$ grid,
hence no portal goes to a non-existent cell as such in this example.

There is only one way to escape the labyrinth: reach the cell $(M, N)$,
where there is a door that will bring you back to our reality.
Your goal is to determine whether you can reach this door or not if you start from cell $(1, 1)$.

### Input

The first line contains a single integer $M$ ($1 \le M \le 10^3$),
the number of rows the grid has.
The second line contains a single integer $N$ ($1 \le N \le 10^3$),
the number of columns the grid has.

The remaining $M$ lines each contain $N$ space-separated integers,
which are the integers contained in the centre of each cell in that row.
Specifically, every Line $i$ ($1 \le i \le M$)
contains the space-separated integers $x_{i, 1}, x_{i, 2}, \dots, x_{i, N}$,
such that $x_{i, j}$ is the integer contained in the tablet of cell $(i, j)$.
In all cases, $1 \le x_{i, j} \le 10^6$.

*Note for Java users: To pass all test cases of this question,
using a `Scanner` will be too slow in reading the entire input.
Used a `BufferedReader` instead.*

### Output

Your output is a single line.
If it is possible to escape the labyrinth, output `yes`.
Otherwise, output `no`.

### Example

#### Sample Input 1
```
3
4
3 10 8 14
1 11 12 12
6 2 3 9
```

#### Sample Output 1
```
yes
```

#### Explanation 1
Starting at cell $(1, 1)$, you can make the following portal jumps to reach $(3, 4)$:
* Move to cell $(1, 3)$ (since the previous room's number was $3$ and $3 = 1 \times 3$).
* Move to cell $(2, 4)$ (since the previous room's number was $8$ and $8 = 2 \times 4$).
* Move to cell $(3, 4)$ (since the previous room's number was $12$ and $12 = 3 \times 4$).
