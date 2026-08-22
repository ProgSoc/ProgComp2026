#include <stdio.h>
#include <string.h>

#define MAX_NODES 200005
#define HASH_SIZE 524288
#define HASH_MASK (HASH_SIZE - 1)

// standard disjoint set union arrays, parent[x] points towards the
// representative of x's set, setSize is only meaningful for the root
// of each set and is used for union by size
int parent[MAX_NODES];
int setSize[MAX_NODES];
int dsuCount;

// hashIndex maps a hashed city name to its assigned integer id, using
// open addressing, -1 marks an empty slot
int hashIndex[HASH_SIZE];
// nameStr[i] stores the original city name string for id i, allowing
// us to resolve hash collisions by comparing actual strings
char nameStr[MAX_NODES][256];

// standard path compressed find, follows parent pointers to the root
// of x's set, flattening the path along the way for future queries
int find(int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = find(parent[x]);
    return parent[x];
}

// merges the sets containing x and y, using union by size so the
// smaller set is always attached under the larger one, keeping tree
// depth low and find operations fast
void unionSets(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (setSize[x] < setSize[y]) {
            int temp = x;
            x = y;
            y = temp;
        }
        parent[y] = x;
        setSize[x] += setSize[y];
    }
}

// registers a brand new city id, initialising it as its own singleton
// set in the dsu, and returns the id assigned to it
int grow(void) {
    int newNum = dsuCount;
    parent[newNum] = newNum;
    setSize[newNum] = 1;
    dsuCount++;
    return newNum;
}
// djb2 string hash, chosen for being fast and having good distribution
// across typical ascii strings such as city names
unsigned long hashString(const char *s) {
    unsigned long h = 5381;
    while (*s) {
        h = ((h << 5) + h) + (unsigned char)(*s);
        s++;
    }
    return h;
}
// looks up the integer id for a given city name, assigning it a new
// one if it hasn't been seen before, uses open addressing with linear
// probing to resolve hash collisions
int getOrAdd(const char *s) {
    unsigned long h = hashString(s) & HASH_MASK;
    // probe forward from the hashed slot until we either find the
    // matching city name already stored, or reach an empty slot
    while (hashIndex[h] != -1) {
        if (strcmp(nameStr[hashIndex[h]], s) == 0) {
            return hashIndex[h];
        }
        h = (h + 1) & HASH_MASK;
    }
    // reached an empty slot without finding a match, this city hasn't
    // been seen before, so register it as a new node
    int newIndex = grow();
    strcpy(nameStr[newIndex], s);
    hashIndex[h] = newIndex;
    return newIndex;
}

int main(void) {
    // process exactly 5 workdays, resetting all state at the start of
    // each one since the problem states no portals persist overnight
    for (int t = 0; t < 5; t++) {
        dsuCount = 0;
        memset(hashIndex, -1, sizeof(hashIndex));

        int n;
        scanf("%d", &n);

        while (n--) {
            char pToken[8];
            char aStr[256];
            char bStr[256];
            scanf("%7s %255s %255s", pToken, aStr, bStr);
            // resolve both city names to integer ids, registering
            // either one as new if this is the first time it's seen
            int i = getOrAdd(aStr);
            int j = getOrAdd(bStr);

            if (pToken[0] == 'p') {
                // portal activation, merge the two cities' sets
                unionSets(i, j);
            } else if (pToken[0] == 'q') {
                
                // delivery query, cities are reachable from each other
                // if and only if they belong to the same dsu set
                if (find(i) == find(j)) {
                    printf("connected\n");
                } else {
                    printf("not connected\n");
                }
            }
        }
    }

    return 0;
}