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

<details>
	<summary>Using Centroid decomposition</summary>

* Let `ans[a]` be the distance to the closest rose node to `a` in the component where node a is centroid. Initially, `ans[a] = ∞` because all nodes are blue (we’ll update the first node before reading the operations).
* For each update(a), we do `ans[b] = min(ans[b], dist(a, b))` for every ancestor b of a in centroid tree, where `dist(a,b)` is the distance in the original tree. 
* The time complexity of update is `O(lg²(n))` because we are moving up on the tree of height `lg(n)` and for each step we evaluate `dist(a,b)` in `O(lg(n))`.
* For each query(a), we take the minimum of `dist(a,b) + ans[b]` for every ancestor `b` of `a`, where `dist(a,b)` is the distance in the original tree.

</details>



### 757G — Can Bash Save the Day? CodeCraft 17

https://codeforces.com/contest/757/problem/G

Simpler question: Given a weighted tree, initially all the nodes of the given tree are inactive. We need to support the following operations fast:
* Query v : Report the sum of distances of all active nodes from node v in the given tree.
* Activate v : Mark node v to be an active node.

<details>
	<summary>Centroid Decomposition</summary>

For any such questions, we should think about the following:
* What information do we need to maintain to answer the query efficiently?
* How would the update impact the information we have maintained?

At each centroid vertex, we will store the sum of distances to all activates nodes in the centroid subtree. We will need to store some more information to make sure that we don't count some values more than once.

Let us store the following information:
* Let `sum[i]` deonote the sum of distances to all activated nodes for the centroid `i` in its corresponding part.
* Let `contribution[i]` deonote contribution of all activated nodes in the subtree of `i` to `sum[par[i]]` in centroid tree. What is this subtree at `i` contributing to it's parents.
* let `cnt[i]` deonote the number of activated nodes in the subtree of `i` in the centroid tree.
* For each update, to activate a node `u`, we  move up to all the ancestors `x` of `u` in the centroid tree and update their `sum[x] += dist(x,y);`, `contribution[x] += dist(par[x], u);` and `cnt[x] += 1;`
* For each query on u, we compute `sum[u]` + `(sum[par[x]] - contribution[x] + (cnt[par[x]] - cnt[x]) * dist(par[x], u))` for all ancestors `x` of `u`.
</details>

Original Problem: Given a weighted tree and a sequence `a_1, a_2, ..., a_n (permutation of 1 .. n)`. We need to answer `Q` queries of the form:
* Query l, r, v: Report Sum(dist(a_i, v)) for l ≤ i ≤ r
* Update x: Swap(a_x, a_{x+1}) in the given input sequence.

<details>
  <summary>Using Persistent Centroid Decomposition </summary>

**Solution Idea for query:**
* Each query of the form (L, R, v) can be divided into two queries of the form (1, R, v) - (1, L-1, v). Hence it is sufficient if we can support the following query: (i, v): Report the answer to query (1, i, v).
* To answer a single query of the form (i, v) we can think of it as what is the sum of distance of all active nodes from v, if we consider the first i nodes to be active.
* Hence initially if we can preprocess the tree such that we activate nodes from 1 to n and after each update, store a copy of the centroid tree, then for each query (i, v) we can lookup the centroid tree corresponding to i, which would have the first i nodes activated, and query for node v in O(log N) time by looking at it's ancestors.
* To store a copy of the centroid tree for each i, we need to make it persistent.

**Persistent Centroid Tree : Key Ideas**
* Important thing to note is that single update in the centroid tree affects only the ancestors of the node in the tree.
* Since height of the centroid tree is O(log N), each update affects only O(log N) other nodes in the centroid tree.
* The idea is very similar to that of a persistent segment tree BUT unlike segtree, here *each node of the centroid tree can have *arbitrarily many children and hence simply creating a new copy of the affected nodes would not work* because linking them to the children of old copy would take O(number of children) for each affected node and this number could be as large as N, hence it could take O(N) time in total!

**Binarizing the Input Tree**
* To overcome the issue, we convert the given tree T into an equivalent binary tree T' by adding extra dummy nodes such that degree of each node in the transformed tree T' is  ≤ 3, and the number of dummy nodes added is bounded by O(N).
* The dummy nodes are added such that the structure of the tree is preserved and weights of the edges added are set to 0.
* To do this, consider a node x with degree d > 3 and let c1, c2...cd be it's adjacent nodes. Add a new node y and change the edges as follows :
* Delete the edges (x - c3), (x - c4) ... (x - cd) and add the edge (x - y) such that degree of node x reduces to 3 from d.
* Add edges (y - c3), (y - c4) ... (y - cd) such that degree of node y is d - 1. Recursively call the procedure on node y.
* Since degree of node y is d - 1 instead of original degree d of node x, it can be proved that we need to add at most O(N) new nodes before degree of each node in the tree is  ≤ 3.

