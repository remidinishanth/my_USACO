const int N = 222222;
const int D = 22;
 
int n, edge_count, first_edge[N], to[N], next_edge[N], jump[N][D], depth[N], weight[N], result[N];

// Adjacency list representation using arrays
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

// Binary Lifting O(NlogN) for preprocessing the tree, O(logN) for each LCA query
// up[i][j] is the 2^j-th ancestor above the node i with i=1...N, j=0...ceil(log(N)).
// This information allow us to jump from any node to any ancestor above it in O(logN) time. 
int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

// source: https://cp-algorithms.com/graph/lca_binary_lifting.html

// Using a Segment Tree O(logN) with preprocessing in O(N) time.
struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

// Tarjan's off-line lowest common ancestors algorithm based on the union-find data structure.
// N = number of nodes and Q = number of queries => in approximately O(N + Q) time.

// The basic idea is every times the algorithm visit a node x, the ancestor of all its descendants will be that node x.

// So to find a Least common ancestor (LCA) r of two nodes (u,v), there will be two cases:
// Node u is a child of node v (vice versa), this case is obvious.
// Node u is ith branch and v is the jth branch (i < j) of node r, so after visit node u, 
// the algorithm backtrack to node r, which is the ancestor of the two nodes, 
// mark the ancestor of node u as r and go to visit node v. 
// At the moment it visit node v, as u is already marked as visited (black), so the answer will be r. 
