# Slippery Slide

The local water park has a new attraction: a massive complex of water slides. This slide complex consists of a number of stations, with slides connecting in between them. These stations are numbered $1$ to $n$ (for some positive integer $n$), such that they are ordered in decreasing order of altitude. That is, Station $1$ is situated at a higher point than Station $2$, which is also situated at a higher point than Station $3$.

Naturally, there is a safety concern about possible collisions or cross-overs between slides, but for the purpose of our task we won't be too concerned about that. Instead, you hear a curious kid passing by ask the following question: "How many possible ways are there to slide from Station $1$ to Station $n$?" This question captures your attention, and you are now determined to find the answer.

In this situation, you may assume that there is at most one slide directly connecting any two stations. For example, if Station $1$ and Station $3$ are directly connected by a slide, but there is no slide directly connecting Station $2$ and Station $3$, then there is exactly $1$ way to slide from Station $1$ to Station $3$.

### Input

The first line contains a single integer $n$ ($1 \le n < 10^4$), the number of stations in the water park. The next lines each contain pairs of the form `x y` ($1 \le x < y \le n$), representing the presence of a direct slide connecting Station $x$ to Station $y$. The last line of input is indicated by the pair `0 0`, and this line is not to be processed or interpreted as a slide connection.

You may assume that $\ell$ lines of input of the form `x y` will be provided (excluding `0 0`), where $\ell < 4 \times 10^7$.

### Output

Output a single integer, which is the number of distinct slide paths that can be taken from Station $1$ to Station $n$. You may assume that this number will be less than $2^{30}$. If there is no possible path from Station $1$ to Station $n$, then the number of paths will be $0$.

### Example

#### Sample Input 1

```
4
1 2
1 4
2 3
2 4
3 4
0 0
```

#### Sample Output 1

```
3
```

#### Explanation 1

Station $1$ has two outgoing slides: one to Station $2$ and one to Station $4$.
Station $2$ has two outgoing slides: one to Station $3$ and one to Station $4$.
Station $3$ has one outgoing slide to Station $4$.

Thus, there are 3 distinct paths that go from Station $1$ to Station $4$, as follows:
* `1 -> 2 -> 3 -> 4`
* `1 -> 2 -> 4`
* `1 -> 4`
