## Sack - DSU on Trees

The technique described can be used to answer the following queries

* How many vertices in the subtree of vertex v has some property in 𝑂(𝑛 𝑙𝑜𝑔 𝑛) time (for all of the queries)?

Problem: CSES Distinct Colors https://cses.fi/problemset/task/1139/

You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a color.

Your task is to determine for each node the number of distinct colors in the subtree of the node.

Let's see how we can solve this problem and similar problems.

First, we have to calculate the size of the subtree of every vertex. It can be done with simple dfs:

```cpp
int sz[maxn];
void getsz(int v, int p){
    sz[v] = 1;  // every vertex has itself in its subtree
    for(auto u : g[v])
        if(u != p){
            getsz(u, v);
            sz[v] += sz[u]; // add size of child u to its parent(v)
        }
}
```

Now we have the size of the subtree of vertex v in `sz[v]`.

#### Naive way O(N²)

The naive method for solving distinct colors problem is this code(that works in `O(N²)` time)

```cpp
int cnt[maxn];
void add(int v, int p, int x){
    cnt[ col[v] ] += x;
    for(auto u: g[v])
        if(u != p)
            add(u, v, x)
}
void dfs(int v, int p){
    add(v, p, 1);
    // now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // You can answer the queries easily.
    add(v, p, -1);
    for(auto u : g[v])
        if(u != p)
            dfs(u, v);
}
```

Now, how to improve it? There are several styles of coding for this technique.

#### Easy to code but O(N log²N)

This is same as small to large merging/ heavy light decomposition idea. Instead of creating the distinct colors from empty set, we start with the distinct colors of the heavy child then merge other children's data. Note that the `bigChild` of vertex `v` is the child with max subtree size

```cpp
map<int, int> *cnt[maxn];
void dfs(int v, int p){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p){
           dfs(u, v);
           if(sz[u] > mx)
               mx = sz[u], bigChild = u;
       }
    if(bigChild != -1)
        cnt[v] = cnt[bigChild];
    else
        cnt[v] = new map<int, int> ();
    (*cnt[v])[ col[v] ] ++;
    for(auto u : g[v])
       if(u != p && u != bigChild){
           for(auto x : *cnt[u])
               (*cnt[v])[x.first] += x.second;
       }
    // now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c.

}
```

#### Easy to Code and O(N log N)

Instead of using map, we can use a vector with `cnt` and use the vector of `bigChild`. `bool keep` denote if we are working on the subtree of `bigchild (keep=1)` or `smallchild (keep=0)`.

Make sure that we call `dfs` on small child before large child, otherwise colors of large child will be in `cnt`.

```cpp
vector<int> *vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
           mx = sz[u], bigChild = u;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           dfs(u, v, 0);
    if(bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int> ();
    vec[v]->push_back(v);
    cnt[ col[v] ]++;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           for(auto x : *vec[u]){
               cnt[ col[x] ]++;
               vec[v] -> push_back(x);
           }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    if(keep == 0)
        for(auto u : *vec[v])
            cnt[ col[u] ]--;
}
```

More Readable code

```cpp
vector < int > vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep) {
    int mx = -1, bigchild = -1;
    for (auto u: adj[v]) {
        if (u != p && mx < sz[u]) {
            mx = sz[u], bigchild = u;
        }
    }
    for (auto u: adj[v]) {
        if (u != p && u != bigchild) {
            dfs(u, v, 0);
        }
    }
    if (bigchild != -1) {
        dfs(bigchild, v, 1);
        swap(vec[v], vec[bigchild]);
    }
    vec[v].push_back(v);
    cnt[color[v]]++;
    for (auto u: adj[v]) {
        if (u != p && u != bigchild) {
            for (auto x: vec[u]) {
                cnt[color[x]]++;
                vec[v].push_back(x);
            }
        }
    }
    // there are cnt[c] vertex in subtree v color with c
    if (keep == 0) {
        for (auto u: vec[v]) {
            cnt[color[u]]--;
        }
    }
}
```

#### Heavy-Light decomposition style O(N log N)

```cpp
int cnt[maxn];
bool big[maxn];
void add(int v, int p, int x){
    cnt[ col[v] ] += x;
    for(auto u: g[v])
        if(u != p && !big[u])
            add(u, v, x)
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    // now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(v, p, -1);
}
```

#### Arpa's code O(N logN)

This implementation is easier to code than others. Let `st[v]` dfs starting time of vertex v, `ft[v]` be it's finishing time and `ver[time]` is the vertex which it's starting time is equal to time.

```cpp
int cnt[maxn];
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
    for(auto u : g[v])
	if(u != p && u != bigChild)
	    for(int p = st[u]; p < ft[u]; p++)
		cnt[ col[ ver[p] ] ]++;
    cnt[ col[v] ]++;
    // now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    if(keep == 0)
        for(int p = st[v]; p < ft[v]; p++)
	    cnt[ col[ ver[p] ] ]--;
}
```

