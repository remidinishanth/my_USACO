TODO https://codeforces.com/blog/entry/47764

TODO https://apps.topcoder.com/forums/?module=Thread&threadID=700080&start=0

TODO https://codeforces.com/blog/entry/8219

TODO https://www.students.cs.ubc.ca/~cs-490/2017W2/lec06.pdf & DP optimizations https://sites.google.com/site/ubcprogrammingteam/educational?authuser=0

### Things to watch out
1. Whether your subproblem array indicies become negative or will exceed bounds.

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

Using probabilities `ev_waste = p_waste / (1 - p_waste) + 1;`. Current step always uses a turn no matter what happens, the rest of the sum is the expected number of additional turns after this one.

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

**Bonus**: https://math.stackexchange.com/questions/2772873/show-that-n-sum-k-1n-frac1k-sim-n-logn-collectors-problem

Consider coupons numbered `1,2,...,n`, which you collect until you have all numbers. Each time you get a coupon, its number is independent of previous numbers and all numbers are equally likely. Let `n` be the number of coupons you need,

![image](https://user-images.githubusercontent.com/19663316/117919450-a4270e80-b30a-11eb-9b7b-b4166824bc60.png)

So in the above problem if all the sushis are '1', then answer will be `N log(N)`


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

Observation: In the above solution `dp[i][j][0] = -dp[i][j][1]`. Hence we can modify and just use what is the value if first player starts from deque[i:j] and simplify to the following code. 

An alternative way to think is that `dp[i][j]` denotes by how much difference `X - Y` does the first player win.

```cpp
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
The above problem can be solved in O(n). REF: https://qr.ae/pGnaCy, https://youtu.be/pOv4LRNt0jo

TODO: `Termites` by Tomasz Idziaszek from Looking for a challenge book.

### Game in Momotetsu World

We have a grid with `H` rows and `W` columns of squares, where each square is blue or red. The square at the `i-th` row and `j-th` column is blue if `A[i][j]` is `+`, and red if `A[i][j]` is `-`. There is a piece on this grid, which is initially placed on the top-left square. Takahashi and Aoki will play a game using this piece. Each of the two players has `0` points in the beginning. They will alternately do the following operation, with Takahashi going first: Move the piece one square right or one square down. It is not allowed to move the piece outside the grid. Then, the player (who moved the piece) gets one point if the piece is now on a blue square, and loses one point if the piece is now on a red square. The game ends when one of the players is unable to do the operation. Then, the player with the greater number of points wins the game if they have different numbers of points. Otherwise, the game is drawn. Find the result of the game when both players play the game to get the best outcome.

**Solution**

Let `dp[i][j]` be a `pair<int,int>` which stores the scores of `Takshahi` and `Aoki` when they playing from submatrix `(i,j)` to `(h-1, w-1)`.
```cpp
    dp[h-1][w-1] = {0, 0};
    for(int i=h-1;i>=0;i--){
        for(int j=w-1;j>=0;j--){
            if(i==h-1 && j==w-1) continue;
            int tak = (i+j+1)%2;
            if(tak) dp[i][j] = {-INF, 0};
            else dp[i][j] = {0, -INF};
            if(i+1 < h){
                int sign = (V[i+1][j] == '+' ? 1 : -1);
                if(tak){
                    if(dp[i][j].F - dp[i][j].S < dp[i+1][j].F - dp[i+1][j].S + sign){
                        dp[i][j] = dp[i+1][j];
                        dp[i][j].F = dp[i+1][j].F + sign;
                    }
                }else{
                    if(dp[i][j].S - dp[i][j].F < dp[i+1][j].S -dp[i+1][j].F + sign){
                        dp[i][j] = dp[i+1][j];
                        dp[i][j].S = dp[i+1][j].S + sign;
                    }
                }
            }
            if(j+1 < w){
                int sign = (V[i][j+1] == '+' ? 1 : -1);
                if(tak){
                    if(dp[i][j].F - dp[i][j].S < dp[i][j+1].F -dp[i][j+1].S + sign){
                        dp[i][j] = dp[i][j+1];
                        dp[i][j].F = dp[i][j+1].F + sign;
                    }
                }else{
                    if(dp[i][j].S - dp[i][j].F < dp[i][j+1].S -dp[i][j+1].F + sign){
                        dp[i][j] = dp[i][j+1];
                        dp[i][j].S = dp[i][j+1].S + sign;
                    }
                }
            }
        }
    }
    int f = dp[0][0].F;
    int s = dp[0][0].S;
    if(f > s){
        printf("Takahashi\n");
    }else if(s>f){
        printf("Aoki\n");
    }else printf("Draw\n");
```

Observation: All we need to minimize is `dp[i][j].F - dp[i][j].S` if this is positive in the ending then Takshashi wins, by using this the above code can be simplified.

```cpp
    IREP(i, H) IREP(j, W) {
        if (i == H - 1 and j == W - 1) continue;
        int t = (i + j) % 2;
        dbg(t);
        if (t == 0) {
            dp[i][j] = -INF;
            if (i + 1 < H) chmax(dp[i][j], dp[i + 1][j] + (S[i + 1][j] == '+' ? 1 : -1)); // Takshashi tries to maximize it
            if (j + 1 < W) chmax(dp[i][j], dp[i][j + 1] + (S[i][j + 1] == '+' ? 1 : -1));
        } else {
            dp[i][j] = INF;
            if (i + 1 < H) chmin(dp[i][j], dp[i + 1][j] - (S[i + 1][j] == '+' ? 1 : -1)); // Aoki tries to minimize the score
            if (j + 1 < W) chmin(dp[i][j], dp[i][j + 1] - (S[i][j + 1] == '+' ? 1 : -1));
        }
    }
    if (dp[0][0] > 0) puts("Takahashi");
    else if (dp[0][0] < 0) puts("Aoki");
    else puts("Draw");
```

Remember this trick to simplify the code in Game Theory DP problems.

## Combinatorics & Prefix sum trick in DP

### M Candies Atcoder DP

source: https://atcoder.jp/contests/dp/tasks/dp_m

There are `N (1 ≤ N ≤ 100)` children, numbered `1 , 2 , … , N`. They have decided to share `K  (1 ≤ K ≤ 10^5)` candies among themselves. Here, for each `i ( 1 ≤ i ≤ N )`, Child `i` must receive between `0` and `ai (0 ≤ ai ≤ K)` candies (inclusive). Also, no candies should be left over. Find the number of ways for them to share candies, modulo `10^9 + 7`. Here, two ways are said to be different when there exists a child who receives a different number of candies.

#### Solution

let `dp[i][j]` denote the number of ways of distributing `j` candies between first `i` children.

Transition `dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-ai]` assume that `d[i-1][j]` = 0 if `j` is negative.

Since `1 ≤ i ≤ maxN = 100` and `1 ≤ j ≤ maxK = 10^5` and `1 ≤ ai ≤ maxK = 10^5`, the time limit is` O(N.K^2)`. We get TLE if we compute the above DP directly. But if we observe the relation, we find that we can compute this efficiently with prefix sums, therefore `dp[i][j] = prefix_sum([i-1][j]) - prefix_sum(dp[i-1][j-ai-1])`, we can compute `prefix_sum` once for every `i` and can solve the problem in `O(NK)`

```cpp
#include <bits/stdc++.h>
using namespace std;

