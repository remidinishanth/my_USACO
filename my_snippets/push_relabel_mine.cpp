 #include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
 
struct edge{
    int from,to; ll cap,f;
};
 
vector<edge> ed;
vector<vector<int> > adj,hs;
vector<int> h;vector<ll> ex;
int N,S,T;
 
void init(int n,int s,int t){
    N=n;S=s;T=t;
    h=vector<int>(N);
    ex=vector<ll>(N);
    adj=vector<vector<int>>(N);
    hs=vector<vector<int>>(2*N+1);
}
 
void add_edge(int from,int to,int cap){
    if(from==to) return;
    adj[from].push_back(ed.size());
    ed.push_back({from,to,cap,0});
    adj[to].push_back(ed.size());
    ed.push_back({to,from,0,0});
}
 
void push(int id){
    int v=ed[id].from,to=ed[id].to;
    ll fl=min(ex[v],ed[id].cap-ed[id].f);
    if(to!=S && to!=T && !ex[to] && fl) hs[h[to]].push_back(to);
    ed[id].f+=fl;
    ed[id^1].f-=fl;
    ex[v]-=fl;
    ex[to]+=fl;
}
 
int relabel(int v){
    h[v]=2*N;
    for(int id:adj[v])
        if(ed[id].cap>ed[id].f)
            h[v]=min(h[v],h[ed[id].to]+1);
    hs[h[v]].push_back(v);
    return h[v];
}
 
ll max_flow(){
    h[S]=N;
    for(int id:adj[S]){
        ex[S]+=ed[id].cap;
        push(id);
    }
 
    if(hs[0].size())
    for(int hi=0;hi>=0;){
        // find a vertex v with ex[v]>0 && max height
        int v=hs[hi].back();hs[hi].pop_back();
        while(ex[v] >0){
            for(int i=0;i<(int)adj[v].size() && ex[v];i++){
                int id=adj[v][i];edge e=ed[id];
                if(e.cap-e.f>0 && h[v]==h[e.to]+1)
                    push(id);
            }
            if(ex[v]) hi=relabel(v);
        }
        while(hi>=0 && hs[hi].empty()) --hi;
    }
    ll res=0;
    for(int id:adj[S]) res+=ed[id].f;
    return res;
}

int main(){
	return 0;
}