But why it is O(N logN) ? You know that why dsu has time O(q logN)(for q queries); the code uses the same method. Merge smaller to greater.

If you have heard `heavy-light decomposition` you will see that function `add` will go light edges only, because of this, code works in  time.

Any problems of this type can be solved with same `dfs` function and just differs in `add` function.

#### Complexity

Let `y = vec[big_child].size()`, `x = vec[small_child].size()` (`y ≥ x`)

Let us consider a vertex u (1 ≤ u ≤ n) of size `x` and merge it to the bigger child, the size of vec[] of the subtree containing u becomes `x + y ≥ x + x = 2x`. So each time we merge to parent subtree the size increase at least twice when adding and total size is only n so we cannot add/merge a node more than `log(n)` times. We have `n` vertices `u` so the complexity becomes `O(n log n)`

### Small to Large merging O(N log²N)

One `log` factor because of small to large merging, another because of `set<int>``
```cpp
const int nax = 2e5 + 10;

int color[nax];
int ans[nax];
vector<int> adj[nax];
set<int> distinct[nax];

void dfs(int u, int p){
    distinct[u].insert(color[u]);
    for(int v:adj[u]){
        if(v==p) continue;
        dfs(v, u);
        if(distinct[v].size() > distinct[u].size()) swap(distinct[u], distinct[v]);
        for(int c:distinct[v]) distinct[u].insert(c);
    }
    ans[u] = distinct[u].size();
}

int main() {
    int n; scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%d", color+i);
    for(int i=0;i<n-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    for(int i=0;i<n;i++) printf("%d ", ans[i]);
    return 0;
}
```

source: https://codeforces.com/blog/entry/44351 and https://codeforces.com/blog/entry/67696

### Using Euler Tour Tree

```cpp
#include <bits/stdc++.h>

#define maxn 200020
using namespace std;
int n;
vector<int> graph[maxn]; // adjacency matrix
int a[maxn], bit[maxn], b[maxn];
vector <pair<int, int>> qry[maxn];
map <int, int> fst;
int tin[maxn], tout[maxn];
int timer = 0;

// Fenwick tree
void upd(int i, int v) {
    for (; i < n; i |= i + 1) {
        bit[i] += v;
    }
}

int calc(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & i + 1) - 1) {
        ans += bit[i];
    }
    return ans;
}

// euler tour tree
void dfs(int x, int p) {
    tin[x] = timer++;
    for (int i = 0; i < graph[x].size(); i++) {
        int to = graph[x][i];
        if (to != p) dfs(to, x);
    }
    tout[x] = timer - 1;
}

int main() {
    cin >> n;
    // color of node i is stored in a[i]
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(0, 0);
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        qry[tin[i]].push_back(make_pair(tout[i], i));
    }
    // store the color of node i at b[tin[i]]
    for (int i = 0; i < n; i++) b[tin[i]] = a[i];
    for (int i = n - 1; i >= 0; i--) {
        // if b[i] is already considered, first remove it
        if (fst.count(b[i])) upd(fst[b[i]], -1);
        upd(i, 1);
        fst[b[i]] = i;
        for (int j = 0; j < qry[i].size(); j++) {
            res[qry[i][j].second] = calc(qry[i][j].first);
        }
    }
    for (int i = 0; i < n; i++) cout << res[i] << " ";
}
```

TODO: This problem can also be solved using Mo's algorithm on Trees https://codeforces.com/blog/entry/79048

## Problems

### CF 211 Div1. D Tree and Queries

You have a rooted tree consisting of `n` vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from `1` to `n`. Then we represent the color of vertex `v` as `cv`. The tree root is a vertex with number `1`.

In this problem you need to answer to `m` queries. Each query is described by two integers `vj, kj`. The answer to query `vj, kj` is the number of such colors of vertices `x`, that the subtree of vertex `vj` contains at least `kj` vertices of color `x`.

https://codeforces.com/contest/375/problem/D

<details>
	<summary> Using DSU, Sack CPP implementation </summary>

Using Heavy-Light decomposition based sytle mentioned above.
	
```cpp
const int nax = 1e5 + 10;

// Fenwick Tree to store frequency of colors
template<class T> struct BIT {
    int n; vector<T> data;
    void init(int _n) { n = _n; data.resize(n); }
    void add(int p, T x) { for (++p;p<=n;p+=p&-p) data[p-1] += x; }
    T sum(int l, int r) { return sum(r+1)-sum(l); }
    T sum(int r) { T s = 0; for(;r;r-=r&-r)s+=data[r-1]; return s; }
    int lower_bound(T sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1<<25; pw; pw >>= 1) {
            int npos = pos+pw;
            if (npos <= n && data[npos-1] < sum)
                pos = npos, sum -= data[pos-1];
        }
        return pos;
    }
};

vector<int> adj[nax];
int color[nax], sub_sz[nax]; // subtree size
int cnt[nax], big[nax];
vector<pair<int,int>> query[nax];
int ans[nax];