int dp[105][100005];
int MOD = 1e9 + 7;
 
int main(){
    int n,k;
    scanf("%d%d", &n, &k);
    vector<int> A(n);
    for(int i=0;i<n;i++) scanf("%d", &A[i]);
    dp[0][0] = 1; // base case
    for(int i=0;i<n;i++){
        vector<int> prefix_sum(k+1);
        prefix_sum[0] = dp[i][0];
        for(int j=1;j<=k;j++){
            prefix_sum[j] = (1ll*prefix_sum[j-1] + dp[i][j])%MOD;
        }
        for(int j=0;j<=k;j++){
            int remove = 0;
            if(j>A[i]){
                remove = prefix_sum[j-A[i]-1];
            }
            dp[i+1][j] = (1ll*prefix_sum[j] - remove + MOD)%MOD;
        }
    }
    printf("%d\n", dp[n][k]);
    return 0;
}
```

### Segment tree to find maximum in log time.

There are `N (1 ≤ N ≤ 2×10^5)` flowers arranged in a row. For each `i ( 1 ≤ i ≤ N )`, the height and the beauty of the `i-th` flower from the left is `hi` and `ai (1 ≤ ai ≤ 10^9)`, respectively. Here, `h1, h2, …, hN` are all distinct and `(1 ≤ hi ≤ N)`.

Taro is pulling out some flowers so that the following condition is met:

* The heights of the remaining flowers are monotonically increasing from left to right.

Find the maximum possible sum of the beauties of the remaining flowers.

#### Solution
Let `dp[i]` be the solution till `i-th` flower. When we are at `i-th` flower, we want to find `max( dp[j] for all j such that h[j] < h[i]) + ai`. To answer the problem for subproblem faster, we can use segment tree using `hj (1 ≤ hi ≤ N)` as index  and `dp[j]` as value and solve this problem is `O(N logN)`.

<details>
	<summary> Segment Tree solution </summary>
	
```cpp
using ll = long long;
 
