#include <bits/stdc++.h>
using namespace std;
const int inf = (1 << 30) - 1;

// 0 - indexed
template <typename Monoid>
struct Segmenttree
{
	using F = function<Monoid(Monoid, Monoid)>;
	const Monoid e;
	const F f;

	int sz;
	vector<Monoid> seg;

	// size, operator, unit
	Segmenttree(int N, const F &f, const Monoid &e) : f(f), e(e)
	{
		sz = 1;
		while (sz < N)
			sz *= 2;
		seg.assign(2 * sz - 1, e);
	}

	void set(int k, const Monoid &x) { seg[k + sz - 1] = x; }

	void build()
	{
		for (int k = sz - 2; k >= 0; k--)
		{
			seg[k] = f(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}

	void update(int k, const Monoid &x)
	{
		k += sz - 1;
		seg[k] = x;
		while (k > 0)
		{
			k = (k - 1) / 2;
			seg[k] = f(seg[k * 2 + 1], seg[k * 2 + 2]);
		}
	}

	Monoid sub_query(int a, int b, int k, int l, int r)
	{
		if (r <= a || b <= l)
			return e;

		if (a <= l && r <= b)
			return seg[k];
		else
		{
			Monoid vl = sub_query(a, b, k * 2 + 1, l, (l + r) / 2);
			Monoid vr = sub_query(a, b, k * 2 + 2, (l + r) / 2, r);
			return f(vl, vr);
		}
	}

	// [l, r)
	Monoid query(int l, int r)
	{
		return sub_query(l, r, 0, 0, sz);
	}

	Monoid operator[](const int &k) const
	{
		return seg[k + sz];
	}
};

auto RMQ = [](int a, int b) { return min(a, b); };

int main()
{
	int N, Q;
	cin >> N >> Q;
	Segmenttree<int> seg(N, RMQ, inf);
	for (int i = 0; i < N; i++)
	{
		int a;
		cin >> a;
		seg.set(i, a);
	}

	seg.build();

	while (Q--)
	{
		int f;
		cin >> f;
		if (f == 1)
		{
			int l, r;
			cin >> l >> r;
			l--, r--;
			cout << seg.query(l, r + 1) << "\n";
		}
		if (f == 2)
		{
			int i, a;
			cin >> i >> a;
			i--;
			seg.update(i, a);
		}
	}
}

// https://kcs.miz-miz.biz/contest/7/code/100184
// https://github.com/ei1333/library/blob/master/structure/segment-tree/segment-tree.cpp
