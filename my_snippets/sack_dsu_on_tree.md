TODO: https://codeforces.com/blog/entry/44351

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

This is same as small to large merging/ heavy light decomposition idea. Instead of creating the distinct colors from empty set, we start with the distinct colors of the heavy child then merge other children's data.

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

Instead of using map, we can use a vector with `cnt` and use the vector of `bigChild`.

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

### Small to Large merging

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

TODO: This problem can also be solved using Mo's algorithm on Trees https://codeforces.com/blog/entry/79048