![image](https://user-images.githubusercontent.com/19663316/120901187-f67ff480-c656-11eb-8012-581b409e3620.png)

We need to binarize the original tree and not centroid tree. If we binarize the cetroid tree, then height of centroid tree would increase, may not be be O(log N).


**Conclusion**
Hence we perform centroid decomposition of this transformed tree T'. The centroid tree formed would have the following properties.

The height of the centroid tree is O(logN)

Each node in the centroid tree has ≤ 3 children.

Now we can easily make this tree persistent by path-copying approach.

To handle the updates,
* Way-1 : Observe that swapping A[i] and A[i + 1] would affect only the i'th persistent centroid tree, which can be rebuilt from the tree of i - 1 by a single update query. In this approach, for each update we add  new nodes. See author's code below for more details.
* Way-2 : First we go down to the lca of A[x] and A[x + 1] in the x'th persistent tree, updating the values as we go. Now, let cl be the child of lca which is an ancestor of A[x], and let cr be the child which is an ancestor of A[x + 1]. Now, we replace cr of x'th persistent tree with cr of (x + 1)'th persistent tree. Similarly, we replace cl of x + 1'th persistent tree with cl of x'th persistent tree. So now A[x + 1] is active in x'th persistent tree and both A[x] and A[x + 1] are active in (x + 1)'th persistent tree.To deactivate A[x] in x'th persistent tree we replace cl of x'th persistent tree with cl of (x - 1)'th persistent tree. Hence in this approach we do not need to create new O(log N) nodes for each update. See testers's code below for more details.

```cpp
//Tanuj Khattar
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
const int MAXN = int(2e5)+10;
const int MAXQ = int(2e5)+10;
const int N = 2*MAXN;
const int M = 2*N;
int A[N]; //the permutation given
int last[N],prv[M],nxt[M],to[M],deg[N],W[M],root[N];
namespace tree{
  int sz,edge,vis[N];
  void addEdge(int u,int v,int w = 0){
    prv[edge] = last[u];W[edge] = w;
    if(last[u]!=-1)nxt[last[u]] = edge;
    last[u] = edge;
    to[edge] = v;
    edge++;
  }
  void addEdge1(int u,int v,int e){
    prv[e] = last[u];nxt[e] = -1;
    if(last[u]!=-1)nxt[last[u]] = e;
    last[u] = e;
    to[e] = v;
  }
  void deleteEdge(int u,int e){
    if(nxt[e]!=-1)prv[nxt[e]] = prv[e];
    if(prv[e]!=-1)nxt[prv[e]] = nxt[e];
    if(last[u] == e) last[u] = prv[e];
  }
  void changeEdge(int u,int v,vector<int> edges){
    //assert(SZ(edges) == 3);assert(deg[u] > 3);
    sort(ALL(edges));reverse(ALL(edges));
    for(auto e : edges)
      deleteEdge(u,e);
    last[v] = last[u];
    last[u] = -1;
    for(auto e : edges)
      addEdge1(u,to[e],e);
  }
  void pre(){
    SET(last,-1);SET(nxt,-1);
    SET(prv,-1);SET(to,-1);
  }
  //binarize the give tree.should be called from a leaf node.
  void binarize(int u,int p,int edge){
    vis[u]=1;
    if(deg[u] > 3){
      addEdge(u,++sz);
      deg[sz] = deg[u] - 1;
      set<int> temp;temp.insert(edge^1);
      int e = last[u];
      while(SZ(temp) < 3){
        temp.insert(e);
        e = prv[e];
      }
      changeEdge(u,sz,vector<int>(temp.begin(),temp.end()));
      deg[u] = 3;
      addEdge(sz,u);
    }
    for(int e = last[u];e >= 0; e = prv[e]){
      if(!vis[to[e]])
        binarize(to[e],u,e);
      else to[e] = p;
    }
  }
}
namespace Centroid{
  const int LOGN = 19;
  const int MAXC = N + (MAXN + MAXQ)*LOGN;
  int sub[N],nn,done[M],C[MAXC][3],L[N],R[N],idx[N],len[N],T,cnt[MAXC],lvl,IDX[MAXC];
  LL sum[MAXC],cntbn[MAXC],dist[LOGN][N];
  void dfs1(int u,int p){
    sub[u]=1;nn++;
    for(int e = last[u];e >= 0; e = prv[e]){
      int w = to[e];
      if(w!=p && !done[e])
        dfs1(w,u),sub[u]+=sub[w];
    }
  }
  int dfs2(int u,int p){
    for(int e = last[u];e >= 0; e = prv[e]){
      if(done[e])continue;int w = to[e];
      if(w!=p && sub[w]>nn/2)
        return dfs2(w,u);
    }return u;
  }
  void dfs(int u,int p){
    for(int e = last[u];e >= 0; e = prv[e]){
      if(done[e] || to[e]==p)continue;
      dist[lvl][to[e]] = dist[lvl][u] + W[e];
      dfs(to[e],u);
    }
  }
  int decompose(int root,int p,int l = 0){
    nn=0;dfs1(root,root);
    root=dfs2(root,root);
    lvl = l;dfs(root,root);
    idx[root] = ++T;
    int id = idx[root];IDX[T] = T;
    L[id] = T;
    for(int e = last[root];e >= 0;e = prv[e]){
      if(done[e])continue;
      assert(!done[e^1]);
      done[e]=done[e^1]=1;
      int c = decompose(to[e],root,l+1);
      assert(len[id] < 3);
      C[id][len[id]++] = idx[c];
    }
    R[id] = T;
    return root;
  }
  int update(int x,int id,int lvl=0){
    int ID = ++T;
    cnt[ID] = cnt[id] + 1;
    sum[ID] = sum[id] + dist[lvl][x];
    IDX[ID] = IDX[id];
    for(int i=0;i<len[IDX[id]];i++)
      if(L[IDX[C[id][i]]] <= idx[x] && idx[x] <= R[IDX[C[id][i]]]){
        C[ID][i] = update(x,C[id][i],lvl+1);
        cntbn[C[ID][i]] = cntbn[C[id][i]] + dist[lvl][x];
      }
      else C[ID][i] = C[id][i];
    return ID;
  }
  LL query(int x,int id,int lvl=0){
    LL ret = sum[id];
    for(int i=0;i<len[IDX[id]];i++)
      if(L[IDX[C[id][i]]] <= idx[x] && idx[x] <= R[IDX[C[id][i]]])
        ret += query(x,C[id][i],lvl+1) - cntbn[C[id][i]] + (cnt[id] - cnt[C[id][i]])*dist[lvl][x];
    return ret;
  }
}
void binarize(int n){
  int root = -1;
  for(int i=1;i<=n;i++)
    if(deg[i] == 1)
      root = i;
  tree::binarize(root,root,-1);
}
int main()
{
  tree::pre();
  int n,q;
  si(n);si(q);
  tree::sz = n;
  for(int i=1;i<=n;i++)si(A[i]);
  for(int i=1;i<n;i++){
    int u,v,w;
    si(u);si(v);si(w);
    tree::addEdge(u,v,w);
    tree::addEdge(v,u,w);
    deg[u]++;deg[v]++;
  }
  //binarize the given tree
  binarize(n);
  //build the centroid tree.
  Centroid::decompose(1,-1);
  root[0] = 1;
  //make it persistent and handle the queries.
  for(int i=1;i<=n;i++)
    root[i] = Centroid::update(A[i],root[i-1]);
  const int MOD = (1 << 30);
  LL ans = 0;
  while(q--){
    int t;si(t);
    if(t==1){
      int l,r,v;
      si(l);si(r);si(v);
      l = l ^ ans;
      r = r ^ ans;
      v = v ^ ans;
      ans = Centroid::query(v,root[r])-Centroid::query(v,root[l-1]);
      lldout(ans);
      ans = ans % MOD;
    }
    else{
      int x;si(x);x = x ^ ans;
      root[x] = Centroid::update(A[x+1],root[x-1]);
      swap(A[x],A[x+1]);
    }
  }
  return 0;
}
```

Another approach: https://codeforces.com/blog/entry/49743?#comment-337109, http://codeforces.com/contest/757/submission/23772311

![image](https://user-images.githubusercontent.com/19663316/120901066-28448b80-c656-11eb-8fe0-a80eedef2d7f.png)

</details>

**Difference between HLD and CD**
* If we want to compute something on paths then we use HLD
* If we want to compute something on an area surrounding node, we use CD. For example: Say we are given node `u` and distance `D` and we want to compute something on nodes `v` such that `dist(u, v) ≤ D`, something around node `u`.


TODO - https://codeforces.com/blog/entry/52492?locale=en

Implementation: https://codeforces.com/contest/321/submission/3973635, https://codeforces.com/contest/321/submission/45791725, https://usaco.guide/plat/centroid?lang=cpp, https://codeforces.com/contest/1303/submission/76216413, neal https://codeforces.com/contest/1303/submission/70880989, https://github.com/SuprDewd/CompetitiveProgramming/blob/5b326ad153f52d46a84f3d670f035af59a3ec016/code/graph/centroid_decomposition.cpp



Solve this problem https://codeforces.com/contest/1174/problem/F

REF: 
* https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308
* https://robert1003.github.io/2020/01/16/centroid-decomposition.html 
* https://threadsiiithyderabad.quora.com/Centroid-Decomposition-of-a-Tree
* https://petr-mitrichev.blogspot.com/2015/03/this-week-in-competitive-programming_22.html
* https://codeforces.com/blog/entry/10533#comment-159119
