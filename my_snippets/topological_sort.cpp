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
