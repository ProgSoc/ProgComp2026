# Road Trip

Congratulations! You're getting near the end of this programming competition. To celebrate, you'll be going on a road trip, but you will need to pick up your friend on the way. Naturally, this is quite the lengthy road trip, so you are going to have to travel through a network of cities connected by bi-directional highways. This network is fully connected, meaning there always exists a path between any two cities. In the world we're concerned with, there are $N$ cities (ranging from City $0$ to City $N-1$). You start your road trip in City $0$, and your goal is to reach City $N-1$.

Of course, road trips don't come without a cost. Every time you cross the $i$-th highway (in either direction), it will take you $t_i$ minutes (and if you cross it $x$ times, it will take you $x \times t_i$ minutes in total). Your intention is to get from City $0$ to City $N-1$ in the shortest amount of time.

To add more confusion to the mix, you actually have no idea where your friend is right now. They could be in any one of the $N$ cities within the network, and you *must* pick up your friend on the way from City $0$ to City $N-1$. Note that it is also possible for your friend to be already in City $0$ or City $N-1$, in which case you would not have to go specifically out of your way to pick them up. Also, you are allowed to pass through City $N-1$ when on the way to pick up your friend, but you must then make your way back to City $N-1$ to complete the trip.

Your task is to determine the maximum number of minutes your trip could take considering all possible cities your friend could be in, assuming you always take the fastest route in every possibility.

### Input

The first line contains two space-separated integers. The first integer in this line is the number of cities $N$ ($2 \le N \le 10^5$), and the second integer in this line is the number of highways $M$ ($1 \le M \le 3 \times 10^5$). In the following $M$ lines, each line $i$ contains three space-separated integers regarding information about the $i$-th highway: $A_i$ ($0 \le A_i \le N-1$), $B_i$ ($0 \le B_i \le N-1$), and $t_i$ ($1 \le t_i \le 10^4$). The $i$-th highway connects City $A_i$ with City $B_i$, such that crossing the highway in either direction takes $t_i$ minutes.

### Output

Your output will be a single integer, which is the number of minutes that a worst-case trip from City $0$ to City $N-1$ will take when considering all the possible cities your friend could be in.

### Example

#### Sample Input 1
```
5 5
0 1 5
1 2 4
0 3 8
2 3 2
4 2 3
```

#### Sample Output 1
```
13
```

#### Explanation 1
If our friend is in City $0$, City $1$, City $2$, or City $4$, then the shortest path we can take from City $0$ to City $4$ while also picking them up on the way is $0 \rightarrow 1 \rightarrow 2 \rightarrow 4$, which has a cost of $5 + 4 + 3 = 12$ minutes.

If our friend is in City $3$, then the shortest path we can take from City $0$ to City $4$ while passing through City $3$ is $0 \rightarrow 3 \rightarrow 2 \rightarrow 4$, which has a cost of $8 + 2 + 3 = 13$ minutes.

Thus, our worst-case trip time is $13$ minutes.
