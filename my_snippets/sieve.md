## Sieve optimization

We can actually optimize this sieve in a few ways. First, for a prime `i`, instead of marking `2i, 3i, 4i, ...`, we can just mark `i², i²+i, i²+2i, i²+3i, ...` . The reason is that every composite number `x` has a prime factor `≤ √x`, so for every prime i, we only need to mark its multiples `≥ i²`.

A second optimization is to initially only mark odd numbers as prime, i.e. mark all even numbers (except 2) composite. And then for every odd prime i, we increment by 2i instead of i, avoiding all even numbers. In fact, we can save half the memory needed by only allocating is_prime for odd numbers.

```cpp
vector<int> all_primes(int n) {
    // the old 'is_prime[i]' now corresponds to 'is_prime[i/2]'
    bool *is_prime = new bool[n/2+1];

    for (int i = 2; i <= n; i++) is_prime[i/2] = true;

    for (int i = 3; i*i <= n; i += 2) {           // only iterate through odd 'i'
        if (is_prime[i/2]) {
            for (int j = i*i; j <= n; j += 2*i) { // odd multiples >= i^2
                is_prime[j/2] = false;
            }
        }
    }

    // extract the primes
    vector<int> primes;
    primes.push_back(2);                          // add '2' as prime
    for (int i = 3; i <= n; i += 2) {
        if (is_prime[i/2]) {
            primes.push_back(i);
        }
    }

    free(is_prime);

    return primes;
}
```

### Modified sieves

This “sieve” procedure is actually somewhat flexible. For example, it can be modified to compute one prime factor for every number up to n. Study the following code to understand how:

```cpp
// assume n <= one million. change this number if needed
int pfac[1000111];

void compute_prime_factors(int n) {
    for (int i = 2; i <= n; i++) pfac[i] = 0;

    for (int i = 2; i <= n; i++) {
        if (pfac[i] == 0) {                     // this means i is prime
            pfac[i] = i;                        // set i's prime factor to itself
            for (int j = i*i; j <= n; j += i) { // iterate through proper multiples
                pfac[j] = i;                    // set i as the prime factor
            }
        }
    }
}
```

It can also be modified to compute other things, such as divisor counts, divisor sums, and even Euler's totient function (if you're familiar with it).

As a side effect, being able to compute a prime factor allows us to prime factorize every number up to n quickly, using one of our older algorithms:

```cpp
int pfac[1000111];

... // compute_prime_factors here

vector<int> prime_factorize(int n) {
    vector<int> primes;
    // extract prime factors
    while (n > 1) {
        int p = pfac[n]; // use pfac to get a prime factor
        primes.push_back(p);
        n /= p;
    }
    return primes;
}
```

This is our original prime factorization algorithms, but much faster because we use our computed pfac to extract a prime factor quickly. This runs very quickly, though it only works for numbers ≤n.

Don't for get to call compute_prime_factors first for it work properly!

source: http://noi-ph-training.herokuapp.com/topics/num_sieves

## Memory tight sieve by "Yarin" 
source: https://onlinejudge.org/board/viewtopic.php?t=2447

```cpp
#define MAXSIEVE 100000000 // All prime numbers up to this
#define MAXSIEVEHALF (MAXSIEVE/2)
#define MAXSQRT 5000 // sqrt(MAXSIEVE)/2
char a[MAXSIEVE/16+2];
#define isprime(n) (a[(n)>>4]&(1<<(((n)>>1)&7))) // Works when n is odd


void sieve(){
    int i,j;
    memset(a,255,sizeof(a));
    a[0]=0xFE; // 254
    for(i=1;i<MAXSQRT;i++)
        if(a[i>>3]&(1<<(i&7)))
            for(j=i+i+i+1;j<MAXSIEVEHALF;j+=i+i+1)
                a[j>>3]&=~(1<<(j&7));
}
```

Notes:
* `a[0] = 0xFE`; (254) exclude 1 from the primes
* `a[i>>3]&(1<<(i&7))` isn't about the primality of `i`, but the primality of `2i + 1`.
* char can store `8` bits and we are storing it using `j>>3` and unsetting using `~(1<<(j&7))`

### How to come up with such a thing?

You start with the original sieve algorithm, like this:

