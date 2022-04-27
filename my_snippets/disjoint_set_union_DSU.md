The best way I've seen to 
code this kind of DSU, is style of bmerry : (C++)

* When `data[x] < 0`, `x` is a root and `-data[x]` is its tree size. When `data[x] >= 0`, `data[x]` is x's parent.

```
initially are parents are set to -1

for each root v, 
  par[v] equals the negative of number of tools in that box.
```

source: Algorithm Gym :: Data structures by DarthKnight https://codeforces.com/blog/entry/15729

```cpp
vector<int> par = vector<int>(n, -1);

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}

void merge(int x,int y){    //  x and y are some tools (vertices)
    if((x = root(x)) == (y = root(y)))  return;
    if(par[y] < par[x]) // balancing the height of the tree
        swap(x, y);
    par[x] += par[y];
    par[y] = x;
}
```	   

source: kmjp https://kmjp.hatenablog.jp/entry/2020/06/18/0900
https://codeforces.com/contest/1278/submission/67749296
	   
```cpp	   
template<int um> class UF {
    public:
    vector<int> par,rank,cnt;
    UF() {par=rank=vector<int>(um,0); cnt=vector<int>(um,1); for(int i=0;i<um;i++) par[i]=i;}
    void reinit() {for(int i=0;i<um;i++) rank[i]=0,cnt[i]=1,par[i]=i;}
    int operator[](int x) {return (par[x]==x)?(x):(par[x] = operator[](par[x]));}
    int count(int x) { return cnt[operator[](x)];}
    int operator()(int x,int y) {
        if((x=operator[](x))==(y=operator[](y))) return x;
        cnt[y]=cnt[x]=cnt[x]+cnt[y];
        if(rank[x]>rank[y]) return par[x]=y;
        rank[x]+=rank[x]==rank[y]; return par[y]=x;
    }
};
UF<500000> uf;

```

Can directly use uf[y]==uf[x] to check whether both are in same union and uf(y,x); to combine both of them

```cpp	   
struct UnionFind{
  int num;
  vector<int> rs,ps;
  UnionFind(int n):num(n),rs(n,1),ps(n,0){
    iota(ps.begin(),ps.end(),0);
  }
  int find(int x){
    return (x==ps[x]?x:ps[x]=find(ps[x]));
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
  void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(rs[x]<rs[y]) swap(x,y);
    rs[x]+=rs[y];
    ps[y]=x;
    num--;
  }
  int size(int x){
    return rs[find(x)];
  }
  int count() const{
    return num;
  }
};
```

source: User:beet https://atcoder.jp/contests/zone2021/submissions/22207964

	   
Benq's implementation

```cpp
struct DSU {
	vector<int> e; void init(int N) { e = vector<int>(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};
	   
// Usage
DSU D;
int n,m;
vector<int> comps;

void init() {
	cin >> n >> m; D.init(n);
	for (int i = 0; i < m; ++i) {
		int a,b; cin >> a >> b;
		D.unite(a-1,b-1);
	}
	for (int i = 0; i < n; ++i) if (D.get(i) == i)
		comps.push_back(D.size(i));
}
```

source: https://usaco.guide/plat/bitsets?lang=cpp


## Union Find Data Structure Application

You are given an integer n indicating the number of people in a network. Each person is labeled from `0` to `n - 1`.

You are also given a 0-indexed 2D integer array restrictions, where `restrictions[i] = [xi, yi]` means that person `xi` and person `yi` cannot become friends, either directly or indirectly through other people.

Initially, no one is friends with each other. You are given a list of friend requests as a 0-indexed 2D integer array requests, where `requests[j] = [uj, vj]` is a friend request between person `uj` and person `vj`.

A friend request is successful if `uj` and `vj` can be friends. Each friend request is processed in the given order (i.e., `requests[j]` occurs before `requests[j + 1]`), and upon a successful request, `uj` and `vj` become direct friends for all future friend requests.

Return a boolean array result, where each `result[j]` is `true` if the `jth` friend request is successful or `false` if it is not.

Note: If `uj` and `vj` are already direct friends, the request is still successful.

```python
class Solution(object):
    def friendRequests(self, n, restrictions, requests):
        """
        :type n: int
        :type restrictions: List[List[int]]
        :type requests: List[List[int]]
        :rtype: List[bool]
        """
        ufp = [-1] * n
        ufr = [0] * n

        def _find(u):
            p = []
            while ufp[u] >= 0:
                p.append(u)
                u = ufp[u]
            for v in p:
                ufp[v] = u
            return u

        def _union(u, v):
            u = _find(u)
            v = _find(v)
            if u == v:
                return
            if ufr[u] < ufr[v]:
                u, v = v, u
            ufp[v] = u
            if ufr[u] == ufr[v]:
                ufr[u] += 1

        def _check(u, v):
            u = _find(u)
            v = _find(v)
            if u == v:
                return True
            for x, y in restrictions:
                x = _find(x)
                y = _find(y)
                assert x != y
                if x == u and y == v:
                    return False
                if x == v and y == u:
                    return False
            return True

        r = []
        for u, v in requests:
            u = _find(u)
            v = _find(v)
            if _check(u, v):
                r.append(True)
                _union(u, v)
            else:
                r.append(False)
        return r
```
