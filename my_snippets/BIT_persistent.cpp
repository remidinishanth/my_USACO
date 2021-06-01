// BIT or Fenwick Tree
int n;
int tree[100005];
#define lowbit(x) x&(-x)
inline void modify(int x,int d){
	for(;x<=n;x+=lowbit(x))tree[x]+=d;
}
inline int query(int x){
	int ans=0;
	for(;x;x-=lowbit(x))ans+=tree[x];
	return ans;
}

// Persistent Fenwick Tree using Fat Node persistence
#include<vector>
#include<algorithm>
#define lowbit(x) x&(-x)
struct P{
	int data,id;
	P(int d=0,int i=0):data(d),id(i){}
	inline friend bool operator<(const P &a,const P &b){
		return a.id<b.id;
	}
};
int n,now;
std::vector<P >tree[100005];
inline void init(){
	now=0;
	for(int i=1;i<=n;++i)tree[i].clear(),tree[i].push_back(P());
}
inline void modify(int x,int d){
	for(;x<=n;x+=lowbit(x))tree[x].push_back(P(tree[x].back().data+d,now));
	++now;
}
inline int query(int x,int id){/*查詢第id次操作的區間和，id從0開始計算*/
	int ans=0;
	std::vector<P >::iterator a;
	for(;x;x-=lowbit(x)){
		a=std::upper_bound(tree[x].begin(),tree[x].end(),P(0,id))-1;
		ans+=a->data;
	}
	return ans;
}
