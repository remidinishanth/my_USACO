MO's Algorithm
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
