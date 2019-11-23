struct TEdge{
    int from,to,cap,f;
};

vector<TEdge> edges;
vector<int> adj[VCOUNT];
vector<bool> vis;

void add_edge(int from,int to,int cap){
    adj[from].push_back(edges.size());
    edges.push_back({from,to,cap,0});
    adj[to].push_back(edges.size());
    edges.push_back({to,from,0,0});
}

//almost a DFS
//what is largest amount of flow w 
//we can push starting from vertex v
//returned value is amount pushed
int push(int v,int w){
    if(v==sink) return w;
    if(vis[v]) return 0;
    vis[v]=1;
    for(int ind:adj[v]){
        int go=edges[ind].c-edges[ind].f;
        if(go==0) continue;
        int res=push(edges[ind].to,min(w,go));
        if(res==0) continue; // didn't manage to push
        edges[ind].f+=res;
        edges[ind^1].f-=res;
        return res;
    }
    return 0;
}

while(push(src,INF)>0) vis.clear();

while(int sent=push(src,INF)) total+=sent,vis.clear();

// only applying DFS is just finding some augmenting path
// and the running time of above algorithm can be 
// Pseudo-polynomial O(mf) for flow f

// If we use BFS instead, then the augmented path will be 
// shortest in terms on number of hops(hop count) then the 
// augmented path is fixed and the running time is polynomial
// O(nm^2), this is Edmonds Karp algorithm

// If we use BFS and then Level graph and then blocking flow
// then we get Dinic algorithm and this is O(n^2m)


// Dinic Algo

// 1 Construct a level graph by doing BFS from source to label
// all the levels of the current flow graph, residual edges of 
// the level graph myst have (cap-flow)>0

// 2 If the sink was never reached while building the level graph
// then stop and return the max flow

// 3 Using only valid edges in the level graph, do multiple DFSs
// from s->t until a blocking flow is reached, and sum over the 
// bottleneck values of all the augmenting paths found to 
// calculate the max flow

// Repeat Steps 1 to 3

// Idea of blocking flows is to destroy all Shortest paths
// of a given distance, so it increases distance
