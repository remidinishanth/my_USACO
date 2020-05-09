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


// source: monsoon https://codeforces.com/blog/entry/67138
// Standard approach
// One of standard ways to implement constant-time LCA queries on a tree is to preprocess it 
// by doing an Eulerian tour which creates an array of pairs (depth, index) for subsequent 
// vertices visited on the tour, and then reduce an LCA query to RMQ query on a certain fragment of this array:

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

// The RMQ problem can be solved with a sparse table, which after 𝑂(nlogn) preprocessing 
// allows to answer RMQ queries in constant time:

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
