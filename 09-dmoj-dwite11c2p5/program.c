#include <stdio.h>
#include <string.h>

#define MAX_NODES 200005
#define HASH_SIZE 524288
#define HASH_MASK (HASH_SIZE - 1)

int parent[MAX_NODES];
int setSize[MAX_NODES];
int dsuCount;

int hashIndex[HASH_SIZE];
char nameStr[MAX_NODES][256];

int find(int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = find(parent[x]);
    return parent[x];
}

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

int grow(void) {
    int newNum = dsuCount;
    parent[newNum] = newNum;
    setSize[newNum] = 1;
    dsuCount++;
    return newNum;
}

unsigned long hashString(const char *s) {
    unsigned long h = 5381;
    while (*s) {
        h = ((h << 5) + h) + (unsigned char)(*s);
        s++;
    }
    return h;
}

int getOrAdd(const char *s) {
    unsigned long h = hashString(s) & HASH_MASK;
    while (hashIndex[h] != -1) {
        if (strcmp(nameStr[hashIndex[h]], s) == 0) {
            return hashIndex[h];
        }
        h = (h + 1) & HASH_MASK;
    }
    int newIndex = grow();
    strcpy(nameStr[newIndex], s);
    hashIndex[h] = newIndex;
    return newIndex;
}

int main(void) {
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

            int i = getOrAdd(aStr);
            int j = getOrAdd(bStr);

            if (pToken[0] == 'p') {
                unionSets(i, j);
            } else if (pToken[0] == 'q') {
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