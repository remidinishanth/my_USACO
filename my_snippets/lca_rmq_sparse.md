# RANGE MINIMUM QUERY AND LOWEST COMMON ANCESTOR

## SPARSE TABLE (ST) ALGORITHM

A better approach is to preprocess RMQ for sub arrays of length 2k using dynamic programming. We will keep an array M[0, N-1][0, logN] where M[i][j] is the index of the minimum value in the sub array starting at i having length 2j. Here is an example:

![image](https://user-images.githubusercontent.com/19663316/115985129-04f2df00-a5c8-11eb-845c-af1d614d56c6.png)

For computing M[i][j] we must search for the minimum value in the first and second half of the interval. It’s obvious that the small pieces have 2^(j-1) length, so the recurrence is:

![image](https://user-images.githubusercontent.com/19663316/115985155-2653cb00-a5c8-11eb-979a-4a406fe35abd.png)

The preprocessing function will look something like this:

```cpp
void process2(int M[MAXN][LOGMAXN], int A[MAXN], int N) {
    int i, j;

    //initialize M for the intervals with length 1
    for (i = 0; i < N; i++)
      M[i][0] = i;
    //compute values from smaller to bigger intervals
    for (j = 1; 1 << j <= N; j++)
      for (i = 0; i + (1 << j) - 1 < N; i++)
        if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = M[i + (1 << (j - 1))][j - 1];
}
```
  
Once we have these values preprocessed, let’s show how we can use them to calculate RMQA(i, j). The idea is to select two blocks that entirely cover the interval [i…j] and find the minimum between them. Let k = [log(j - i + 1)]. For computing RMQA(i, j) we can use the following formula:

![image](https://user-images.githubusercontent.com/19663316/115985212-65821c00-a5c8-11eb-9535-c8186fd8d481.png)

So, the overall complexity of the algorithm is <Preprocessing, Query> = <O(N logN), O(1)>.

source: <https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor>

### Implementation

```cpp
const int N = int(1e5)+10;
const int LOGN = 20;
int A[N],msb[N],DP[LOGN][N];
LL dp[N],dp2[N];
int MX(int l,int r){
	int d = msb[r-l+1];
	int L = DP[d][l];
	int R = DP[d][r-(1<<d)+1];
	int mx = (A[L]>A[R]?L:R);
  return mx;
}

{	// inside main
	//RMQ PRE-PROCESSING
	for(int i=1;i<=n;i++)
		DP[0][i]=i;
	for(int i=1;i<LOGN;i++)
		for(int j=1;j<=n;j++)
		{
			int l = DP[i-1][j], r=DP[i-1][min(n,j+(1<<(i-1)))];
			if(A[l]>A[r])
				DP[i][j] = l;
			else
				DP[i][j] = r;
		}
	// calculating most significant bit
	for(int i=1,x=0;i<N;i++)
		if((1<<(x+1)<=i))
			msb[i]=(++x);
		else
			msb[i]=x;
}
```

source: Baba <https://codeforces.com/contest/675/submission/17946839>

Description: 1D range minimum query. Can also do queries for any associative operation in $O(1)$ with D\&C
Source: KACTL
 * Verification: 
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N logN)
 * Time: O(1)


```cpp
#define F0R(i, a) for (int i=0; i<a; i++)

template<class T> struct RMQ { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); } 
	vector<T> v; vector<vi> jmp;
	int comb(int a, int b) { // index of min
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); } 
	void init(const vector<T>& _v) {
		v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) { // get index of min element
		assert(l <= r); int d = level(r-l+1);
		return comb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};
```

source: <https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Static%20Range%20Queries%20(9.1)/RMQ%20(9.1).h>

## Lowest Common Ancestor

Given a rooted tree T and two nodes u and v, find the furthest node from the root that is an ancestor for both u and v. Here is an example (the root of the tree will be node 1 for all examples in this editorial):

![image](https://user-images.githubusercontent.com/19663316/115987367-628c2900-a5d2-11eb-8816-e66d0710ec19.png)

### DP solution

First, let’s compute a table P[1,N][1,logN] where P[i][j] is the 2j-th ancestor of i. For computing this value we may use the following recursion:

![image](https://user-images.githubusercontent.com/19663316/115987414-abdc7880-a5d2-11eb-94ef-dee27711f953.png)

The preprocessing function should look like this:

```cpp
void process3(int N, int T[MAXN], int P[MAXN][LOGMAXN]) {
   int i, j;

   //we initialize every element in P with -1
   for (i = 0; i < N; i++)
     for (j = 0; 1 << j < N; j++)
       P[i][j] = -1;

   //the first ancestor of every node i is T[i]
   for (i = 0; i < N; i++)
     P[i][0] = T[i];

   //bottom up dynamic programing
   for (j = 1; 1 << j < N; j++)
     for (i = 0; i < N; i++)
       if (P[i][j - 1] != -1)
         P[i][j] = P[P[i][j - 1]][j - 1];
 }
 ```
 
This takes O(N logN) time and space. Now let’s see how we can make queries. Let L[i] be the level of node i in the tree. We must observe that if p and q are on the same level in the tree we can compute LCA(p, q) using a meta-binary search. So, for every power j of 2 (between log(L[p]) and 0, in descending order), if P[p][j] != P[q][j] then we know that LCA(p, q) is on a higher level and we will continue searching for LCA(p = P[p][j], q = P[q][j]). At the end, both p and q will have the same father, so return T[p]. Let’s see what happens if L[p] != L[q]. Assume, without loss of generality, that L[p] < L[q]. We can use the same meta-binary search for finding the ancestor of p situated on the same level with q, and then we can compute the LCA as described below. Here is how the query function should look:

```cpp
int query(int N, int P[MAXN][LOGMAXN], int T[MAXN],
  int L[MAXN], int p, int q) {
  int tmp, log, i;

  //if p is situated on a higher level than q then we swap them
  if (L[p] < L[q])
    tmp = p, p = q, q = tmp;

  //we compute the value of [log(L[p)]
  for (log = 1; 1 << log <= L[p]; log++);
  log–-;

  //we find the ancestor of node p situated on the same level
  //with q using the values in P
  for (i = log; i >= 0; i–-)
    if (L[p] - (1 << i) >= L[q])
      p = P[p][i];

  if (p == q)
    return p;

  //we compute LCA(p, q) using the values in P
  for (i = log; i >= 0; i–)
    if (P[p][i] != -1 && P[p][i] != P[q][i])
      p = P[p][i], q = P[q][i];

  return T[p];
}
```

Now, we can see that this function makes at most 2 * log(H) operations, where H is the height of the tree. In the worst case H = N, so the overall complexity of this algorithm is <O(N logN), O(logN)>. This solution is easy to code too, and it’s faster than the previous one.

### CF blog

One of standard ways to implement constant-time LCA queries on a tree is to preprocess it by doing an Eulerian tour which creates an array of pairs (depth, index) for subsequent vertices visited on the tour, and then reduce an LCA query to RMQ query on a certain fragment of this array:

```cpp
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,n) for(int i=(a);i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N = 1<<LOGN;
typedef pair<int,int> pii;
int n, T;
vector<int> adj[N];  // adjacency lists
pii euler[2*N];  // Eulerian tour of pairs (depth, index)
int tin[N];  // visit times for vertices

void dfs(int v, int par, int depth) {
  tin[v] = T;
  euler[T++] = make_pair(depth, v);
  FORE(i,adj[v]) if (*i != par) {
    dfs(*i, v, depth+1);
    euler[T++] = make_pair(depth, v);
  }
}

dfs(0, -1, 0);

int lca(int u, int v) {
  return query_rmq(min(tin[u], tin[v]), max(tin[u], tin[v]) + 1).second;
}
```

The RMQ problem can be solved with a sparse table, which after 𝑂(𝑛log𝑛) preprocessing allows to answer RMQ queries in constant time:

```cpp
pii sparse[LOGN][N];
int log[2*N];  // binary logarithm

void init_rmq() {
  REP(i,T) { sparse[0][i] = euler[i]; }
  int logT = 0;
  while ((1<<logT) < T) { ++logT; }
  REP(f,logT) REP(i,T - (1<<f)) {
    sparse[f+1][i] = min(sparse[f][i], sparse[f][i + (1<<f)]);
  }
  log[0] = -1;
  FOR(i,1,T) { log[i] = 1 + log[i>>1]; }
}

pii query_rmq(int a, int b) {
  // query range [a, b)
  int f = log[b-a];
  return min(sparse[f][a], sparse[f][b - (1<<f)]);
}
```

source: <https://codeforces.com/blog/entry/67138>, <https://codeforces.com/contest/986/submission/38947175>
