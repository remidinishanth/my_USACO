// This is set up for range minimum queries, but can be easily adapted for computing other quantities.
// To enable lazy propagation and range updates, uncomment the following line.
// #define LAZY
struct Segtree {
	int n;
	vector<int> data;
#ifdef LAZY
#define NOLAZY 2e9
#define GET(node) (lazy[node] == NOLAZY ? data[node] : lazy[node])
	vector<int> lazy;
#else
#define GET(node) data[node]
#endif
	void build_rec(int node, int* begin, int* end) {
		if (end == begin+1) {
			if (data.size() <= node) data.resize(node+1);
			data[node] = *begin;
		} else {
			int* mid = begin + (end-begin+1)/2;
			build_rec(2*node+1, begin, mid);
			build_rec(2*node+2, mid, end);
			data[node] = min(data[2*node+1], data[2*node+2]);
		}
	}
#ifndef LAZY
	void update_rec(int node, int begin, int end, int pos, int val) {
		if (end == begin+1) {
			data[node] = val;
		} else {
			int mid = begin + (end-begin+1)/2;
			if (pos < mid) {
				update_rec(2*node+1, begin, mid, pos, val);
			} else {
				update_rec(2*node+2, mid, end, pos, val);
			}
			data[node] = min(data[2*node+1], data[2*node+2]);
		}
	}
#else
	void update_range_rec(int node, int tbegin, int tend, int abegin, int aend, int val) {
		if (tbegin >= abegin && tend <= aend) {
			lazy[node] = val;
		} else {
			int mid = tbegin + (tend - tbegin + 1)/2;
			if (lazy[node] != NOLAZY) {
				lazy[2*node+1] = lazy[2*node+2] = lazy[node]; lazy[node] = NOLAZY;
			}
			if (mid > abegin && tbegin < aend)
				update_range_rec(2*node+1, tbegin, mid, abegin, aend, val);
			if (tend > abegin && mid < aend)
				update_range_rec(2*node+2, mid, tend, abegin, aend, val);
			data[node] = min(GET(2*node+1), GET(2*node+2));
		}
	}
#endif
	int query_rec(int node, int tbegin, int tend, int abegin, int aend) {
		if (tbegin >= abegin && tend <= aend) {
			return GET(node);
		} else {
#ifdef LAZY
			if (lazy[node] != NOLAZY) {
				data[node] = lazy[2*node+1] = lazy[2*node+2] = lazy[node]; lazy[node] = NOLAZY;
			}
#endif
			int mid = tbegin + (tend - tbegin + 1)/2;
			int res = INT_MAX;
			if (mid > abegin && tbegin < aend) 
				res = min(res, query_rec(2*node+1, tbegin, mid, abegin, aend));
			if (tend > abegin && mid < aend)
				res = min(res, query_rec(2*node+2, mid, tend, abegin, aend));
			return res;
		}
	}

	// Create a segtree which stores the range [begin, end) in its bottommost level.
	Segtree(int* begin, int* end): n(end - begin) {
		build_rec(0, begin, end);
#ifdef LAZY
		lazy.assign(data.size(), NOLAZY);
#endif
	}

#ifndef LAZY
	// Call this to update a value (indices are 0-based). If lazy propagation is enabled, use update_range(pos, pos+1, val) instaed.
	void update(int pos, int val) {
		update_rec(0, 0, n, pos, val);
	}
#else 
	// Call this to update range [begin, end), if lazy propagation is enabled. Indices are 0-based.
	void update_range(int begin, int end, int val) {
		update_range_rec(0, 0, n, begin, end, val);
	}
#endif
	// Returns minimum in range [begin, end). Indices are 0-based.
	int query(int begin, int end) {
		return query_rec(0, 0, n, begin, end);
	}
};

// source: t3nsor/codebook

// Usage: https://github.com/t3nsor/SPOJ/blob/ce4cde04a328c8b4050ba5586f6a8f500542f38e/orders-1.cpp

// 2014-10-02
// Uses a segtree with lazy propagation to repeatedly locate the
// highest ranking remaining soldier.
// TODO: There's an easier solution with BIT.
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
struct Segtree {
    int n;
    vector<int> data;
#define NOLAZY 0
#define GET(node) (data[node] + lazy[node])
    vector<int> lazy;
    void build_rec(int node, int* begin, int* end) {
        if (end == begin+1) {
            if (data.size() <= node) data.resize(node+1);
            data[node] = *begin;
        } else {
            int* mid = begin + (end-begin+1)/2;
            build_rec(2*node+1, begin, mid);
            build_rec(2*node+2, mid, end);
            data[node] = min(data[2*node+1], data[2*node+2]);
        }
    }
    void update_range_rec(int node, int tbegin, int tend, int abegin, int aend, int val) {
        if (tbegin >= abegin && tend <= aend) {
            lazy[node] += val;
        } else {
            int mid = tbegin + (tend - tbegin + 1)/2;
            if (lazy[node] != NOLAZY) {
                lazy[2*node+1] += lazy[node];
                lazy[2*node+2] += lazy[node];
                lazy[node] = NOLAZY;
            }
            if (mid > abegin && tbegin < aend)
                update_range_rec(2*node+1, tbegin, mid, abegin, aend, val);
            if (tend > abegin && mid < aend)
                update_range_rec(2*node+2, mid, tend, abegin, aend, val);
            data[node] = min(GET(2*node+1), GET(2*node+2));
        }
    }
    int find_rightmost_zero_rec(int node, int begin, int end) {
        if (end == begin + 1) {
            return begin;
        } else {
            if (lazy[node] != NOLAZY) {
                data[node] += lazy[node];
                lazy[2*node+1] += lazy[node];
                lazy[2*node+2] += lazy[node];
                lazy[node] = NOLAZY;
            }
            int mid = begin + (end - begin + 1)/2;
            if (GET(2*node+2) == 0) {
                return find_rightmost_zero_rec(2*node+2, mid, end);
            } else {
                return find_rightmost_zero_rec(2*node+1, begin, mid);
            }
        }
    }

    // Create a segtree which stores the range [begin, end) in its bottommost level.
    Segtree(int* begin, int* end): n(end - begin) {
        build_rec(0, begin, end);
        lazy.assign(data.size(), NOLAZY);
    }

    // Call this to update range [begin, end), if lazy propagation is enabled. Indices are 0-based.
    void update_range(int begin, int end, int val) {
        update_range_rec(0, 0, n, begin, end, val);
    }
    int find_rightmost_zero() {
        return find_rightmost_zero_rec(0, 0, n);
    }
};

int w[200000];
int a[200000];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", w + i);
        }
        Segtree T(w, w+n);
        for (int i = n; i >= 1; i--) {
            // find rightmost zero
            int pos = T.find_rightmost_zero();
            a[pos] = i;
            T.update_range(pos+1, n, -1);
            T.update_range(pos, pos+1, 1e6);
        }
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        putchar('\n');
    }
    return 0;
}
