### TODO 

Read https://codeforces.com/blog/entry/76150

### Codeforces

https://codeforces.com/contest/1092/problem/F

<img width="851" alt="image" src="https://user-images.githubusercontent.com/19663316/222914606-2876112e-8be4-4356-aadf-3b44bedf2b5d.png">

```cpp
#include <bits/stdc++.h>

using namespace std;

long long res, ans;

vector<int> a;
vector<long long> sum;
vector<vector<int>> g;

void dfs(int v, int p = -1, int h = 0) {
	res += h * 1ll * a[v];
	sum[v] = a[v];
	
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v, h + 1);
		sum[v] += sum[to];
	}
}

void go(int v, int p = -1) {
	ans = max(ans, res);
	
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		
		res -= sum[to];
		sum[v] -= sum[to];
		res += sum[v];
		sum[to] += sum[v];
		
		go(to, v);
		
		sum[to] -= sum[v];
		res -= sum[v];
		sum[v] += sum[to];
		res += sum[to];
	}
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int n;
	cin >> n;
	a = vector<int>(n);
	sum = vector<long long>(n);
	g = vector<vector<int>>(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < n - 1; ++i) {
		int x, y;
		cin >> x >> y;
		--x, --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	
	dfs(0);
	go(0);
	
	cout << ans << endl;
	
	return 0;
  ```

### Count possible number of root nodes

https://leetcode.com/contest/biweekly-contest-99/problems/count-number-of-possible-root-nodes/

```cpp
class Solution {
public:
    vector<vector<int>> adj;
    
    set<pair<int, int>> S;
    
    int res = 0, K;
    
    vector<int> sum;
    
    void dfs(int v, int p = -1) {
        for(int to: adj[v]){
            if(to == p) continue;
            if(S.count({v, to})) sum[v]++;
            dfs(to, v);
            sum[v] += sum[to];
        }
    }
    
    set<int> ans;
    
    void go(int v, int p = -1) {
        // printf("%d %d\n", v, res);
        if(res >= K){
            ans.insert(v);
        }

        for (auto to : adj[v]) {
            if (to == p) {
                continue;
            }

            if(S.count({v, to})) res--;
            if(S.count({to, v})) res++;

            go(to, v);

            if(S.count({v, to})) res++;
            if(S.count({to, v})) res--;

        }
    }
    
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        K = k;
        int n = edges.size() + 1;
        sum = vector<int>(n);
        adj = vector<vector<int>>(n, vector<int>());
        for(vector<int> e:edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        for(vector<int> v: guesses){
            S.insert({v[0], v[1]});
        }
        dfs(0);
        res = sum[0];
        go(0);
        return ans.size();
    }
};
```
