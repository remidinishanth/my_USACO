// Implementation of Dijkstra's algorithm using adjacency lists
// and priority queue for efficiency.
//
// Running time: O(|E| log |V|)
// source: Stanford Notebook

#include <queue>
#include <cstdio>

using namespace std;
const int INF = 2000000000;
typedef pair<int, int> PII;

int main() {

	int N, s, t;
	scanf("%d%d%d", &N, &s, &t);
	vector<vector<PII> > edges(N);
	for (int i = 0; i < N; i++) {
		int M;
		scanf("%d", &M);
		for (int j = 0; j < M; j++) {
			int vertex, dist;
			scanf("%d%d", &vertex, &dist);
			edges[i].push_back(make_pair(dist, vertex)); // note order of arguments here
		}
	}

	// use priority queue in which top element has the "smallest" priority
	priority_queue<PII, vector<PII>, greater<PII> > Q;
	vector<int> dist(N, INF), dad(N, -1);
	Q.push(make_pair(0, s));
	dist[s] = 0;
	while (!Q.empty()) {
		PII p = Q.top();
		Q.pop();
		int here = p.second;
		if (here == t) break;
		if (dist[here] != p.first) continue; // this is important

		for (vector<PII>::iterator it = edges[here].begin(); it != edges[here].end(); it++) {
			if (dist[here] + it->first < dist[it->second]) {
				dist[it->second] = dist[here] + it->first;
				dad[it->second] = here;
				Q.push(make_pair(dist[it->second], it->second));
			}
		}
	}

	printf("%d\n", dist[t]);
	if (dist[t] < INF)
		for (int i = t; i != -1; i = dad[i])
			printf("%d%c", i, (i == s ? '\n' : ' '));
	return 0;
}

/*
Sample input:
5 0 4
2 1 2 3 1
2 2 4 4 5
3 1 4 3 3 4 1
2 0 1 2 3
2 1 5 2 1
Expected:
5
4 2 3 0
*/


// Dijsktra's algorithm in O(n^2 + m)

// Dijkstra's algorithm performs n iterations. On each iteration it selects an unmarked vertex v with the lowest value d[v], 
// marks it and checks all the edges (v,to) attempting to improve the value d[to].

// The running time of the algorithm consists of:
// n searches for a vertex with the smallest value d[v] among O(n) unmarked vertices
// m relaxation attempts

// For the simplest implementation of these operations on each iteration vertex search requires O(n) operations, 
// and each relaxation can be performed in O(1). Hence, the resulting asymptotic behavior of the algorithm is: O(n^2+m)

// This complexity is optimal for dense graph, i.e. when m≈n^2. However in sparse graphs, when m is much smaller than the maximal number of edges O(n^2), 
// the problem can be solved in O(nlogn+m) complexity using the above implementation.

// Here the graph adj is stored as adjacency list: for each vertex v adj[v] contains the list of edges going from this vertex, 
// i.e. the list of pair<int,int> where the first element in the pair is the vertex at the other end of the edge, and the second element is the edge weight.

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

// After performing all the iterations array d[] stores the lengths of the shortest paths to all vertices, 
// and array p[] stores the predecessors of all vertices (except starting vertex s). 


//The path to any vertex t can be restored in the following way:

vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}



/*
In a directed graph, if we apply Dijkstra’s algorithm from vertex i, we can obtain the distance from vertex i to each vertex j. 
	
Also, if we reverse all the directions of edges and similarly apply Dijkstra’s algorithm from vertex i, we can find the minimum distance from each 
vertex j to vertex i in the original graph.
*/
	

// source: https://github.com/ta7uw/atcoder-cpp/blob/master/lib/graph/dijkstra.cpp	
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll, ll>;
using Graph = vector<vector<ll>>;
#define rep(i, n) for(ll i=0;i<(ll)(n);i++)
#define rep2(i, m, n) for(ll i=m;i<(ll)(n);i++)
#define rrep(i, n, m) for(ll i=n;i>=(ll)(m);i--)
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int ddy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const ll MOD = 1000000007;
const ll INF = 1000000000000000000L;

/**
 * Library
 * --------------------------------------------------------
 */
struct edge {
    int from, to;
    ll cost;
};

class Dijkstra {
    int V;
    vector<vector<edge>> edges;
    vector<ll> dist;
    vector<ll> prev;
    vector<ll> route_count;

public:
    Dijkstra(int v) : V(v) {
        edges.resize(V);
        dist.resize(V, INF);
        prev.resize(V, INF);
        route_count.resize(V, 0);
    }

    void add_edge(int from, int to, ll cost) {
        edges[from].push_back({from, to, cost});
    }

    /**
     * @param goal 0-indexed
     * @return return cost to reach the goal. return INF if the goal is unreachable.
     */
    ll get_cost(int goal) {
        return dist[goal];
    }

