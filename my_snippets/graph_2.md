## Longest path in Graphs

### Acyclic graphs

A longest path between two given vertices s and t in a weighted graph G is the same thing as a shortest path in a graph −G derived from G by changing every weight to its negation. Therefore, if shortest paths can be found in −G, then longest paths can also be found in G.

### DAG

For each vertex v in a given DAG, the length of the longest path ending at v may be obtained by the following steps:

* Find a topological ordering of the given DAG.
* For each vertex v of the DAG, in the topological ordering, compute the length of the longest path ending at v by looking at its incoming neighbors and adding one to the maximum length recorded for those neighbors. If v has no incoming neighbors, set the length of the longest path ending at v to zero. In either case, record this number so that later steps of the algorithm can access it.

Once this has been done, the longest path in the whole DAG may be obtained by starting at the vertex v with the largest recorded value, then repeatedly stepping backwards to its incoming neighbor with the largest recorded value, and reversing the sequence of vertices found in this way.

**Trick**
You do not need to do the DFS (topological sort) and DP separately. Just do the DP in recursive
manner. The situation where the recursive DP is good is exactly when the order of the DP is hidden.

DFS in case of longest path for a DAG: What you can do is use `in_degree[x] == 0` before you call `dfs(x)`, that is 
```cpp
for(int v:Adj[u]){
    in_degree[v]--;
    if(in_degree[v]==0){
        dfs(v);
    }
}
```

```cpp
// DAG - directed acyclic graph
 
const int nax = 1e5 + 5;
vector<int> edges[nax];
int in_degree[nax]; // the number of edges going to 'b'
int dist[nax];
bool visited[nax];
 
void dfs(int a) {
    assert(!visited[a]);
    visited[a] = true;
    for(int b : edges[a]) {
        dist[b] = max(dist[b], dist[a] + 1);
        --in_degree[b];
        if(in_degree[b] == 0) {
            dfs(b);
        }
    }
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while(m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        ++in_degree[b];
    }
    for(int i = 1; i <= n; ++i) {
        if(!visited[i] && in_degree[i] == 0) {
            dfs(i);
        }
    }
    int answer = 0;
    for(int i = 1; i <= n; ++i) {
        answer = max(answer, dist[i]);
    }
    printf("%d\n", answer);
}
```

## Diameter of Weighted Tree

For general graph, we need O(V^3) Floyd Warshall's algorithm plus O(V^2) all-pairs check to compute the diameter. However,
if the given graph is a weighted tree, the problem becomes simpler. We only need two O(V) traversals: 
* Do DFS/BFS from any vertex s to find the furthest vertex x,
* Do DFS/BFS one more time from vertex x to get the true furthest vertex y from x.

The length of the unique path along x to y is the diameter of that tree.

source: CP3 Chapter 4. Graph

Proof: <https://cs.stackexchange.com/questions/22855/algorithm-to-find-diameter-of-a-tree-using-bfs-dfs-why-does-it-work>

Since it is a tree, DFS/BFS doesn't matter

For un-weighted graphs, we can use n BFS and thus reduce the complexity to O(VE)

<details>
    <summary>Breaking tree recursively based on diameters</summary>
    
