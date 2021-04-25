# Heavy-light decomposition

The heavy-light (H-L) decomposition of a rooted tree is a method of partitioning the vertices of the tree into 
disjoint paths (all vertices have degree two, except the endpoints of a path, with degree one) that gives important 
asymptotic time bounds for certain problems involving trees.

The heavy-light decomposition of a tree T=(V, E) is a coloring of the tree's edges. Each edge is either heavy or light. 

## Motivation

Suppose we are given a tree where each node is having some value, we want to answer queries like the sum of values on nodes on the path from u to v.

We can calculate LCA and find the answer by breaking path(u,v) into path(u, lca) and path(lca, v), now Calc(u,v) = Calc(u, root) + Calc(v, root) - 2 Calc(root, LCA(u,v)).

But say we also have an update query set(v,x) where we are given node v and value x, and we need to update the value of node v to x. Now we can use LCA to answer efficiently.

Say instead of a tree, we just have a chain(set of nodes connected one after another), we can support both calc(u,v) and set(v,x) by using BIT/Segment tree.

![image](https://user-images.githubusercontent.com/19663316/115997295-42735e80-a600-11eb-9d0c-84b492d83964.png)

Key: HLD supports updating the tree node/edge values unlike the LCA sparse array approach, but the tree structure is fixed.

## Basic idea

We will divide the tree into vertex-disjoint chains (meaning no two chains has a node in common) in such a way that to move from any node in the tree to the root node, we will have to change at most log N chains. To put it in other words, if the path from any node to root can be broken into pieces such that each piece belongs to only one chain, then we will have no more than log N pieces.

We already know that queries in each chain can be answered with O(log N) complexity and there are at most log N chains we need to consider per path. So on the whole we have O( log^2 N ) complexity solution.

## What does this decomposition accomplish?

Imagine that you are traveling down the tree, starting at the root. How many times can you use a light edge? Clearly, lg N is an upper bound, because each time you use a light edge the number of vertices in your subtree is at least halved.

We just showed that for any vertex v the path from v to the root only contains at most lg N light edges. Now imagine that as we walk along the path from v to the root, we are keeping track of the important path we are on. This only changes when we use a light edge. And as there are at most lg N light edges on our path, we only change the important path at most lg N times.

Almost the same is true for a path between two arbitrary vertices v and w: Let x be their least common ancestor in the rooted tree. The path from v to w can be split into two paths, v to x and x to w. Each of these two paths only uses edges from at most lg N important paths, hence the entire path from v to w crosses at most 2lg N important paths.

For each heavy path, we will keep an interval tree, hence to answer a query, we first identify the segments of heavy paths it uses. 
This can be done in O(log N). Then we process each segment separately. Processing each segment involves two queries on the interval tree for its important path, hence the total time complexity is O(log 2N) per query.

source: <https://ipsc.ksp.sk/2009/real/solutions/l.html> IPSC 2009 problem L in http://ipsc.ksp.sk/archive

## Two school of thoughts

* For each vertex that isn’t a leaf, find the edge that leads to the child with the largest subtree (breaking ties arbitrarily) and call it heavy.

* To determine which, consider the edge's two endpoints: one is closer to the root, and one is further away. 
  If the size of the subtree rooted at the latter is more than half that of the subtree rooted at the former, the edge is heavy. 
  Otherwise, it is light.


![image](https://user-images.githubusercontent.com/19663316/115995981-24efc600-a5fb-11eb-8722-7233db484cfc.png)

In the first case, we'll have many heavy edges and hence our code will run faster, in the second case we might have not any heavy edges for some trees.

![image](https://user-images.githubusercontent.com/19663316/115997083-6e421480-a5ff-11eb-93f1-42cd4a97a50c.png)

Based on the subtree sizes, mark the edges as heavy, breaking ties arbitrarily.

![image](https://user-images.githubusercontent.com/19663316/115997107-7bf79a00-a5ff-11eb-8fcc-3d46478b2954.png)

Consider some node, if you choose heavy edge and go down, we will have heavy paths. Using these, our tree nodes can be split into heavy paths, along with some single leaf nodes(these can be thought of as paths of size 1).

Now the key idea about this setup is that any path on the tree will pass through at most 𝑂(log n) light edges. By extension, each path also passes through at most 𝑂(log n) vertical chains.

### Proof

One useful idea for the proof of this claim is that you can break any path 𝑢 -> 𝑣 on a tree into two (possibly non-existent) components: the path from 𝑢 up to 𝑙𝑐𝑎(𝑢,𝑣) and the path from 𝑣 up to 𝑙𝑐𝑎(𝑢,𝑣), where 𝑙𝑐𝑎(𝑢,𝑣) is the lowest common ancestor of 𝑢 and 𝑣. Because 𝑙𝑐𝑎(𝑢,𝑣) is an ancestor of both 𝑢 and 𝑣, both of these separate paths will also be vertical chains themselves. So now let's prove that both of these vertical chains only pass through 𝑂(log n) light edges.

Consider some vertex `v` in some vertical chain. Let the size of its subtree be `x` and its parent be `p`. If the edge from `v` to `p` is light, then there must be some other child `u` of `p` with subtree size `y`, where `y ≥ x`. Then when we move up to `p`, the size of `p`'s subtree is at least `x+y ≥ 2x`. So whenever we move up a light edge, the size of our current subtree is at least doubled. Because the size of a subtree can't be more than `n`, we end up moving up a light edge at most 𝑂(log n) times.

### Psuedo code to calculate heavy edges

```python
def go(x):
  sz = 1
  for y in children[x]:
    y_sz = go(y)
    sz += y_sz
    if y_sz > max:
      max = y_sz
      heavy[x] = y
  return sz
```
### Psuedo code for segment trees on chains

Instead of using many small segments trees(one for each chain), we can just use one segment tree.

We first recursively build for the heavy node and then for all other subtrees.

```python
def go2(x):
  p.append(x)
  if not children[x].empty():
    go2(heavy[x])
    for y in children[x]:
      if y!=heavy[x]:
        go2(x)
```

![image](https://user-images.githubusercontent.com/19663316/115999338-f11b9d00-a608-11eb-9c6c-148742a297aa.png)

If you look at array p, it can be breaked into heavy chains segments. For two nodes within a chain, we can directly query segment tree to find the result. Also we can just use one segement tree for the whole graph instead of using one for each heavy chain.

![image](https://user-images.githubusercontent.com/19663316/115999408-363fcf00-a609-11eb-8412-3e89d89d4288.png)


We don't need any special code to calculate LCA, we can leverage HLD code to do it. From each node let's have a pointer to the top node in the heavy path. For node u let's call this top node of chain as top[u]

![image](https://user-images.githubusercontent.com/19663316/115999560-e6153c80-a609-11eb-8a08-f9b03b66f407.png)

```python
while True:
  x = top[u]
  y = top[v]
  if x==y:
    # u and v belong to same heavy chain
    res += sum(u,v) # sum is call to segment tree
    break
  if d[x] > d[y]: # d[x] is depth from the root
    res += sum(u,x)
    u = x.parent
  else:
    res += sum(y,v)
    v = y.parent
```

<details>
  <summary>CPP implementation</summary>
  
```cpp
// root[v] = top[v] the node with lowest depth in the heavy chain containing v

template <class T, int V>
class HeavyLight {
  int parent[V], heavy[V], depth[V];
  int root[V], treePos[V];
  SegmentTree<T> tree;

  template <class G>
  int dfs(const G& graph, int v) {
    int size = 1, maxSubtree = 0;
    for (int u : graph[v]) if (u != parent[v]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      int subtree = dfs(graph, u);
      if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
      size += subtree;
    }
    return size;
  }

  template <class BinaryOperation>
  void processPath(int u, int v, BinaryOperation op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) swap(u, v); // root[u] == root[v], same chain, query in Segtree
    op(treePos[u], treePos[v] + 1);
  }

public:
  template <class G>
  void init(const G& graph) {
    int n = graph.size();
    fill_n(heavy, n, -1);
    parent[0] = -1;
    depth[0] = 0;
    // find heavy chains
    dfs(graph, 0);
    // update top[v]
    for (int i = 0, currentPos = 0; i < n; ++i)
      if (parent[i] == -1 || heavy[parent[i]] != i)
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          treePos[j] = currentPos++;
        }
    tree.init(n);
  }

  void set(int v, const T& value) {
    tree.set(treePos[v], value);
  }

  void modifyPath(int u, int v, const T& value) {
    processPath(u, v, [this, &value](int l, int r) { tree.modify(l, r, value); });
  }

  T queryPath(int u, int v) {
    T res = T();
    processPath(u, v, [this, &res](int l, int r) { res.add(tree.query(l, r)); });
    return res;
  }
};

// source: https://codeforces.com/blog/entry/22072
// https://codeforces.com/contest/484/submission/24715608
```
</details>


*Extra care must be taken in processPath if the binary operation isn't commutative, you'll need two segment trees, one for downward sums and one for upward sums.*

### Adamant's implementation

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

Then you will have array such that subtree of `v` correspond to segment `[in_v; out_v)` and the path from `v` to the last vertex in ascending heavy path from `v` (which is `nxt_v`) will be `[in_nxt_v; in_v]` subsegment which gives you the opportunity to process queries on pathes and subtrees simultaneously in the same segment tree.

With the above implementation we can solve the following problem: given a tree on n vertices and q queries of form 1) add x to all numbers in the subtree 2) add x to all numbers on the path 3) find maximum number in the subtree 4) find maximum number on the path, answer all queries in O((n + q)log^2n) because batch updates may be performed over subtrees and arbitrary paths across the tree simultaneously using the single segment tree built across the traversal of the tree.

source: https://codeforces.com/blog/entry/53170

### Benq's complete implementation

<details>
	<summary> Benq's cpp implementation </summary>
	
```cpp
// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

/**
 * Description: 1D range increment and sum query.
 * Source: USACO Counting Haybales
 * Verification: SPOJ Horrible
 */

template<class T, int SZ> struct LazySeg { 
	static_assert(pct(SZ) == 1); // SZ must be power of 2
	const T ID = 0; T comb(T a, T b) { return a+b; }
	T seg[2*SZ], lazy[2*SZ]; 
	LazySeg() { F0R(i,2*SZ) seg[i] = lazy[i] = ID; }
	void push(int ind, int L, int R) { /// modify values for current node
		seg[ind] += (R-L+1)*lazy[ind]; // dependent on operation
		if (L != R) F0R(i,2) lazy[2*ind+i] += lazy[ind]; /// prop to children
		lazy[ind] = 0; 
	} // recalc values for current node
	void pull(int ind) { seg[ind] = comb(seg[2*ind],seg[2*ind+1]); }
	void build() { ROF(i,1,SZ) pull(i); }
	void upd(int lo,int hi,T inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=SZ-1) {
		push(ind,L,R); if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2; 
		return comb(query(lo,hi,2*ind,L,M),query(lo,hi,2*ind+1,M+1,R));
	}
};

/**
 * Description: Heavy-Light Decomposition, add val to verts 
 	* and query sum in path/subtree.
 * Time: any tree path is split into $O(\log N)$ parts
 * Source: http://codeforces.com/blog/entry/22072, https://codeforces.com/blog/entry/53170
 * Verification: *
 */

template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N; vi adj[SZ];
	int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
	int pos[SZ]; vi rpos; // rpos not used, but could be useful
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfsSz(int x) { 
		sz[x] = 1; 
		each(y,adj[x]) {
			par[y] = x; depth[y] = depth[x]+1;
			adj[y].erase(find(all(adj[y]),x)); // remove parent from adj list
			dfsSz(y); sz[x] += sz[y];
			if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
		}
	}
	void dfsHld(int x) {
		pos[x] = ti++; rpos.pb(x);
		each(y,adj[x]) {
			root[y] = (y == adj[x][0] ? root[x] : y);
			dfsHld(y); }
	}
	void init(int _N, int R = 0) { N = _N; 
		par[R] = depth[R] = ti = 0; dfsSz(R); 
		root[R] = R; dfsHld(R); 
	}
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
		return depth[x] < depth[y] ? x : y;
	}
	/// int dist(int x, int y) { // # edges on path
	/// 	return depth[x]+depth[y]-2*depth[lca(x,y)]; }
	LazySeg<ll,SZ> tree; // segtree for sum
	template <class BinaryOp>
	void processPath(int x, int y, BinaryOp op) {
		for (; root[x] != root[y]; y = par[root[y]]) {
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
			op(pos[root[y]],pos[y]); }
		if (depth[x] > depth[y]) swap(x,y);
		op(pos[x]+VALS_IN_EDGES,pos[y]); 
	}
	void modifyPath(int x, int y, int v) { 
		processPath(x,y,[this,&v](int l, int r) { 
			tree.upd(l,r,v); }); }
	ll queryPath(int x, int y) { 
		ll res = 0; processPath(x,y,[this,&res](int l, int r) { 
			res += tree.query(l,r); });
		return res; }
	void modifySubtree(int x, int v) { 
		tree.upd(pos[x]+VALS_IN_EDGES,pos[x]+sz[x]-1,v); }
};
```

source: <https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h>, <https://usaco.guide/plat/hld?lang=cpp>

</details>

<details>
	<summary> Problem: 1553. Caves and Tunnels </summary>
	
Problem: <https://acm.timus.ru/problem.aspx?space=1&num=1553>

source: https://codeforces.com/blog/entry/12239, https://ideone.com/KgO3Kj

```cpp
#pragma comment(linker,"/STACK:100000000000,100000000000")

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#include <queue>
#include <map>
#include <functional>
#include <list>
#include <sstream>
#include <ctime>
#include <climits>
#include <bitset>
#include <list>
#include <cassert>
#include <complex>

using namespace std;

/* Constants begin */
const long long inf = 1e18+7;
const long long mod = 1e9+7;
const double eps = 1e-9;
const double PI = 2*acos(0.0);
const double E = 2.71828;
/* Constants end */

/* Defines begin */
#define pb push_back
#define mp make_pair
#define ll long long
#define double long double
#define F first
#define S second
#define all(a) (a).begin(),(a).end()
#define forn(i,n) for (int (i)=0;(i)<(ll)(n);(i)++)
#define random (rand()<<16|rand())
#define sqr(x) (x)*(x)
#define base complex<double>
/* Defines end */

int n, m;
vector<int> g[100005];
int val[100005];
int nxt[100005], size[100005], p[100005], chain[100005], num[100005], csz[100005], top[100005], all, cnt = 1, depth[100005];
ll t[400005], mx[400005];

// segment tree update
void upd(int v, int tl, int tr, int pos, int d){
  if(tl == tr){
    t[v] += d;
    return;
  }
  int tm = (tl + tr) >> 1;
  if(pos <= tm) upd(v + v, tl, tm, pos, d); else
    upd(v + v + 1, tm + 1, tr, pos, d);
  t[v] = max(t[v + v], t[v + v + 1]);
}

// segment tree get
ll go(int v, int tl, int tr, int l, int r){
  if(l > tr || r < tl){
    return 0;
  }
  if(l <= tl && r >= tr){
    return t[v];
  }
  int tm = (tl + tr) >> 1;
  return max(go(v + v, tl, tm, l, r), go(v + v + 1, tm + 1, tr, l, r));
}

// dfs to computer heavy chains using size
void dfs(int v, int pr = 0){
  p[v] = pr;
  size[v] = 1;
  forn(i, g[v].size()){
    int to = g[v][i];
    if(to == pr){
      continue;
    }
    depth[to] = depth[v] + 1;
    dfs(to, v);
    size[v] += size[to];
    if(nxt[v] == -1 || size[to] > size[nxt[v]]){
      nxt[v] = to;
    }
  }
}

// dfs to compute decompostion
void hld(int v, int pr = -1){
  chain[v] = cnt - 1;
  num[v] = all++;
  if(!csz[cnt - 1]){
    top[cnt - 1] = v;
  }
  ++csz[cnt - 1];
  if(nxt[v] != -1){
    hld(nxt[v], v);
  }
  forn(i, g[v].size()){
    int to = g[v][i];
    if(to == pr || to == nxt[v]){
      continue;
    }
    ++cnt;
    hld(to, v);
  }
}

// computing result on some path
ll go(int a, int b){
  ll res = 0;
  while(chain[a] != chain[b]){
    if(depth[top[chain[a]]] < depth[top[chain[b]]]) swap(a, b);
    int start = top[chain[a]];
    if(num[a] == num[start] + csz[chain[a]] - 1)
      res = max(res, mx[chain[a]]);
    else
      res = max(res, go(1, 0, n - 1, num[start], num[a]));
    a = p[start];
  }
  if(depth[a] > depth[b]) swap(a, b);
  res = max(res, go(1, 0, n - 1, num[a], num[b]));
  return res;
}

void modify(int a, int b){
  upd(1, 0, n - 1, num[a], b);
  int start = num[top[chain[a]]];
  int end = start + csz[chain[a]] - 1;
  mx[chain[a]] = go(1, 0, n - 1, start, end);
}

int main(void) {
  #ifdef nobik
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
  #endif
  scanf("%d", &n);
  forn(i, n - 1){
    int a, b; scanf("%d %d", &a, &b); --a; --b;
    g[a].pb(b); g[b].pb(a);
  }
  memset(nxt, -1, sizeof nxt);
  dfs(0);
  hld(0);
  scanf("%d", &m);
  forn(i, m){
    char c;
    scanf(" %c", &c);
    if(c == 'G'){
      int a, b; scanf("%d %d", &a, &b); --a; --b;
      printf("%lld\n", go(a, b));
    } else {
      int a, b; scanf("%d %d", &a, &b); --a;
      modify(a, b);
    }
  }
  return 0;
}
```
</details>

## REF

* <https://blog.anudeep2011.com/heavy-light-decomposition/>
* <https://codeforces.com/blog/entry/81317>
* <https://codeforces.com/blog/entry/22072>
* https://codeforces.com/blog/entry/12239
* <https://apps.topcoder.com/forums/?module=Thread&threadID=796128&start=0&mc=8>
