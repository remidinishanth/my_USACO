#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long unsigned int llui;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector< vector<int> > vvi;
typedef set<int> si;
typedef map<string, int> msi;
typedef map<int, int> mii;

#define INF 1000000000
#define MOD 1000000007
#define EPS 1e-9
#define DEBUG(x) cout<< '>' << #x << ':' << x << "\n";
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SORT(x) sort((x).begin(),(x).end())
#define UNIQUE(x) SORT(x),(x).erase(unique((x).begin(),(x).end()),(x).end())
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound
#define SZ(a) int((a).size())
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a,b) memset(a,b,sizeof(a))

#define FOR(i,a,b) for (int i = int(a); i < int(b); i++)
#define FORD(i,a,b) for(int i=int(b)-1; i>=int(a); i--)
#define REP(i, n) for (int i = 0; i < int(n); i++)
#define REP1(i,n) for (int i = 1; i <= int(n); i++)
#define REV(i, n) for (int i = int(n)-1; i >=0 ; i--)

#define sd(n) scanf("%d",&n)
#define dsd(n) int n; scanf("%d",&n)
#define sd2(a,b) scanf("%d%d",&a,&b)
#define dsd2(a,b) int a,b; scanf("%d%d",&a,&b)
#define sd3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define dsd3(a,b,c) int a,b,c; scanf("%d%d%d",&a,&b,&c)
#define pd(n) printf("%d\n",n)
#define pds(n) printf("%d ",n)
#define sll(n) scanf("%lld",&n)
#define dsll(n) ll n; scanf("%lld",&n)
#define sll2(a,b) scanf("%lld%lld",&a,&b)
#define dsll2(a,b) ll a,b; scanf("%lld%lld",&a,&b)
#define sll3(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define dsll3(a,b,c) ll a,b,c; scanf("%lld%lld%lld",&a,&b,&c)
#define pll(n) printf("%lld\n",n)	
#define plls(n) printf("%lld ",n)	

#define trace(x) cout << '>' << #x << ':' << x << "\n"
#define trace2(x,y) cout<< '>' << #x << ':' << x << " | " << #y << ':' << y << "\n"
#define trace3(a,b,c) cout<<#a<<"="<<(a)<<", "<<#b<<"="<<(b)<<", "<<#c<<"="<<(c)<<"\n"
#define trace4(a,b,c,d) cout<<#a<<"="<<(a)<<", "<<#b<<"="<<(b)<<", "<<#c<<"="<<(c)<<", "<<#d<<"="<<(d)<<"\n"

#define PR(a,n) { cout<<#a<<" = "; REP(_,n) cout<<a[_]<<' '; cout<<"\n"; }
#define PR1(a,n) { cout<<#a<<" = "; REP1(_,n) cout<<a[_]<<' '; cout<<"\n"; }
#define _W(a,n) { REP(_,n) cout<<a[_]<<' '; cout<<"\n"; }

inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }

#define LSOne(S) (S&(-S))

const double pi = acos(-1);
const int oo = 0x3f3f3f3f;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

template<class T> bool uin(T &a,T b) {return a > b ? (a=b, true):false;}
template<class T> bool uax(T &a,T b) {return a < b ? (a=b, true):false;}

/////////////////////////////////////////////////////////////////////

const int MAX_N = 5*1010*100;
//const int MAXN = 510;
//int arr[MAXN][MAXN];

int main(){
    return 0;
}
