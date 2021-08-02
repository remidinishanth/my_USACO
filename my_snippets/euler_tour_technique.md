![](images/ett_1.png)
![](images/ett_2.png)
![](images/ett_3.png)
![](images/ett_4.png)
![](images/ett_5.png)

source: Competitive Programmer's Handbook - CSES

## Queries on Trees:

### Path Query and Update Problems
* **Path Query:** Given two nodes x, y - compute some function f(x, y) that depends on the path between nodes x & y.
  * Eg: sum, min, max, number of distinct elements etc.
* **Point Update:** Change the value for any one edge/node in the tree.
* **Path Range Update:** Change the value of all nodes/edges on a path.
  * Eg: Add x to all nodes in a path, take mod x for all nodes in a path etc.  

### Subtree Query and Update Problems
* **Subtree Query:** Given a node x - compute some function f(x) that depends on values of nodes/edges in the subtree of x
  * Eg: sum, min, max, number of distinct elements etc.
* **Point Update:** Change the value of any one edge / node in the tree
* **Subtree Range Update:** Change the value of all nodes/edges in the subtree of a node x.
  * Eg: Add "val" to all all nodes in the subtree of node x etc. 

### How to support Updates & Queries on a Tree?

* **Step-1:** Find a way to "Linaerize" the tree into an array.
  * **Heavy Light Decomposition:** Any path between (x, y) can be represented as concatenation of at-most logN different [L,R] ranges in the linearised array.
  * **Euler Tour Traversal:** Any subtree of a node x corresponds to a single range [L, R] in the linearised array.
* **Step-2:** Use one of the "standard" techniques to solve the update/query problem on the linearised tree.
  * Eg: Segment Trees, Square Root Decomposition etc. 

### Euler Tour Technique(ETT)

#### Way-1: Insert every node twice
* Insert every node/edge in the euler tour array whenever you enter/exit the node.
* Thereforce, everynode/edge of the tree will occur twice in the euler tour array - at indices `start[x]/in[x]` and `end[x]/out[x]` for a given node/edge x.

<p align="center"><img src="images/ett_6.png" width=300></p>

* A subtree of node x is represented by the continous range `[start[x], end[x]]`
* A path between the two nodes A & B contain nodes which occur exactly once in the continous range `[end[A], start[B]]` -- Useful for applying MO's on Trees where we can ignore an element y if it occurs twice in the range `[L, R]`. For example in case of Addition of path, When we see the node for the first time, we can add the element to sum and, when we see it the second time we can subtract thus nullifying the element which occurs twice in the range `[L, R]`.

#### Way-2: Insert every node only once
* Insert every node/edge in the eruler tour array whenever you enter the node and increment the timer
* start[x] = timer at which you enter the node x.
* end[x] = timer at which you exit the node x.
* All nodes in subtree of x occur exact once in the `range[start[x], end[x]]`

### Steps to support subtree updates/queries
* Build the Euler tour array for the given tree by doing a DFS
* Maintain a data structure on the Euler Tour array that supports range queries/updates
* For any query/update on all nodes in the subtree of node x, process it as a query/update on range `[start[x], end[x]]` in the linearised array.

### Simultaneously maintaining Euler Tour & HLD
* What if you wish to support path and subtree updates & queries together?
* tl;dr Simply add start[x], end[x] computation to HLD DFS.
* HLD is also a Way-2 Euler Tour Ordering
* In HLD, the "order" in which we call DFS on children is decided by subtree sizes.
* But once that is done, we "add our node to the array" and "increase the timer" whenever we enter a node for the first time.
* Therefore we can simply maintain the start[x] and end[x] times for every node `x`, similar to Way-2 of Euler Tour Technique.
* Now any subtree `x` will be present as a linear range [start[x], end[x]]
* Any path from vertex A to chainHead[chainNo[A]] will be present as a linaer range[start[chainHead[chainNo[A]]], start[A]] - exactly same as the usual HLD

```cpp
void dfs_sz(int v = 0) {
    sz[v] = 1;
    for(auto &u: g[v]) {
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]]) {
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v = 0) {
    in[v] = t++;
    for(auto u: g[v]) {
        nxt[u] = (u == g[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = t;
}
```

source: https://codeforces.com/blog/entry/53170

### Hackerrank: Subtrees and Paths

https://www.hackerrank.com/challenges/subtrees-and-paths/problem

You can now support simultaneous Queries and Updates of the form
* Range subtree Update: Add val to all nodes in the subtree of x
* Range Path Update: Add val to all nodes on path from node x to y
* Range Subtree Query: Return sum of all nodes in the subtree of x
* Range Path Query: Return sum of all nodes on the path from node x to y

In O(log²N) via HLD + Euler Tour + Segment Tree 🚀

### USACO guide implementation

If we can preprocess a rooted tree such that every subtree corresponds to a contiguous range on an array, we can do updates and range queries on it!

After running `dfs()`, each range `[st[i], en[i]]` contains all ranges `[st[j], en[j]]` for each `j` in the subtree of `i`. Also, `en[i]-st[i]+1` is equal to the subtree size of i.

```cpp
const int MX = 2e5+5;
vector<int> adj[MX];

int timer = 0, st[MX], en[MX];

void dfs(int node, int parent) {	
    st[node] = timer++;	
    for (int i : adj[node]) {
        if (i != parent) {
            dfs(i, node);		
        }	
    }
    en[node] = timer-1;
}
```