void max_self(ll& a, ll b) {
    a = max(a, b);
}
 
 
int main() {
    int n;
    scanf("%d", &n);
    
    int base = 1;
    while(base <= n) {
        base *= 2;
    }
    // base is the smallest power of 2 that is not smaller than n
    // iterative implementation
    vector<ll> tree(2 * base);
    
    vector<int> h(n), a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    vector<ll> dp(n + 1);
    // dp[i] - the max total beauty so far if the last taken flower has height i
    for(int flower = 0; flower < n; ++flower) {
        
        // max dp[i] for i in [0, h[flower]-1]
        int x = h[flower] + base;
        ll best = 0;
        while(x > 1) {
            if(x % 2 == 1) {
                max_self(best, tree[x-1]);
            }
            x /= 2;
        }
        dp[h[flower]] = best + a[flower];
        
        for(int i = base + h[flower]; i >= 1; i /= 2) {
            max_self(tree[i], dp[h[flower]]);
        }
        
        //~ for(int i = 0; i < h[flower]; ++i) { // brute force dp, TLE
            //~ max_self(dp[h[flower]], dp[i] + a[flower]);
        //~ }
    }
    ll answer = 0;
    for(int i = 0; i <= n; ++i) {
        max_self(answer, dp[i]);
    }
    printf("%lld\n", answer);
}
```
</details>

## Dynamic Programming and Bit Masking

### Assignment Problem
source: https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/tutorial/

There are `N` persons and `N` tasks, each task is to be alloted to a single person. We are also given a matrix `cost` of size `N x N`, where `cost[i][j]` denotes, how much person `i` is going to charge for task `j`. Now we need to assign each task to a person in such a way that the total cost is minimum. Note that each task is to be alloted to a single person, and each person will be alloted only one task.

#### Solution
The brute force approach here is to try every possible assignment. Algorithm is given below:
```python
assign(N,  cost)
    for i = 0 to N
        assignment[i] = i            //assigning task i to person i
    res = INFINITY
    for j = 0 to factorial(N)
        total_cost = 0
        for i = 0 to N
            total_cost = total_cost + cost[i][assignment[i]]
        res = min(res, total_cost)
        generate_next_greater_permutation(assignment)
    return res
