/*
ID: remidin1
TASK: transform
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

int n;

bool test(vvi &I,vvi &O){
    REP(i,n) REP(j,n) if(I[i][j]!=O[i][j]) return false;
    return true;
}

vvi rotate(vvi &I){
    vvi V(n,vi(n));
    REP(i,n) REP(j,n) V[i][j]=I[n-1-j][i];
    return V;
}

vvi reflect(vvi &I){
    vvi V(n,vi(n));
    REP(i,n) REP(j,n) V[i][j]=I[i][n-1-j];
    return V;
}

int main(){
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    fin>>n;
    vvi I(n,vi(n)),O(n,vi(n)),T;
    char c;
    REP(i,n) REP(j,n){ fin>>c; I[i][j]=c-'a';}
    REP(i,n) REP(j,n){ fin>>c; O[i][j]=c-'a';}
    T=rotate(I);
    if(test(O,T)){ fout<<"1"<<"\n"; return 0;}
    T=rotate(T);
    if(test(O,T)){ fout<<"2"<<"\n"; return 0;}
    T=rotate(T);
    if(test(O,T)){ fout<<"3"<<"\n"; return 0;}
    if(test(I,O)){ fout<<"6"<<"\n"; return 0;}
    T=reflect(I);
    if(test(O,T)){ fout<<"4"<<"\n"; return 0;}
    T=rotate(T);
    if(test(O,T)){ fout<<"5"<<"\n"; return 0;}
    T=rotate(T);
    if(test(O,T)){ fout<<"5"<<"\n"; return 0;}
    T=rotate(T);
    if(test(O,T)){ fout<<"5"<<"\n"; return 0;}
    fout<<7<<"\n";
	return 0;
}