    /**
     * @param goal 0-indexed
     * @return return total route count to reach the goal ( result value % MOD )
     */
    ll get_route_count(int goal) {
        return route_count[goal];
    }

    /**
     * @param goal 0-indexed
     * @return return route from start to goal
     */
    vector<ll> get_route(int goal) {
        vector<ll> res;
        res.push_back(goal);
        ll dest = goal;
        while (prev[dest] != INF) {
            res.push_back(prev[dest]);
            dest = prev[dest];
        }
        reverse(res.begin(), res.end());
        return res;
    }

    void exec(int start) {
        dist[start] = 0;
        route_count[start] = 1;
        priority_queue<P, vector<P>, greater<>> queue;
        queue.push({dist[start], start});
        while (!queue.empty()) {
            P p = queue.top();
            queue.pop();
            ll prev_cost = p.first;
            ll src = p.second;
            if (dist[src] < prev_cost) continue;

            for (edge &e : edges[src]) {
                ll to = e.to;
                ll cost = e.cost;
                if (cost != INF && dist[to] > dist[src] + cost) {
                    dist[to] = dist[src] + cost;
                    queue.push({dist[to], to});
                    prev[to] = src;
                    route_count[to] = route_count[src];
                } else if (dist[to] == dist[src] + cost) {
                    route_count[to] += route_count[src];
                    route_count[to] %= MOD;
                }
            }
        }
    }
};
/**
 * --------------------------------------------------------
 */

/**
 * ABC 035 D - トレジャーハント
 * https://atcoder.jp/contests/abc035/submissions/7668866
 */
void Main() {
    int N, M, T;
    cin >> N >> M >> T;
    vector<ll> t_list(N);
    rep(i, N) cin >> t_list[i];
    Dijkstra dijkstra1(N);
    Dijkstra dijkstra2(N);
    rep(i, M) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        dijkstra1.add_edge(a, b, c);
        dijkstra2.add_edge(b, a, c);
    }

    dijkstra1.exec(0);
    dijkstra2.exec(0);
    ll ans = t_list[0] * T;
    rep2(i, 1, N) {
        ll go = dijkstra1.get_cost(i);
        ll back = dijkstra2.get_cost(i);
        if (go != INF && back != INF) ans = max(ans, t_list[i] * (T - go - back));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    Main();
    return 0;
}


// Dijkstra using own implementation of priority queue
// refer: https://codeforces.com/contest/1528/submission/117224037 & https://youtu.be/hZAJ-VLYflw?t=2511
// Using Segment Tree -  Range Minimum Query and Point Update
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ops = 0;

int mAdd(int a, int b, int mod) {
	return (a + b >= mod ? a + b - mod : a + b);
}

// Struct for priority queue operations on index set [0, n-1]
// push(i, v) overwrites value at position i if one already exists
// decKey is faster but requires that the new key is smaller than the old one
struct Prique {
	const ll INF = 4 * (ll)1e18;
	vector<pair<ll, int>> data;
	const int n;

	Prique(int siz) : n(siz), data(2*siz, {INF, -1}) { data[0] = {-INF, -1}; }
	bool empty() const { return data[1].second >= INF; }
	pair<ll, int> top() const { return data[1]; }

	void push(int i, ll v) {
		++ops;
		data[i+n] = {v, (v >= INF ? -1 : i)};
		for (i += n; i > 1; i >>= 1) data[i>>1] = min(data[i], data[i^1]);
	}
	void decKey(int i, ll v) {
		++ops;
		for (int j = i+n; data[j].first > v; j >>= 1) data[j] = {v, i};
	}
	pair<ll, int> pop() {
		auto res = data[1];
		push(res.second, INF);
		return res;
	}
};

const ll INF = 1e18;
const int N = 600;
vector<pair<int, ll>> edges[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	for (int j = 0; j < m; ++j) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		edges[a].emplace_back(b, c);
	}

	for (int s = 0; s < n; ++s) {
		vector<ll> dist(n, INF);
		Prique pq(n);

		for (auto pr : edges[s]) {
			int t = pr.first;
			ll c = pr.second;
			dist[t] = c;
			pq.decKey(t, c);
		}

		for (int i = pq.pop().second; i != -1; i = pq.pop().second) {
			ll c = dist[i];
			int sf = c % n;
			for (auto pr : edges[i]) {
				int t = mAdd(pr.first, sf, n);
				ll off = c + pr.second;
				if (dist[t] > off) {
					dist[t] = off;
					pq.decKey(t, off);
				}
			}
			
			int t = mAdd(i, 1, n);
			if (dist[t] > c + 1) {
				dist[t] = c + 1;
				pq.decKey(t, c + 1);
			}
		}

		dist[s] = 0;
		for (int i = 0; i < n; ++i) cout << dist[i] << ' '; cout << '\n';
	}

	double rat = (double)ops / (N*N*N);
	cerr << rat << endl;
	assert(rat <= 0.025);
}
