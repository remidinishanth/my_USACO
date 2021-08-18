## Anudeep's blog

source: https://blog.anudeep2011.com/mos-algorithm/

### State a problem

Given an array of size N. All elements of array `<= N`. You need to answer M queries. Each query is of the form `L, R`. You need to answer the count of values in range `[L, R]` which are repeated at least 3 times.

Example: Let the array be `{1, 2, 3, 1, 1, 2, 1, 2, 3, 1}` (zero indexed)

* Query: `L = 0, R = 4`. Answer = 1. Values in the range `[L, R] = {1, 2, 3, 1, 1}` only 1 is repeated at least 3 times.
* Query: `L = 1, R = 8`. Answer = 2. Values in the range `[L, R] = {2, 3, 1, 1, 2, 1, 2, 3}` 1 is repeated 3 times and 2 is repeated 3 times. Number of elements repeated at least 3 times = Answer = 2.

### Explain a simple solution which takes O(N^2)

For each query, loop from L to R, count the frequency of elements and report the answer. Considering M = N, following runs in O(N^2) in worst case.

```cpp
for each query:
  answer = 0
  count[] = 0
  for i in {l..r}:
    count[array[i]]++
    if count[array[i]] == 3:
      answer++
```

### Slight modification to above algorithm. It still runs in O(N^2)

```python
def add(position):
  count[array[position]]++
  if count[array[position]] == 3:
    answer++

def remove(position):
  count[array[position]]--
  if count[array[position]] == 2:
    answer--

currentL = 0
currentR = 0
answer = 0
count[] = 0
for L,R in query:
  # currentL should go to L, currentR should go to R
  while currentL < L:
    remove(currentL)
    currentL += 1
  while currentL > L:
    add(currentL)
    currentL -= 1
  while currentR < R:
    add(currentR)
    currentR += 1
  while currentR > R:
    remove(currentR)
    currentR -= 1
  print(answer) # Number of elements whose frequency > 3
```

Initially we always looped from `L` to `R`, but now we are changing the positions from previous query to adjust to current query.

If previous query was `L=3, R=10`, then we will have `currentL=3` and `currentR=10` by the end of that query. Now if the next query is `L=5, R=7`, then we move the `currentL` to `5` and `currentR` to `7`.

* `add` function means we are adding the element at position to our current set. And updating answer accordingly.
* `remove` function means we are deleting the element at position from our current set. And updating answer accordingly.

Although not a bug but I would like to mention to the readers that the code snippet given in the blog suffers from a logical counter intuitiveness that remove operation of an element can happen before add operation on it. For example n = 8, and we have 2 queries (0,7) ans (1,4) then after ordering the queries appear in (1,4) followed by (0,7) and the code snippet removes 0th element while increasing the left pointer while it was not added previously. Now this may cause serious problem because in some problems where this assumption is necessary to ensure certain quantity does not become negative.

### Explain an algorithm to solve above problem and state its correctness

MO’s algorithm is just an order in which we process the queries. We were given `M` queries, we will re-order the queries in a particular order and then process them. Clearly, this is an offline algorithm. Each query has `L` and `R`, we will call them opening and closing. Let us divide the given input array into `Sqrt(N)` blocks. Each block will be `N / Sqrt(N) = Sqrt(N)` size. Each opening has to fall in one of these blocks. Each closing has to fall in one of these blocks.

A query belongs to P’th block if the opening of that query fall in P’th block. In this algorithm we will process the queries of 1st block. Then we process the queries of 2nd block and so on.. finally `Sqrt(N)`’th block. We already have an ordering, queries are ordered in the ascending order of its block. There can be many queries that belong to the same block.

From now, I will ignore about all the blocks and only focus on how we query and answer block 1. We will similarly do for all blocks. All of these queries have their opening in block 1, but their closing can be in any block including block 1. Now let us reorder these queries in ascending order of their R value. We do this for all the blocks.

