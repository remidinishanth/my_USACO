# Centroid Decomposition

## Problem & Motivation

Given a tree, we are asked to find all the number of pairs `(u, v)` such that `dist(u, v) ≤ D`.

**Solution**

Note: This problem can also be solved by Small-To-Large Merging https://usaco.guide/plat/merging?lang=cpp

Let us fix one node of Tree by picking a vertex of the tree and call it `c`. Now let us split all the possible paths into classes: 
1) Some of the paths may not include this vertex `c`, then it will be completely inside one of the subtrees formed after removing `c`.
2) If the path includes node `c`, then we can break into two segments `u to c` and `c to v`.

![image](https://user-images.githubusercontent.com/19663316/119270642-5029fd00-bc1b-11eb-8d9c-9143a631b52e.png)
![image](https://user-images.githubusercontent.com/19663316/119270647-57510b00-bc1b-11eb-8fb4-08779a76f9a9.png)
![image](https://user-images.githubusercontent.com/19663316/119270631-3e485a00-bc1b-11eb-9722-7521a300f3af.png)

So what will do is that: We will pick a vertex `c`, remove that vertex from the tree and recursively find the number of pairs `(u, v)` in the subtree. In the end we will calculate the number of pairs which include the vertex `c`.

![image](https://user-images.githubusercontent.com/19663316/119271233-49e95000-bc1e-11eb-9e33-067163ea3e2f.png)

We will need to calculate `d[v]` which is distance from `(c, v)`, this can be precalculated in linear time. If we fix vertex `u`, then we will need to find all the vertices such that `d[v] ≤ D - d[u]`. Say we have an array of distances `d[i]` and maintain sorted order of this array and find the number of nodes `v` using binary search.

In this problem we will need to find the vertices which belong to different subtrees. We can do it in the following ways:

1. Add elements of first subtree into binary search tree form left to right and then iterate for elements `v` of second subtree and query the number of elements `u` satisfying `dist(u, v) ≤ D`.
![image](https://user-images.githubusercontent.com/19663316/119271191-1f979280-bc1e-11eb-9c30-7ad4144d959d.png)\
Then add the elements of second subtree to binary search tree and continue. Each time we consider a subtree, all the elements of previous subtrees are in our binary search tree.

2. Another way to calculate is to subtract the values we don't want to include. For a node `u` calculate all the nodes `v` of tree such that `d[v] ≤ D - d[u]` and then subtract the number of nodes which are in the same subtree as `u`.


Important thing is how to choose node `c`. Time complexity depends on how good is the node `c`, when we use divide and conquer technique we want to divide our problem into subproblems of equal size. We choose our vertex to be centroid of the tree.

A centroid is defined as a vertex such that when removed, all of the resulting subtrees have a size of at most half that of the original tree (that is, `⌊n/2⌋`).

![image](images/centorid_decomposition.gif)

Centroid of the tree is different than centre of tree(centre of a tree is simply the middle vertex/vertices of the diameter of the tree). Centre of the tree is the node such that if rooted minimizes the height of the rooted tree. The centre of the tree in the middle of the largest path in the tree. In the following image `blue` node is the centre of the tree whereas the `red` node is the centroid of the tree.

![image](https://user-images.githubusercontent.com/19663316/119272034-c3367200-bc21-11eb-9a8f-25e2805ff07e.png)


**Existence: Is there always a centroid?** Yes. Every tree has at least one centroid.

**Theorem (Jordan, 1869):** Given a tree with `N` nodes, there exists a vertex whose removal partitions the tree into components, each with at most `N/2` nodes. (i.e. For any given tree, the centroid always exists)

**Proof:** Let us chose any arbitrary vertex `a` in the tree, if `a` satisfies the property of the centroid, then we are done, else there exists one (and only one - if two such nodes exists then size of tree is `> N`) component with more than `N/2` vertices. We now consider the vertex `b` adjacent to `a` in that component and apply the same argument for `b` . We continue the same procedure unless we find the required vertex. Also, we never go back to any old vertices because the component containing them must have less than `N/2` vertices(because the subtree of `b` contains size `> N/2`). Since the no of vertices are finite, and we visit each vertex at most once, the procedure must end and hence the centroid must exist.

![image](images/centroid_decomposition2.gif)

![image](https://user-images.githubusercontent.com/19663316/119269663-6aada780-bc16-11eb-8d91-051c2db7fbe3.png)

**Finding the centroid of a tree:** One way to find the centroid is to pick an arbitrary root, then run a depth-first search computing the size of each subtree, and then move starting from root to the largest subtree until we reach a vertex where no subtree has size greater than N/2. This vertex would be the centroid of the tree.

Pavel marvin

```python
def dfs_size(x, p):
    s = 1
    for y in Adj[x]:
        if y != p:
	    s += dfs_size(y, p)
    return s
    
def dfs_centroid(x, p):
    s = 1
    ok = True
    for y in Adj[x]:
    	if y == p:
	    continue
	sz_y = dfs_centroid(y, x)
	if sz_y > n/2:
	    ok = False
	s += sz_y
    if s < n/2: # checking for n - s ≤ n/2
        ok = False
    if ok:
        centroid = x
    return s
    
# To compute centroid
n = dfs_size(v, -1)
dfs_centroid(v, -1)
```

```cpp
vector<int> Adj[maxn];
int sub[maxn]; // subtree size

int dfs_sz(int u, int p) {
    for (int v : Adj[u])
        if (v != p) sub[u] += dfs_sz(v, u);
	
    return sub[u] + 1;
}

int centroid(int u, int p) {
    for (int v : Adj[u])
        if (v != p and sub[v] > n/2) return centroid(v, u);

    return u;
}
```

**Centroid Decomposition**

On removing the centroid, the given tree decomposes into a number of different trees, each having no of nodes < N/2 . We make this centroid the root of our centroid tree and then recursively decompose each of the new trees formed and attach their centroids as children to our root. Thus , a new centroid tree is formed from the original tree. 

![image](https://user-images.githubusercontent.com/19663316/119269676-81ec9500-bc16-11eb-9448-ab4e7968c6b9.png)

Centroid Decomposition works by repeated splitting the tree and each of the resulting subgraphs at the centroid, producing `O(log N)` layers of subgraphs. Since at each step, the new trees formed by removing the centroid have size at-most `N/2`, the maximum no of levels would be `O(log N)`. Hence, the height of the centroid tree would be at most `O(log N)`.

Decomposing the Original Tree to get Centroid Tree

```python
def decompose(root, centroid_parent = -1):
    centroid = find_centroid(root)
    if centroid_parent != -1:
    	add_edge_in_centroid_tree(centroid_parent, centroid)
    for (adjacent_edge, adjacent_vertex) in G[centroid]:
    	delete_edge(adjacent_edge)
	decompose(adjacent_vertex, centroid)
```

source: Indian Programming Camp 2020, Thanuj Khattar

![image](https://user-images.githubusercontent.com/19663316/120892968-5dd57e80-c62e-11eb-9a66-0c057bab04f6.png)
![image](https://user-images.githubusercontent.com/19663316/120892971-61690580-c62e-11eb-8a43-5d3979b430b7.png)
![image](https://user-images.githubusercontent.com/19663316/120892975-6928aa00-c62e-11eb-92ed-2d424389452e.png)
![image](https://user-images.githubusercontent.com/19663316/120892979-6d54c780-c62e-11eb-8e36-3789b3b48c3a.png)

Let's mark the centroid with label 0, and remove it. After removing the centroid the tree separates into several parts of size at most N/2. Naturally, now we do the same recursively for each part, only marking the new centroids with label 1, then we get even more parts of size at most N/4, mark their centroids with label 2, and so on, until we reach parts of size 1. Since the size decreases at least twice with each step, the labels will be at most log(N).

**Observation 1:** Time Complexity of Centroid decomposition: `O(NlogN)`

![image](https://user-images.githubusercontent.com/19663316/119274243-8cb22480-bc2c-11eb-9d6f-b47e3b881e5b.png)

**Observation 2:** A vertex belongs to the component(in the original tree) of all its ancestors in the centroid tree. For example: The node 14 belongs to the component of 14, 15, 11 and 3.

![image](https://user-images.githubusercontent.com/19663316/119326345-6ed1d780-bc9f-11eb-8c7b-22f615e09618.png)

* It's simple if we think in terms of descendants instead of ancestors. The node `a` is a descendant of node `b` if `a` belong to the subtree resulting after removal of `b`. Note that the removal of `b` will only affect its own component/subtree, because we already disconnected `b` from its `parent` in the centroid decomposition. This means that all the descendants of `b` belong to its component.

**Observation 3:** Consider any two arbitrary vertices `a` and `b` and the path between them (in the original tree) can be broken down into path from `a` to `lca(a,b)` and the path from `lca(a,b)` to `b`, where `lca(a,b)` is the lowest common ancestor of `a` and `b` in the centroid tree. For example: The path from 9 to 10 in the original tree can be decomposed into the path from 9 to 3 and the path from 3 to 10.

![image](https://user-images.githubusercontent.com/19663316/119274357-1a8e0f80-bc2d-11eb-9829-eae232d4cd1f.png)

* It is not hard to see that given any arbitray vertices `a` and `b` and their `lca(a, b)` in the centroid tree, both `a` and `b` lie inside the part which the vertex `lca(a, b)` was centroid of, and they were first separated into different parts when the vertex `lca(a, b)` was removed.
* Both `a` and `b` belong to the component(subtree) where the node `lca(a,b)` is the centroid. Suppose, by contradiction, that `lca(a,b)` doesn’t divide the path from `a` to `b` into two disjoint parts. It means that both `a` and `b` will be in the same component(subtree) after the removal of `lca(a,b)` in the original tree. Consequently, the centroid of that component would be a common ancestor of `a` and `b` lower than `lca(a,b)` which is contradiction.

**Observation 4:** We decompose the given tree into `O(NlogN)` different paths (from each centroid to all the vertices in the corresponding part) such that any path in the original tree is a concatenation of two different paths from this set. (This is the most important/new/extra part in this Data Structure(DS) that should be focused on).

* Using some DS, we maintain the required information (based on the problem) about these `O(NlogN)` different paths chosen such that any other path can be decomposed into 2 different paths from this set and these two paths can be found in `O(logN)` time, by finding the LCA in the centroid tree (since height of centroid tree is at most `O(logN)`, we can find the LCA by just moving up from the deeper node).
* Each path from `a` to `b` in the original tree can be represented path from `a -> lca(a, b)` and `lca(a, b) -> b`. For each node we have `O(logN)` ancestors becuase the height of tree is `O(logN)`. There are `N` nodes in total and hence number of paths in `O(NlogN)`, that is there are only `O(NlogN)` paths from every node to its ancestors.

## Problems & Analysis

### Distance in the Tree - Timus

A weighted tree is given. You must find the distance between two given nodes.

**Input**

The first line contains the number of nodes of the tree n (1 ≤ n ≤ 50000). The nodes are numbered from 0 to n – 1. Each of the next n – 1 lines contains three integers u, v, w, which correspond to an edge with weight w (0 ≤ w ≤ 1000) connecting nodes u and v. The next line contains the number of queries m (1 ≤ m ≤ 75000). In each of the next m lines there are two integers.


<details>
	<summary> Using centroid decomposition </summary>


Given a tree with N nodes and Q queries of the form `u` `v` - Return the sum of elements on the path from `u` to `v`.

Instead of using `set<int> Adj` and deleting the actual edges, if we use `deleted[v]` marker then it is easy to delete.
	
```cpp
// Accepted code for https://acm.timus.ru/problem.aspx?space=1&num=1471
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
const int LOGN = 20;
// Original Tree
vector<int> g[N];
int sub[N], nn, U[N], V[N], W[N], deleted[N];
// Centroid Tree
int par[N], level[N], dist[LOGN][N];
// dist[LOGN][N] : dist[lvl][x] :  Distance between C and x in the original tree, when node C becomes a centroid at level "lvl". 
// G[u] --> [v1, v2, v3] ... Not doing this.
// G[u] --> [e1, e1, e3 ..] 
int adj(int x, int e) { return U[e] ^ V[e] ^ x; } // find the other end of this edge
void dfs1(int u, int p) { // to calculate size of subtrees
  sub[u] = 1;
  nn++; // global variable
  for (auto e : g[u]) {
    int w = adj(u, e);
    if (w != p && !deleted[e]) dfs1(w, u), sub[u] += sub[w];
  }
}
int find_centroid(int u, int p) {
  for (auto e : g[u]) {
    if (deleted[e]) continue;
    int w = adj(u, e);
    if (w != p && sub[w] > nn / 2) return find_centroid(w, u);
  }
  return u;
}
void add_edge_centroid_tree(int parent, int child) {
  // this func depends on the information to store in the question
  par[child] = parent;
  level[child] = level[parent] + 1; // level in centroid tree
}
void dfs2(int u, int p, int lvl) {
  for (auto e : g[u]) {
    int w = adj(u, e);
    if (w == p || deleted[e]) continue;
    dist[lvl][w] = dist[lvl][u] + W[e]; // key to make implementation efficient
    dfs2(w, u, lvl);
  }
}

// unordered_map<int, int> dist[N]; -- inefficient.
// all the nn nodes which lie in the component of "centroid"
// dist[centroid][x] = <value>
// int dist[LOGN][N]; (centroid,x) --> one to one mapping --> (level[centroid], x);
void decompose(int root, int p = -1) {
  nn = 0; // size of subtree of which this decompose is being called
  // Compute subtree sizes and no. of nodes (nn) in this tree.
  dfs1(root, root);
  // Find the centroid of the tree and make it the new root.
  int centroid = find_centroid(root, root);
  // Construct the Centroid Tree
  if (p == -1) p = root;
  add_edge_centroid_tree(p, centroid);
  // Process the O(N) paths from centroid to all leaves in this component.
  dfs2(centroid, centroid, level[centroid]);
  // Delete the adjacent edges and recursively decompose the adjacent subtrees.
  for (auto e : g[centroid]) {
    if (deleted[e]) continue;
    deleted[e] = 1;
    int w = adj(centroid, e);
    decompose(w, centroid);
  }
}

int compute_distance(int x, int y) {
  // We need to compute the LCA(x, y) in the centroid tree. 
  // Height of centroid tree is O(logN), so can compute in brute force way.
  int lca_level = 0;
  for (int i = x, j = y; (lca_level = level[i]) && i != j;
       level[i] < level[j] ? (j = par[j]) : (i = par[i]))
    ;
  return dist[lca_level][x] + dist[lca_level][y];
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    // Adj List & Edge list representation
    // i-th edges goes from U[i] to V[i] and has weight W[i]
    scanf("%d %d %d", U + i, V + i, W + i);
    U[i]++; V[i]++; // one based indexing
    g[U[i]].push_back(i); // pushing edge number instead of vertex
    g[V[i]].push_back(i);
  }
  decompose(1); // calling centroid decomposition on arbitrary vertex
  int m;
  scanf("%d", &m);
  while (m--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", compute_distance(x + 1, y + 1));
  }
}
```
</details>

### Open Cup 2014-15 Grand Prix of Tatarsta 

Problem D. LWDB, ICL’2015 - main event Russia, Kazan, 15.05.2015

You are given a tree with at most 10^5 vertices, where each edge has an integer length, and a sequence of 10^5 updates and queries. Each update tells to color all vertices in the tree that are at most the given distance from the given vertex with the given color. Each query requires you to output the current color of a given vertex.

<details> 
  <summary> Solution </summary>

![image](https://user-images.githubusercontent.com/19663316/120893226-c709c180-c62f-11eb-9db2-baa6d7b50b2c.png)

Consider any two vertices `A` and `B` in the tree and the path connecting them, and let's find the vertex `C` with the smallest label on that path. It's not hard to see that the path connecting `A` and `B` lies entirely in the part that vertex `C` was the centroid of in the above process, and that `A` and `B` lie in different parts that appear after removing `C`. So our path is concatenation of two paths: from `C` to `A`, and from `C` to `B`.

Whenever we need to color all vertices `B` at distance at most `D` from the given vertex `A` with color `X`, we will group possible `B`'s by `C` - the vertex with the smallest label on the path from A to B - Centroid. To find all possible `C`'s, we just need to follow the "decomposition parent" links from `A`, and there are at most `O(logN)` such `C`'s. For each candidate `C`, we will remember that all vertices in its part with distance at most `D-dist(A,C)` from `C` need to be colored with color `X`.

When we need to handle the second type of query, in other words when we know vertex `B` but not `A`, we can also iterate over possible candidate `C`'s. For each `C`, we need to find the latest update recorded there where the distance is at least `dist(B, C)`. After finding the latest update for each `C`, we just find the latest update affecting `B` by comparing them all, and thus learn the current color of `B`.

Finally, in order to find the last update for each `C` efficiently, we will keep the updates for each `C` in a stack where the distance decreases and the time increases (so the last item in the stack is always the last update, the previous item is the last update before that one that had larger distance, and so on). Finding the latest update with at least the given distance is now a matter of simple binary search.

</details> 

### IOI 2011

Given a weighted tree with N(1 ≤ N ≤ 200000) nodes, find the minimum number of edges in a path of length K(1 ≤ K ≤ 1000000), or return −1 if such a path does not exist.
1 ≤ length(i, j) ≤ 1000000 (integer weights)

<details>
	<summary> Brute force solution</summary>
	
* For every node, perform DFS to find distance and number of edges to every other node.
* Time complexity: O(n^2)
* Obviously fails because N = 200000.
</details>	

<details>
	<summary> Centroid Decomposition </summary>

* Perform centroid decomposition to get a “tree of subtrees”
* Start at the root of the decomposition, solve the problem for each
subtree as follows
  * Solve the problem for each “child tree” of the current subtree
  * Perform DFS from the centroid on the current subtree to compute the minimum edge count for paths that include the centroid
    * Two cases: centroid at the end or in the middle of path
    * Use a timestamped array of size 1000000 to keep track of which distances from centroid are possible and the minimum edge count for that distance
  * Take the minimum of the above two
* Time complexity: O(n log n)
	
</details>

### CF 199 Div 2 E. Xenia and Tree 

https://codeforces.com/contest/342/problem/E

Given a tree of `n` nodes indexed from `1` to `n`. The first node is initially painted red, and the other nodes are blue. 

We should execute two types of queries:
* paint a specified blue node to red
* calculate which red node is the closest to the given one and print the shortest distance to the closest red node.

**Solution**

# TODO


**Difference between HLD and CD**
* If we want to compute something on paths then we use HLD
* If we want to compute something on an area, we use CD. For example: Say we are given node `u` and distance `D` and we want to compute something on nodes `v` such that `dist(u, v) ≤ D`, something around node `u`.


TODO - https://codeforces.com/blog/entry/52492?locale=en

Implementation: https://codeforces.com/contest/321/submission/3973635, https://codeforces.com/contest/321/submission/45791725, https://usaco.guide/plat/centroid?lang=cpp, https://codeforces.com/contest/1303/submission/76216413, neal https://codeforces.com/contest/1303/submission/70880989, https://github.com/SuprDewd/CompetitiveProgramming/blob/5b326ad153f52d46a84f3d670f035af59a3ec016/code/graph/centroid_decomposition.cpp



Solve this problem https://codeforces.com/contest/1174/problem/F

REF: 
* https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308
* https://robert1003.github.io/2020/01/16/centroid-decomposition.html 
* https://threadsiiithyderabad.quora.com/Centroid-Decomposition-of-a-Tree
* https://petr-mitrichev.blogspot.com/2015/03/this-week-in-competitive-programming_22.html
* https://codeforces.com/blog/entry/10533#comment-159119
