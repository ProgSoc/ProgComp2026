# Since conducting a DFS for every query is too slow,
# we use a DSU for each query instead.

# Size-ranked disjoint set union (DSU).
class DSU:
    def __init__(self):
        self.parent = []
        self.size = []

    def find(self, x):
        if self.parent[x] == x:
            return x
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        x, y = self.find(x), self.find(y)
        if x != y:
            x, y = sorted([x, y], key=lambda z: self.size[z], reverse=True)
            self.parent[y] = x
            self.size[x] += self.size[y]

    # We additionally implement the `grow` method to expand the DSU when needed.
    def grow(self):
        new_num = len(self.parent)
        self.parent.append(new_num)
        self.size.append(1)
        return new_num

for _ in range(5):
    # For every workday (5 workdays) a new DSU is made, and a new name lookup is made too.
    dsu = DSU()
    names = {}

    n = int(input())
    for _ in range(n):
        p, a, b = input().split()
        # If a name is already seen, we retrieve it from the `names` dictionary to find its corresponding index in the DSU.
        # Otherwise, we grow the DSU and assign this name to the new index.
        names[a] = names.get(a, dsu.grow())
        names[b] = names.get(b, dsu.grow())

        if p == 'p':
            # In the `p`-type query, we connect two cities together.
            dsu.union(names[a], names[b])
        elif p == 'q':
            # In the `q`-type query, we check whether two cities are connected and output whether they are.
            print('connected' if dsu.find(names[a]) == dsu.find(names[b]) else 'not connected')