How does the final order look like?
All the queries are first ordered in ascending order of their block number (block number is the block in which its opening falls). Ties are ordered in ascending order of their R value.
For example consider following queries and assume we have 3 blocks each of size 3. `{0, 3} {1, 7} {2, 8} {7, 8} {4, 8} {4, 4} {1, 2}`
* Let us re-order them based on their `block number`. `{0, 3} {1, 7} {2, 8} {1, 2} {4, 8} {4, 4} {7, 8}`
* Now let us re-order ties based on their `R` value. `{1, 2} {0, 3} {1, 7} {2, 8} {4, 4} {4, 8} {7, 8}`

Now we use the same code stated in previous section and solve the problem. Above algorithm is correct as we did not do any changes but just reordered the queries.

### Proof for complexity of above algorithm – O(Sqrt(N) * N)

We are done with MO’s algorithm, it is just an ordering. Awesome part is its runtime analysis. It turns out that the `O(N^2)` code we wrote works in `O(Sqrt(N) * N)` time if we follow the order specified above. Thats awesome right, with just reordering the queries we reduced the complexity from `O(N^2)` to `O(Sqrt(N) * N)`, and that too with out any further modification to code. Hurray! we will get AC with `O(Sqrt(N) * N)`.

Have a look at our code above, the complexity over all queries is determined by the 4 while loops. First 2 while loops can be stated as “Amount moved by left pointer in total”, second 2 while loops can be stated as “Amount moved by right pointer”. Sum of these two will be the over all complexity.

Most important. Let us talk about the right pointer first. For each block, the queries are sorted in increasing order, so clearly the right pointer (currentR) moves in increasing order. During the start of next block the pointer possibly at extreme end will move to least R in next block. That means for a given block, the amount moved by right pointer is `O(N)`. We have `O(Sqrt(N)) blocks`, so the total is `O(N * Sqrt(N))`. Great!

Let us see how the left pointer moves. For each block, the left pointer of all the queries fall in the same block, as we move from query to query the left pointer might move but as previous L and current L fall in the same block, the moment is `O(Sqrt(N))` (Size of the block). In each block the amount left pointer movies is `O(Q * Sqrt(N))` where Q is number of queries falling in that block. Total complexity is `O(M * Sqrt(N))` for all blocks.

There you go, total complexity is `O( (N + M) * Sqrt(N)) = O( N * Sqrt(N))`

### Explain where and when we can use above algorithm

As mentioned, this algorithm is offline, that means we cannot use it when we are forced to stick to given order of queries. That also means we cannot use this when there are update operations. Not just that, there is one important possible limitation: We should be able to write the functions add and remove. There will be many cases where add is trivial but remove is not. One such example is where we want maximum in a range. As we add elements, we can keep track of maximum. But when we remove elements it is not trivial. Anyways in that case we can use a set to add elements, remove elements and report minimum. In that case the add and delete operations are O(log N) (Resulting in O(N * Sqrt(N) * log N) algorithm).

There are many cases where we can use this algorithm. In few cases we can also use other Data Structures like segment trees, but for few problems using MO’s algorithm is a must. Lets discuss few problems in the next section.

### TODO Problems

* Powerful array – CF Div1 D: This is an example where MO’s algorithm is a must. I cannot think of any other solution. CF Div1 D means it is a hard problem. See how easy it is using MO’s algorithm in this case. You only need to modify add(), remove() functions in above code.
* GERALD07 – Codechef
* GERALD3 – Codechef
* Tree and Queries – CF Div1 D
* Jeff and Removing Periods – CF Div1 D
* Sherlock and Inversions – Codechef

## MO's Algorithm

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
// Accepted Solution for https://www.spoj.com/problems/XXXXXXXX/ using MO's with Updates,
// as discussed in https://unacademy.com/educator/class/square-root-decomposition/BURZLN1E
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

### Implementation trick

Comparator within struct

```cpp
// mo stuff
int BL[nax]; // block of l
int ans[nax];
int cnt[nax];

struct query {
    int id, l, r, k;
    const bool operator<(const query &other) const{
        return BL[l] == BL[other.l] ? r < other.r : BL[l] < BL[other.l];
    }
};
```

Nice implementation by ffao https://codeforces.com/contest/375/submission/18814449

## Mo's Algorithm on Trees

### Handling Subtree Queries

