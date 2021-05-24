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


In a directed graph, if we apply Dijkstra’s algorithm from vertex i, we can obtain the distance from vertex i to each vertex j. 
	
Also, if we reverse all the directions of edges and similarly apply Dijkstra’s algorithm from vertex i, we can find the minimum distance from each 
vertex j to vertex i in the original graph.

	

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
