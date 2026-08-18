#include <stdio.h>
#include <limits.h>
// i accidentally put the quesiton 12 code here instead of my 13 solution oops
#define MAX_N 100005
#define MAX_M 300005
#define MAX_EDGES (2 * MAX_M)

// adjacency list stored in linked-list-over-arrays style, to[e] is the
// destination of edge e, nxt[e] points to the next edge sharing the
// same source city, head[u] is the first edge out of city u
int to[MAX_EDGES];
int weight[MAX_EDGES];
int nxt[MAX_EDGES];
int head[MAX_N];
int edgeCount;

// costStart[i] is the shortest distance from city 0 to city i
// costEnd[i] is the shortest distance from city n-1 to city i
int costStart[MAX_N];
int costEnd[MAX_N];

typedef struct {
    int cost;
    int node;
} HeapItem;

// binary min-heap used as the priority queue for dijkstra, 1-indexed
// (heap[1] is the root) since that simplifies the parent/child index
// arithmetic (parent = i / 2, children = i * 2 and i * 2 + 1)
HeapItem heap[MAX_EDGES + 10];
int heapSize;

// adds a single directed edge u -> v with the given weight, called
// twice per input line since highways are bidirectional
void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    weight[edgeCount] = w;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
    edgeCount++;
}

void heapPush(int cost, int node) {
    heapSize++;
    int i = heapSize;
    heap[i].cost = cost;
    heap[i].node = node;

    // bubble the new entry up towards the root while it's smaller
    // than its parent
    while (i > 1) {
        int parent = i / 2;
        if (heap[parent].cost > heap[i].cost) {
            HeapItem temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

HeapItem heapPop(void) {
    // the minimum is always at the root, save it before overwriting
    HeapItem top = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;

    // sift the moved element down to restore the min-heap property
    int i = 1;
    while (1) {
        int left = i * 2;
        int right = i * 2 + 1;
        int smallest = i;
        if (left <= heapSize && heap[left].cost < heap[smallest].cost) {
            smallest = left;
        }
        if (right <= heapSize && heap[right].cost < heap[smallest].cost) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        HeapItem temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }

    return top;
}

// standard dijkstra's single source shortest path from source, fills
// distOut[] with the shortest distance to every city, uses lazy
// deletion, outdated heap entries are naturally skipped since any
// city popped with a cost higher than its already-finalised distOut
// value will just fail the newCost < distOut[v] check for its own
// neighbours anyway, so no explicit visited array is needed here
void sssp(int source, int n, int *distOut) {
    for (int i = 0; i < n; i++) {
        distOut[i] = INT_MAX;
    }
    distOut[source] = 0;

    heapSize = 0;
    heapPush(0, source);

    while (heapSize > 0) {
        HeapItem top = heapPop();
        int cost = top.cost;
        int u = top.node;

        // relax every edge out of u, if going through u gives a
        // shorter path to a neighbour v, update it and push the new
        // distance onto the heap
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];
            int newCost = cost + w;
            if (newCost < distOut[v]) {
                distOut[v] = newCost;
                heapPush(newCost, v);
            }
        }
    }
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }

    // read every highway and add it in both directions, since crossing
    // it either way costs the same t minutes
    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        addEdge(a, b, t);
        addEdge(b, a, t);
    }

    // shortest distance from city 0 to every city, and from city n-1
    // to every city, the graph being undirected means the second call
    // also gives us the shortest distance from every city to n-1
    sssp(0, n, costStart);
    sssp(n - 1, n, costEnd);

    // if the friend is in city i, the fastest trip is 0 to i to n-1,
    // costing costStart[i] + costEnd[i], we want the worst case across
    // every possible city the friend could be in, so take the maximum
    // of this sum over all cities
    int maxCost = costStart[0] + costEnd[0];
    for (int i = 0; i < n; i++) {
        int total = costStart[i] + costEnd[i];
        if (total > maxCost) {
            maxCost = total;
        }
    }

    printf("%d\n", maxCost);

    return 0;
}