Consider the following problem. You will be given a rooted Tree T of N nodes where each node is associated with a value A[node]. You need to handle Q queries, each comprising one integer u. In each query you must report the number of distinct values in the subtree rooted at u. In other words, if you store all the values in the subtree rooted at u in a set, what would be the size of this set? `1 ≤ N, Q ≤ 10^5` and `1 ≤ A[node] ≤ 10^9`

**Solution:**  One easy way to solve this is to flatten the tree into an array by doing a Preorder traversal(Euler tour tree) and then implement Mo's Algorithm. Once we flatten the tree, subtree queries becomes range queries. Maintain a lookup table which maintains the frequency of each value in the current window. By maintaining this, the answer can be updated easily. Complexity of solution would be `O(Q √N)`.

Note that we can also solve this in `O(N log^2N)` by maintaining a set in each node and using Small to Large merging(or DSU Sack on tree).

### Handling Path Queries

In the above problem, instead of subtree of `u`, we are asked to compute the number of distinct values in the path from `u` to `v`.

**Issue:** While handling subtree queries, because of Euler tour tree, it was possible to represent any subtree as a contiguous range in an array. Thus the problem was reduced to "finding number of distinct values in a subarray `[L, R]` of `A[]`.  Note that it is not possible to do so for path queries, as nodes which are `O(N)` distance apart in the tree might be `O(1)` distance apart in the flattened tree (represented by Array `A[]`). So doing a normal dfs-order would not work out.

**Observations:** Let a node `u` have `k` children. Let us number them as `v1, v2, ..., vk`. Let `S(u)` denote the subtree rooted at `u`. Let us assume that `dfs()` will visit u's children in the order `v1, v2, ..., vk`. Let `x` be any node in `S(vi)` and `y` be any node in `S(vj)` and let `i < j`. Notice that `dfs(y)` will be called only after `dfs(x)` has been completed and S(x) has been explored. Thus, before we call `dfs(y)`, we would have entered and exited `S(x)`. We will exploit this seemingly obvious property of dfs() to modify our existing algorithm and try to represent each query as a contiguous range in a flattened array. Each vertex which is not on the path will appear twice in Euler Tour tree between `start[u] and start[v]` if we insert vertices at `start` and `finish` of vertex.

**Algorithm:**

Let a query be (u, v). We will try to map each query to a range in the flattened array. Let ST(u) ≤ ST(v) where ST(u) denotes visit time of node u in T. Let P = LCA(u, v) denote the lowest common ancestor of nodes u and v. There are 2 possible cases:

