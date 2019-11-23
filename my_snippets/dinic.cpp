struct edge{
    int from,to,cap,f;
};

vector<edge> ed; //edges
vector<vector<int>> adj;
vector<int> dd,pt; //dist and ptr
int N,S,T; // src,sink

void init(int n,int s,int t){
    N=n,S=s,T=t;
    dd=vector<int>(N);
    pt=vector<int>(N);
    adj=vector<vector<int>>(N);
}

void add_edge(int from,int to,int cap){
    adj[from].push_back(ed.size());
    ed.push_back({from,to,cap,0});
    adj[to].push_back(ed.size());
    ed.push_back({to,from,0,0});
}

bool bfs(){
    fill(dd.begin(),dd.end(),N+1);
    queue<int> q;
    dd[S]=0;q.push(S);
    while(!q.empty()){
        int v=q.front();q.pop();
        if(v==T) break;
        for(int id:adj[v]){
            int to=ed[id].to;
            if(dd[to]>dd[v]+1 && ed[id].f<ed[id].cap)
                dd[to]=dd[v]+1,q.push(to);
        }
    }
    return dd[T]!=N+1;
}

int dfs(int v,int w){
    if(v==T || w==0) return w;
    int res=0;
    for(;pt[v]<(int)adj[v].size();pt[v]++){
        int id=adj[v][pt[v]];
        int to=ed[id].to;
        int go=ed[id].cap-ed[id].f;
        if(dd[to]!=dd[v]+1) continue;
        int fl=dfs(to,min(w,go));
        w-=fl;res+=fl;
        ed[id].f+=fl;
        ed[id^1].f-=fl;
        if(!w) return res;
    }
    return res;
}

int dinic(){
    int res=0;
    while(bfs()){
        fill(pt.begin(),pt.end(),0);
        while(int fl=dfs(S,INF)) res+=fl;
    }
    return res;
}
