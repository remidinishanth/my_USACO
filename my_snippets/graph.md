## Finding cycle in (directed) graph

### Tarjan's strongly connected components algorithm
Use colors, for example, white, grey and black.
You can even find the edges in the cycle. All the grey edges correspond to the cycle.

```cpp
vector<vector<int>> Adj;
vector<int> V;  // To store color of vertices (visited)
bool flag=true;
void dfs(int u){
    V[u]=1; // GREY
    for(int v:Adj[u]){
        if(V[v]==1){ flag=false;  // Cycle detected
            // you found a cycle, it's easy to recover it now.
        }
        else if(V[v]==0) dfs(v);
    }
    V[u]=2; // BLACK
}

for(int i = 0; i < n; i++)
    if(color[i] == 0) dfs(i, -1); // IF NODE IS WHITE, START NEW DFS
```

Strong Connectivity applies only to directed graphs. A directed graph is strongly connected if there is a directed path from any vertex to every other vertex.

```cpp
vi S, visited;                                    // additional global variables
int numSCC;

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
  S.push_back(u);           // stores u in a vector based on order of visitation
  visited[u] = 1;
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    ii v = AdjList[u][j];
    if (dfs_num[v.first] == DFS_WHITE)
      tarjanSCC(v.first);
    if (visited[v.first])                                // condition for update
      dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
  }

  if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
    printf("SCC %d:", ++numSCC);            // this part is done after recursion
    while (1) {
      int v = S.back(); S.pop_back(); visited[v] = 0;
      printf(" %d", v);
      if (u == v) break;
    }
    printf("\n");
} }
```

## Def
Let G = (V; E) be a connected, undirected graph. An articulation point of G is
a vertex whose removal disconnects G. A bridge of G is an edge whose removal
disconnects G. A biconnected component of G is a maximal set of edges such
that any two edges in the set lie on a common simple cycle, We can determine articulation points, bridges, and biconnected
components using DFS.
    
## Articulation Points

An ‘Articulation Point’ is defined as a vertex in a graph G whose removal (all edges
incident to this vertex are also removed) disconnects G. A graph without any articulation
point is called ‘Biconnected’. Similarly, a ‘Bridge’ is defined as an edge in a graph G whose
removal disconnects G. These two problems are usually defined for undirected graphs.

We maintain two numbers `dfs_num(u)` and `dfs_low(u)`. Here, `dfs_num(u)` stores the iteration counter when the vertex u is 
visited *for the first time*, `dfs_low(u)` stores the lowest `dfs_num` rechable from the current DFS spanning subtree of u.
At the beginning, `dfs_low(u) = dfs_num(u)` when vertex u is visited for the first time. Then, `dfs_low(u)` can only be made 
smaller if there is cycle(a back edge exists). Note that we do not update `dfs_low(u)` with a back edge (u, v) if v is a direct parent of u.

* When we are in a vertex u with v as its neighbor and `dfs_low(v) ≥ dfs_num(u)`, then
u is an articulation vertex. This is because the fact that `dfs_low(v)` is *not smaller* than
`dfs_num(u)` implies that there is no back edge from vertex v that can reach another vertex w
with a lower dfs_num(w) than dfs_num(u).

* A vertex w with lower `dfs_num(w)` than vertex
u with `dfs_num(u)` implies that w is the ancestor of u in the DFS spanning tree. This
means that to reach the ancestor(s) of u from v, one must pass through vertex u. Therefore,
removing vertex u will disconnect the graph.

However, there is one special case: The root of the DFS spanning tree (the vertex
chosen as the start of DFS call) is an articulation point only if it has more than one children
in the DFS spanning tree (a trivial case that is not detected by this algorithm).

```cpp
vi dfs_low;       // additional information for articulation points/bridges/SCCs
vi articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    ii v = AdjList[u][j];
    if (dfs_num[v.first] == DFS_WHITE) {                          // a tree edge
      dfs_parent[v.first] = u;
      if (u == dfsRoot) rootChildren++;  // special case, count children of root

      articulationPointAndBridge(v.first);

      if (dfs_low[v.first] >= dfs_num[u])              // for articulation point
        articulation_vertex[u] = true;           // store this information first
      if (dfs_low[v.first] > dfs_num[u])                           // for bridge
        printf(" Edge (%d, %d) is a bridge\n", u, v.first);
      dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);       // update dfs_low[u]
    }
    else if (v.first != dfs_parent[u])       // a back edge and not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);       // update dfs_low[u]
} }

  // inside main
  dfsNumberCounter = 0; dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0);
  dfs_parent.assign(V, -1); articulation_vertex.assign(V, 0);
  printf("Bridges:\n");
  for (int i = 0; i < V; i++)
    if (dfs_num[i] == DFS_WHITE) {
      dfsRoot = i; rootChildren = 0;
      articulationPointAndBridge(i);
      articulation_vertex[dfsRoot] = (rootChildren > 1); }       // special case
  printf("Articulation Points:\n");
  for (int i = 0; i < V; i++)
    if (articulation_vertex[i])
      printf(" Vertex %d\n", i);
```

The process to find bridges is similar. When `dfs_low(v) > dfs_num(u)`, then edge u-v is
a bridge (notice that we remove the equality test ‘=’ for finding bridges). 

source: <https://github.com/remidinishanth/cp3files/blob/master/ch4/ch4/ch4_01_dfs.cpp>

## Single Source Shortest Paths on Weighted Tree

Generally we use Dijkstra's O((V+E)logV) and Bellman-Ford's O(VE) algorithms for solving SSP problem on weighted graph. But if the 
given graph is a weighted tree, the SSSP problem becomes simpler: Any O(V) graph traversal algorithm, i.e BFS or DFS can be used to solve
this problem. There is only one unique path between any two vertices in a tree, so we simply traverse the tree to find the unique path connecting 
the two vertices. The shortest path weight between these two vertices is basically the sum of edge weights of this unique path.

## Diameter of Weighted Tree

For general graph, we need O(V^3) Floyd Warshall's algorithm plus O(V^2) all-pairs check to compute the diameter. However,
if the given graph is a weighted tree, the problem becomes simpler. We only need two O(V) traversals: 
* Do DFS/BFS from any vertex s to find the furthest vertex x,
* Do DFS/BFS one more time from vertex x to get the true furthest vertex y from x.

The length of the unique path along x to y is the diameter of that tree.

source: CP3 Chapter 4. Graph

Proof: <https://cs.stackexchange.com/questions/22855/algorithm-to-find-diameter-of-a-tree-using-bfs-dfs-why-does-it-work>
