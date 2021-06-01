#include <bits/stdc++.h>
using namespace std;

// max1 - first maximum
// max2 - second maximum
// maxc - count of first maximum
// Tree starts at 0, iterative implementation
// left child l = i * 2 + 1; right child r = i * 2 + 2;
// Range sum is for [l,r), // 0-based, [l, r)

const long long INF = 1000000000000000000;
template <typename T>
struct segment_tree_beats{
	int N;
	vector<T> max1, max2, min1, min2;
	vector<T> add, sum;
	vector<int> maxc, minc, len;
	void update_max(int i, T x){
		sum[i] += (x - max1[i]) * maxc[i];
		if (max1[i] == min1[i]){
			min1[i] = x;
		} else if (max1[i] == min2[i]){
			min2[i] = x;
		}
		max1[i] = x;
	}
	void update_min(int i, T x){
		sum[i] += (x - min1[i]) * minc[i];
		if (min1[i] == max1[i]){
			max1[i] = x;
		} else if (min1[i] == max2[i]){
			max2[i] = x;
		}
		min1[i] = x;
	}
	void update_add(int i, T x){
		max1[i] += x;
		if (max2[i] != -INF){
			max2[i] += x;
		}
		min1[i] += x;
		if (min2[i] != INF){
			min2[i] += x;
		}
		sum[i] += x * len[i];
		add[i] += x;
	}
	void push(int i){
		if (i >= N - 1){
			return;
		}
		int l = i * 2 + 1;
		int r = i * 2 + 2;
		if (add[i] != 0){
			update_add(l, add[i]);
			update_add(r, add[i]);
			add[i] = 0;
		}
		if (max1[i] < max1[l]){
			update_max(l, max1[i]);
		}
		if (min1[i] > min1[l]){
			update_min(l, min1[i]);
		}
		if (max1[i] < max1[r]){
			update_max(r, max1[i]);
		}
		if (min1[i] > min1[r]){
			update_min(r, min1[i]);
		}
	}
	void update(int i){
		int l = i * 2 + 1;
		int r = i * 2 + 2;
		sum[i] = sum[l] + sum[r];
		if (max1[l] > max1[r]){
			max1[i] = max1[l];
			max2[i] = max(max2[l], max1[r]);
			maxc[i] = maxc[l];
		} else if (max1[l] < max1[r]){
			max1[i] = max1[r];
			max2[i] = max(max1[l], max2[r]);
			maxc[i] = maxc[r];
		} else {
			max1[i] = max1[l];
			max2[i] = max(max2[l], max2[r]);
			maxc[i] = maxc[l] + maxc[r];
		}
		if (min1[l] < min1[r]){
			min1[i] = min1[l];
			min2[i] = min(min2[l], min1[r]);
			minc[i] = minc[l];
		} else if (min1[l] > min1[r]){
			min1[i] = min1[r];
			min2[i] = min(min1[l], min2[r]);
			minc[i] = minc[r];
		} else {
			min1[i] = min1[l];
			min2[i] = min(min2[l], min2[r]);
			minc[i] = minc[l] + minc[r];
		}
	}
	segment_tree_beats(vector<T> A){
		int n = A.size();
		N = 1;
		while (N < n){
			N *= 2;
		}
		max1 = vector<T>(N * 2 - 1, -INF);
		max2 = vector<T>(N * 2 - 1, -INF);
		min1 = vector<T>(N * 2 - 1, INF);
		min2 = vector<T>(N * 2 - 1, INF);
		add = vector<T>(N * 2 - 1, 0);
		sum = vector<T>(N * 2 - 1, 0);
		maxc = vector<int>(N * 2 - 1, 0);
		minc = vector<int>(N * 2 - 1, 0);
		len = vector<int>(N * 2 - 1, 1);
		for (int i = 0; i < n; i++){
			max1[N - 1 + i] = A[i];
			min1[N - 1 + i] = A[i];
			sum[N - 1 + i] = A[i];
			maxc[N - 1 + i] = 1;
			minc[N - 1 + i] = 1;
		}
		for (int i = N - 2; i >= 0; i--){
			len[i] = len[i * 2 + 1] + len[i * 2 + 2];
			update(i);
		}
	}
	void range_chmin(int L, int R, T x, int i, int l, int r){
		if (r <= L || R <= l || x >= max1[i]){
			return;
		} else if (L <= l && r <= R && x > max2[i]){
			update_max(i, x);
			return;
		}
		push(i);
		int m = (l + r) / 2;
		range_chmin(L, R, x, i * 2 + 1, l, m);
		range_chmin(L, R, x, i * 2 + 2, m, r);
		update(i);
	}
	void range_chmin(int L, int R, T x){  // 0-based, [l, r)
		range_chmin(L, R, x, 0, 0, N);
	}
	void range_chmax(int L, int R, T x, int i, int l, int r){
		if (r <= L || R <= l || x <= min1[i]){
			return;
		} else if (L <= l && r <= R && x < min2[i]){
			update_min(i, x);
			return;
		}
		push(i);
		int m = (l + r) / 2;
		range_chmax(L, R, x, i * 2 + 1, l, m);
		range_chmax(L, R, x, i * 2 + 2, m, r);
		update(i);
	}
	void range_chmax(int L, int R, T x){  // 0-based, [l, r)
		range_chmax(L, R, x, 0, 0, N);
	}
	void range_add(int L, int R, T x, int i, int l, int r){
		if (r <= L || R <= l){	
			return;
		} else if (L <= l && r <= R){
			update_add(i, x);
			return;
		}
		push(i);
		int m = (l + r) / 2;
		range_add(L, R, x, i * 2 + 1, l, m);
		range_add(L, R, x, i * 2 + 2, m, r);
		update(i);
	}
	void range_add(int L, int R, T x){  // 0-based, [l, r)
		range_add(L, R, x, 0, 0, N);
	}
	T range_sum(int L, int R, int i, int l, int r){
		if (r <= L || R <= l){
			return 0;
		} else if (L <= l && r <= R){
			return sum[i];
		}
		push(i);
		int m = (l + r) / 2;
		return range_sum(L, R, i * 2 + 1, l, m) + range_sum(L, R, i * 2 + 2, m, r);
	}
	T range_sum(int L, int R){  // 0-based, [l, r)
		return range_sum(L, R, 0, 0, N);
	}
};
int main(){
  int N;
  cin >> N;
  vector<long long> a(N);
  vector<int> t(N);
  for (int i = 0; i < N; i++){
    cin >> a[i] >> t[i];
  }
  int Q;
  cin >> Q;
  vector<long long> x(Q);
  for (int i = 0; i < Q; i++){
    cin >> x[i];
  }
  segment_tree_beats ST(x);
  for (int i = 0; i < N; i++){
    if (t[i] == 1){
      ST.range_add(0, Q, a[i]);
    }
    if (t[i] == 2){
      ST.range_chmax(0, Q, a[i]);
    }
    if (t[i] == 3){
      ST.range_chmin(0, Q, a[i]);
    }
  }
  for (int i = 0; i < Q; i++){
    cout << ST.range_sum(i, i + 1) << endl;
  }
}