BIT<int> freq;

int dfs_sz(int u, int p){
    sub_sz[u] = 1;
    for(int v:adj[u]) if(v!=p) sub_sz[u] += dfs_sz(v, u);
    return sub_sz[u];
}

void add(int u, int p, int x){
    freq.add(cnt[color[u]], -1);
    cnt[color[u]] += x;
    freq.add(cnt[color[u]], 1);
    for(int v: adj[u]) if(v!=p && !big[v]) add(v, u, x);
}

void dfs(int u, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(int v: adj[u])
        if(v != p && sub_sz[v] > mx)
            mx = sub_sz[v], bigChild = v;
    for(int v: adj[u])
        if(v != p && v != bigChild)
            dfs(v, u, 0);
    if(bigChild != -1)
        dfs(bigChild, u, 1), big[bigChild] = 1;
    add(u, p, 1);
    // Query for u
    for(auto [i, k]: query[u]){
        ans[i] = freq.sum(nax) - freq.sum(k);
    }
    if(bigChild != -1) big[bigChild] = 0;
    if(keep == 0) add(u, p, -1);
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &color[i]);
    for(int i=0;i<n-1;i++){
        int a, b; scanf("%d %d", &a, &b);
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i=0;i<m;i++){
        int u, k; scanf("%d %d", &u, &k); u--;
        query[u].push_back({i, k});
    }
    dfs_sz(0, -1);
    freq.init(nax);
    dfs(0, -1, 0);
    for(int i=0;i<m;i++) printf("%d\n", ans[i]);
    return 0;
}
```
	
Similar to rng's implementation https://codeforces.com/contest/375/submission/5508178
</details>
	
<details>
	<summary>Using Mo's algorithm on trees</summary>
	
* Flatten the tree into array using Euler tour tree technique, now tsubtree queries becomes range queries on array
* For range queries on array we can use mo's algorithm
* Here we need to find number of colors exceeding the limit for a given k, for this we can store frequency of counts using BIT/Segment tree
	
```cpp
const int nax = 1e5 + 10;

// To store frequencies of count of colors
template<class T> struct BIT {
    int n; vector<T> data;
    void init(int _n) { n = _n; data.resize(n); }
    void add(int p, T x) { for (++p;p<=n;p+=p&-p) data[p-1] += x; }
    T sum(int l, int r) { return sum(r+1)-sum(l); }
    T sum(int r) { T s = 0; for(;r;r-=r&-r) s+=data[r-1]; return s; }
    int lower_bound(T sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1<<25; pw; pw >>= 1) {
            int npos = pos+pw;
            if (npos <= n && data[npos-1] < sum)
                pos = npos, sum -= data[pos-1];
        }
        return pos;
    }
};

BIT<int> freq;

int color[nax];
vector<int> adj[nax];

// euler tour tree
int timer;
int st[nax], en[nax];
int node[nax]; // node at time[i]

void dfs(int u, int p){
    st[u] = timer++;
    node[st[u]] = u;
    for(int v: adj[u]) if(v!=p) dfs(v, u);
    en[u] = timer-1;
}

// mo stuff
int BL[nax]; // block of l
int ans[nax];
int cnt[nax];

struct query {
    int id, l, r, k;
    const bool operator<(const query &other) const{
        return BL[l] == BL[other.l] ? r < other.r : BL[l] < BL[other.l];
    }
};

vector<query> Q;

void add(int u, int x){
    freq.add(cnt[color[u]], -1);
    cnt[color[u]] += x;
    freq.add(cnt[color[u]], 1);
}

void compute(){
    int curL = Q[0].l, curR = Q[0].l - 1;
    for(int i=0; i<Q.size(); i++){
        query q = Q[i];
        while(curL > q.l) add(node[--curL], 1);
        while(curR < q.r) add(node[++curR], 1);
        while(curL < q.l) add(node[curL++], -1);
        while(curR > q.r) add(node[curR--], -1);

        ans[q.id] = freq.sum(q.k, nax-1);
    }
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &color[i]);
    for(int i=0;i<n-1;i++){
        int a, b; scanf("%d %d", &a, &b);
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    freq.init(nax);
    dfs(0, -1);

    int sqrtn = sqrt(n);
    for(int i=0;i<n;i++) BL[i] = i/sqrtn;

    for(int i=0;i<m;i++){
        int u, k; scanf("%d %d", &u, &k); u--;
        query q;
        q.id = i; q.l = st[u], q.r = en[u], q.k = k;
        Q.push_back(q);
    }
    sort(Q.begin(), Q.end());
    compute();
    for(int i=0;i<m;i++) printf("%d\n", ans[i]);
    return 0;
}
```
			 
Inspired from ffao solution https://codeforces.com/contest/375/submission/18814449
</details>	
	
TODO: Problems from https://codeforces.com/blog/entry/44351