```cpp
vector<set<int>> Adj;

int n;
vi D, P; // Depth, Parent

vvi dd; // vector of diameter chains

vii Ans1, Ans2; // cuts and links

void dfs(int x, int p, int &far, int &last){
    P[x] = p;
    for(int y:Adj[x]){
        if(y!=p){
            D[y] = D[x] + 1;
            if(D[y]>far){
                far = D[y];
                last = y;
            }
            dfs(y,x, far, last);
        }
    }
}

void solve(int start=0){
    if(Adj[start].size()==0){
        dd.PB({start});
        return;
    }

    int far = 0; int t = 0;
    D[start] = 0;
    dfs(start, -1, far, t);

    far = 0; int last=t;
    D[t] = 0;
    dfs(t, -1, far, last);

    set<int> Diamater;
    vi dia;

    while(P[last]!=-1){
        dia.push_back(last);
        Diamater.insert(last);
        Diamater.insert(P[last]);
        last = P[last];
    }
    dia.push_back(last);

    dd.PB(dia);

    for(int x:dia){
        for(int y:Adj[x]){
            if(Diamater.find(y)==Diamater.end()){
                Ans1.PB({x,y});
                Adj[y].erase(x);
                solve(y);
            }
        }
    }
}

int main(){
    dsd(TC);
    while(TC--){
        Ans1.clear();
        Ans2.clear();
        dd.clear();
        Adj.clear();
        sd(n); D = vi(n); P = vi(n);
        Adj = vector<si>(n, set<int>());
        REP(i,n-1){
            dsd2(x,y);
            x--;
            y--;
            Adj[x].insert(y);
            Adj[y].insert(x);
        }
        solve();
        int first_end = dd[0].back();
        for(int i=1;i<dd.size();i++){
            Ans2.PB({first_end, dd[i][0]});
            first_end = dd[i].back();
        }
        pd(SZ(Ans1));
        REP(i,SZ(Ans1)){
            printf("%d %d ", Ans1[i].F + 1, Ans1[i].S + 1);
            printf("%d %d\n", Ans2[i].F + 1, Ans2[i].S + 1);
        }
    }
    return 0;
}
```
</details>

## Single Source Shortest Paths on Weighted Tree

Generally we use Dijkstra's O((V+E)logV) and Bellman-Ford's O(VE) algorithms for solving SSP problem on weighted graph. But if the 
given graph is a weighted tree, the SSSP problem becomes simpler: Any O(V) graph traversal algorithm, i.e BFS or DFS can be used to solve
this problem. There is only one unique path between any two vertices in a tree, so we simply traverse the tree to find the unique path connecting 
the two vertices. The shortest path weight between these two vertices is basically the sum of edge weights of this unique path.