```cpp
char isprime[MAX];
for(int i=0;i<MAX;i++) isprime=i>=2;
for(int i=2;i<MAX;i++)
    if (isprime) // i is a prime, so make all multiples of it non-prime
	for(int j=i*2;j<MAX;j+=i) isprime[j]=0;
```

Then you realize you can store the data more compact since isprime is really just a bit array. That introduces bitmasks. The final step is to only consider odd numbers, and make 2 a special case. When considering only odd numbers, you let index 1 be 3, index 2 be 5 etc. This causes the somewhat strange loops...

```cpp
for (int i = 1; i < MAXSQRT; i++)
  if (isprime(2 * i + 1))
    for (int j = 3 * i + 1; j < MAXSIEVEHALF; j += 2 * i + 1)
      mark 2 * j + 1 as not prime;
```

Now let's do the substitutions `u = 2i + 1` and `v = 2j + 1`.

```cpp
for (int u = 3; u < sqrt(MAXSIEVE); u += 2)
  if (isprime(u))
    for (int v = 3 * u; v < MAXSIEVE; v += 2 * u)
      mark v as not prime;
```

Now this is quite standard. 
The only thing to notice here is that `u` and `v` both skip the even numbers,
that's why you see `u += 2` and `v += 2 * u`, contrary to the standard implementation.

### O(n) sieve

Calculate minimum prime factor `lp[i]` for every number `i` in the segment `[2;n]` in `O(n)` 
which allows us to find factorization of any number in the segment `[2;n]`

```cpp
const int N = 10000000;
int lp[N+1];
vector<int> pr;

for (int i=2; i<=N; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back (i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
        lp[i * pr[j]] = pr[j];
}
```

While we do need to cross out each composite once, in practice we run the inner loop for a 
composite multiple times due to the fact that it has multiple factors. Thus, if we can establish a unique 
representation for each composite and pick them out only once, our algorithm will be somewhat better.
`i = lp[i].x`, Since `lp[i]` is the smallest prime factor, we have `x ≥ lp[i]`

**Correctness proof:**
Notice that every number i has exactly one representation in form: `i=lp[i]⋅x`, where `lp[i]` is the minimal prime factor of i, and the number x doesn't have any prime factors less than `lp[i]`, i.e. `lp[i] ≤ lp[x]`.

Now, let's compare this with the actions of our algorithm: in fact, for every x it goes through all prime numbers it 
could be multiplied by, i.e. all prime numbers up to lp[x] inclusive, in order to get the numbers in the form given above.

source: https://codeforces.com/blog/entry/54090

```cpp
// Simple to code
const int N = 200200;
int d[N];
for (int i = 2; i < N; i++) {
    if (d[i]) continue;
    for (int j = i; j < N; j += i)
        if (d[j] == 0)
            d[j] = i;
```

source: https://codeforces.com/contest/1349/submission/79817454    

```cpp
const int M = 300 * 1000;
int prm[M];
 
void Sieve() {
    iota(prm, prm + M, 0);
 
    for (int p = 2; p < M; ++p) {
	if (prm[p] < p) { continue; }
	for (int i = p * 2; i < M; i += p)
	    prm[i] = p;
    }
}
```

source: https://codeforces.com/contest/1349/submission/79817664

