### Two Sum

Given an array of N elements (1 ≤ N ≤ 10^5), find two elements that sum to X, if they
exist.

```cpp
int left = 0;
int right = n - 1;
while (left < right) {
    if (arr[left] + arr[right] == x) {
        break;
    } else if (arr[left] + arr[right] < x) {
        left++;
    } else {
        right--;
    }
}
// if left >= right after the loop ends, no answer exists.
```

### Subarray Sum

Given an array of N (1 ≤ N ≤ 10^5) positive elements, find a contiguous subarray that
sums to X.

Solution: We can do this in a similar manner to how we did the 2SUM problem: except
this time we start both pointers at the left, and the pointers mark the beginning and end of
the subarray we are currently checking. We advance the right pointer one step to the right if
the total of the current subarray is too small, advance the left pointer one step to the right if
the current total is too large, and we are done when we find the correct total.

```cpp
int left = 0; int right = 0; int sum = arr[0];
for (right = 0; right < n; right++) {
    sum += arr[right];
    while (sum > x && left < right) {
        sum -= arr[left];
        left++;
    }
    if (sum == x) {
        break;
    }
}
```


### Ferris Wheel https://cses.fi/problemset/task/1090/

```cpp
int main() {
    int n, x; scanf("%d %d", &n, &x);
    multiset<int> S;
    REP(i, n){
        int y; scanf("%d", &y);
        S.insert(y);
    }
    int ans = 0;
    while(!S.empty()){
        ans++;
        auto it = S.begin();
        int a = *it;
        S.erase(it);
        it = S.upper_bound(x - a);
        if(it != S.begin()){
            it--;
            S.erase(it);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

Using two pointers

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

// Variables used for the current problem
int n, x, p[maxn], i, j, ans;
// Keeps track of the number of children who have had their own gondola
bool have_gondola_yet[maxn];

void solve() {
    cin >> n >> x;
    for (int i = 0; i < n; ++i) cin >> p[i];
    sort(p, p + n);
    i = 0;
    j = n - 1;
    while (i < j) {
        if (p[i] + p[j] > x) {
            // If the total weight of two children exceeds x
            // Then we move to the lighter child.
            --j;
        } else { // If it satisfies the condition.
            ++ans; // Increment the number of gondolas used
            // Mark that they have had their gondola
            have_gondola_yet[i] = have_gondola_yet[j] = true;
            ++i;
            --j; //Move to the next children.
        }
    }
    for (int i = 0; i < n; ++i) {
        // Calculate the number of children not having gondolas yet
        // to get the total number of gondolas needed for the problem.
        ans += have_gondola_yet[i] == false;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```

### Subarray Distinct Values

https://cses.fi/problemset/task/2428

Given an array of n integers, your task is to calculate the number of subarrays that have at most k distinct values.


```cpp
int main() {
    dsd2(n, k);
    int left = 0;
    map<int, int> M;
    vi V(n);
    ll ans = 0;
    REP(i, n){
        scanf("%d", &V[i]);
        M[V[i]]++;
        while(M.size() > k){
            M[V[left]]--;
            if(M[V[left]]==0) M.erase(V[left]);
            left++;
        }
        ans += i - left + 1;
    }
    pl(ans);
    return 0;
}
```

### Distinct Value Queries 

https://cses.fi/problemset/task/1734

Sort the queries in a specific order before answering them.

Answer queries in order of the right indices. Use a BIT to keep track of indices that contain distinct values. For every value, update the latest index for it and answer all queries at the current index. This ensures later indices are included in the BIT to accurately answer queries.

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MX = 4e5 + 5;

int bit[MX];
int n, q, sol[MX];
vector < pair < int, int >> query[MX];
vector < int > x(MX);
map < int, int > fst;

int qry(int i) {
    int res = 0;
    for (; i; i -= i & (-i)) {
        res += bit[i];
    }
    return res;
}

void upd(int i, int val) {
    for (; i <= n; i += i & (-i)) {
        bit[i] += val;
    }
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        query[a].push_back(make_pair(b, i));
    }
    for (int i = n; i >= 1; i--) {
        int z = x[i - 1];
        if (fst.count(z)) upd(fst[z], -1);
        fst[z] = i;
        upd(i, 1);
        for (auto t: query[i]) {
            sol[t.second] = qry(t.first);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << sol[i] << '\n';
    }
}
```

Largest Subarray with gcd > 1

source: Killjee and non-co-prime subarray https://www.hackerearth.com/submission/9367277/

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define upperlimit 1000100
#define INF 1000000100
#define INFL 1000000000000000100
#define eps 1e-8
#define endl '\n'
#define sd(n) scanf("%d",&n)
#define slld(n) scanf("%lld",&n)
#define pd(n) printf("%d",n)
#define plld(n) printf("%lld",n)
#define pds(n) printf("%d ",n)
#define pllds(n) printf("%lld ",n)
#define pdn(n) printf("%d\n",n)
#define plldn(n) printf("%lld\n",n)
#define REP(i,a,b) for(i=a;i<=b;i++)
#define mp make_pair
#define pb emplace_back
#define pcc pair<char,char>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pii>
#define vll vector<pll>
#define tr(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define F first
#define S second
#define clr(a) memset(a,0,sizeof(a))
 
using namespace std;
 
int gcd(int n1,int n2){
	if(!n1)return n2;
	if(!n2)return n1;
	if(n1%n2==0)return n2;
	return gcd(n2,n1%n2);
}
ll powmod(ll base,ll exponent){
	base%=mod;
	ll ans=1;
	while(exponent){
		if(exponent&1)ans=(ans*base)%mod;
		base=(base*base)%mod;
		exponent/=2;
	}
	ans%=mod;
	return ans;
}
int arr[upperlimit+1];
int segtree[4*upperlimit+1];
void build(int node,int i,int j){
	if(i>j)return;
	if(i==j){
		segtree[node]=arr[i];
		return;
	}
	int mid=(i+j)>>1;
	build(2*node,i,mid);
	build(2*node+1,mid+1,j);
	segtree[node]=gcd(segtree[2*node],segtree[2*node+1]);
}
int query(int node,int i,int j,int l,int r){
	if(i>j || i>r || j<l || l>r)return 0;
	if(i>=l && j<=r)return segtree[node];
	int mid=(i+j)>>1;
	int q1=query(2*node,i,mid,l,r);
	int q2=query(2*node+1,mid+1,j,l,r);
	return gcd(q1,q2);
}
int main()
{
	int n,i,j,k;
	sd(n);
	for(i=1;i<=n;i++)sd(arr[i]);
	build(1,1,n);
	int ptr=n+1;
	ll answer=0;
	for(i=n;i>=1;i--){
		while(ptr>0 && query(1,1,n,ptr,i)!=1)ptr--;
		answer+=ptr;
	}
	answer=(1LL*n*(n+1))/2-answer;
	plldn(answer);
	return 0;
}
```

Similar problem https://codeforces.com/contest/1549/problem/D
