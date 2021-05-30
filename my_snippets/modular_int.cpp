#include <bits/stdc++.h>
 
using namespace std;
 
const int md = 998244353;
 
inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}
 
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) a += md;
}
 
inline int mul(int a, int b) {
  return (int) ((long long) a * b % md);
}
 
inline int power(int a, long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}
 
inline int inv(int a) {
  a %= md;
  if (a < 0) a += md;
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += md;
  return u;
}

//Um_nik from https://codeforces.com/contest/1336/submission/76831744
const ll MOD = 998244353;
ll add(ll x, ll y) {
	x += y;
	if (x >= MOD) return x - MOD;
	return x;
}
ll sub(ll x, ll y) {
	x -= y;
	if (x < 0) return x + MOD;
	return x;
}
ll mult(ll x, ll y) {
	return (x * y) % MOD;
}
ll bin_pow(ll x, ll p) {
	if (p == 0) return 1;
	if (p & 1) return mult(x, bin_pow(x, p - 1));
	return bin_pow(mult(x, x), p / 2);
}
ll rev(ll x) {
	return bin_pow(x, MOD - 2);
}

/////////////////////////

const ll MOD = (ll)1e9 + 7;
ll add(ll x, ll y) {
	x += y;
	if (x >= MOD) return x - MOD;
	return x;
}
ll sub(ll x, ll y) {
	x -= y;
	if (x < 0) return x + MOD;
	return x;
}
ll mult(ll x, ll y) {
	return (x * y) % MOD;
}
ll bin_pow(ll x, ll p) {
	if (p == 0) return 1;
	if (p & 1) return mult(x, bin_pow(x, p - 1));
	return bin_pow(mult(x, x), p / 2);
}
ll rev(ll x) {
	return bin_pow(x, MOD - 2);
}
 
const int N = 200200;
ll f[N], rf[N];
ll pA[N], pB[N];
int n;
ll A, B, C;
 
ll getC(int n, int k) {
	if (k < 0 || k > n) return 0;
	return mult(f[n], mult(rf[k], rf[n - k]));
}
 
int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
 
	f[0] = 1;
	for (int i = 1; i < N; i++)
		f[i] = mult(f[i - 1], i);
	rf[N - 1] = rev(f[N - 1]);
	for (int i = N - 1; i > 0; i--)
		rf[i - 1] = mult(rf[i], i);
 
	scanf("%d%lld%lld%lld", &n, &A, &B, &C);
	pA[0] = pB[0] = 1;
	pA[1] = mult(A, rev(A + B));
	pB[1] = mult(B, rev(A + B));
	for (int i = 2; i < N; i++) {
		pA[i] = mult(pA[i - 1], pA[1]);
		pB[i] = mult(pB[i - 1], pB[1]);
	}
	ll ans = 0;
	for (int k = 0; k < n; k++) {
		ll cur = getC(n - 1 + k, k);
		ans = add(ans, mult(mult(cur, n + k), add(mult(pA[n], pB[k]), mult(pB[n], pA[k]))));
	}
	ans = mult(ans, mult(100, rev(A + B)));
	printf("%lld\n", ans);
 
	return 0;
}
// source: https://atcoder.jp/contests/m-solutions2019/submissions/5729508

// source: https://codeforces.com/contest/1264/submission/66344993 (ksun48)
using ll = long long;
ll modinv(ll a, ll m) {
	assert(m > 0);
	if (m == 1) return 0;
	a %= m;
	if (a < 0) a += m;
	assert(a != 0);
	if (a == 1) return 1;
	return m - modinv(m, a) * m / a;
}


// Nice blog https://discuss.codechef.com/t/guide-to-modular-arithmetic-plus-tricks-codechef-edition-there-is-no-other-edition/67424


// tourist https://codeforces.com/contest/1523/submission/117878219
