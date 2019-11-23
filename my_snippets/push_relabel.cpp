// Push relabel in O(V^2 E^0.5) with gap heuristic
// It's quite fast
// From dacin21
template<typename flow_t = long long>
struct PushRelabel {
    struct Edge {
        int to, rev;
        flow_t f, c;
    };
    vector<vector<Edge> > g;
    vector<flow_t> ex;
    vector<Edge*> cur;
    vector<vector<int> > hs;
    vector<int> H;
    PushRelabel(int n) : g(n), ex(n), cur(n), hs(2*n), H(n) {}
    void add_edge(int s, int t, flow_t cap, flow_t rcap=0) {
        if (s == t) return;
        Edge a = {t, (int)g[t].size(), 0, cap};
        Edge b = {s, (int)g[s].size(), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    void push(Edge& e, flow_t f) {
        Edge &back = g[e.to][e.rev];
        if (!ex[e.to] && f)
            hs[H[e.to]].push_back(e.to);
        e.f += f; e.c -= f;
        ex[e.to] += f;
        back.f -= f; back.c += f;
        ex[back.to] -= f;
    }
    flow_t max_flow(int s, int t) {
        int v = g.size();
        H[s] = v;
        ex[t] = 1;
        vector<int> co(2*v);
        co[0] = v-1;
        for(int i=0;i<v;++i) cur[i] = g[i].data();
        for(auto &e:g[s]) push(e, e.c);
        if(hs[0].size())
        for (int hi = 0;hi>=0;) {
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ex[u] > 0) // discharge u
                if (cur[u] == g[u].data() + g[u].size()) {
                    H[u] = 1e9; // Relabel
                    for(auto &e:g[u])
                        if (e.c && H[u] > H[e.to]+1)
                            H[u] = H[e.to]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        for(int i=0;i<v;++i) // Gap Heuristic
                            if (hi < H[i] && H[i] < v){
                                --co[H[i]];
                                H[i] = v + 1;
                            }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->to]+1)
                    push(*cur[u], min(ex[u], cur[u]->c));
                else ++cur[u];
            while (hi>=0 && hs[hi].empty()) --hi;
        }
        return -ex[s];
    }
};