// REF: https://atcoder.jp/contests/abc196/submissions/21092752


// Another implementation
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) std::begin(x), std::end(x)

/**
 * @brief a segment tree beats
 */
class segment_tree_beats {
    // MEMO: values for queries (max, min, lazy_add, and lazy_update) already apply to the current node; but not for children
    typedef struct {
        int64_t max;
        int64_t max_second;
        int max_count;
        int64_t min;
        int64_t min_second;
        int min_count;
        int64_t lazy_add;
        int64_t lazy_update;
        int64_t sum;
    } value_type;

    int n;
    std::vector<value_type> a;

public:
    segment_tree_beats() = default;
    segment_tree_beats(int n_) {
        n = 1; while (n < n_) n *= 2;
        a.resize(2 * n - 1);
        tag<UPDATE>(0, 0);
    }
    template <class InputIterator>
    segment_tree_beats(InputIterator first, InputIterator last) {
        int n_ = std::distance(first, last);
        n = 1; while (n < n_) n *= 2;
        a.resize(2 * n - 1);
        REP (i, n_) {
            tag<UPDATE>(n - 1 + i, *(first + i));
        }
        REP3 (i, n_, n) {
            tag<UPDATE>(n - 1 + i, 0);
        }
        REP_R (i, n - 1) {
            update(i);
        }
    }

