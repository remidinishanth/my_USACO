TODO: https://codeforces.com/contest/1533/problem/E and https://codeforces.com/contest/1533/problem/F

solutions: https://www.youtube.com/watch?v=ll-UwTagrU0

TODO: https://leetcode.com/problems/three-equal-parts/

Making all numbers equal: https://www.codechef.com/START50B/problems/ADDSUBTRACT

#### Wrapping Chocolate 

source: https://atcoder.jp/contests/abc245/tasks/abc245_e

Takahashi has `N` pieces of chocolate. 
* The i-th piece has a rectangular shape with a width of `Ai` centimeters and a length of `Bi` centimeters. 

He also has `M` boxes. 
* The i-th box has a rectangular shape with a width of `Ci` centimeters and a length of `Di` centimeters. 

Determine whether it is possible to put the `N` pieces of chocolate in the boxes under the conditions below. A box can contain at most one piece of chocolate. `Ai ≤ Cj` and `Bi ≤ Dj` must hold when putting the i-th piece of chocolate in the j-th box (they cannot be rotated).

Solution: We cannot use `multiset<pair<int,int>>` directly because, Say we have `[4, 2]` and `[2, 3]` chocolates and `[5, 5]` and `[8, 2]` boxes. If we start choosing chocos from largest X, then we choose box `[5, 5]` for `[4, 2]` choco, then we will not be able to select box `[8, 2]` for `[2, 3]`.

Similary, if we have chocos `[2, 3]`, `[2, 5]` and boxes `[3, 5]`, `[4, 3]`. Then if we start choosing boxes from smallest X it will not work. Hence using lower_bound in multiset won't work.

```cpp
#include <bits/stdc++.h>
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::array<int, 2>> box(m), choco(n);
    for (int i = 0; i < n; i++) {
        std::cin >> choco[i][0];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> choco[i][1];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> box[i][0];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> box[i][1];
    }
    
    // sort the boxes and choco in decreasing x order
    std::sort(choco.begin(), choco.end(), std::greater());
    std::sort(box.begin(), box.end(), std::greater());
    
    std::multiset<int> s;
    for (int i = 0, j = 0; i < n; i++) {
        // all the chocos with x greater than choco[i] 
        // have been allocated
        
        // among all boxes that can fix choco[i]
        while (j < m && box[j][0] >= choco[i][0]) {
            s.insert(box[j][1]);
            j++;
        }
        // choose the smallest box
        auto it = s.lower_bound(choco[i][1]);
        if (it == s.end()) {
            std::cout << "No\n";
            return 0;
        }
        s.erase(it);
    }
    
    std::cout << "Yes\n";
    
    return 0;
}
```

### Maximum Performance of a Team

Optimization over two dimentions: The performance of a team is the sum of their engineers speeds multiplied by the minimum efficiency among their engineers. Here it is `sum(speed) * min(efficiency)`

https://leetcode.com/contest/weekly-contest-180/problems/maximum-performance-of-a-team/

Choose atmost k different engineers. 
* Once you fix the minimum efficiency, it is better to always choose k engineers if possible, because this way, sum of speeds increase.

```cpp
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> V;
        for(int i=0;i<speed.size();i++) V.push_back({efficiency[i], speed[i]});
        sort(V.begin(), V.end());
        long long ans = 0, speedSum = 0;
        multiset<int> S;
        for(int i=n-1;i>=0;i--){
            speedSum += V[i].second;
            S.insert(V[i].second);
            if(S.size() > k){
                speedSum -= *S.begin();
                S.erase(S.begin());
            }
            ans = max(ans, V[i].first * speedSum);
        }
        int md = 1e9 + 7;
        return ans % md;
    }
};
```

#### Coins AGC-18 C

https://atcoder.jp/contests/agc018/tasks/agc018_c