```

The complexity of above algorithm is , well that's clearly not good.

#### DP bitmask solution

Let's try to improve it using dynamic programming. When we want to assign a task to person `k`, all that matters is which of the tasks have been assigned already. Suppose that state of `dp` is `(k, mask)`, where `k` represents that person `0` to `k-1` have been assigned a task, and `mask` is a binary number, whose `i-th` bit represents if the `i-th` task has been assigned or not.

Now, suppose, we have `answer(k, mask)`, we can assign a task `i` to person `k`, iff `i-th` task is not yet assinged to any person i.e, `mask & (1 << i) = 0` then, `answer(k+1, mask | (1 << i)` will be given as:

```answer(k + 1, mask | (1 << i)) = min( answer(k + 1, mask | (1 << i)), answer(k, mask) + cost[k][i])```

One thing to note here is `k` is always equal to the number of set bits in `mask`, so we can remove that. So the dp state now is just `(mask)`, ans if we have `answer(mask)`, then

```answer(mask | (1 << i)) = min( answer(mask | (1 << i)), answer(mask) + cost[x][i])```

here `x` = number of set bits in `mask`.

```python
assign(N, cost)
    for i = 0 to power(2,N)
        dp[i] = INFINITY
    dp[0] = 0
    for mask = 0 to power(2, N)
        x = count_set_bits(mask)
        for j = 0 to N
            if jth bit is not set in i
                dp[mask|(1<<j)] = min(dp[mask|(1<<j)], dp[mask]+cost[x][j])
    return dp[power(2,N)-1]                
```

Time complexity of above algorithm is `O(n 2^n)` and space complexity if `O(2^n)`.

### Matching problem

There are `N (1 ≤ N ≤ 21)` men and `N` women, both numbered `1 , 2 , … , N`. For each `i , j ( 1 ≤ i , j ≤ N )`, the compatibility of Man `i` and Woman `j` is given as an integer a `i` , `j` . If `a[i,j]` = 1 , Man `i` and Woman `j` are compatible; if `a[i ,j] = 0`, they are not. Taro is trying to make N pairs, each consisting of a man and a woman who are compatible. Here, each man and each woman must belong to exactly one pair. Find the number of ways in which Taro can make `N` pairs, modulo `10^9 + 7`.

#### Solution

A brute force dp solution can take `O(n^2. 2^n)` time. `solve(i, mask)` is the number of ways of matching `[i:]` men, `mask` represents women matched till now using bitmask. Solution to original problem is `solve(0, 0)`.

source: https://atcoder.jp/contests/dp/submissions/3947427

```cpp
ll solve(int i,int mask){
	if(i==n) return mask==lim;
	if(dp[i][mask]!=-1) return dp[i][mask];
	ll c = 0;
	for(int j=0; j<n; j++){
		// check whether i & j are compatible and j is not matched yet
		if(a[i][j] && ((mask & (1<<j))==0)){ 
			c += solve(i+1,mask|(1<<j));
		}
	}
	return dp[i][mask]=c%MOD;
}
```

We can solve in `O(n. 2^n)` time in bottom-up fashion similar to Assignment problem solution.

```cpp
const int mod = 1e9 + 7;
 
void add_self(int& a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> can(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &can[i][j]);
        }
    }
    vector<int> dp(1 << n); // 2^n
    dp[0] = 1;
    for(int mask = 0; mask < (1 << n) - 1; ++mask) {
        int a = __builtin_popcount(mask); // the number of bits set to 1
	// till now a/n men are matched, and we want to match (a+1)-th person now
        for(int b = 0; b < n; ++b) {
            if(can[a][b] && !(mask & (1 << b))) { // check whether we can match a-th person with b
                int m2 = mask ^ (1 << b);
                add_self(dp[m2], dp[mask]);
            }
        }
    }
    printf("%d\n", dp[(1<<n)-1]);
}
```

### Digit DP

#### S - Digit Sum

Find the number of integers between `1` and `K` (inclusive) satisfying the following condition, modulo `10^9 + 7`: 
* The sum of the digits in base ten is a multiple of D.

#### Solutions

Observation: If we want to find sum of digits to be multiple of `D`, only thing that matters is what is the remainder modulo `D`.

Think in terms of what information we need to place a digit at the current position `i`, if the number till now is already smaller than we can place all digits from `0` to `9` digits. If not we can only place from `0` to `digit[i]`. We don't need to know what digits are present but only the sum of these digits.

Subproblems: `dp[sum][i][sm_already]` - Number of integers such that digit sum remainder modulo `D` is `sum`, only considering only first `i` digits of `K` i.e `K[1:i]`, `sm_already` denotes whether these numbers are strictly smaller than `K[1:i]`.

```cpp
const int nax = 10123;
char k[nax];
const int mod = 1e9 + 7;
 
