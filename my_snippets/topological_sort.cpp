/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */
 
template<int SZ> struct TopoSort {
	int N, in[SZ];
	vi res, adj[SZ];
	void ae(int x, int y) { adj[x].pb(y), in[y] ++; }
	bool sort(int _N) {
		N = _N; queue<int> todo;
		FOR(i,1,N+1) if (!in[i]) todo.push(i);
		while (sz(todo)) {
			int x = todo.front(); todo.pop(); res.pb(x);
			trav(i,adj[x]) if (!(--in[i])) todo.push(i);
		}
		return sz(res) == N;
	}
};

if (!T.sort(n)) { return -1; }

// Source: CP3

vi ts; // global vector to store the toposort in reverse order
void dfs2(int u) { // different function name compared to the original dfs
  dfs_num[u] = VISITED;
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    ii v = AdjList[u][j];
    if (dfs_num[v.first] == UNVISITED)
      dfs2(v.first);
  }
  ts.push_back(u); // that’s it, this is the only change
}

// inside int main()
ts.clear();
memset(dfs_num, UNVISITED, sizeof dfs_num);
for (int i = 0; i < V; i++) // this part is the same as finding CCs
if (dfs_num[i] == UNVISITED)
dfs2(i);
reverse(ts.begin(), ts.end());

// source tourist: https://codeforces.com/contest/1344/submission/79163314
template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };
 
  vector<edge> edges;
  vector<vector<int>> g;
  int n;
 
  graph(int _n) : n(_n) {
    g.resize(n);
  }
 
  virtual int add(int from, int to, T cost) = 0;
};
 
template <typename T>
class digraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;
 
  digraph(int _n) : graph<T>(_n) {
  }
 
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
 
  digraph<T> reverse() const {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    return rev;
  }
};
 
template <typename T>
vector<int> find_topsort(const digraph<T> &g) {
  vector<int> deg(g.n, 0);
  for (int id = 0; id < (int) g.edges.size(); id++) {
    deg[g.edges[id].to]++;
  }
  vector<int> x;
  for (int i = 0; i < g.n; i++) {
    if (deg[i] == 0) {
      x.push_back(i);
    }
  }
  for (int ptr = 0; ptr < (int) x.size(); ptr++) {
    int i = x[ptr];
    for (int id : g.g[i]) {
      auto &e = g.edges[id];
      int to = e.to;
      if (--deg[to] == 0) {
        x.push_back(to);
      }
    }
  }
  if ((int) x.size() != g.n) {
    return vector<int>();
  }
  return x;
}

// Usage: digraph<int> g(n); edge g.add(x, y); vector<int> order = find_topsort(g);
