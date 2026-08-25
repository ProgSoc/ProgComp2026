# Counting Lights

Your friend presents you with a small but interesting contraption. It consists of a row of lights, each of which can be either on or off at any point in time. At a regular time interval, the pattern lit up by the device changes instantaneously. Currently, the prototype device changes patterns once every second, but your friend has secured funding to create a version that changes much faster than this. (Apparently, this final device is going to change lighting patterns once every *femtosecond*, which is $10^{-15}$ seconds!)

After careful observation of this device, you realise the pattern of lights follows a very simple pattern. It turns out this device is actually just counting from $0$ upwards, displaying the integer $n$ in binary format at the $n$-th time interval. A light is on if and only if the bit at the corresponding position is a 1 bit. For example, one second after the prototype device is turned on, it is displaying the number $1$, and only one light is lit (the right-most one). Five seconds after that, the device is displaying the number $6$, and two lights are lit (the second and third ones from the right).

You are thus presented with a question. After $n$ time intervals, how many 'on' lights in total would you have seen? While it is possible for you to count these manually on the prototype device currently, that won't be possible on the bigger version of the device, where the time interval is one femtosecond instead of one second.

Hence, your task is to write a program that will calculate the total number of 'on' lights seen
after $n$ femtoseconds have passed after the bigger device is turned on.

### Input

Your input consists of a single integer $n$ ($1 \le n \le 10^{15}$), the number of femtoseconds the bigger device will be turned on for.

### Output

Your output is a single integer, which is the total number of 'on' lights displayed by the bigger device after $n$ femtoseconds.

### Example

#### Sample Input 1
```
7
```

#### Sample Output 1
```
12
```

#### Explanation 1

After $7$ femtoseconds, the device would have displayed the binary representations of numbers $0$, $1$, $2$, $3$, $4$, $5$, $6$, and $7$. Their binary representations are as follows:
* $0$ in binary is `0`.
* $1$ in binary is `1`.
* $2$ in binary is `10`.
* $3$ in binary is `11`.
* $4$ in binary is `100`.
* $5$ in binary is `101`.
* $6$ in binary is `110`.
* $7$ in binary is `111`.

Thus, the total number of 'on' lights seen is $0 + 1 + 1 + 2 + 1 + 2 + 2 + 3 = 12$.
