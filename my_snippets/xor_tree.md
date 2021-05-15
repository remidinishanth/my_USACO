![image](https://user-images.githubusercontent.com/19663316/118364727-4f5bf000-b5b7-11eb-90fc-21d9974225f3.png)

**Solution**

![image](https://user-images.githubusercontent.com/19663316/118364668-0c9a1800-b5b7-11eb-9b8a-76204ac82f12.png)

source: https://atcoder.jp/contests/abc201/editorial/1837

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9+7;

int main(){
    int N; cin >> N;
    vector<vector<ll>> edge(N), weight(N);
    for(int i=1; i<N; i++){
        ll u,v,w; cin >> u >> v >> w;
        edge[--u].push_back(--v);
        edge[v].push_back(u);
        weight[u].push_back(w);
        weight[v].push_back(w);
    }
    vector<ll> dist(N,-1);
    std::queue<int> que;
    que.push(0);
    dist[0] = 0;
    while(!que.empty()){
        int now = que.front(); que.pop();
        for(int i=0; i<edge[now].size(); i++){
            int next = edge[now][i];
            ll sum = dist[now]^weight[now][i];
            if(dist[next] == -1){
                dist[next] = sum;
                que.push(next);
            }
        }
    }
    ll ans = 0;
    for(int i=0; i<60; i++){
        vector<int> cnt(2);
        for(int j=0; j<N; j++) cnt[dist[j]>>i&1]++;
        ans += (1ll<<i)%mod*cnt[0]%mod*cnt[1];
        ans %= mod;
    }
    cout << ans << endl;
}
```
