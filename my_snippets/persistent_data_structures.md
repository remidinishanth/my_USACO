## What is persistence?
* Keep all versions of DS.
* DS operations relative to specified version
* Update creates(& returns) new version (never modify a version)

## Types of Persistence
* Partial persistence
  * Update only the latest version - versions are linearly ordered
  * Query any versoin of the data structure
* Full persistence
  * Update any version - versions form a tree
  * Query any version of the data structure

## Motivating Problem (Spoj KQUERY)

**Problem:** Given an array `A` with `N` elements, answer `Q` queries of the form:
* Range query: Given `L, R, K` - Find the number of elements in `[L, R]` which are greater than `K`

**Solution**

* Observation: Answer = (Number of numbers `> K` in `[1:R]`) - (Number of numbers `> K` in `[1:L-1]`)

* Modified question: Given an index `i`, query number of elements `> K` in `[1:i]`

  Given `i, K`: We can maintain have a frequency of elements in the array from `[1:i]` and return Sum of `F[p]` for `p > K`. 
  
  For a fixed `i` this can be done by segment tree range sum and point update.
  
  If we have a way to maintain this segment tree for all `i` then we are done. Observation: Segment tree for `i+1` will differ segment tree of position `i` only in `logN` nodes because we only increment `Frequency[A[i+1]]`.
  
* Persistent Segment Tree

  We want to save all the versions of the segment tree. If we do naively we require `O(NQ)` memory. We can do better because every time we do a modify in segment tree, we change only `O(log N)` nodes. Example Say we modify element `[4:4]` in the segment tree.
  
  ![image](https://user-images.githubusercontent.com/19663316/120119696-ccda4f80-c1b6-11eb-9e3b-a1c141a8d5aa.png)



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

### Adamant's implementation
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5, maxk = 1e6 + 1;
int root[maxn], L[16 * maxn], R[16 * maxn], sum[16 * maxn];
int rt = 1, sz = 1;
int lpos[maxk];
 
int copy(int v, int &u)
{
    L[sz] = L[v];
    R[sz] = R[v];
    sum[sz] = sum[v];
    return u = sz++;
}
 
void make_root()
{
    copy(root[rt - 1], root[rt]);
    rt++;
}
 
void add(int pos, int x, int v = root[rt - 1], int l = 0, int r = maxn)
{
	sum[v] += x;
    if(r - l == 1)
        return;
    int m = (l + r) / 2;
    if(pos < m)
        add(pos, x, copy(L[v], L[v]), l, m);
    else
        add(pos, x, copy(R[v], R[v]), m, r);
}
 
int get(int a, int b, int v, int l = 0, int r = maxn)
{
    if(a <= l && r <= b)
        return sum[v];
    if(r <= a || b <= l)
        return 0;
    int m = (l + r) / 2;
    return get(a, b, L[v], l, m) + get(a, b, R[v], m, r);
}
 
int main()
 {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        make_root();
        add(lpos[t], -1);
        lpos[t] = i;
        add(lpos[t], 1);
    }
 
    int q, l, r;
    cin >> q;
    while(q--)
    {
        cin >> l >> r;
        cout << get(l, r + 1, root[r]) << "\n";
    }
    return 0;
 }
```

source: https://codeforces.com/blog/entry/45428?#comment-304665
