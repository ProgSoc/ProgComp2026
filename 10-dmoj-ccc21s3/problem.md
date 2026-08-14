# Food Truck Waiting Line

Today's going to be a busy day! You run a food truck and you've secured permission to set up adjacent to a big concert.
As you pull into the parking spot, you find that all the concert-goers are organised neatly arranged in a single file.
To get as much attention as you can for your food truck,
you can park at any point adjacent to this line and start up your grill,
so the smell of your food preparation can attract the concert-goers as much as possible.

Once a concert-goer smells your food,
they will be so enticed that they will immediately think of buying from your truck at the next chance they get.
However, it isn't always possible for *all* concert-goers to be immediately in range when you start up the grill.
Hence, you want to find the spot where all concert-goers can walk into range to smell the food in the quickest possible time.

Every concert-goer $i$ is initially at some position $P_i$ along the single file,
with a walking speed of one metre per $W_i$ seconds,
and will be able to pick up the scent of food when within $D_i$ metres from your truck.
If you choose the optimal location,
what is the **total** walking time needed from *all* concert-goers to pick up the scent of your food?

### Input

The first line of your input contains a single integer $N$ ($1 \le N \le 2 \times 10^5$), the number of concert-goers.
Following this is $N$ lines of input providing information about the concert-goers.
Each line $i$ ($1 \le i \le N$) contains three space-separated integers regarding concert-goer $i$:
their initial position $P_i$ ($0 \le P_i \le 10^9$),
the number of seconds they take to walk one metre $W_i$ ($1 \le W_i \le 10^3$),
and the range (in metres) within which they can pick up the scent of food $D_i$ ($0 \le D_i \le 10^9$).

### Output

Your output will be a single integer, which is the minimum possible sum of walking times over all given concert-goers
(assuming you park your food truck at the optimal location).

### Example

#### Sample Input 1
```
1
0 1000 0
```

#### Sample Output 1
```
0
```

#### Explanation 1
There is only one concert-goer at position $P_1 = 0$ (where $W_1 = 1000$ and $D_i = 0$),
so you can park your truck at $0$ metres along the field
and the concert-goer will be able to pick up the scent of food without moving at all.
Hence, it takes $0$ seconds to achieve what you want.

#### Sample Input 2
```
2
10 4 3
20 4 2
```

#### Sample Output 2
```
20
```

#### Explanation 2
Here there are two concert-goers.

* Concert-goer $1$ is at position $P_1 = 10$ metres along the line,
  with a walking speed of one metre per $W_1 = 4$ seconds and a range of $D_1 = 3$ metres.
* Concert-goer $2$ is at position $P_2 = 20$ metres along the line,
  with a walking speed of one metre per $W_2 = 4$ seconds and a range of $D_2 = 2$ metres.

The optimal position for your truck is $14$ metres along the line,
requiring concert-goer $1$ to walk one metre to position $11$ (to be $3$ metres away from your truck)
and concert-goer $2$ to walk four metres to position $16$ (to be $2$ metres away from your truck).

The walking time is $4 \times 1 = 4$ seconds for concert-goer $1$
and $4 \times 4 = 16$ seconds for concert-goer $2$,
making the total walking time $20$ seconds.

#### Sample Input 3
```
3
6 8 3
1 4 1
14 5 2
```

#### Sample Output 3
```
43
```

#### Explanation 3
The optimal position for your truck is $9$ metres along the line.

* Concert-goer $1$ is at position $P_1 = 6$ and has a range of $D_1 = 3$,
  so they need to move **0** metres to notice your truck.
* Concert-goer $2$ is at position $P_2 = 1$ and has a range of $D_2 = 1$,
  so they need to move **7** metres to position $8$ to notice your truck.
* Concert-goer $3$ is at position $P_3 = 14$ and has a range of $D_3 = 2$,
  so they need to move **3** metres to position $11$ to notice your truck.

The total walking time is thus $0 \times W_1 + 7 \times W_2 + 3 \times W_3 = 0 \times 8 + 7 \times 4 + 3 \times 5 = 43$ seconds.