```cpp	
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector < int > VI;
typedef long long ll;
typedef pair < int, int > PII;
typedef double db;
mt19937 mrand(random_device {}());
const ll mod = 1000000007;

int rnd(int x) { return mrand() % x; }
ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
ll gcd(ll a,ll b) { return b ? gcd(b, a%b) : a; }
// head

typedef pair < ll, ll > PLL;
namespace Factor {
    const int N = 1010000;
    ll C, fac[10010], n, mut, a[1001000];
    int T, cnt, i, l, prime[N], p[N], psize, _cnt;
    ll _e[100], _pr[100];
    vector < ll > d;
    inline ll mul(ll a, ll b, ll p) {
        if (p <= 1000000000) return a * b % p;
        else if (p <= 1000000000000 ll) return (((a * (b >> 20) % p) << 20) + (a * (b & ((1 << 20) - 1)))) % p;
        else {
            ll d = (ll) floor(a * (long double) b / p + 0.5);
            ll ret = (a * b - d * p) % p;
            if (ret < 0) ret += p;
            return ret;
        }
    }
    void prime_table() {
        int i, j, tot, t1;
        for (i = 1; i <= psize; i++) p[i] = i;
        for (i = 2, tot = 0; i <= psize; i++) {
            if (p[i] == i) prime[++tot] = i;
            for (j = 1; j <= tot && (t1 = prime[j] * i) <= psize; j++) {
                p[t1] = prime[j];
                if (i % prime[j] == 0) break;
            }
        }
    }
    void init(int ps) {
        psize = ps;
        prime_table();
    }
    ll powl(ll a, ll n, ll p) {
        ll ans = 1;
        for (; n; n >>= 1) {
            if (n & 1) ans = mul(ans, a, p);
            a = mul(a, a, p);
        }
        return ans;
    }
    bool witness(ll a, ll n) {
        int t = 0;
        ll u = n - 1;
        for (; ~u & 1; u >>= 1) t++;
        ll x = powl(a, u, n), _x = 0;
        for (; t; t--) {
            _x = mul(x, x, n);
            if (_x == 1 && x != 1 && x != n - 1) return 1;
            x = _x;
        }
        return _x != 1;
    }
    bool miller(ll n) {
        if (n < 2) return 0;
        if (n <= psize) return p[n] == n;
        if (~n & 1) return 0;
        for (int j = 0; j <= 7; j++)
            if (witness(rand() % (n - 1) + 1, n)) return 0;
        return 1;
    }
    ll gcd(ll a, ll b) {
        ll ret = 1;
        while (a != 0) {
            if ((~a & 1) && (~b & 1)) ret <<= 1, a >>= 1, b >>= 1;
            else if (~a & 1) a >>= 1;
            else if (~b & 1) b >>= 1;
            else {
                if (a < b) swap(a, b);
                a -= b;
            }
        }
        return ret * b;
    }
    ll rho(ll n) {
        for (;;) {
            ll X = rand() % n, Y, Z, T = 1, * lY = a, * lX = lY;
            int tmp = 20;
            C = rand() % 10 + 3;
            X = mul(X, X, n) + C;*(lY++) = X;
            lX++;
            Y = mul(X, X, n) + C;*(lY++) = Y;
            for (; X != Y;) {
                ll t = X - Y + n;
                Z = mul(T, t, n);
                if (Z == 0) return gcd(T, n);
                tmp--;
                if (tmp == 0) {
                    tmp = 20;
                    Z = gcd(Z, n);
                    if (Z != 1 && Z != n) return Z;
                }
                T = Z;
                Y = * (lY++) = mul(Y, Y, n) + C;
                Y = * (lY++) = mul(Y, Y, n) + C;
                X = * (lX++);
            }
        }
    }
    void _factor(ll n) {
        for (int i = 0; i < cnt; i++) {
            if (n % fac[i] == 0) n /= fac[i], fac[cnt++] = fac[i];
        }
        if (n <= psize) {
            for (; n != 1; n /= p[n]) fac[cnt++] = p[n];
            return;
        }
        if (miller(n)) fac[cnt++] = n;
        else {
            ll x = rho(n);
            _factor(x);
            _factor(n / x);
        }
    }
    void dfs(ll x, int dep) {
        if (dep == _cnt) d.pb(x);
        else {
            dfs(x, dep + 1);
            for (int i = 1; i <= _e[dep]; i++) dfs(x *= _pr[dep], dep + 1);
        }
    }
    void norm() {
        sort(fac, fac + cnt);
        _cnt = 0;
        rep(i, 0, cnt) if (i == 0 || fac[i] != fac[i - 1]) _pr[_cnt] = fac[i], _e[_cnt++] = 1;
            else _e[_cnt - 1]++;
    }
    vector < ll > getd() {
        d.clear();
        dfs(1, 0);
        return d;
    }
    vector < ll > factor(ll n) {
        cnt = 0;
        _factor(n);
        norm();
        return getd();
    }
    vector < PLL > factorG(ll n) {
        cnt = 0;
        _factor(n);
        norm();
        vector < PLL > d;
        rep(i, 0, _cnt) d.pb(mp(_pr[i], _e[i]));
        return d;
    }
    bool is_primitive(ll a, ll p) {
        assert(miller(p));
        vector < PLL > D = factorG(p - 1);
        rep(i, 0, SZ(D)) if (powl(a, (p - 1) / D[i].fi, p) == 1) return 0;
        return 1;
    }
}
```

source: MiFaFaOvO https://codeforces.com/contest/1349/submission/79897715 
