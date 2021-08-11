# RANGE MINIMUM QUERY AND LOWEST COMMON ANCESTOR

The term range minimum/maximum query (RMQ) comprises all variations of the problem of finding the smallest element (or the position of the smallest element) in a contiguous subsequence of a list of items taken from a totally ordered set (usually numbers).

We have seen that Segment Tree data structure can be used to solve the Range Minimum Query (RMQ) problem—the problem of finding the index that has the
minimum element within a range `[i..j]` of the underlying array A. It takes O(n) preprocessing time to build the Segment Tree, and once the Segment Tree is ready, each RMQ is just O(log n). With Segment Tree, we can deal with the dynamic version of this RMQ problem, i.e. when the underlying array is updated, we usually only need `O(log n)` to update the corresponding Segment Tree structure.

However, some problems involving RMQ never change the underlying array A after the first query. This is called the static RMQ problem. Although Segment Tree obviously can be used to deal with the static RMQ problem, this static version has an alternative DP solution with `O(n log n)` pre-processing time and `O(1)` per RMQ.

## SPARSE TABLE (ST) ALGORITHM

The approach here is to preprocess RMQ for sub arrays of length `2^k` using dynamic programming. We will keep an array `M[0, N-1][0, logN]` where `M[i][j]` is the index of the minimum value in the sub array starting at `i` having length `2^j`. Here is an example:

