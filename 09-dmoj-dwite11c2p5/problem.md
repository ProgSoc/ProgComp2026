# Intergalactic Transportation

It's the year 3000, and Earth currently serves as the hub of a large intergalactic transportation network.
Naturally, ships still cannot travel faster than light speed,
hence travel across such large distances has been made realistic by the invention of teleportation.
In fact, the entire network runs on a collection of portals, connecting various locations instantaneously.

To your dismay, however, this system has not eliminated the need for delivery personnel:
in fact *more* such personnel have been employed, and you are one of these people.
In addition to this, the network has to regularly deactivate and reactivate portals for maintenance.
This is of importance to you since it is only possible for you to make an instantaneous delivery between two cities if they are connected by
*any series of activated portals*.

It's another workweek for you.
Before the start of every day, a network-wide shutdown for maintenance is conducted,
such that no cities are connected by any activated portals at the start of each day.
Throughout every workday, one of two possible events will happen:

* A portal will be activated between two cities, or
* You will be asked to make an instantaneous delivery from one city to another.

Note that portals are *bi-directional*, such that if a portal connects some City A to some City B,
you can also use that portal to travel from City B to City A.

As mentioned previously, however, it is possible that when you are asked to make a delivery,
it is impossible to do so instantaneously, if there is *no* series of portals you can take to get from one city to another.
Hence, your task is as follows:
given a series of possible events on the day as specified above,
every time you are asked to make an instantaneous delivery,
output whether the two cities are connected by a series of activated portals or not.

### Input

Your input will consist of a series of $5$ test cases (corresponding to the five days of the workweek).
Every test case $i$ ($1 \le i \le 5$) starts with a line containing a single integer $n_i$ ($1 \le n_i \le 10^5$),
followed by $n_i$ lines, each corresponding to one of the two possible kinds of events that can happen in a workday.
Each line $j_i$ ($1 \le j_i \le n_i$) contains a single character (either "p" or "q")
followed by two space-separated strings `a` and `b` ($1 \le |a| \le 255$ and $1 \le |b| \le 255$),
representing the names of the two relevant cities for this event.

* If the first character is "p", this corresponds to a portal being activated between City `a` and City `b`.
* If the first character is "q", this corresponds to a command asking you to make an instantaneous delivery from City `a` to City `b`.

It is guaranteed that every test case $i$ contains at least one "q"-type line.

### Output

Your output will contain a series of lines,
with each line corresponding to every delivery command in the input (that is, every line in the input that starts with "q").
For that command, if it is possible to make an instantaneous delivery, then the output should be `connected`.
Otherwise, the output should be `not connected`.

### Example

#### Sample Input 1
```
7
p Waterloo Toronto
q Waterloo Toronto
p Dubai Toronto
p Montreal Vancouver
q Montreal Waterloo
p Dubai Vancouver
q Montreal Waterloo
1
q Waterloo Waterloo
2
p Dubai Toronto
q Dubai Sydney
4
p Sydney Canberra
q Sydney Melbourne
p Canberra Melbourne
q Sydney Melbourne
5
p Madrid Paris
p Berlin Amsterdam
q Madrid Amsterdam
p Paris Berlin
q Amsterdam Madrid
```

#### Sample Output 1
```
connected
not connected
connected
connected
not connected
not connected
connected
not connected
connected
```

#### Explanation 1

Let's first partition the lines of the sample output according to the workdays they belong to.

**Day 1:**
```
connected
not connected
connected
```

* The first delivery is from Waterloo to Toronto.
  These two cities were connected by a portal in the line just before.
* The second delivery is from Montreal to Waterloo.
  At this point, Montreal is only connected to Vancouver,
  which is not connected to any other city yet.
* The third delivery is again from Montreal to Waterloo.
  This time, there is a path of activated portals,
  going from Montreal to Vancouver, then to Dubai (newly activated in the previous line),
  then to Toronto, and then finally to Waterloo.

**Day 2:**
```
connected
```

* The first and only delivery is from Waterloo to Waterloo.
  This is the same city, and trivially an instantaneous delivery can be made by not using any portal.
  Note that in this case, no portals in the network have been activated.

**Day 3:**
```
not connected
```

* The first and only delivery is from Dubai to Sydney.
  However, Dubai is only connected to Toronto, hence an instantaneous delivery cannot be made.

**Day 4:**
```
not connected
connected
```

* The first delivery is from Sydney to Melbourne.
  At this point, Sydney is only connected to Canberra,
  hence an instantaneous delivery cannot be made.
* The second delivery is again from Sydney to Melbourne.
  This time, there is a series of portals allowing you to go from Sydney to Canberra
  and then from Canberra to Melbourne.
  Hence, the delivery can be made.

**Day 5:**
```
not connected
connected
```

* The first delivery is from Madrid to Amsterdam.
  At this point, Madrid is only connected to Paris,
  and Amsterdam is only connected to Berlin.
  No other portal connections exist, hence it is not possible to make the instantaneous delivery.
* The second delivery is from Amsterdam to Madrid.
  After the Paris to Berlin connection was made,
  the delivery can be achieved by going from Amsterdam to Berlin,
  then to Paris, then finally to Madrid.
  Hence, the delivery can be made.
