TODO https://codeforces.com/blog/entry/47764

TODO https://apps.topcoder.com/forums/?module=Thread&threadID=700080&start=0

## Expected Number DP

### J Sushi Atcoder
https://atcoder.jp/contests/dp/tasks/dp_j

There are `N((1 ≤ N ≤ 300)` dishes, numbered `1,2,...,N`. Initially, for each `i(1 ≤ i ≤ N)`, Dish `i` has `ai(1 ≤ ai ≤ 3)` pieces of sushi on it.

Taro will perform the following operation repeatedly until all the pieces of sushi are eaten:
* Roll a die that shows the numbers `1,2, … ,N` with equal probabilities, and let `i` be the outcome. If there are some pieces of sushi on Dish `i` , eat one of them; if there is none, do nothing.

Find the expected number of times the operation is performed before all the pieces of sushi are eaten.

**Input**
```
N
a1 a2 ... aN
```

#### Solution

If we choose our subproblem or DP state to be something like `dp(r1,r2,...,rN)` where `ri` is the number of remaining sushi in `i-th` dish, the number of DP states will be `O(4^N)` because `0 ≤ ri ≤ 3` and `0 ≤ i ≤ N`

So instead of considering each `i-th` dish seperately we can combine them and use the state `dp(i,j,k)`, where `i` denotes number of dishes with `1 sushi`, `j` denotes number of dishes with `2 sushi` and `k` denotes number of dishes with `3 sushi`, `(N-i-j-k)` will be number of dishes with `0 sushi` left. The number of DP state will now be `O(N^3)`

Relation between subproblems
```
dp[i,j,k] = k/N . ( dp[i,j,k-1] + 1) + j/N . (dp[i,j-1,k] + 1) +  i/N . (dp[i-1,j,k] + 1) + (N-i-j-k)/N . (dp[i,j,k] + 1)
```

We also have `dp[i,j,k]` on the right side, grouping `dp[i,j,k]` we get
```
dp[i,j,k] = k/(i+j+k) . (dp[i,j,k-1] + 1) + j/(i+j+k) . (dp[i,j-1,k] + 1) + i/(i+j+k) . (dp[i-1,j,k] + 1) + (N-i-j-k)/(i+j+k)
```

After simplification we get
```
dp[i,j,k] = k/(i+j+k) . (dp[i,j,k-1]) + j/(i+j+k) . (dp[i,j-1,k]) + i/(i+j+k) . (dp[i-1,j,k]) + N/(i+j+k)
```

Code
```cpp
double dp[305][305][305];
int n,a[3];
// expected number of days to get from (a,b,c) to (0,0,0)
double rec(int a,int b,int c){
	if(dp[a][b][c] >= -1e16) return dp[a][b][c];
	if(a+b+c == 0) return 0.0;
	double sum = 0;
	if(a) sum += (double)(a)/(double)(a+b+c)*rec(a-1,b,c);
	if(b) sum += (double)(b)/(double)(a+b+c)*rec(a+1,b-1,c);
	if(c) sum += (double)(c)/(double)(a+b+c)*rec(a,b+1,c-1);
	sum += 1.0*(double)(n)/(double)(a+b+c);
	return dp[a][b][c] = sum;
}
int main(){
	cin>>n;
	for(int i=0;i<305;i++) for(int j=0;j<305;j++) for(int k=0;k<305;k++){
		dp[i][j][k]=-1e18;
	}
	for(int i=0;i<305;i++) for(int j=0;j<305;j++) for(int k=0;k<305;k++){
		if(i+j+k > n) continue;
		dp[i][j][k] = rec(i,j,k);
	}
	rep(i,n){
		int x; cin>>x; a[x-1]++;
	}
	printf("%.12f\n",dp[a[0]][a[1]][a[2]]);
}
```
source: https://atcoder.jp/contests/dp/submissions/3943172

Using probabilities

