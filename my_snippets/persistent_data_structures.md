```cpp
// Author: Tanuj Khattar (Baba)
// Code for https://www.spoj.com/problems/KQUERY/
// Accepted via both Path Copying and Fat Node persistence.
#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 10;
const int MX = 1e9 + 10;
const int LOGN = 32;
namespace path_copying_segree {
int L[N * LOGN], R[N * LOGN], ST[N * LOGN], blen, root[N];
// sparse persistent-segtree. range sum, initially 0
int update(int pos, int add, int l, int r, int id) {
  if (l > pos || r <= pos) return id;
  int ID = ++blen, m = l + (r - l) / 2;
  if (l == r - 1) return (ST[ID] = ST[id] + add, ID);
  L[ID] = update(pos, add, l, m, L[id]);
  R[ID] = update(pos, add, m, r, R[id]);
  return (ST[ID] = ST[L[ID]] + ST[R[ID]], ID);
}
void update(int A[], int n) {
  root[0] = ++blen;
  for (int i = 1; i <= n; i++) root[i] = update(A[i], 1, 1, MX, root[i - 1]);
}
int query(int qL, int qR, int l, int r, int x) {
  if (!x || r <= qL || qR <= l) return 0;
  if (l >= qL && r <= qR) return ST[x];
  int m = l + (r - l) / 2;
  return query(qL, qR, l, m, L[x]) + query(qL, qR, m, r, R[x]);
}
int query(int l, int r, int k) {
  return query(k + 1, MX, 1, MX, root[r]) -
         query(k + 1, MX, 1, MX, root[l - 1]);
}
}  // namespace path_copying_segree

namespace fat_node_segtree {
int L[N * LOGN], R[N * LOGN], blen, root;
vector<pair<int, int>> ST[N * LOGN];
// sparse persistent-segtree. range sum, initially 0
int latest_value_or_zero(int id) {
  return (ST[id].empty() ? 0 : ST[id].back().second);
}
int update(int pos, int add, int curr_time, int l, int r, int id) {
  if (pos < l || pos >= r) return id;
  if (!id) id = ++blen;
  if (l == r - 1) {
    int val = latest_value_or_zero(id) + add;
    ST[id].emplace_back(curr_time, val);
    return id;
  }
  int m = l + (r - l) / 2;
  L[id] = update(pos, add, curr_time, l, m, L[id]);
  R[id] = update(pos, add, curr_time, m, r, R[id]);
  int val = latest_value_or_zero(L[id]) + latest_value_or_zero(R[id]);
  ST[id].emplace_back(curr_time, val);
  return id;
}
void update(int A[], int n) {
  for (int i = 1; i <= n; i++) root = update(A[i], 1, i, 1, MX, root);
}
int value_at_time(int id, int qTime) {
  auto pos = upper_bound(begin(ST[id]), end(ST[id]), make_pair(qTime, MX)) -
             begin(ST[id]) - 1;
  return pos < 0 ? 0 : ST[id][pos].second;
}
int query(int qL, int qR, int qTime, int l, int r, int x) {
  if (!x || r <= qL || qR <= l) return 0;
  if (l >= qL && r <= qR) return value_at_time(x, qTime);
  int m = l + (r - l) / 2;
  return query(qL, qR, qTime, l, m, L[x]) + query(qL, qR, qTime, m, r, R[x]);
}
int query(int l, int r, int k) {
  return query(k + 1, MX, r, 1, MX, root) -
         query(k + 1, MX, l - 1, 1, MX, root);
}
}  // namespace fat_node_segtree
int A[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", A + i);
  }
  fat_node_segtree::update(A, n);
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    int l, r, k;
    scanf("%d %d %d", &l, &r, &k);
    printf("%d\n", fat_node_segtree::query(l, r, k));
  }
}
```
