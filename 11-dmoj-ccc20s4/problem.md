# Carnival Seating Plan

Today is the day of the sports carnival in your school!
As the first activity of the day, you've got the difficult job of getting all the children to sit neatly in a circle
such that all members of a particular school faction are sitting contiguously in a block of consecutive positions.
This school has three factions (we can call them `A`, `B`, and `C`) for convenience.

Naturally, since these children are very eager to get started (and have various friend groups affecting their seating tendencies),
they have already sat themselves down in a circle before you had prompted them to do anything.
To your dismay, however, they're not always sitting in an arrangement that satisfies your requirement
(that is, children of the same faction must sit together in one contiguous block).
Hence, you're now going to have to tell two children at a time to swap seats with one another to get what you want.
Your task is to find the minimum number of swaps to achieve this.

### Input

The input consists of a single line,
which is a string containing $N$ ($1 \le N \le 10^6$) characters
such that every character is `A`, `B`, or `C`.
The $i$-th character denotes the faction that the child sitting in the $i$-th seat belongs to.
The children are numbered in clockwise order, such that Child $1$ is adjacent to Child $2$ and Child $N$,
and Child $2$ is adjacent to Child $1$ and Child $3$ and so on.

### Output

Your output will be a single integer,
which is the minimum possible number of swaps
needed to arrange the children correctly to prepare for the sports carnival.

### Example

#### Sample Input 1
```
BABCBCACCA
```

#### Sample Output 1
```
2
```

#### Explanation 1
The optimal solution is to swap Child $1$ and Child $7$, then to swap Child $4$ and Child $7$.

The layout thus changes in between swaps as follows.
```
BABCBCACCA
AABCBCBCCA (After first swap)
AABBBCCCCA (After second swap)
```

Notice here the final layout is such that the contiguous stretch of Faction `A` spans the 10th, 1st, and 2nd children
(since $N = 10$ in this case, the 10th child is adjacent to the 1st).
