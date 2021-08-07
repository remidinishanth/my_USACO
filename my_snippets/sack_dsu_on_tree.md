TODO: https://codeforces.com/blog/entry/44351

The technique described can be used to answer the following queries

* How many vertices in the subtree of vertex v has some property in 𝑂(𝑛 𝑙𝑜𝑔 𝑛) time (for all of the queries)?

Problem: CSES Distinct Colors https://cses.fi/problemset/task/1139/

You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a color.

Your task is to determine for each node the number of distinct colors in the subtree of the node.

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