void add_self(int& a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}
 
int main() {
    scanf("%s", k);
    int D;
    scanf("%d", &D);
    int len = strlen(k);
    vector<vector<int>> dp(D, vector<int>(2));
    // dp[sum][smaller_already] - the number of ways to choose digits so far
    // such that the sum of digits modulo D is 'sum' and 'smaller_already'
    // says whether we already chosen some digit smaller than in K
    dp[0][0] = 1;
    for(int where = 0; where < len; ++where) {
        vector<vector<int>> new_dp(D, vector<int>(2));
        for(int sum = 0; sum < D; ++sum) {
            for(bool sm_already : {false, true}) {
                for(int digit = 0; digit < 10; ++digit) {
                    if(digit > k[where] - '0' && !sm_already) {
                        break;
                    }
                    add_self(new_dp[(sum+digit)%D][sm_already || (digit < k[where]-'0')],
                        dp[sum][sm_already]);
                }
            }
        }
        dp = new_dp;
    }
    int answer = (dp[0][false] + dp[0][true]) % mod;
    --answer; // don't include 0
    if(answer == -1) {
        answer = mod - 1;
    }
    printf("%d\n", answer);
}
```

#### SPOJ CPCRC1C - Sum of Digits

Problem: Find the sum of the digits of numbers a through b.

Solution: `sum_of_digits(1..b) - sum_of_digits(1..a-1)`

Recursive solution to find the sum of digits from 1 to K, assuming digits of K are stored in `vector<int> num`. 
```cpp
vector<int> num;
long long int solve(int pos,int sum,int f){
	if(pos==num.size()){
	  return sum;
	}
	if (DP[pos][sum][f] != -1) return DP[pos][sum][f];
	
	long long int res = 0;
	int lmt;
	if(f==0){
	  lmt = num[pos];
	}
	else lmt = 9;
	
	for(int dgt=0;dgt<=lmt;dgt++){
	   int nf = f;
	   if(f==0 && dgt<lmt) nf = 1; // from pos+1 the numbers will be smaller
	   res += solve(pos+1,sum+dgt,nf);
	}
	return DP[pos][sum][f]=res;
}
```

Brian Bi t3nsor SPOJ solution https://github.com/t3nsor/SPOJ/blob/master/cpcrc1c.cpp


How to compute sum(x)? Let us try finding out a pattern

```
sum(9) = 1 + 2 + 3 + 4 ........... + 9
       = 9*10/2 
       = 45

sum(99)  = 45 + (10 + 45) + (20 + 45) + ..... (90 + 45)
         = 45*10 + (10 + 20 + 30 ... 90)
         = 45*10 + 10(1 + 2 + ... 9)
         = 45*10 + 45*10
         = sum(9)*10 + 45*10 

sum(999) = (1...99) + (100...199) + ... + (900...999)
         = sum(99) + [100 + sum(99)] + ... + [9*100 + sum(99)]
         = sum(99)*10 + 45*100