![image](https://user-images.githubusercontent.com/19663316/117138431-a51ae600-adc8-11eb-8f19-78851e93f58c.png)

## SSSP on Weighted Graph

If the given graph is weighted, BFS does not work. This is because there can be ‘longer’
path(s) (in terms of number of vertices and edges involved in the path) but has smaller total
weight than the ‘shorter’ path found by BFS. To solve the SSSP problem on weighted graph, we use a greedy Edsger Wybe Dijkstra’s
algorithm. 

When this algorithm process u, it tries to relax all neighbors v of u. Every time it
relaxes an edge u → v, it will enqueue a pair (newer/shorter distance to v from source, v)
into pq and leave the inferior pair (older/longer distance to v from source, v) inside pq. This
is called ‘Lazy Deletion’ and it causes more than one copy of the same vertex in pq with
different distances from source. That is why we have the check earlier to process only the
first dequeued vertex information pair which has the correct/shorter distance (other copies
will have the outdated/longer distance). The code is shown below and it looks very similar
to BFS and Prim’s code 

```cpp
 AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &u, &v, &w);
    AdjList[u].push_back(ii(v, w));                              // directed graph
  }

// Dijkstra routine
  vi dist(V, INF); dist[s] = 0;                    // INF = 1B to avoid overflow
  priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
                             // ^to sort the pairs by increasing distance from s
  while (!pq.empty()) {                                             // main loop
    ii front = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
    int d = front.first, u = front.second;
    if (d > dist[u]) continue;   // this check is important, see the explanation
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
      ii v = AdjList[u][j];                       // all outgoing edges from u
      if (dist[u] + v.second < dist[v.first]) {
        dist[v.first] = dist[u] + v.second;                 // relax operation
        pq.push(ii(dist[v.first], v.first));
  } } }  // note: this variant can cause duplicate items in the priority queue
```

## SSSP on Graph with Negative Weight Cycle

If the input graph has negative edge weight, typical Dijkstra’s implementation can produces wrong answer.

To solve the SSSP problem in the potential presence of negative weight cycle(s), the more
generic (but slower) Bellman Ford’s algorithm must be used. This algorithm was invented
by Richard Ernest Bellman (the pioneer of DP techniques) and Lester Randolph Ford, Jr
(the same person who invented Ford Fulkerson’s method). The main idea
of this algorithm is simple: Relax all E edges (in arbitrary order) V -1 times!

Initially dist[s] = 0, the base case. If we relax an edge s → u, then dist[u] will have
the correct value. If we then relax an edge u → v, then dist[v] will also have the correct
value. If we have relaxed all E edges V -1 times, then the shortest path from the source
vertex to the furthest vertex from the source (which will be a simple path with V -1 edges)
should have been correctly computed. The main part of Bellman Ford’s code is simpler than
BFS and Dijsktra’s code:

```cpp
  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &a, &b, &w);
    AdjList[a].push_back(ii(b, w));
  }

  // Bellman Ford routine
  vi dist(V, INF); dist[s] = 0;
  for (int i = 0; i < V - 1; i++)  // relax all E edges V-1 times, overall O(VE)
    for (int u = 0; u < V; u++)                        // these two loops = O(E)
      for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j];        // we can record SP spanning here if needed
        dist[v.first] = min(dist[v.first], dist[u] + v.second);         // relax
      }

  bool hasNegativeCycle = false;
  for (int u = 0; u < V; u++)                          // one more pass to check
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
      ii v = AdjList[u][j];
      if (dist[v.first] > dist[u] + v.second)                 // should be false
        hasNegativeCycle = true;     // but if true, then negative cycle exists!
    }
  printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

  if (!hasNegativeCycle)
    for (int i = 0; i < V; i++)
      printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);
```

### Why does Bellman Ford Work?
* A shortest path can have at most n − 1 edges
* At the kth iteration, all shortest paths using k or less edges
are computed
* After n − 1 iterations, all distances must be final; for every
edge u → v of cost c, dv ≤ du + c holds
    * Unless there is a negative-weight cycle
    * This is how the negative-weight cycle detection works

## Floyd Warshall All pairs shortest Path

### Dynamic Programming I

![image](https://user-images.githubusercontent.com/19663316/117145494-d8617300-add0-11eb-84a9-0a88b3016885.png)

![image](https://user-images.githubusercontent.com/19663316/117145617-f7f89b80-add0-11eb-9e45-bd473f1f726b.png)

### DP II

![image](https://user-images.githubusercontent.com/19663316/117145729-15c60080-add1-11eb-85b0-f7743fc863d3.png)

![image](https://user-images.githubusercontent.com/19663316/117145780-24141c80-add1-11eb-82fc-e6351cef5cf8.png)

The basic idea behind Floyd Warshall’s is to gradually allow the usage of *intermediate vertices* (vertex [0..k]) to form the shortest paths.

![image](https://user-images.githubusercontent.com/19663316/117146699-18752580-add2-11eb-834f-252db6aa2b7b.png)

This DP formulation must be filled layer by layer (by increasing k). To fill out an entry in
the table k, we make use of the entries in the table k-1. 

The naive implementation is to use a 3-dimensional matrix
D[k][i][j] of size O(V^3). 

However, since to compute layer k we only need to know the
values from layer k-1, we can drop dimension k and compute D[i][j] ‘on-the-fly’ (the space
saving trick). Thus, Floyd Warshall’s algorithm just need O(V^2)
space although it still runs in O(V^3).

```cpp
// inside int main()
// precondition: AdjMat[i][j] contains the weight of edge (i, j)
// or INF (1B) if there is no such edge
// AdjMat is a 32-bit signed integer array
for (int k = 0; k < V; k++) // remember that loop order is k->i->j
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);
```

If `dij + dji < 0` for some i and j, then the graph has a negative weight cycle

## Printing Shortest Paths

A common issue encountered by programmers who use the four-liner Floyd Warshall’s without understanding how it works is when they are asked to print the shortest paths too. In BFS/Dijkstra’s/Bellman Ford’s algorithms, we just need to remember the shortest paths
spanning tree by using a 1D `vector<int> p` to store the parent information for each vertex. In Floyd
Warshall’s, we need to store a 2D parent matrix. The modified code is shown below.

```cpp
// inside int main()
// let p be a 2D parent matrix, where p[i][j] is the last vertex before j
// on a shortest path from i to j, i.e. i -> ... -> p[i][j] -> j
for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
        p[i][j] = i; // initialize the parent matrix

for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) // this time, we need to use if statement
            if (AdjMat[i][k] + AdjMat[k][j] < AdjMat[i][j]) {
                AdjMat[i][j] = AdjMat[i][k] + AdjMat[k][j];
                p[i][j] = p[k][j]; // update the parent matrix
            }
//-------------------------------------------------------------------------
// when we need to print the shortest paths, we can call the method below:
void printPath(int i, int j) {
    if (i != j) printPath(i, p[i][j]);
    printf(" %d", j);
}
```

Source: Wiki

```
let dist be a VxV array of minimum distances initialized to infinity.
let next be a VxV array of vertex indices initialized to null

procedure FloydWarshallWithPathReconstruction() is
    for each edge (u, v) do
        dist[u][v] ← w(u, v)  // The weight of the edge (u, v)
        next[u][v] ← v
    for each vertex v do
        dist[v][v] ← 0
        next[v][v] ← v
    for k from 1 to |V| do // standard Floyd-Warshall implementation
        for i from 1 to |V|
            for j from 1 to |V|
                if dist[i][j] > dist[i][k] + dist[k][j] then
                    dist[i][j] ← dist[i][k] + dist[k][j]
                    next[i][j] ← next[i][k]
procedure Path(u, v)
    if next[u][v] = null then
        return []
    path = [u]
    while u ≠ v
        u ← next[u][v]
        path.append(u)
    return path
```

## System of Difference Constraints

* Given m inequalities of the form xi − xj ≤ c
* Want to find real numbers x1, . . . , xn that satisfy all the given inequalities
* Seemingly this has nothing to do with shortest paths
    – But it can be solved using Bellman-Ford
    
![image](https://user-images.githubusercontent.com/19663316/117266809-4199c280-ae73-11eb-96ba-c73246120b84.png)

![image](https://user-images.githubusercontent.com/19663316/117266847-4c545780-ae73-11eb-8b05-ef62ac4807c2.png)

It turns out that our solution minimizes the span of the variables: max xi − min xi

source: Stanford CS 97SI: Introduction to Programming Contests


## Minimum Spanning Tree

We have an undirected weighted graph. 

The vertices along with a subset of the edges in the graph is called a
spanning tree if
* it forms a tree (i.e. does not contain a cycle) and
* the tree spans all vertices (all vertices can reach all other vertices)

The weight of a spanning tree is the sum of the weights of the edges
in the subset, We want to find a minimum spanning tree

### Algorithm

Several greedy algorithms work
* Go through the edges in the graph in increasing order of weight
* Greedily pick an edge if it doesn't form a cycle (Union-Find can be used to keep track of when we would get a cycle)
* When we've gone through all edges, we have a minimum spanning tree
    * This is Kruskal's algorithm
    * Time complexity is E.log(E)

```cpp
struct edge {
    int u, v;
    int weight;

    edge(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        weight = _w;
    }
};

vector<edge> adj[N];

struct union_find {
    vector<int> parent;
    union_find(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

bool edge_cmp(const edge &a, const edge &b) {
    return a.weight < b.weight;
}

vector<edge> mst(int n, vector<edge> edges) {
    union_find uf(n);
    sort(edges.begin(), edges.end(), edge_cmp);

    vector<edge> res;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u,
            v = edges[i].v;

        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            res.push_back(edges[i]);
        }
    }

    return res;
}
```

## TODO: Fracturing Search