* lca(u, v) = u. 
  In this case, our query range would be [ST(u), ST(v)]. Why will this work?

  Consider any node x that does not lie in the (u, v) path. Notice that x occurs twice or zero times in our specified query range. Therefore, the nodes which occur exactly once in this range are precisely those that are on the (u, v) path! (Try to convince yourself of why this is true : It's all because of dfs() properties.)
  
  This forms the crux of our algorithm. While implementing Mo's, our add/remove function needs to check the number of times a particular node appears in a range. If it occurs twice (or zero times), then we don't take it's value into account! This can be easily implemented while moving the left and right pointers.
  
* lca(u, v) != u
  In this case, our query range would be [EN(u), ST(v)] + [ST(P), ST(P)].
  
  Same logic from previous case applies here. The only difference is that we need to consider the value of P i.e the LCA separately, as it would not be counted in the query range.
  
#### SPOJ COT2 - Count on a tree II

You are given a tree with N nodes. The tree nodes are numbered from 1 to N. Each node has an integer weight.

We will ask you to perform the following operation:

u v : ask for how many different integers that represent the weight of nodes there are on the path from u to v. (N <= 40000, Queries M <= 100000)

Solution: 

```cpp
#include<bits/stdc++.h>

using namespace std;

const int nax = 1e5 + 10;
const int LG = 19;

int color[nax];
vector<int> adj[nax];

// euler tour tree
int timer;
int st[nax], en[nax];
int node[nax]; // node at time[i]
int depth[nax];
int par[nax][LG];

// insert every node twice in ETT
void dfs(int u, int p){
    st[u] = timer++; node[st[u]] = u;
    for(int v: adj[u]){
        if(v==p) continue;
        depth[v] = depth[u] + 1;
        par[v][0] = u;
        for(int i=1; par[v][i-1]; i++){
            par[v][i] = par[par[v][i-1]][i-1];
        }
        dfs(v, u);
    }
    en[u] = timer++; node[en[u]] = u;
}

int jump(int u, int k){
    for(int i=LG-1;i>=0;i--){
        if(k >= (1<<i)){
            u = par[u][i];
            k -= 1<<i;
        }
    }
    return u;
}

int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    v = jump(v, depth[v] - depth[u]);
    if(u == v) return u;
    for(int i=LG-1;i>=0;i--){
        if(par[u][i] != par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

// mo stuff
int BL[nax]; // block of l
int ans[nax];
int cnt[nax];
int curAns; // global answer
int vis[nax]; // to check whether node is visited

struct query {
    int id, l, r, u, v, z; // z is lca(u, v)
    bool operator<(const query &other) const{
        return BL[l] == BL[other.l] ? r < other.r : BL[l] < BL[other.l];
    }
};

vector<query> Q;

void add(int u){
    // if (u) occurs twice, then don't consider it's value
    if(vis[u] && --cnt[color[u]] == 0) curAns--;
    else if(!vis[u]  && cnt[color[u]]++ == 0) curAns++;
    vis[u] ^= 1;
}

void compute(){
    int curL = Q[0].l, curR = Q[0].l - 1;
    for(int i=0; i<Q.size(); i++){
        query q = Q[i];
        while(curL > q.l) add(node[--curL]);
        while(curR < q.r) add(node[++curR]);
        while(curL < q.l) add(node[curL++]);
        while(curR > q.r) add(node[curR--]);

        // if lca(u, v) != u then include lca in the answer
        if(q.z != q.u) add(q.z);
        ans[q.id] = curAns;
        if(q.z != q.u) add(q.z);

    }
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &color[i]);
    // coordinate compress on colors
    map<int, int> M;
    int tt = 1;
    for(int i=1;i<=n;i++){
        // no need to sort colors first
        if(M[color[i]] == 0) M[color[i]] = ++tt;
        color[i] = M[color[i]];
    }

    for(int i=1;i<n;i++){
        int a, b; scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    for(int i=0;i<nax;i++) BL[i] = i/320;

    for(int i=0;i<m;i++){
        int u, v; scanf("%d %d", &u, &v);
        if(st[u] > st[v]) swap(u, v);
        query q;
        q.id = i; q.u = u; q.v = v; q.z = lca(u, v);
        if(q.z == u){ // lca is u, then query from st[u] to st[v]
            q.l = st[u]; q.r = st[v];
        }else{ // query from en[u] to en[v], also include lca
            q.l = en[u]; q.r = st[v];
        }
        Q.push_back(q);
    }
    sort(Q.begin(), Q.end());
    compute();
    for(int i=0;i<m;i++) printf("%d\n", ans[i]);
    return 0;
}
```

source: https://ideone.com/6NVoPD

## TODO: 

Basics https://blog.anudeep2011.com/mos-algorithm/ and https://codeforces.com/blog/entry/83248 and https://codeforces.com/blog/entry/81716

With Update: https://codeforces.com/blog/entry/72690

MO's Algorithm on Trees https://codeforces.com/blog/entry/43230 and https://codeforces.com/blog/entry/68271

Checkout: https://discuss.codechef.com/t/mos-algorithm-uses/18482

Query Sqrt decomposition: https://codeforces.com/gym/100589/problem/A

Hilbert curve sorting - https://codeforces.com/blog/entry/61203

https://www.hackerearth.com/practice/notes/mos-algorithm/

https://h0rnet.hatenablog.com/entry/2016/03/03/CFR_Educational_2_E__Lomsat_gelral_(_Smaller_to_Larger_or_Time_stamp_+_Mo's_Algorithm_)

TODO: https://www.geeksforgeeks.org/sqrt-square-root-decomposition-set-2-lca-tree-osqrth-time/


Checkout: TODO: https://www.cnblogs.com/bibibi/p/8525527.html, also look at other pages on https://www.cnblogs.com/bibibi/p/?page=3

https://codeforces.com/blog/entry/92568