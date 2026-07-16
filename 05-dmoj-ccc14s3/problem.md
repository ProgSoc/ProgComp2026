# Not-So-Parallel Parking

Congratulations! You've just been hired to the esteemed job of 'downhill traffic controller'.
You now specialise in directing traffic through tricky situations,
specifically ones that involve travelling downhill.
Naturally, one of the main key performance indicators of your job is that nobody crashes into each other.
However, today we won't be so worried about that just yet. You have a special shift today.

Today, you have been given a job on a notorious parking lot situated on the side of a mountain.
Near the mountain top, there is a single line of cars, each numbered from $1$ to $N$ in some order.
Cars can only move down the mountain one at a time, so a car cannot overtake another car.
There is also a separate parking line that goes horizontally (we refer to this as the 'branch'),
which cars can drive into to stay temporarily before finally going further down the hill
(cars cannot go back up towards the mountain top).
At the bottom of this mountain is a lake, where all the cars are trying to go.
A diagram of this mountain you're on is shown below.

![Mountain Diagram](https://static.dmoj.ca/texoid/2b0580e67e261c9a59df7e1532337a6e0b7e7325/svg)

Your boss today has given you some very specific instructions.
Rather than just letting the cars go on through in the order they're in,
he wants them to exit the mountain strictly in the order of Car $1$ first, followed by Car $2$, all the way until Car $N$.
Since the cars may not be starting in the suitable order for this and cannot overtake each other,
some cars may have to temporarily park in the branch to achieve this.
Cars also cannot overtake each other along the branch.
For example, if Car $x$ enters the branch followed by Car $y$,
Car $y$ *must* exit the branch first before Car $x$ can.

However, you come to the concerning realisation that it might not even be possible to achieve what your boss wants at all!
Therefore, your task is to write a program that takes in the order of cars as they start at the mountain top,
and indicates whether it is possible for the cars to exit the mountain top in the order of Car $1$, Car $2$, all until Car $N$.

### Input

The first line contains a single integer $T$ ($1 \le T \le 10$), the number of test cases.
Every test case $i$ ($1 \le i \le T$) will start with a line containing a single integer $N_i$ ($1 \le N_i \le 10^5$),
followed by $N_i$ lines, listing the $N_i$ cars at the mountain top from top to bottom.
That is, the last car in the list is the first one that is free to drive (either to the branch or to the lake).

### Output

Output $T$ lines, with each output line $i$ corresponding to test case $i$.
For test case $i$, if it is possible for the cars to exit in the required order, then line $i$ should be the character `Y`.
If it is not possible, line $i$ should be the character `N`.

### Example

#### Sample Input 1
```
2
4
2
3
1
4
4
4
1
3
2
```

#### Sample Output 1
```
Y
N
```

#### Explanation 1

The starting point of the first test case is illustrated below.

![Test Case 1](https://static.dmoj.ca/texoid/e63ff495096b962bee479fe1263e8eaea74ae103/svg)

The cars can exit the mountain and get to the lake in the required order with the following steps.
* Car 4 moves to the branch.
* Car 1 **exits** the mountain top and goes directly to the lake.
* Car 3 moves to the branch.
* Car 2 **exits** the mountain top and goes directly to the lake.
* Car 3 **exits** the branch and goes directly to the lake.
* Car 4 **exits** the branch and goes directly to the lake.

In the second test case, it is impossible to achieve the required exit order.
The closest attempt we can make is:
* Car 2 moves to the branch.
* Car 3 moves to the branch.
* Car 1 **exits** the mountain top and goes directly to the lake.

However, either Car 4 (in the mountain top) or Car 3 (who is in front of Car 2 along the branch) must be the next to exit.
Car 2 cannot overtake Car 3 along the branch to exit next,
and as a result the exit order can *never* be 1, 2, 3, 4.

Hence, it is possible in the first test case and impossible in the second test case.
