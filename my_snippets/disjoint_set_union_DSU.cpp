// The best way I've seen to 
// code this kind of DSU, is style of bmerry : (C++)

// Algorithm Gym :: Data structures by DarthKnight // CF

//initially are parents are set to -1

// for each root v, 
// par[v] equals the negative of number of tools in that box.

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}

void merge(int x,int y){	//	x and y are some tools (vertices)
	if((x = root(x)) == (y = root(y))  return ;
	if(par[y] < par[x])	// balancing the height of the tree
		swap(x, y);
	par[x] += par[y];
	par[y] = x;
}


// source: kmjp https://kmjp.hatenablog.jp/entry/2020/06/18/0900
// https://codeforces.com/contest/1278/submission/67749296
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
// can directly use uf[y]==uf[x] to check whether both are in same union and uf(y,x); to combine both of them

	   
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
// source: User:beet https://atcoder.jp/contests/zone2021/submissions/22207964