```

So in general

```sum(10^d - 1) = sum(10^{d-1} - 1) * 10 + 45*(10^{d-1})```

Algorithm: sum(n) 

1) Find number of digits minus one in `n`. Let this value be `d`.  
   For 328, d is 2.

2) Compute some of digits in numbers from `1` to `10^d - 1`.  
   Let this sum be w. For 328, we compute sum of digits from 1 to 
   99 using above formula.

3) Find Most significant digit (msd) in n. For 328, msd is 3.

4) Overall sum is sum of following terms

    a) Sum of digits in 1 to `msd * 10^d - 1`.  For 328, sum of digits in numbers from 1 to 299.
        For 328, we compute `3*sum(99) + (1 + 2)*100`.  Note that sum of
        sum(299) is sum(99) + sum of digits from 100 to 199 + sum of digits
        from 200 to 299.  
        Sum of 100 to 199 is sum(99) + 1*100 and sum of 299 is sum(99) + 2*100.
        In general, this sum can be computed as `w*msd + (msd*(msd-1)/2)*10^d`

    b) Sum of digits in `msd * 10^d` to` n`.  For 328, sum of digits in 300 to 328.
        For 328, this sum is computed as 3*29 + recursive call "sum(28)"
        In general, this sum can be computed as  msd * (n % (msd*10^d) + 1) 
        + sum(n % (10^d))

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int sum_of_digits(int x) {
    if (x == 0) return 0; else return x%10 + sum_of_digits(x/10);
}
long long sum(int x) {
    // returns sum of digits in 0 + 1 + ... + (x-1)
    long long res = 0;
    long long cur = 0;
    long long increment = 1;
    int exponent = 0;
    while (10*increment <= x) { increment *= 10; exponent++; }
    while (cur < x) {
        if (cur + increment > x) {
            increment /= 10; exponent--; continue;
        }
        long long sod = sum_of_digits(cur);
        res += increment*sod + 45*exponent*increment/10;
        cur += increment;
    }
    return res;
}
int main() {
    for (;;) {
        int a, b; scanf("%d %d", &a, &b);
        if (a == -1) return 0;
        printf("%lld\n", sum(b+1) - sum(a));
    }
}
```

TODO: https://csacademy.com/contest/archive/task/and-closure/

### Cherry Pickup
source: https://leetcode.com/problems/cherry-pickup/

You are given an `n x n` grid representing a field of cherries, each cell is one of three possible integers.
* `0` means the cell is empty, so you can pass through,
* `1` means the cell contains a cherry that you can pick up and pass through, or
* `-1` means the cell contains a thorn that blocks your way.

Return the maximum number of cherries you can collect by following the rules below:
* Starting at the position `(0, 0)` and reaching `(n - 1, n - 1)` by moving right or down through valid path cells (cells with value 0 or 1).
* After reaching `(n - 1, n - 1)`, returning to `(0, 0)` by moving left or up through valid path cells.
* When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
* If there is no valid path between `(0, 0)` and `(n - 1, n - 1)`, then no cherries can be collected.

Example:

