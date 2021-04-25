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
