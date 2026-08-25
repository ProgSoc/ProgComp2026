from itertools import product, repeat

def is_group(table, n):
    return (
        # Tests if the group is closed.
        all(0 <= x < n for row in table for x in row) and
        # Tests if the group is associative (x * (y * z) = (x * y) * z) for all x, y, z triplets.
        all(table[x][table[y][z]] == table[table[x][y]][z] for x, y, z in product(*repeat(range(n), 3))) and
        # Tests if the group has any identity element that also satisfies the inverse property.
        any(
            (all(table[x][i] == table[i][x] == x for x in range(n))                                # Identity property for i: (x * i = i * x = x)
                and all(any(table[x][y] == table[y][x] == i for y in range(n)) for x in range(n))) # Inverse: (x * y = y * x = i)
            for i in range(n)))

n = int(input())
while n != 0:
    table = []
    for _ in range(n):
        # When reading in the group, decrement everything by 1 to make the elements identical to the indices used in the program,
        # allowing the entire 2D list to map to its own indices neatly.
        table.append(list(map(lambda x: int(x) - 1, input().split())))
    print('yes' if is_group(table, n) else 'no')
    # Keep reading `n` until 0 is entered.
    n = int(input())