![image](https://user-images.githubusercontent.com/19663316/115985129-04f2df00-a5c8-11eb-845c-af1d614d56c6.png)

For computing `M[i][j]` we must search for the minimum value in the first and second half of the interval. It’s obvious that the small pieces have `2^(j-1)` length, so the recurrence is:

![image](https://user-images.githubusercontent.com/19663316/115985155-2653cb00-a5c8-11eb-979a-4a406fe35abd.png)

The preprocessing function will look something like this:

```cpp
void process2(int M[MAXN][LOGMAXN], int A[MAXN], int N) {
    int i, j;

    //initialize M for the intervals with length 1
    for (i = 0; i < N; i++)
      M[i][0] = i;
    //compute values from smaller to bigger intervals
    for (j = 1; 1 << j <= N; j++)
      for (i = 0; i + (1 << j) - 1 < N; i++)
        if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = M[i + (1 << (j - 1))][j - 1];
}
```
  
Once we have these values preprocessed, let’s show how we can use them to calculate `RMQ A(i, j)`. The idea is to select two blocks that entirely cover the interval `[i…j]` and find the minimum between them. Let `k = [log(j - i + 1)]`. For computing `RMQ A(i, j)` we can use the following formula:

![image](https://user-images.githubusercontent.com/19663316/115985212-65821c00-a5c8-11eb-9535-c8186fd8d481.png)

Each algorithm has complexities  `< O(f(n)), O(g(n)) >`, it means that this algorithm's preprocess is `O(f(n))` and answering a query is `O(g(n))`.

So, the overall complexity of the algorithm is `<Preprocessing, Query> = <O(N logN), O(1)>`. 

source: <https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor>

### Implementation

#### Baba's implementation
Cache-friendly traversal
```cpp
const int N = int(1e5)+10;
const int LOGN = 20;
int A[N],msb[N],DP[LOGN][N];
LL dp[N],dp2[N];
int MX(int l,int r){
	int d = msb[r-l+1];
	int L = DP[d][l];
	int R = DP[d][r-(1<<d)+1];
	int mx = (A[L]>A[R]?L:R);
  return mx;
}

{	// inside main
	//RMQ PRE-PROCESSING
	for(int i=1;i<=n;i++)
		DP[0][i]=i;
	for(int i=1;i<LOGN;i++)
		for(int j=1;j<=n;j++)
		{
			int l = DP[i-1][j], r=DP[i-1][min(n,j+(1<<(i-1)))];
			if(A[l]>A[r])
				DP[i][j] = l;
			else
				DP[i][j] = r;
		}
	// calculating most significant bit
	for(int i=1,x=0;i<N;i++)
		if((1<<(x+1)<=i))
			msb[i]=(++x);
		else
			msb[i]=x;
}
```

source: Baba <https://codeforces.com/contest/675/submission/17946839>

#### Benq's implementation
Description: 1D range minimum query. Can also do queries for any associative operation in $O(1)$ with D\&C
Source: KACTL
 * Verification: 
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N logN)
 * Time: O(1)


```cpp
template<class T> struct RMQ { // floor(log_2(x))
    int level(int x) { return 31-__builtin_clz(x); } 
    vector<T> v; vector<vi> jmp;
    int comb(int a, int b) { // index of min
        return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
    void init(const vector<T>& _v) {
        v = _v; jmp = {vector<int>(v.size())}; iota(jmp[0].begin(), jmp[0].end(),0);
        for (int j = 1; 1<<j <= v.size(); ++j) {
            jmp.push_back(vi(v.size()-(1<<j)+1));
            for(int i=0; i<jmp[j].size(); i++)
                jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i+(1<<(j-1))]);
        }
    }
    int index(int l, int r) { // get index of min element
        assert(l <= r); int d = level(r-l+1);
        return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
    T query(int l, int r) { return v[index(l,r)]; }
};

int main() {
    int n, q; scanf("%d %d", &n, &q);
    vector<int> V(n);
    for(int i=0;i<n;i++) scanf("%d", &V[i]);
    RMQ<int> t;
    t.init(V);
    while(q--){
        int a, b; scanf("%d %d", &a, &b);
        a--; b--;
	// 0-based indexing
        printf("%d\n", t.query(a, b));
    }
    return 0;
}
```

source: <https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Static%20Range%20Queries%20(9.1)/RMQ%20(9.1).h>


```cpp
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int inf = 1e9+10;
const ll inf_ll = 1e18+10;
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define cmax(x, y) (x = max(x, y))
#define cmin(x, y) (x = min(x, y))
 
template<typename it, typename bin_op>
struct sparse_table {
 
    using T = typename remove_reference<decltype(*declval<it>())>::type;
    vector<vector<T>> t; bin_op f;
 
    sparse_table(it first, it last, bin_op op) : t(1), f(op) {
        int n = distance(first, last);
        t.assign(32-__builtin_clz(n), vector<T>(n));
        t[0].assign(first, last);
        for (int i = 1; i < t.size(); i++)
            for (int j = 0; j < n-(1<<i)+1; j++)
                t[i][j] = f(t[i-1][j], t[i-1][j+(1<<(i-1))]);
    }
 
    // returns f(a[l..r]) in O(1) time
    T query(int l, int r) {
        int h = floor(log2(r-l+1));
        return f(t[h][l], t[h][r-(1<<h)+1]);
    }
};
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n), d(n-1);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n-1; i++)
            d[i] = abs(a[i+1]-a[i]);
        sparse_table g(all(d), [](ll x, ll y){
            return __gcd(x, y);
        });
        int j = 0, ans = 1;
        for (int i = 0; i < n-1; i++) {
            while (j <= i && g.query(j, i) == 1) j++;
            cmax(ans, i-j+2);
        }
        cout << ans << "\n";
    }
}
```

source: emorgan5289 CF #736 Div 2 D Solution https://codeforces.com/blog/entry/92335 

## Lowest Common Ancestor

Given a rooted tree T and two nodes u and v, find the furthest node from the root that is an ancestor for both u and v. Here is an example (the root of the tree will be node 1 for all examples in this editorial):

![image](https://user-images.githubusercontent.com/19663316/115987367-628c2900-a5d2-11eb-8816-e66d0710ec19.png)

### Warm-up, a slow algorithm

To get warmed up, let's start with a naive algorithm for computing LCAs. It seems pretty straightforward that we could simply walk up the tree from `u` and `v`
 until the two meet, then we are at the LCA. For instance, say we preprocess the tree and compute the level (distance from the root) of each vertex using a depth-first search, then we simply iterate by moving the lower vertex up one until the two meet.

```cpp
// Precomputes levels
function precompute() {
  dfs(root, 0)
}

// Traverse the tree downwards from the vertex v
// Mark each vertex with its "level", i.e. its
// distance from the root
function dfs(v, lvl) {
  level[v] = lvl
  for (each child u of v) {
    dfs(u, lvl+1)
  }
}

// Compute the LCA of u and v
function lca(u, v) {
  while (u != v) {
    if (level[u] > level[v]) {
      u = parent[u]
    } else {
      v = parent[v]
    }
  }
  return u
}
```

This algorithm will compute the LCA of the vertices `u` , `v` after `O(n)` preprocessing to compute the levels. However, this algorithm will be really slow if the tree is very deep, because it may have to climb from the bottom of the tree all the way to the top. The complexity of a query is therefore `O(h)`, where `h` is the height of the tree, which can be `O(n)` in the worst case. To be faster, we will need a smarter algoriithm.

### Binary lifting, a faster algorithm

The binary lifting technique (a fast algorithm): The naive algorithm was slow because it could have to walk from the bottom to the top of a very tall tree. To overcome this, we will use the technique of binary lifting. The idea at its core is quite simple. At each vertex of the tree, instead of only knowing who the parent is, we also remember who the 2nd, 4th, 8th, ... ancestors are. We call these the binary ancestors of the vertex. This means that each vertex remembers `O( log n)` of its ancestors, so we pay `O(n log n)` space, but it will be worth it. We can compute the binary ancestors in our preprocessing step with a depth-first search. The key observation that makes binary ancestors easy to compute is the following: The `k-th` binary ancestor of a vertex is the `(k-1)`th binary ancestor of its `(k-1)`th binary ancestor We can use this fact to precompute all of the binary ancestors of all vertices in `O (n log n)` time, as follows.

```cpp
// Preprocess and compute binary ancestors
function preprocess() {
  for (each vertex v in the tree) {
    ancestor[v][0] = parent[v]
    for (k = 1 to log(n)) {
      ancestor[v][k] = -1
    }
  }
  dfs(root, 0)
  for (k = 1 to log(n)) {
    for (each vertex v in the tree) {
      if (ancestor[i][k-1] != -1) {      
        ancestor[i][k] = ancestor[ancestor[i][k-1]][k-1]
    }
  }
}

// Traverse the tree downwards from the vertex v
// Mark each vertex with its "level", i.e. its
// distance from the root
function dfs(v, lvl) {
  level[v] = lvl
  for (each child u of v) {
    dfs(u, lvl+1)
  }
}
```

LCA code
```cpp
// Compute the LCA of u and v using binary lifting
function lca(u, v) {
  if (level[u] > level[v]) swap(u, v)
  for (k = log(n) - 1 to 0) {
    if (level[v] - pow(2, k) >= level[u]) {
      v = ancestor[v][k]
    }
  }
  if (u == v) {
    return u
  }
  for (k = log(n) - 1 to 0) {
    if (ancestor[v][k] != ancestor[u][k]) {
      u = ancestor[u][k]
      v = ancestor[v][k]
    }
  }
  return parent[u]
}
```

source: https://contest.cs.cmu.edu/295/s20/tutorials/lca.mark

### DP solution

First, let’s compute a table `P[1,N][1,logN]` where `P[i][j]` is the `2^j`-th ancestor of `i`. For computing this value we may use the following recursion:

![image](https://user-images.githubusercontent.com/19663316/115987414-abdc7880-a5d2-11eb-94ef-dee27711f953.png)

The preprocessing function should look like this:

```cpp
void process3(int N, int T[MAXN], int P[MAXN][LOGMAXN]) {
   int i, j;

   //we initialize every element in P with -1
   for (i = 0; i < N; i++)
     for (j = 0; 1 << j < N; j++)
       P[i][j] = -1;

   //the first ancestor of every node i is T[i]
   for (i = 0; i < N; i++)
     P[i][0] = T[i];

   //bottom up dynamic programing
   for (j = 1; 1 << j < N; j++)
     for (i = 0; i < N; i++)
       if (P[i][j - 1] != -1)
         P[i][j] = P[P[i][j - 1]][j - 1];
 }
 ```
 
This takes O(N logN) time and space. Now let’s see how we can make queries. Let L[i] be the level of node i in the tree. We must observe that if p and q are on the same level in the tree we can compute LCA(p, q) using a meta-binary search. So, for every power j of 2 (between log(L[p]) and 0, in descending order), if P[p][j] != P[q][j] then we know that LCA(p, q) is on a higher level and we will continue searching for LCA(p = P[p][j], q = P[q][j]). At the end, both p and q will have the same father, so return T[p]. Let’s see what happens if L[p] != L[q]. Assume, without loss of generality, that L[p] < L[q]. We can use the same meta-binary search for finding the ancestor of p situated on the same level with q, and then we can compute the LCA as described below. Here is how the query function should look:

```cpp
int query(int N, int P[MAXN][LOGMAXN], int T[MAXN], int L[MAXN], int p, int q) {
  int tmp, log, i;

  //if p is situated on a higher level than q then we swap them
  if (L[p] < L[q])
    tmp = p, p = q, q = tmp;

  //we compute the value of [log(L[p)]
  for (log = 1; 1 << log <= L[p]; log++);
  log–-;

  //we find the ancestor of node p situated on the same level
  //with q using the values in P
  for (i = log; i >= 0; i–-)
    if (L[p] - (1 << i) >= L[q])
      p = P[p][i];

  if (p == q)
    return p;

  //we compute LCA(p, q) using the values in P
  for (i = log; i >= 0; i–)
    if (P[p][i] != -1 && P[p][i] != P[q][i])
      p = P[p][i], q = P[q][i];

  return T[p];
}
```

Now, we can see that this function makes at most 2 * log(H) operations, where H is the height of the tree. In the worst case H = N, so the overall complexity of this algorithm is <O(N logN), O(logN)>. This solution is easy to code too, and it’s faster than the previous one.

#### Binary lifting KACTL

Binary Lifting is a dynamic programming approach where we pre-compute an array `jmp[1, n][1, log(n)]` where `jmp[i][j]` contains `2^j`-th ancestor of node `i`. For computing the values of jmp[][], the `2^j`-th ancestor of `i` can be thought of as `2^(j-1)`th ancestor of `(2^(j-1)`th ancestor of `i`), 
hence the following recursion may be used 

	jmp[i][j] = parent[i] if j = 0 and 
	jmp[i][j] = jmp[jmp[i][j – 1]][j – 1] if j > 0. 

```cpp
/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]); // find ancestor of a which is at same depth as b
	if (a == b) return a;
	for (int i = sz(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}


// Usage
void getPars(vector<vi> &tree, int cur, int p, int d, vector<int> &par, vector<int> &depth) {
    par[cur] = p;
    depth[cur] = d;
    for(auto i: tree[cur]) if (i != p) {
        getPars(tree, i, cur, d+1, par, depth);
    }
}
 	vector<int> par(n), depth(n);
        getPars(tree, 0, 0, 0, par, depth);
        vector<vi> tbl = treeJump(par);
	int binLca = lca(tbl, depth, a, b);
```

### Applications of LCA

A common and useful application of LCA queries is for computing distances between vertices in trees. Suppose we have a weighted tree, i.e. the edges of the tree have weights, and we want to compute the lengths of paths between pairs of vertices. First, we solve an easier problem -- given a rooted, weighted tree, let's try to compute the lengths of paths from the root to any given vertex. This is much easier, we can simply perform a single depth-first search and aggregate the total weight of each path.

```cpp
// Compute the weights of all root-to-vertex paths
function compute_path_weights() {
  dfs(root, 0)
}

function dfs(v, dist) {
  distance[v] = dist
  for (each child u of v) {
    dfs(u, dist + w(u,v))
  }
}
```

This will compute `distance[v]` for all vertices. We can now extend this to work for arbitrary paths in the tree. First, if our our tree is not already rooted, we can pick an aribtrary root, and perform the preprocessing step above to compute all root-to-vertex path lengths. Then, to compute the length of the path from `u` to `v`, we just notice that it is equal to 

	δ ( u , v ) = distance [ u ] + distance [ v ] − 2 × distance [ L C A ( u , v ) ] .
	
#### SPOJ QTREE2

You are given a tree (an undirected acyclic connected graph) with `N (2 ≤ N ≤ 10^4)` nodes, and edges numbered `1, 2, 3...N-1`. Each edge has an integer value assigned to it, representing its length.

We will ask you to perfrom some instructions of the following form:

* `DIST a b` : ask for the distance between node a and node b (or)
* `KTH a b k` : ask for the k-th node on the path from node a to node b

<details>
	<summary>CPP solution</summary>
	
```cpp
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a,b) memset(a,b,sizeof(a))

vector<vii> Adj;
int n;
 
const int nax = 10004;
const int L = 15;
 
int depth[nax], par[nax][L], h[nax];
 
void dfs(int u, int p){
    if(p == -1){
        depth[u] = 0;
        h[u] = 0;
        par[u][0] = -1;
    }
    for(ii x:Adj[u]){
        int v = x.F, c = x.S;
        if(v == p) continue;
        depth[v] = depth[u] + c;
        h[v] = h[u] + 1;
        par[v][0] = u;
        for(int k = 1; k < L; k++){
            int w = par[v][k - 1];
            if(w == -1) break;
            par[v][k] = par[w][k-1];
        }
        dfs(v, u);
    }
}
 
int up(int v, int dh){
    for(int k = L-1; k >= 0; k--){
        if(dh < ( 1 << k)) continue;
        v = par[v][k];
        dh -= (1 << k);
    }
    return v;
}
 
int LCA(int u, int v){
    if(h[v] > h[u]) swap(u,v);
    // v is at higher node
    u = up(u, h[u] - h[v]);
    if(v == u) return v;
    for(int k = L-1; k >= 0; k--){
        if(par[v][k] != par[u][k]){
            v = par[v][k];
            u = par[u][k];
        }
    }
    return par[v][0];
}
 
void solve(){
    scanf("%d", &n);
    Adj = vector<vii>(n, vii());
    for(int i = 0; i < n-1; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;b--;
        Adj[a].push_back(ii(b, c));
        Adj[b].push_back(ii(a, c));
    }
    SET(par, -1);
    SET(h, 0);
    SET(depth, 0);
    dfs(0, -1);
    int a, b, k, ans, d, l;
    while(true){
        char c[10];
        scanf("%s", c);
        if(c[1] == 'O') return;
        scanf("%d %d", &a, &b);
        a--;b--;
        l = LCA(a,b);
        if(c[1] == 'I'){
            d = depth[a] + depth[b] - 2*depth[l];
            printf("%d\n", d);
        }else{
            scanf("%d", &k);
            k--;
            if(k <= h[a] - h[l]){
                ans = up(a, k);
                printf("%d\n", ans + 1);
            }else{
                k -= (h[a] - h[l]);
                int bh = (h[b] - h[l]);
                ans = up(b, bh - k);
                printf("%d\n", ans + 1);
            }
        }
    }
}
 
int main(){
    int TC;
    scanf("%d", &TC);
    while(TC--){
        solve();
        printf("\n");
    }
    return 0;
}
```
</details>	

## Reduction from LCA to RMQ

Now, let’s show how we can use RMQ for computing LCA queries. Actually, we will reduce the LCA problem to RMQ in linear time, so every algorithm that solves the RMQ problem will solve the LCA problem too. Let’s show how this reduction can be done using an example:

![image](https://user-images.githubusercontent.com/19663316/115987711-da0e8800-a5d3-11eb-99f3-cbee9518fa7d.png)

![image](https://user-images.githubusercontent.com/19663316/115987721-e266c300-a5d3-11eb-96b2-1b02eca1fe2f.png)

Notice that LCAT(u, v) is the closest node from the root encountered between the visits of u and v during a depth first search of T. So, we can consider all nodes between any two indices of u and v in the Euler Tour of the tree and then find the node situated on the smallest level between them. For this, we must build three arrays:

E[1, 2*N-1] – the nodes visited in an Euler Tour of T; E[i] is the label of i-th visited node in the tour

L[1, 2*N-1] – the levels of the nodes visited in the Euler Tour; L[i] is the level of node E[i]
H[1, N] – H[i] is the index of the first occurrence of node i in E (any occurrence would be good, so it’s not bad if we consider the first one)


Assume that H[u] < H[v] (otherwise you must swap u and v). It’s easy to see that the nodes between the first occurrence of u and the first occurrence of v are E[H[u]…H[v]]. Now, we must find the node situated on the smallest level. For this, we can use RMQ. So, LCAT(u, v) = E[RMQL(H[u], H[v])] (remember that RMQ returns the index). Here is how E, L and H should look for the example:

![image](https://user-images.githubusercontent.com/19663316/115987737-ed215800-a5d3-11eb-80f5-d17a038a2543.png)

*Notice that consecutive elements in L differ by exactly 1.*

### CF blog

One of standard ways to implement constant-time LCA queries on a tree is to preprocess it by doing an Eulerian tour which creates an array of pairs (depth, index) for subsequent vertices visited on the tour, and then reduce an LCA query to RMQ query on a certain fragment of this array:

```cpp
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,n) for(int i=(a);i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N = 1<<LOGN;
typedef pair<int,int> pii;
int n, T;
vector<int> adj[N];  // adjacency lists
pii euler[2*N];  // Eulerian tour of pairs (depth, index)
int tin[N];  // visit times for vertices

void dfs(int v, int par, int depth) {
  tin[v] = T;
  euler[T++] = make_pair(depth, v);
  FORE(i,adj[v]) if (*i != par) {
    dfs(*i, v, depth+1);
    euler[T++] = make_pair(depth, v);
  }
}

dfs(0, -1, 0);

int lca(int u, int v) {
  return query_rmq(min(tin[u], tin[v]), max(tin[u], tin[v]) + 1).second;
}
```

The RMQ problem can be solved with a sparse table, which after 𝑂(𝑛log𝑛) preprocessing allows to answer RMQ queries in constant time:

```cpp
pii sparse[LOGN][N];
int log[2*N];  // binary logarithm

void init_rmq() {
  REP(i,T) { sparse[0][i] = euler[i]; }
  int logT = 0;
  while ((1<<logT) < T) { ++logT; }
  REP(f,logT) REP(i,T - (1<<f)) {
    sparse[f+1][i] = min(sparse[f][i], sparse[f][i + (1<<f)]);
  }
  log[0] = -1;
  FOR(i,1,T) { log[i] = 1 + log[i>>1]; }
}

pii query_rmq(int a, int b) {
  // query range [a, b)
  int f = log[b-a];
  return min(sparse[f][a], sparse[f][b - (1<<f)]);
}
```

The drawback of the solution above is long preprocessing. We can reduce it to 𝑂(𝑛) by using clever trick: we split the array into blocks of length 𝑚 and produce sparse table for array of size 𝑂(𝑛/𝑚) created by taking minimum from each block. Then every query range either is an infix of some block or consists of several consecutive full blocks (which are handled by the new sparse table in constant time) and some prefix and some suffix of a block (which are also infixes).

Queries for infixes of blocks are preprocessed brutally: since the RMQ problem obtained from LCA has a property that differences between consecutive depths in the array are either +1 or -1, we can represent each block as the first element plus a binary string of length 𝑚−1 encoding the changes in depths. Thus there are 2^(𝑚−1) different bitmasks and for each of them we have 𝑂(𝑚^2) infixes. For each infix we want to calculate the minimum value relative to the first element. It's easy to show how to preprocess them in 𝑂(2^𝑚.𝑚^2) time and memory, and if we take 𝑚=(log𝑛)/2, this is actually 𝑂(𝑛).

Conceptually this idea is quite easy, but in terms of implementation it could be rather lengthy ([see e-maxx implementation](https://cp-algorithms.com/graph/lca_farachcoltonbender.html)). Now I will present my alternative approach to this problem, which results in a slightly shorter code.

source: <https://codeforces.com/blog/entry/67138>, <https://codeforces.com/contest/986/submission/38947175>

KACTL: <https://codeforces.com/contest/1304/submission/71134293> , <https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h>

### Counting Descendants

We have a rooted tree with `N` vertices, numbered `1, 2, …, N`. Vertex `1` is the root, and the parent of Vertex `i ( 2 ≤ i ≤ N )` is Vertex `Pi` . You are given `Q` queries. In the `i`-th query `( 1 ≤ i ≤ Q )`, given integers `Ui` and `Di`, find the number of vertices u that satisfy all of the following conditions: 
* Vertex `Ui` is in the shortest path from `u` to the root (including the endpoints). 
* There are exactly `Di` edges in the shortest path from `u` to the root.

**Solution**

For first condition to satisfy, `Ui` has to be on the path from `1` to `u`. For the second condition to satisfy, `u` has to be at `depth[Di]` assumming that `depth[root] = 0`. So we need to find all the children in the subtree rooted at `Ui` whose `depth[Di] = Ui`.

Perform a Depth-First search (DFS) from the root and record the timestamp when entering a vertex, `in_u` , and when exitting a vertex, `out_u`. For the Sample Input, it will be as follows:

![image](https://user-images.githubusercontent.com/19663316/119229614-80e43680-bb36-11eb-8baf-d1f57be5f408.png)
![image](https://user-images.githubusercontent.com/19663316/119229276-d15a9480-bb34-11eb-8543-5280d51b9046.png)

Here, the following property is important:
* `x` is a descendant of `y` <=> `in_y ≤ in_x < out_y`.

Here, `x` is said to be a descendant of y if and only if the shortest path from the root to `x` contains `y`.

That “`x` is a descendant of `y` <=> `in_y ≤ in_x < out_y`” is obvious by the progression of DFS; if `x` is a descendant of `y` , then it enters `x` after entering `y` , and exits `x` before exiting `y`. Therefore, it is sufficient to show “`in_y ≤ in_x < out_y => x is a descendant of y`”.

We will show the contraposition. Assume that `x` is not a descendant of `y`. If `y` is a descendant of `x`, then `in_x ≤ in_y < out_x`, and since `x ≠ y`, `in_x ≠ in_y`, so we can see that “it does not hold that `in_y ≤ in_x < out_y`.” Now we also assume that `y` is not a descendant of `x`.

Let `z` be the lowest common ancestor (LCA) of `x` and `y`. By the assumption, `x ≠ z` and `y ≠ z`.

Let `c_x` be a child of `z` such that its subtree contains `x`, and let us define `c_y` similarly. Here, `c_x ≠ c_y`; if `c_x = c_y`, it contradicts to the fact `z` is the LCA.

![image](https://user-images.githubusercontent.com/19663316/119229406-91e07800-bb35-11eb-9624-f575be93dde4.png)

Considering the progression of the DFS, we can see that one of the following holds:
* `in_c_x < out_c_x < in_c_y < out_c_y`
* `in_c_y < out_c_y < in_c_x < out_c_x`

In any case, `[ in_x , out_x ]` and `[ in_y , out_y ]` have nothing in common, since `x` is a descendant of `c_x` and `y` is a descendant of `c_y`. Therefore, we have shown that it does not hold that `in_y ≤ in_x < out_y`.

The proof above can be understood intuitively by considering the rooted tree as a parenthesis sequence.

This problem can be solved easily by applying the property we proved. For each depth, record the values of `in` of vertices of that depth. For a query `(U , D)` , it is sufficient to answer the number of such elements associated with depth `D` that is more than or equal to `in_U`, and less than `out_U`. This can be accomplished by binary search. In C++, we can use a function such as `std::lower_bound`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> children, list;
std::vector<int> in, out, depth;
int timer;

void dfs(const int u) {
    in[u] = timer++;
    list[depth[u]].push_back(in[u]);
    for (const int v : children[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
    }
    out[u] = timer++;
}

int main() {
    int N;
    std::cin >> N;
    children = list = std::vector<std::vector<int>>(N);
    in = out = depth = std::vector<int>(N);
    for (int i = 1; i < N; ++i) {
        int p;
        std::cin >> p;
        children[p - 1].push_back(i);
    }
    dfs(0);
    int Q;
    std::cin >> Q;
    while (Q--) {
        int u, d;
        std::cin >> u >> d;
        u -= 1;
        const auto& v = list[d];
        std::cout << std::lower_bound(v.cbegin(), v.cend(), out[u]) - std::lower_bound(v.cbegin(), v.cend(), in[u]) << '\n';
    }
    return 0;
}
```

## LCA - Tarjan's Offline Algorithm

We assume that all queries are known in advance, and we therefore answer the queries in any order we like. The algorithm answers all queries with one DFS traversal of the tree. Namely a query `(u,v)` is answered at node `u`, if node `v` has already been visited previously, or vice versa.

So let's assume we are currently at node `v`, we have already made recursive DFS calls, and also already visited the second node `u` from the query `(u,v)`. Let's learn how to find the LCA of these two nodes. Note that `LCA(u,v)` is either the node `v` or one of its ancestors. So we need to find the lowest node among the ancestors of `v` (including `v`), for which the node `u` is a descendant. Also note that for a fixed `v` the visited nodes of the tree split into a set of disjoint sets. Each ancestor `p` of node `v` has his own set containing this node and all subtrees with roots in those of its children who are not part of the path from `v` to the root of the tree. The set which contains the node `u` determines the `LCA(u,v)`: the LCA is the representative of the set, namely the node on lies on the path between v and the root of the tree.

![image](https://user-images.githubusercontent.com/19663316/119238097-1d6dff00-bb5e-11eb-9be7-c47e1283b2f1.png)

```cpp
vector<vector<int>> adj;
vector<vector<int>> queries;
vector<int> ancestor;
vector<bool> visited;

void dfs(int v)
{
    visited[v] = true;
    ancestor[v] = v;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
            union_sets(v, u);
            ancestor[find_set(v)] = v;
        }
    }
    for (int other_node : queries[v]) {
        if (visited[other_node])
            LCA[{v, other_node}] = ancestor[find_set(other_node)];
    }
}

void compute_LCAs() {
    // initialize n, adj and DSU
    // for (each query (u, v)) {
    //    queries[u].push_back(v);
    //    queries[v].push_back(u);
    // }

    ancestor.resize(n);
    visited.assign(n, false);
    dfs(0);
}
```
