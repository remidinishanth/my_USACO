#include <bits/stdc++.h>
using namespace std;
const int inf = (1 << 30) - 1;

// 0 - indexed
template <typename Monoid>
struct Segmenttree
{
	using F = function<Monoid(Monoid, Monoid)>;
	const Monoid e;
	const F f;

	int sz;
	vector<Monoid> seg;

	// size, operator, unit
	Segmenttree(int N, const F &f, const Monoid &e) : f(f), e(e)
	{
		sz = 1;
		while (sz < N)
			sz *= 2;
		seg.assign(2 * sz - 1, e);
	}

	void set(int k, const Monoid &x) { seg[k + sz - 1] = x; }

	void build()
	{
		for (int k = sz - 2; k >= 0; k--)
		{
			seg[k] = f(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}

	void update(int k, const Monoid &x)
	{
		k += sz - 1;
		seg[k] = x;
		while (k > 0)
		{
			k = (k - 1) / 2;
			seg[k] = f(seg[k * 2 + 1], seg[k * 2 + 2]);
		}
	}

	Monoid sub_query(int a, int b, int k, int l, int r)
	{
		if (r <= a || b <= l)
			return e;

		if (a <= l && r <= b)
			return seg[k];
		else
		{
			Monoid vl = sub_query(a, b, k * 2 + 1, l, (l + r) / 2);
			Monoid vr = sub_query(a, b, k * 2 + 2, (l + r) / 2, r);
			return f(vl, vr);
		}
	}

	// [l, r)
	Monoid query(int l, int r)
	{
		return sub_query(l, r, 0, 0, sz);
	}

	Monoid operator[](const int &k) const
	{
		return seg[k + sz];
	}
};

auto RMQ = [](int a, int b) { return min(a, b); };

int main()
{
	int N, Q;
	cin >> N >> Q;
	Segmenttree<int> seg(N, RMQ, inf);
	for (int i = 0; i < N; i++)
	{
		int a;
		cin >> a;
		seg.set(i, a);
	}

	seg.build();

	while (Q--)
	{
		int f;
		cin >> f;
		if (f == 1)
		{
			int l, r;
			cin >> l >> r;
			l--, r--;
			cout << seg.query(l, r + 1) << "\n";
		}
		if (f == 2)
		{
			int i, a;
			cin >> i >> a;
			i--;
			seg.update(i, a);
		}
	}
}

// https://kcs.miz-miz.biz/contest/7/code/100184
// https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree.cpp


/**
 * @brief Segment-Tree(セグメント木)
 * @docs docs/segment-tree.md
 */
template< typename Monoid, typename F >
struct SegmentTree {
  int sz;
  vector< Monoid > seg;

  const F f;
  const Monoid M1;
  
  SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz, M1);
  }

  void set(int k, const Monoid &x) {
    seg[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  void update(int k, const Monoid &x) {
    k += sz;
    seg[k] = x;
    while(k >>= 1) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  Monoid query(int a, int b) {
    Monoid L = M1, R = M1;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) L = f(L, seg[a++]);
      if(b & 1) R = f(seg[--b], R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) const {
    return seg[k + sz];
  }

  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }

  template< typename C >
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
      return -1;
    }
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, seg[a]);
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }

  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
      return -1;
    }
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(seg[--b], R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};

template< typename Monoid, typename F >
SegmentTree< Monoid, F > get_segment_tree(int N, const F& f, const Monoid& M1) {
  return {N, f, M1};
}


// Usage
// https://atcoder.jp/contests/abc186/submissions/18884010
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
template<class T> bool chmin(T& a,T b){if(a>b) {a = b; return true;} return false;}
template<class T> bool chmax(T& a,T b){if(a<b) {a = b; return true;} return false;}
#define rep(i,n) for(int i=0;i<(n);i++)
#define drep(i,n) for(int i=(n)-1;i>=0;i--)
#define all(x) (x).begin(),(x).end()
#define debug(x)  cerr << #x << " = " << (x) << endl;
 
template<typename Monoid,typename F>
class SegmentTree{
private:
    int sz;
    vector<Monoid> seg;
    const F op;
    const Monoid e;
public:
    SegmentTree(int n,const F op,const Monoid &e):op(op),e(e){
        sz = 1;
        while(sz<=n) sz <<= 1;
        seg.assign(2*sz,e);
    }
    void set(int k, const Monoid &x){
        seg[k+sz] = x;
    }
    void build(){
        for(int i=sz-1;i>0;i--){
            seg[i] = op(seg[2*i],seg[2*i+1]);
        }
    }
    void update(int k,const Monoid &x){
        k += sz;
        seg[k] = x;
        while(k>>=1){
            seg[k] = op(seg[2*k],seg[2*k+1]);
        }
    }
    Monoid query(int l,int r){
        Monoid L = e,R = e;
        for(l+=sz,r+=sz;l<r;l>>=1,r>>=1){
            if(l&1) L = op(L,seg[l++]);
            if(r&1) R = op(seg[--r],R);
        }
        return op(L,R);
    }
    Monoid operator[](const int &k)const{
        return seg[k+sz];
    }
};
 
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll H,W,M;
    cin >> H >> W >> M;
    vec<ll> X(M),Y(M);
    vvec<ll> posx(H);
    ll h = H,w = W;
    rep(i,M){
        cin >> X[i] >> Y[i];
        X[i]--,Y[i]--;
        posx[X[i]].push_back(Y[i]);
        if(Y[i]==0) chmin(h,X[i]);
        if(X[i]==0) chmin(w,Y[i]);
    }
    rep(i,H){
        posx[i].push_back(W);
        if(i>=h) posx[i].push_back(0);
        sort(all(posx[i]));
        posx[i].erase(unique(all(posx[i])),posx[i].end());
    }
    ll ans = H*W;
    SegmentTree seg(W,[](ll a,ll b){return a+b;},0LL);
    for(int j=w;j<W;j++) seg.set(j,1);
    seg.build();
    rep(i,H){
        int n = posx[i].size();
        rep(j,n-1){
            ans--;
            ans -= seg.query(posx[i][j]+1,posx[i][j+1]);
            seg.update(posx[i][j],1);
        }
    }
    cout << ans << "\n";
}