![image](https://user-images.githubusercontent.com/19663316/182018959-aaf50038-58d6-417a-b744-6991bfbc4179.png)

![image](https://user-images.githubusercontent.com/19663316/182019023-c390a49c-32b7-4003-b0fe-1c1c69407a66.png)

Ref: https://codeforces.com/blog/entry/53431?#comment-374498

**Implementation Details:**

Note that from each person, we will either choose Gold, Silver or Bronze.

For each container, assume we are taking the Gold at first. If at a later point, we feel that taking the Silver coins or the Bronze coins will be beneficial instead of Gold under the constraints, then we conveniently do so. Say for example, we choose Silver later, we simply add `(B_i - A_i)` to `A_i`. 

For each person do: `sum += A_i` , `B_i = B_i - A_i` , `C_i = C_i - A_i`.

Sort this array of tuples based on `(B_i - C_i)`. 

Maintain a prefix array which for each index `i`, stores the maximum possible sum of `B_i`'s for `Y` number of persons upto index `i` (Can use min heap for this). 

Similarly, store a suffix array which store the maximum possible `C_i`'s for storing the maximum possible sum of `C_i`'s for `Z` number of containers.

Then the final answer will be: `ans = (max{y<=i<=n-z}(pre[i] + suf[i])) + sum`

https://atcoder.jp/contests/agc018/submissions/1449715

### B - Bracket Score 


<img width="1130" alt="image" src="https://user-images.githubusercontent.com/19663316/202887168-13b0ceb7-a4fc-4669-88ad-bc08abf5eab1.png">

Solution:

<img width="1137" alt="image" src="https://user-images.githubusercontent.com/19663316/202887154-329dfd82-bcab-4710-8138-98312c5a8900.png">

```cpp
const int N = 200200;
int n;
ll z[N];
vector<ll> a[2];
 
 
int main()
{
	scanf("%d", &n);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &z[i]);
		ans += z[i];
	}
	for (int i = 0; i < n; i++) {
		ll x;
		scanf("%lld", &x);
		x -= z[i];
		a[i & 1].push_back(x);
	}
	for (int i = 0; i < 2; i++)
		sort(all(a[i]));
	for (int i = n / 2 - 1; i >= 0; i--) {
		ll x = a[0][i] + a[1][i];
		if (x <= 0) break;
		ans += x;
	}
	printf("%lld\n", ans);
 
	return 0;
}
```

source: https://atcoder.jp/contests/agc048/editorial/234, solution: Um_nik https://atcoder.jp/contests/agc048/submissions/17506481

#### AGC-03 B

Done https://atcoder.jp/contests/agc003/tasks/agc003_b Solution: https://img.atcoder.jp/data/agc/003/editorial.pdf

![](images/adhoc_oct_21.png)

Divide and Conquer: https://leetcode.com/problems/beautiful-array/solution/

https://stackoverflow.com/questions/52244676/given-an-array-you-have-to-find-the-max-possible-two-equal-sum

DSU https://leetcode.com/problems/rank-transform-of-a-matrix/discuss/909212/C%2B%2B-with-picture

Strings https://codeforces.com/contest/1560/submission/126302860 Nice solution: Explanation: https://www.youtube.com/watch?v=kCMGWkJIILQ

TODO: Problems of this contest https://codeforces.com/contest/1549/submission/124567744 - D nice problem with gcd over array

Missing coin sum - https://cses.fi/problemset/task/2183, Extensions -> Math, Greedy - https://leetcode.com/problems/patching-array/discuss/280183/Detailed-Explanation-with-Example - Nice idea

```cpp
ll l = 0, r = 0;
ll ans = -1;
for(int v:V){
    if(v + l > r + 1){
        ans = r+1;
        break;
    }
    r += v;
}
```

Array filling - https://atcoder.jp/contests/abc214/editorial/2446

https://codeforces.com/contest/1593/problem/D2

Nested Range count - CSES - https://discuss.codechef.com/t/help-needed-with-nested-range-count-cses/84014

### Contribution to the sum

Facebook Hackercup 2021 Problem A2: Weak Typing - Chapter 2

Timmy the toddler is training to be a top typist. His teacher has assigned some homework in the form of a list of `T` string exercises to be typed, consisting of only the uppercase letters `"F"`, `"O"`, and `"X"`.

Timmy is eating a popsicle on a hot summer afternoon, but still hopes to complete his homework. He would like to hold the popsicle with one hand, and type with the other. Unfortunately, Timmy is still a growing boy, and each of his hands is a tad too small to reach all the way across the keyboard. He can only reach the letters `"F"` and `"X"` with his left hand, and the letters `"F"` and `"O"` with his right.

Consider a string `W` which Timmy must type. Timmy may start typing with any hand of his choice (with the other holding the popsicle). He must then switch hands as necessary to type out the `∣W∣` letters in order, ending on any hand of his choice. Let `F(W)` be the minimum number of times Timmy must switch hands to type such a string `W`.

Given an exercise string `S` of length `N`, let `G(S)` be the sum of `F(W)` over all substrings `W` of `S`. Note that there are `N*(N+1)/2` such substrings. Please help Timmy compute the value of `G(S)` modulo `1,000,000,007`.

**Solution:** Instead of calculating substring wise, we can calculate how much does each character contribute to the overall sum

```cpp
extern const int MOD = int(1e9) + 7;
using mod_int = _m_int<MOD>;


void run_case(int test_case) {
    int N;
    string W;
    cin >> N >> W;
    int previous = -1;
    mod_int total = 0;

    for (int i = 0; i < N; i++)
        if (W[i] == 'X' || W[i] == 'O') {
            if (previous >= 0 && W[i] != W[previous])
                total += mod_int(previous + 1) * (N - i);

            previous = i;
        }

    cout << "Case #" << test_case << ": " << total << '\n';
}

int main() {
    int tests; cin >> tests;
    for (int tc = 1; tc <= tests; tc++) {
        run_case(tc);
        cout << flush;
    }
}
```

source: Neal's submission 

<details>
    <summary> Full Code </summary>
    
```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<const int &MOD>
struct _m_int {
    int val;

    _m_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    _m_int(uint64_t v) {
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    _m_int(int v) : _m_int(int64_t(v)) {}
    _m_int(unsigned v) : _m_int(uint64_t(v)) {}

    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }

    _m_int& operator+=(const _m_int &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    _m_int& operator-=(const _m_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    _m_int& operator*=(const _m_int &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }

    _m_int& operator/=(const _m_int &other) {
        return *this *= other.inv();
    }

    friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
    friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
    friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
    friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }

    _m_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }

    _m_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }

    _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
    _m_int operator--(int) { _m_int before = *this; --*this; return before; }

    _m_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }

    friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
    friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
    friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
    friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
    friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
    friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }

    static const int SAVE_INV = int(1e6) + 5;
    static _m_int save_inv[SAVE_INV];

    static void prepare_inv() {
        // Ensures that MOD is prime, which is necessary for the inverse algorithm below.
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);

        save_inv[0] = 0;
        save_inv[1] = 1;

        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }

    _m_int inv() const {
        if (save_inv[1] == 0)
            prepare_inv();

        if (val < SAVE_INV)
            return save_inv[val];

        _m_int product = 1;
        int v = val;

        while (v >= SAVE_INV) {
            product *= MOD - MOD / v;
            v = MOD % v;
        }

        return product * save_inv[v];
    }

    _m_int pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);

        _m_int a = *this, result = 1;

        while (p > 0) {
            if (p & 1)
                result *= a;

            p >>= 1;

            if (p > 0)
                a *= a;
        }

        return result;
    }

    friend ostream& operator<<(ostream &os, const _m_int &m) {
        return os << m.val;
    }
};

template<const int &MOD> _m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];

extern const int MOD = int(1e9) + 7;
using mod_int = _m_int<MOD>;


void run_case(int test_case) {
    int N;
    string W;
    cin >> N >> W;
    int previous = -1;
    mod_int total = 0;

    for (int i = 0; i < N; i++)
        if (W[i] == 'X' || W[i] == 'O') {
            if (previous >= 0 && W[i] != W[previous])
                total += mod_int(previous + 1) * (N - i);

            previous = i;
        }

    cout << "Case #" << test_case << ": " << total << '\n';
}

int main() {
    int tests;
    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        run_case(tc);
        cout << flush;
    }
}
```
</details>
