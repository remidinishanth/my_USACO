/**
 * Description: Multiply polynomials of ints for any modulus $<2^{31}$. 
 	* For XOR convolution ignore \texttt{m} within \texttt{fft}. 
 * Time: O(N\log N)
 * Source: 
 	* KACTL (https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/NumberTheoreticTransform.h)
 	* https://cp-algorithms.com/algebra/fft.html
 	* https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
 	* maroonrk
 	* https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp
 * Verification: 
	* https://judge.yosupo.jp/problem/convolution_mod
	* SPOJ polymul, CSA manhattan, CF Perfect Encoding
	* http://codeforces.com/contest/632/problem/E
 */

#include "ModInt.h"
// const int MOD = 998244353;

using str = string; // yay python!
const int MOD = (119 << 23) + 1, root = 3; // = 998244353

#define tcT template<class T
tcT> using V = vector<T>;

#define rsz resize
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define each(a,x) for (auto& a: x)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)

// INPUT
#define tcTUU tcT, class ...U
tcT> void re(T& x) { cin >> x; }
tcTUU> void re(T& t, U&... u) { re(t); re(u...); }
tcT> void re(V<T>& x) { each(a,x) re(a); }

// Add mod int code here
// Usage
// typedef mint<MOD,3> mi; // 5 is primitive root for both common mods
// typedef vector<mi> vmi;

template<class T> void fft(V<T>& A, bool inv = 0) { // NTT
	int n = sz(A); assert((T::mod-1)%n == 0); V<T> B(n);
	for(int b = n/2; b; b /= 2, swap(A,B)) {
		T w = pow(T::rt(),(T::mod-1)/n*b), m = 1; // n/b'th root of unity
		for(int i = 0; i < n; i += b*2, m *= w) F0R(j,b) {
			T u = A[i+j], v = A[i+j+b]*m;
			B[i/2+j] = u+v; B[i/2+j+n/2] = u-v;
		}
	}
	if (inv) { reverse(1+all(A)); 
		T z = T(1)/T(n); each(t,A) t *= z; }
}
template<class T> V<T> mul(V<T> A, V<T> B) { // only special moduli for NTT
	if (!min(sz(A),sz(B))) return {};
	int s = sz(A)+sz(B)-1, n = 1; for (; n < s; n *= 2);
	bool eq = A == B; A.rsz(n), fft(A);
	if (eq) B = A; // squaring A, reuse result
	else B.rsz(n), fft(B);
	F0R(i,n) A[i] *= B[i];
	fft(A,1); A.rsz(s); return A;
}
template<class M, class T> V<M> mulMod(V<T> x, V<T> y) {
	auto con = [](const V<T>& v) {
		V<M> w(sz(v)); F0R(i,sz(v)) w[i] = (int)v[i];
		return w; };
	return mul(con(x),con(y));
}
template<class T> V<T> MUL(const V<T>& A, const V<T>& B) { // arbitrary moduli
	using m0 = mint<(119<<23)+1,62>; auto c0 = mulMod<m0>(A,B);
	using m1 = mint<(5<<25)+1,  62>; auto c1 = mulMod<m1>(A,B);
	using m2 = mint<(7<<26)+1,  62>; auto c2 = mulMod<m2>(A,B);
	int n = sz(c0); V<T> res(n);
	m1 r01 = 1/m1(m0::mod); m2 r02 = 1/m2(m0::mod), r12 = 1/m2(m1::mod);
	F0R(i,n) { // a is remainder mod m0::mod, b fixes it mod m1::mod
		int a = c0[i].v, b = ((c1[i]-a)*r01).v, c = (((c2[i]-a)*r02-b)*r12).v;
		res[i] = (T(c)*m1::mod+b)*m0::mod+a; // c fixes it mod m2::mod
	}
	return res;
}

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.


// Usage: https://atcoder.jp/contests/abc196/submissions/21481557
