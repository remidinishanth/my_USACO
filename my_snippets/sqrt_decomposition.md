MO's Algorithm

Usecase: Answering queries on a static array, offline (Mo's algorithm)

You are given array Arr of length N and Q queries. Each query is represented by two numbers L and R, and it asks you to compute some function Func `F` with subarray `Arr[L..R]` as its argument.

Mo’s algorithm provides a way to answer all queries in `O((N + Q) * sqrt(N) * F)` time with at least `O(Q)` additional memory. Meaning of F is explained below.

The algorithm is applicable if all following conditions are met:

* Arr is not changed by queries;
* All queries are known beforehand (techniques requiring this property are often called “offline algorithms”);
* If we know `Func([L, R])`, then we can compute `Func([L + 1, R])`, `Func([L - 1, R])`, `Func([L, R + 1])` and `Func([L, R - 1])`, each in O(F) time.

Algorithm
* Consider a problem where we are asked to find the answer for certain intervals `[l, r]`. We can't quickly compute the answer for an arbitrary interval, but we know how to transition to `[l, r±1]` and `[l±1, r]` fast given some information remaining from `[l, r]` answer calculation. The number of transitions we need to do to get from `[l1, r1]` to `[l2, r2]` is `|l1-l2|+|r1-r2|`.
* If there are only two intervals we need to answer such transitioning would help us. However, if there are many intervals, choosing a good transitioning route will drastically reduce the total time needed. Finding the best transition route quick is allegedly NP-hard, so we will focus on estimating a "good enough" route.
* Just by reordering our queries we can answer our queries faster, but since we reorder our queries, it is offline.

Proof why this works:

![](images/sqrt_mo_1.png)


First always make sure that you `add_element` then `remove_element`, otherwise your code might not work becaue of `--cnt[A[x]]==0`, if we don't add first then count might become negative.
```cpp
// Author: Tanuj Khattar
// Accepted Solution for https://www.spoj.com/problems/DQUERY/
// using MO's with Updates, as discussed in https://unacademy.com/educator/class/square-root-decomposition/BURZLN1E
#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 10;
const int Q = 2e5 + 10;
int A[N], rev[N], cnt[N];
struct Query {
  int idx, l, r, lb, rb;
} q[Q];
int compressed_val;
int ans[Q], curr_ans;
void add_element(int x) {
  if (++cnt[A[x]] == 1) {
    curr_ans += 1;
  }
}
void remove_element(int x) {
  if (--cnt[A[x]] == 0) {
    curr_ans -= 1;
  }
}
bool cmp(Query a, Query b) {
  return (a.lb < b.lb) || (a.lb == b.lb && a.r < b.r);
}
int main() {
  // Read Input.
  int n;
  scanf("%d", &n);
  int block = max(1, int(pow(n, 1.0 / 2.0)));
  map<int, int> mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d", A + i);
    mp[A[i]];
  }
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    q[i] = {i, x, y, x / block, y / block};
  }
  // Coordinate compression.
  // 1 <= A[i] <= 1e9 --> 1 <= A[i] <= N?
  // 2, 5, 10 --> 1, 2, 3 
  // 2 --> 1, 5 --> 2, 10 --> 3.
  for (auto &it : mp) {
    it.second = ++compressed_val;
    rev[compressed_val] = it.first;
  }
  for (int i = 1; i <= n; i++) {
    A[i] = mp[A[i]];
  }
  // Assume: 1 <= A[i] <= 1e5
  // Sort the queries.
  sort(q + 1, q + m + 1, cmp);
  // Answer the queries.
  for (int i = 1, L = 1, R = 0; i <= m; i++) {
    // Total cost of all 4 loops : |L2 - L1| + |R2 - R1|
    // First add_element and then remove_element
    while (R < q[i].r) add_element(++R);
    while (L > q[i].l) add_element(--L);
    while (R > q[i].r) remove_element(R--);
    while (L < q[i].l) remove_element(L++);
    ans[q[i].idx] = curr_ans;
  }
  for (int i = 1; i <= m; i++) {
    printf("%d\n", ans[i]);
  }
}
```

MO's with Updates
```cpp
// Author: Tanuj Khattar
// Accepted Solution for https://www.spoj.com/problems/XXXXXXXX/
// using MO's with Updates, as discussed in https://unacademy.com/educator/class/square-root-decomposition/BURZLN1E
#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;
const int Q = 1e5 + 10;
int A[N], last[N], rev[N + Q], cnt[N + Q];
bool use[N];
struct Query {
  int idx, l, r, t, lb, rb;
} q[Q];
struct Update {
  int x, new_y, prv_y;
} u[Q];
int nq, nu, compressed_val;
int64_t ans[Q], curr_ans;
void add_element(int x) {
  use[x] = true;
  if (++cnt[A[x]] == 1) {
    curr_ans += rev[A[x]];
  }
}
void remove_element(int x) {
  use[x] = false;
  if (--cnt[A[x]] == 0) {
    curr_ans -= rev[A[x]];
  }
}
void reflect_update(int x, int y) {
  // Set A[x] = y;
  if (!use[x]) {
    A[x] = y;
    return;
  }
  remove_element(x);
  A[x] = y;
  add_element(x);
}
void do_update(int i) { reflect_update(u[i].x, u[i].new_y); }
void undo_update(int i) { reflect_update(u[i].x, u[i].prv_y); }

bool cmp(Query a, Query b) {
  return (a.lb < b.lb) || (a.lb == b.lb && a.rb < b.rb) ||
         (a.lb == b.lb && a.rb == b.rb && a.t < b.t);
}
int main() {
  // Read Input.
  int n;
  scanf("%d", &n);
  int block = pow(n, 2.0 / 3.0);
  map<int, int> mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d", A + i);
    last[i] = A[i];
    mp[A[i]];
  }
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    char s[2];
    int x, y;
    scanf("%s %d %d", s, &x, &y);
    if (s[0] == 'Q') {
      nq++;
      q[nq] = {nq, x, y, nu, x / block, y / block};
    } else {
      u[++nu] = {x, y, last[x]};
      last[x] = y;
      mp[y];
    }
  }
  // Coordinate compression.
  for (auto &it : mp) {
    it.second = ++compressed_val;
    rev[compressed_val] = it.first;
  }
  for (int i = 1; i <= n; i++) {
    A[i] = mp[A[i]];
  }
  for (int i = 1; i <= nu; i++) {
    u[i].new_y = mp[u[i].new_y];
    u[i].prv_y = mp[u[i].prv_y];
  }
  // Sort the queries.
  sort(q + 1, q + nq + 1, cmp);
  // Answer the queries.
  for (int i = 1, T = 0, L = 1, R = 0; i <= nq; i++) {
    while (T < q[i].t) do_update(++T);
    while (T > q[i].t) undo_update(T--);
    while (R < q[i].r) add_element(++R);
    while (L > q[i].l) add_element(--L);
    while (R > q[i].r) remove_element(R--);
    while (L < q[i].l) remove_element(L++);
    ans[q[i].idx] = curr_ans;
  }
  for (int i = 1; i <= nq; i++) {
    printf("%lld\n", ans[i]);
  }
}
```

TODO: 

Basics https://blog.anudeep2011.com/mos-algorithm/ and https://codeforces.com/blog/entry/83248 and https://codeforces.com/blog/entry/81716

With Update: https://codeforces.com/blog/entry/72690

MO's Algorithm on Trees https://codeforces.com/blog/entry/43230 and https://codeforces.com/blog/entry/68271

Query Sqrt decomposition: https://codeforces.com/gym/100589/problem/A

Hilbert curve sorting - https://codeforces.com/blog/entry/61203

https://www.hackerearth.com/practice/notes/mos-algorithm/

https://h0rnet.hatenablog.com/entry/2016/03/03/CFR_Educational_2_E__Lomsat_gelral_(_Smaller_to_Larger_or_Time_stamp_+_Mo's_Algorithm_)

TODO: https://www.geeksforgeeks.org/sqrt-square-root-decomposition-set-2-lca-tree-osqrth-time/