    void range_chmin(int l, int r, int64_t value) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        range_apply<CHMIN>(0, 0, n, l, r, value);
    }
    void range_chmax(int l, int r, int64_t value) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        range_apply<CHMAX>(0, 0, n, l, r, value);
    }
    void range_add(int l, int r, int64_t value) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        range_apply<ADD>(0, 0, n, l, r, value);
    }
    void range_update(int l, int r, int64_t value) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        range_apply<UPDATE>(0, 0, n, l, r, value);
    }

    int64_t range_min(int l, int r) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        return range_get<MIN>(0, 0, n, l, r);
    }
    int64_t range_max(int l, int r) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        return range_get<MAX>(0, 0, n, l, r);
    }
    int64_t range_sum(int l, int r) {  // 0-based, [l, r)
        assert (0 <= l and l <= r and r <= n);
        return range_get<SUM>(0, 0, n, l, r);
    }

private:
    static constexpr char CHMIN = 0;
    static constexpr char CHMAX = 1;
    static constexpr char ADD = 2;
    static constexpr char UPDATE = 3;
    static constexpr char MIN = 10;
    static constexpr char MAX = 11;
    static constexpr char SUM = 12;

    template <char TYPE>
    void range_apply(int i, int il, int ir, int l, int r, int64_t g) {
        if (ir <= l or r <= il or break_condition<TYPE>(i, g)) {
            // break
        } else if (l <= il and ir <= r and tag_condition<TYPE>(i, g)) {
            tag<TYPE>(i, g);
        } else {
            pushdown(i);
            range_apply<TYPE>(2 * i + 1, il, (il + ir) / 2, l, r, g);
            range_apply<TYPE>(2 * i + 2, (il + ir) / 2, ir, l, r, g);
            update(i);
        }
    }
    template <char TYPE>
    inline bool break_condition(int i, int64_t g) {
        switch (TYPE) {
            case CHMIN: return a[i].max <= g;
            case CHMAX: return g <= a[i].min;
            case ADD: return false;
            case UPDATE: return false;
            default: assert (false);
        }
    }
    template <char TYPE>
    inline bool tag_condition(int i, int64_t g) {
        switch (TYPE) {
            case CHMIN: return a[i].max_second < g and g < a[i].max;
            case CHMAX: return a[i].min < g and g < a[i].min_second;
            case ADD: return true;
            case UPDATE: return true;
            default: assert (false);
        }
    }
    template <char TYPE>
    inline void tag(int i, int64_t g) {
        int length = n >> (32 - __builtin_clz(i + 1) - 1);
        if (TYPE == CHMIN) {
            if (a[i].max == a[i].min or g <= a[i].min) {
                tag<UPDATE>(i, g);
                return;
            }
            if (a[i].max != INT64_MIN) {
                a[i].sum -= a[i].max * a[i].max_count;
            }
            a[i].max = g;
            a[i].min_second = std::min(a[i].min_second, g);
            if (a[i].lazy_update != INT64_MAX) {
                a[i].lazy_update = std::min(a[i].lazy_update, g);
            }
            a[i].sum += g * a[i].max_count;
        } else if (TYPE == CHMAX) {
            if (a[i].max == a[i].min or a[i].max <= g) {
                tag<UPDATE>(i, g);
                return;
            }
            if (a[i].min != INT64_MAX) {
                a[i].sum -= a[i].min * a[i].min_count;
            }
            a[i].min = g;
            a[i].max_second = std::max(a[i].max_second, g);
            if (a[i].lazy_update != INT64_MAX) {
                a[i].lazy_update = std::max(a[i].lazy_update, g);
            }
            a[i].sum += g * a[i].min_count;
        } else if (TYPE == ADD) {
            if (a[i].max != INT64_MAX) {
                a[i].max += g;
            }
            if (a[i].max_second != INT64_MIN) {
                a[i].max_second += g;
            }
            if (a[i].min != INT64_MIN) {
                a[i].min += g;
            }
            if (a[i].min_second != INT64_MAX) {
                a[i].min_second += g;
            }
            a[i].lazy_add += g;
            if (a[i].lazy_update != INT64_MAX) {
                a[i].lazy_update += g;
            }
            a[i].sum += g * length;
        } else if (TYPE == UPDATE) {
            a[i].max = g;
            a[i].max_second = INT64_MIN;
            a[i].max_count = length;
            a[i].min = g;
            a[i].min_second = INT64_MAX;
            a[i].min_count = length;
            a[i].lazy_add = 0;
            a[i].lazy_update = INT64_MAX;
            a[i].sum = g * length;
        } else {
            assert (false);
        }
    }
    void pushdown(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        // update
        if (a[i].lazy_update != INT64_MAX) {
            tag<UPDATE>(l, a[i].lazy_update);
            tag<UPDATE>(r, a[i].lazy_update);
            a[i].lazy_update = INT64_MAX;
            return;
        }
        // add
        if (a[i].lazy_add != 0) {
            tag<ADD>(l, a[i].lazy_add);
            tag<ADD>(r, a[i].lazy_add);
            a[i].lazy_add = 0;
        }
        // chmin
        if (a[i].max < a[l].max) {
            tag<CHMIN>(l, a[i].max);
        }
        if (a[i].max < a[r].max) {
            tag<CHMIN>(r, a[i].max);
        }
        // chmax
        if (a[l].min < a[i].min) {
            tag<CHMAX>(l, a[i].min);
        }
        if (a[r].min < a[i].min) {
            tag<CHMAX>(r, a[i].min);
        }
    }
    void update(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        // chmin
        std::vector<int64_t> b { a[l].max, a[l].max_second, a[r].max, a[r].max_second };
        std::sort(b.rbegin(), b.rend());
        b.erase(std::unique(ALL(b)), b.end());
        a[i].max = b[0];
        a[i].max_second = b[1];
        a[i].max_count = (b[0] == a[l].max ? a[l].max_count : 0) + (b[0] == a[r].max ? a[r].max_count : 0);
        // chmax
        std::vector<int64_t> c { a[l].min, a[l].min_second, a[r].min, a[r].min_second };
        std::sort(ALL(c));
        c.erase(std::unique(ALL(c)), c.end());
        a[i].min = c[0];
        a[i].min_second = c[1];
        a[i].min_count = (c[0] == a[l].min ? a[l].min_count : 0) + (c[0] == a[r].min ? a[r].min_count : 0);
        // add
        a[i].lazy_add = 0;
        // update
        a[i].lazy_update = INT64_MAX;
        // sum
        a[i].sum = a[l].sum + a[r].sum;
    }

    template <char TYPE>
    int64_t range_get(int i, int il, int ir, int l, int r) {
        if (ir <= l or r <= il) {
            return 0;
        } else if (l <= il and ir <= r) {
            // base
            switch (TYPE) {
                case MIN: return a[i].min;
                case MAX: return a[i].max;
                case SUM: return a[i].sum;
                default: assert (false);
            }
        } else {
            pushdown(i);
            int64_t value_l = range_get<TYPE>(2 * i + 1, il, (il + ir) / 2, l, r);
            int64_t value_r = range_get<TYPE>(2 * i + 2, (il + ir) / 2, ir, l, r);
            // mult
            switch (TYPE) {
                case MIN: return std::min(value_l, value_r);
                case MAX: return std::max(value_l, value_r);
                case SUM: return value_l + value_r;
                default: assert (false);
            }
        }
    }
};

int main() {
    int n, q; scanf("%d%d", &n, &q);

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    segment_tree_beats beats(ALL(a));

    for (int ph = 0; ph < q; ph++) {
        int ty, l, r; scanf("%d%d%d", &ty, &l, &r);
        if (ty == 0) {
            long long b; scanf("%lld", &b);
            beats.range_chmin(l, r, b);
        } else if (ty == 1) {
            long long b; scanf("%lld", &b);
            beats.range_chmax(l, r, b);
        } else if (ty == 2) {
            long long b; scanf("%lld", &b);
            beats.range_add(l, r, b);
        } else {
            long long sum = beats.range_sum(l, r);
            printf("%lld\n", sum);
        }
    }
    return 0;
}

// REF: https://github.com/yosupo06/library-checker-problems/blob/master/datastructure/range_chmin_chmax_add_range_sum/sol/correct.cpp