![image](https://user-images.githubusercontent.com/19663316/118598728-2bbdc300-b7cc-11eb-809d-d811b478219c.png)

```
Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
```

**Constraints:**
* `1 <= n <= 50`
* `grid[0][0] != -1` & `grid[n - 1][n - 1] != -1`

#### Solution

**Attempt 1**

Why not break into two paths from `(0,0)` to `(N-1, N-1)` and then `(N-1, N-1)` to `(0,0)` and solve both of them independently. Once we pickup the cherry on the path from `(0,0)` from `(N-1,N-1)` then we cannot pick it again on the way back from `(N-1, N-1)` to `(0,0)`. Even though we remove the cherries once we pick it up, this idea will not work. Here is a counter example:

```
grid = [[1,1,1,0,1],
        [0,0,0,0,0],
        [0,0,0,0,0],
        [0,0,0,0,0],
        [1,0,1,1,1]]
```

The idea above suggests that we go through the path `(0, 0) ==> (0, 2) ==> (4, 2) ==> (4, 4)` which pickups `6` cherries. Then on the reverse path we only choose `1` cherry. But the optimal way would be to through `(0,0) => (0,4) => (4,4)` and then from `(4,4) => (4,0) => (0,0)` which would take `8` cherries.

**Attempt 2**

We define `T(i, j)` as the maximum number of cherries we can pick up starting from the position `(i, j)`(assume it's not a thorn) of the grid and following the path `(i, j) ==> (N-1, N-1) ==>(0, 0)`, we could move one step forward to either `(i+1, j)` or `(i, j+1)`, and recursively solve for the subproblems starting from each of those two positions (that is, `T(i+1, j)` and `T(i, j+1))`, then take the sum of the larger one (assume it exists) together with `grid[i][j]` to form a solution to the original problem. 

Note: The previous analyses assume we are on the first leg of the round trip, that is, `(0, 0) ==> (N-1, N-1)`; if we are on the second leg, that is, `(N-1, N-1) ==> (0, 0)`, then we should move one step backward from `(i, j)` to either `(i-1, j)` or `(i, j-1)`.

`T(i, j) = grid[i][j] + max{T(i+1, j), T(i, j+1)}`, which means we already counted `grid[i][j]` towards `T(i, j)`. To avoid the duplicate counting, we somehow need to make sure that `grid[i][j]` will not be counted towards any of `T(i+1, j)` and `T(i, j+1)`. We'll need to make sure that `(i,j)` doesn't appear on the apth from `(N-1, N-1) => (0,0)` which would result in double counting.

Maybe, we can redefine `S(i, j)` as the maximum number of cherries for the shortened round trip: `(0, 0) ==> (i, j) ==> (0, 0)` without modifying the grid matrix. The original problem then will be denoted as `S(N-1, N-1)`.  

To obtain the recurrence relations, note that for each position (i, j), we have two options for arriving at and two options for leaving it: (i-1, j) and (i, j-1), so the above round trip can be divide into four cases:

```
Case 1: (0, 0) ==> (i-1, j) ==> (i, j) ==> (i-1, j) ==> (0, 0)
Case 2: (0, 0) ==> (i, j-1) ==> (i, j) ==> (i, j-1) ==> (0, 0)
Case 3: (0, 0) ==> (i-1, j) ==> (i, j) ==> (i, j-1) ==> (0, 0)
Case 4: (0, 0) ==> (i, j-1) ==> (i, j) ==> (i-1, j) ==> (0, 0)
```

By definition, Case 1 is equivalent to `S(i-1, j) + grid[i][j]` and Case 2 is equivalent to `S(i, j-1) + grid[i][j]`. However, our definition of `S(i,j)` doesn't cover the last two cases. 

**Attempt 3**

This suggests that we should include more information in our state and hence use `T(i, j, p, q)` as DP state, where the path is `(0, 0) ==> (i, j); (p, q) ==> (0, 0)` without modifying the grid matrix.


Recurrence relations for `T(i, j, p, q)`
```
Case 1: (0, 0) ==> (i-1, j) ==> (i, j); (p, q) ==> (p-1, q) ==> (0, 0)
Case 2: (0, 0) ==> (i-1, j) ==> (i, j); (p, q) ==> (p, q-1) ==> (0, 0)
Case 3: (0, 0) ==> (i, j-1) ==> (i, j); (p, q) ==> (p-1, q) ==> (0, 0)
Case 4: (0, 0) ==> (i, j-1) ==> (i, j); (p, q) ==> (p, q-1) ==> (0, 0)
```

by definition,

```
Case 1 is equivalent to T(i-1, j, p-1, q) + grid[i][j] + grid[p][q];
Case 2 is equivalent to T(i-1, j, p, q-1) + grid[i][j] + grid[p][q];
Case 3 is equivalent to T(i, j-1, p-1, q) + grid[i][j] + grid[p][q];
Case 4 is equivalent to T(i, j-1, p, q-1) + grid[i][j] + grid[p][q];
```

Therefore, the recurrence relations can be written as:

```T(i, j, p, q) = grid[i][j] + grid[p][q] + max{T(i-1, j, p-1, q), T(i-1, j, p, q-1), T(i, j-1, p-1, q), T(i, j-1, p, q-1)}```

Now to make it work, we need to impose the aforementioned constraint. As mentioned above, since we already counted `grid[i][j]` and `grid[p][q]` towards `T(i, j, p, q)`, to avoid duplicate counting, both of them should NOT be counted for any of `T(i-1, j, p-1, q)`,` T(i-1, j, p, q-1)`, `T(i, j-1, p-1, q)` and `T(i, j-1, p, q-1)`.

![image](https://user-images.githubusercontent.com/19663316/118618334-21f28a80-b7e1-11eb-897d-c2913f88c46a.png)

Note that every step we take from `(i, j)` or `(p, q)`, the distance from `(N-1, N-1)` to `(i, j)` reduces by `1`, similarly for `(p, q)`. Also we can just move right or down, with every move right `i` increases and with every down move `j` increases and `(i - 0) + (j - 0)` is the number of steps taken so far, this suggests we can set the sum of `i (p)` and `j (q)` to some constant, `c = i + j = p + q`. `c` is the total number of steps moved from `(0, 0)`. Thus reducing the dimension of dp.

With the new conditions in place, we can now redefine our `T(i, j, p, q)` such that `c = i + j = p + q`, which can be rewritten, in terms of independent variables, as `T(c, i, p)`, where `T(c, i, p)` = `T(i, c-i, p, c-p)`. Note that under this definition, we have:

Then from the recurrence relation for `T(i, j, p, q)`, we obtain the recurrence relation for `T(n, i, p)` as:

```T(c, i, p) = grid[i][c-i] + grid[p][c-p] + max{T(c-1, i-1, p-1), T(c-1, i-1, p), T(c-1, i, p-1), T(c-1, i, p)}```.

Of course, in the recurrence relation above, only one of `grid[i][c-i]` and `grid[p][c-p]` will be taken if `i == p` (i.e., when the two positions overlap). Also note that all four indices, `i`, `j`, `p` and `q`, are in the range `[0, N)`, meaning `c` will be in the range `[0, 2N-1)` (remember it is the sum of `i` and `j`). Lastly we have the base case given by `T(0, 0, 0) = grid[0][0]`.

Now using the recurrence relation for `T(n, i, p)`, it is straightforward to code for the `O(N^3)` time and `O(N^3)` space solution. However, if you notice that `T(c, i, p)` only depends on those subproblems with `c - 1`, we can iterate on this dimension and cut down the space to `O(N^2)`.

dp holds maximum # of cherries two c-length paths can pickup. The two c-length paths arrive at `(i, c - i)` and `(p, c - p)` respectively.

```java
public int cherryPickup(int[][] grid) {
  int N = grid.length, M = (N << 1) - 1; // M = 2*N - 1
  int[][] dp = new int[N][N];
  dp[0][0] = grid[0][0]; // length c = 0

  for (int c = 1; c < M; c++) {
    for (int i = N - 1; i >= 0; i--) {
      for (int p = N - 1; p >= 0; p--) {
        int j = c - i, q = c - p;

        if (j < 0 || j >= N || q < 0 || q >= N || grid[i][j] < 0 || grid[p][q] < 0) {
          dp[i][p] = -1;
          continue;
        }

        if (i > 0) dp[i][p] = Math.max(dp[i][p], dp[i - 1][p]);
        if (p > 0) dp[i][p] = Math.max(dp[i][p], dp[i][p - 1]);
        if (i > 0 && p > 0) dp[i][p] = Math.max(dp[i][p], dp[i - 1][p - 1]);
	
	// dp[i][p] < 0 => No viable way to arrive at (i,j) (p,q)
        if (dp[i][p] >= 0) dp[i][p] += grid[i][j] + (i != p ? grid[p][q] : 0)
      }
    }
  }

  return Math.max(dp[N - 1][N - 1], 0);
}
```

source: https://leetcode.com/problems/cherry-pickup/discuss/109903/Step-by-step-guidance-of-the-O(N3)-time-and-O(N2)-space-solution
