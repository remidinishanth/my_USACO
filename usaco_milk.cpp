/*
ID: remidin1
TASK: milk 
LANG: C++11                 
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long unsigned int llui;
typedef pair<int,int> ii;
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
#define SORT(x) sort((x).begin(),(x).end())
#define UNIQUE(x) SORT(x),(x).erase(unique((x).begin(),(x).end()),(x).end())
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound
#define SZ(a) int((a).size())
#define clr(a) memset(a,0,sizeof(a))
#define SET(a,b) memset(a,b,sizeof(a))

#define FOR(i,a,b) for (int i = int(a); i < int(b); i++)
#define FORD(i,a,b) for(int i=int(b)-1; i>=int(a); i--)
#define REP(i, n) for (int i = 0; i < int(n); i++)
#define REP1(i,n) for (int i = 1; i <= int(n); i++)
#define REV(i, n) for (int i = int(n)-1; i >=0 ; i--)

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

/////////////////////////////////////////////////////////////////////

const int MAX_N = 2234506;
//int arr[MAX_N];

int main(){
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    int N,M;
    fin>>N>>M;
    vii V(M);
    REP(i,M){
        fin>>V[i].F>>V[i].S;
    }
    SORT(V);
    int t=0,x;
    ll ans=0;
    REP(i,M){
        x=min(N-t,V[i].S);
       ans+=1LL*V[i].F*x; 
       t+=x;
    }
    fout<<ans<<"\n";
	return 0;
}
