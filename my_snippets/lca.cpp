const int N = 222222;
const int D = 22;
 
int n, edge_count, first_edge[N], to[N], next_edge[N], jump[N][D], depth[N], weight[N], result[N];
 
void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}
 
void dfs(int p, int u) {
    depth[u] = p == 0? 0: (depth[p] + 1);
    jump[u][0] = p;
    for (int i = 0; jump[u][i] != 0; ++ i) {
        jump[u][i + 1] = jump[jump[u][i]][i];
    }
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        int v = to[iter];
        if (v != p) {
            dfs(u, v);
        }
    }
}
 
int jump_up(int u, int d) {
    for (int i = D - 1; i >= 0; -- i) {
        if (d >= (1 << i)) {
            u = jump[u][i];
            d -= 1 << i;
        }
    }
    return u;
}
 
int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        return lca(v, u);
    }
    // depth[u] <= depth[v]
    v = jump_up(v, depth[v] - depth[u]);
    if (u == v) {
        return u;
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (jump[u][i] != jump[v][i]) {
            u = jump[u][i];
            v = jump[v][i];
        }
    }
    return jump[u][0];
}

// Usage:
scanf("%d", &n);
edge_count = 0;
memset(first_edge, -1, sizeof(first_edge));
for (int i = 0; i < n - 1; ++ i) {
  int a, b;
  scanf("%d%d", &a, &b);
  add_edge(a, b);
  add_edge(b, a);
}
memset(jump, 0, sizeof(jump));
dfs(0, 1);

// source: https://codeforces.com/contest/191/submission/1726763