```cpp
const int nax = 305;
double p[nax][nax][nax], ev[nax][nax][nax];
// p[a][b][c] - the probability to get to state(a,b,c)
// ev[a][b][c] - the expected number of operations so far to get to state (a,b,c)
 
int main() {
    int n;
    scanf("%d", &n);
    vector<int> cnt(4);
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        ++cnt[x];
    }
    p[cnt[1]][cnt[2]][cnt[3]] = 1; // initial state (ones, twos, threes)
    for(int c = n; c >= 0; --c) {
        for(int b = n; b >= 0; --b) {
            for(int a = n; a >= 0; --a) {
                if(a == 0 && b == 0 && c == 0) {
                    continue;
                }
                if(a + b + c > n) {
                    continue;
                }
                
                double p_waste = (double) (n - (a + b + c)) / n;
                // p_waste + p_waste^2 + ... = S
                // 1 + S = S / p_waste, S = p_waste/(1 - p_waste)
                double ev_waste = p_waste / (1 - p_waste) + 1;
		/*
		The above can also be written as
		    ev_waste = p_waste(1 + ev_waste) + (1 - p_waste)*1
		    ev_waste = 1/(1 - p_waste)
		which is what we get after ev_waste = p_waste/(1 - p_waste) + 1;
		*/
                debug() << imie(a) imie(b) imie(c) imie(ev_waste);
                ev[a][b][c] += ev_waste * p[a][b][c];
                
                // remove 1 -> dp[a-1][b][c]
                // we will eventually choose one of a+b+c
                if(a != 0) {
                    double p_go = (double) a / (a + b + c);
                    p[a-1][b][c] += p[a][b][c] * p_go;
                    ev[a-1][b][c] += ev[a][b][c] * p_go;
                }
                
                // remove 2 -> dp[a+1][b-1][c]
		// number of two sushi will decrease, number of one sushi will increase
                if(b != 0) {
                    double p_go = (double) b / (a + b + c);
                    p[a+1][b-1][c] += p[a][b][c] * p_go;
                    ev[a+1][b-1][c] += ev[a][b][c] * p_go;
                }
                
                // remove 3
                if(c != 0) {
                    double p_go = (double) c / (a + b + c);
                    p[a][b+1][c-1] += p[a][b][c] * p_go;
                    ev[a][b+1][c-1] += ev[a][b][c] * p_go;
                }
            }
        }
    }
    printf("%.10lf\n", ev[0][0][0]);
}
```

source: Errichto https://atcoder.jp/contests/dp/submissions/4303017

## Game Theory, optimization

### L Deque Atcoder
source: https://atcoder.jp/contests/dp/tasks/dp_l

Taro and Jiro will play the following game against each other. Initially, they are given a sequence `a=(a1,a2,…,aN)`. Until `a` becomes empty, the two players perform the following operation alternately, starting from Taro.
* Remove the element at the beginning or the end of a . The player earns x points, where x is the removed element.

Let X and Y be Taro's and Jiro's total score at the end of the game, respectively. Taro tries to maximize `X − Y` , while Jiro tries to minimize `X − Y`.
Assuming that the two players play optimally, find the resulting value of `X − Y` if `1 ≤ N ≤ 3000` and `1 ≤ ai ≤ 10^9`

#### Solution

Let `dp[i][j][0/1]` denote be the value if first/second player starts from deque[i:j]

```cpp
using ll = long long;
ll dp[3005][3005][2];
 
int main(){
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    REP(i,n) scanf("%d", &a[i]);
    for(int l=0;l<n;l++){
        for(int i=0;i+l<n;i++){
            if(l==0){
                dp[i][i][0] = a[i];
                dp[i][i][1] = -a[i];
            }else{
                dp[i][i+l][0] = max(dp[i][i+l-1][1]+a[i+l],dp[i+1][i+l][1]+a[i]);
                dp[i][i+l][1] = min(dp[i][i+l-1][0]-a[i+l],dp[i+1][i+l][0]-a[i]);
            }
        }
    }
    pl(dp[0][n-1][0]);
    return 0;
}
```

Observation: In the above solution `dp[i][j][0] = -dp[i][j][1]`. Hence we can modify and just use what is the value if first player starts from deque[i:j] and simplify to the following code
```
using ll = long long;
const int nax = 3005;
ll dp[nax][nax];
 
int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    // dp[0][n-1]
    for(int L = n - 1; L >= 0; --L) {
        for(int R = L; R < n; ++R) {
            if(L == R) {
                dp[L][R] = a[L];
            }
            else {
                dp[L][R] = max(a[L] - dp[L+1][R], a[R] - dp[L][R-1]);
            }
        }
    }
    printf("%lld\n", dp[0][n-1]);
}
```
