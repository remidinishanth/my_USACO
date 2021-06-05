## What is persistence?
* Keep all versions of DS.
* DS operations relative to specified version
* Update creates(& returns) new version (never modify a version)

Persistence is the ability to return to any of the former states of the data structure. If you see “rollbacks” in the problem statement - this is 99.9% a reference to persistence problem.

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

  We want to save all the versions of the segment tree. If we do naively we require `O(NQ)` memory. We can do better because every time we do a modify in segment tree, we change only `O(log N)` nodes. Example Say we modify element `[5:5]` in the segment tree with sum as combine operation.
  
  ![image](https://user-images.githubusercontent.com/19663316/120120417-acac8f80-c1ba-11eb-8203-451fd2ec3d81.png)


### Making segment tree persistent

* Fat node persistence
  * Add modification history to node, thus each node knows what it's value was at any previous point in time. 
  * We can use a vector(version_number, value) in every node of segment tree. Whenever we want to update a node, we push_back (current_version, value) into the vector of this node.
  * Querying a node will take `O(log m)` time if we have made `m` modifications. Since we’ve arranged the modifications by increasing time, you can find the right version by binary search on the modification history, using the timestamp as key. So query on segment tree takes `O(log^2 m)` time: one log for traversing the segment tree and the other for searching value in the fat node.

* Path copying persistence
  * Create a copy for every affected node and update necessary links to old / new nodes.
  ![image](https://user-images.githubusercontent.com/19663316/120120158-2e032280-c1b9-11eb-9b8d-d17a66e1b298.png)
  * From version's root since we can move to the node, query on segment tree costs just `O(log m)`.
  

<details>
 <summary> SPOJ KQUERY using Path Copying and Fat Node persistence </summary>
 
```cpp
// Author: Tanuj Khattar (Baba)
// Code for https://www.spoj.com/problems/KQUERY/
// Accepted via both Path Copying and Fat Node persistence.

// Range sum for [L, R)

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

source: Codechef Indian Programming Camp IPC 2020

</details>

### Adamant's implementation of DQUERY.

<details>
 
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

</details>

### Implementation and comparision with normal segment tree

One of the key things to note in persistence, and in persistent segment trees, is that there is no child-parent reference. All references and traversals are one-way: down the tree. Also, node numbers are dynamic and not the standard left-child = `2i`, right-child = `2i+1`.

#### Build

Segment Tree

```cpp
int n, t[4*MAXN];
int a[MAXN];

// call this function with parameters v = 1, tl = 0, tr = n-1
void build(int v = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr)
        t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}
```

Persistent Segment Tree

```cpp
int build(int tl, int tr){
    if (tl == tr) return newleaf(a[tl]); // construct as leaf

    int tm = (tl + tr) / 2;
    return newparent(build(tl, tm), build(tm+1, tr)); // construct as parent 
}

// Usage:
int root = build(0, n - 1);
```

Creating New nodes

```cpp
int l[SIZE], r[SIZE], st[SIZE], NODES = 0;
int newleaf(int value) {
    int p = ++NODES;
    l[p] = r[p] = 0; // null
    st[p] = value;
    return p;
}
int newparent(int lef, int rig) {
    int p = ++NODES;
    l[p] = lef;
    r[p] = rig;
    st[p] = st[lef] + st[rig]; // immediately update value from children
    return p;
}
```

#### Point Update

Segment tree

```cpp
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        t[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, new_val);
        else
            update(v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}
```

Persistent Segment Tree
```cpp
int update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) return newleaf(new_val); // or newleaf(st[v] + val) in addition
    
    int tm = (tl + tr) / 2;
    if (pos <= tm) return newparent(update(l[v], tl, tm, pos, new_val), r[v]);
    else return newparent(l[v], update(r[v], tm + 1, tr, pos, new_val));
}

// Usage:
int new_version_root = update(root, 0, n - 1, pos, val);
// Both roots are valid, you can query from both of them!
```

#### Range revert / Range copy

(Bonus) This is the ultimate version control technique one can pull off with regards to reverting a range back to a certain version. Imagine doing a range reset back to initial values - what a breakthrough! Although I find it rare to see problems that need range copy (e.g. [OAK](https://www.codechef.com/problems/OAK)), it’s one of those operations that can come in handy. Fortunately, for a persistent tree, this can easily be achieved a few lines of code:

```cpp
// revert range [a:b] of p
int rangecopy(int a, int b, int p, int revert, int L=0, int R=n-1) {
    if (b < L || R < a) return p; // keep version
    if (a <= L && R <= b) return revert; // reverted version
    return newparent(rangecopy(a, b, l[p], l[revert], L, M),
                     rangecopy(a, b, r[p], r[revert], M+1, R));
}

// Usage: (revert a range [a:b] back to an old version)
int reverted_root = rangecopy(a, b, root, old_version_root);
```

We pass in two roots: the current tree root and the old version root. We traverse both side-by-side, and replace only the relevant nodes during our traversal. This meek five-lined function is the foundation of efficient version-control, which is but one of the many operations you can do with a persistent segment tree.

REF: https://discuss.codechef.com/t/persistence-made-simple-tutorial/14915

#### Pointer based implementation

<details>
 <summary>CP algorithms</summary>

```cpp
struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}
```

source: https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-12

</details>

### Lazy propogation in Persistent Segment Tree

This is just a straightforward combination of both ideas.

If you know both concepts individually and you don’t see how to combine them, try thinking about it in the other direction: instead of adding lazy propagation to persistent segment trees, take a segment tree with lazy propagation and think about how to make it persistent.

Note the following:

* When using lazy propagation in segment trees, you just store some additional information in each node: data on the update that has been lazily postponed and thus still has to be applied to its subtree.
* In lazy segment trees each individual update still runs in logarithmic time, and thus in each individual update we only access (and possibly modify) at most a logarithmic number of nodes in the tree.
* When you have a segment tree and you add persistence using path copying, the asymptotic time complexity of your implementation remains the same, it’s only the space complexity that will increase. This is because in the non-persistent tree you did access all the nodes you also copied in the persistent version.

Now you just do both the lazy updates and path copying, and you are done.

That is, whenever you perform an update on a persistent lazy segment tree, do exactly the same thing you would do in the non-persistent version, but instead of overwriting data always create a new copy of the node you want to modify (and also of all nodes who are their ancestors in the tree, even if you aren’t modifying those). Then:

* As I explained above, doing this does not change the asymptotic time complexity of that particular update. (It does increase the space complexity by a logarithmic number of new nodes per query, but that’s usually still within all reasonable limits.)
* The new nodes you added make the structure persistent: the tree as seen from the new root you created at the end of the update does exactly correspond to the new state of the original tree, and you didn’t destroy any previous information.

Quora: Misof https://qr.ae/pGsx2K

## Problems

Most of the problems use this application of segment trees: Counting the number of zeros, searching for the k-th zero.

In this problem we want to find the number of zeros in a given range, and additionally find the index of the k-th zero using a second function. 

In the segment tree, we will store the number of zeros in each segment in `t[]`. It is pretty clear, how to implement the build, update and count_zero functions, we can simply use the ideas from the sum query problem. Now to find the the `k-th` zero we will descend the Segment Tree, starting at the root vertex, and moving each time to either the left or the right child, depending on which segment contains the k-th zero.

```cpp
int find_kth(int v, int tl, int tr, int k) {
    if (k > t[v])
        return -1;
    if (tl == tr)
        return tl;
    int tm = (tl + tr) / 2;
    if (t[v*2] >= k)
        return find_kth(v*2, tl, tm, k);
    else 
        return find_kth(v*2+1, tm+1, tr, k - t[v*2]);
}
```

In the implementation we can handle the special case, `a[]` containing less than k zeros, by returning `-1`.

With this idea, say our segment tree stores the frequency of numbers in the array in range of elements only from `[L, R]` then we can find the `k-th` order statistics.

#### KQUERY - SPOJ

Given a sequence of `n (1 ≤ n ≤ 30000)` numbers `1, a2, ..., an (1 ≤ ai ≤ 10^9)` and a number of `k` queries. A `k-query` is a triple `(i, j, k) (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 10^9)`. For each k-query `(i, j, k)`, you have to return the number of elements greater than `k` in the subsequence `ai, ai+1, ..., aj`.

<details>
 <summary> Offline solution using Segment Tree, O(log N) per query</summary>

Offline Approach: We find answer for queries in increasing order of `k`. Intially store `1` in all the indicies in the segment tree. For each value of `k`, remove indicies of elements which are less than `k` in the segment tree. The answer to any query will be number of `1`'s in the range from `i:j`

```cpp
const int nax = 3e4 + 10;

int st[4*nax];

void build(int v,int tl,int tr){
    if(tl==tr){
        st[v]=1;
        return;
    }
    int tm=tl+(tr-tl)/2;
    build(v*2,tl,tm);
    build(v*2+1,tm+1,tr);
    st[v]=st[v*2]+st[v*2+1];
}
 
int sum(int v,int tl,int tr,int l,int r){
    if(l>r)
        return 0;
    if(l==tl && r==tr)
        return st[v];
    int tm=tl+(tr-tl)/2;
    return sum(v*2,tl,tm,l,min(r,tm))+sum(v*2+1,tm+1,tr,max(l,tm+1),r);
}
 
void update(int v,int tl,int tr,int pos,int new_val){
    if(tl==tr){
        st[v]=new_val;
        return;
    }
    int tm=(tl+tr)/2;
    if(pos<=tm)
        update(v*2,tl,tm,pos,new_val);
    else
        update(v*2+1,tm+1,tr,pos,new_val);
    st[v]=st[v*2]+st[v*2+1];
}

int main(){
    int n, q;
    scanf("%d", &n);
    vector<pair<int,int>> V(n);
    for(int i=0;i<n;i++){
        scanf("%d", &V[i].F);
        V[i].S = i;
    }
    sort(V.begin(), V.end());

    scanf("%d", &q);
    vector<int> I(q), J(q), K(q), Ans(q);
    vector<pair<int,int>> Q;
    for(int x=0;x<q;x++){
        scanf("%d %d %d", &I[x], &J[x], &K[x]);
        Q.push_back({K[x], x});
    }
    // Sort queries based on K
    sort(Q.begin(), Q.end());

    // Initially fill all the values
    build(1, 0, n-1);

    int pos = 0;

    for(pair<int,int> X:Q){
        int k = X.first, idx = X.second; // index

        // remove elements less than k
        while(pos < n && V[pos].first <= k){
            update(1, 0, n-1, V[pos].second, 0);
            pos++;
        }

        Ans[idx] = sum(1, 0, n-1, --I[idx], --J[idx]);
    }

    for(int ans:Ans) printf("%d\n", ans);
    return 0;
}
```
</details> 

<details>
  <summary> Online solution using Merge Sort Tree, O(log^2 N) per query</summary>
 
Instead of storing aggregate values like sum, min or max, we can save the entire subarrays in each vertex of segment tree. The space used will be `O(NlogN)` because we have `N` elements and each element will appear in `O(logN)` nodes. If we store the elements in the sorted order, then we can it Merge sort tree, because it is similar to Merge sort algorithm.
```cpp
const int MAX_N = 3e4 + 10;

int a[MAX_N];
vector<int> t[4*MAX_N];
 
void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        // merges two sorted vectors and inserts at back of t[v]
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
              back_inserter(t[v]));
    }
}
 
int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        // number of elements > x in [tl, tr]
        return t[v].end() - upper_bound(t[v].begin(), t[v].end(), x);
    }
    int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm), x) + 
               query(v*2+1, tm+1, tr, max(l, tm+1), r, x);
}
 
int main() {
    int n, m;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    build(1,0,n-1);
    scanf("%d",&m);
    while(m--){
        int l, r, k;
        scanf("%d %d %d",&l,&r,&k);
        l--;r--;
        int ans = query(1,0,n-1,l,r,k);
        printf("%d\n",ans);
    }
    return 0;
}
```
</details> 

<details>
 <summary> Online solution using Persistent Segment Tree,  O(logN) per query</summary>
 
```cpp
const int nax = 30020;
const int lg = 20;

int NODES, MX;
int st[lg*nax], L[lg*nax], R[lg*nax], root[lg*nax];

int leaf(int value){
    int p = ++NODES;
    L[p] = R[p] = 0;
    st[p] = value;
    return p;
}

int parent(int l, int r){
    int p = ++NODES;
    L[p] = l;
    R[p] = r;
    st[p] = st[l] + st[r];
    return p;
}

int update(int v, int tl, int tr, int pos, int val){
    if(tl == tr) return leaf(st[v] + 1);

    int tm = (tl + tr)/2;
    if(pos <= tm) return parent(update(L[v], tl, tm, pos, val), R[v]);
    else return parent(L[v], update(R[v], tm+1, tr, pos, val));
}

int build(int tl, int tr){
    if(tl == tr) return leaf(0);
    int tm = (tl + tr)/2;
    return parent(build(tl, tm), build(tm+1, tr));
}

int query(int p, int tl, int tr, int l, int r){
    if(l > r) return 0;
    if(tl == l && tr == r) return st[p];
    int tm = (tl + tr)/2;
    return query(L[p], tl, tm, l, min(tm, r)) + query(R[p], tm+1, r, max(l, tm+1), r);
}

// numbers greater than k between i and j
int query(int l, int r, int k){
    return query(root[r], 0, MX, k, MX) - query(root[l-1], 0, MX, k, MX);
}

int main(){
    int n, q;
    scanf("%d", &n);
    // coordinate compression
    map<int,int> M;
    vi V(n), A(n);
    for(int i=0;i<n;i++) scanf("%d", &V[i]);
    for(int i=0;i<n;i++) A[i] = V[i];
    sort(A.begin(), A.end());
    int cnt = 0, inf = 1e9 + 5;
    for(int a:A){ cnt++; M[a] = cnt; }
    MX = M[A.back()] + 2;
    M[inf] = MX; // keep inf value

    // build persistent segment tree
    root[0] = build(0, MX);
    for(int i=1;i<=n;i++)
        root[i] = update(root[i-1], 0, MX, M[V[i-1]], 1);

    scanf("%d", &q);
    while(q--){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        int x = M.upper_bound(k) -> S;
        printf("%d\n", query(i, j, x));
    }
    return 0;
}
```
 
</details> 

#### MKTHNUM - SPOJ

Given an array `a[1 … N]` of different integer numbers and a set of queries. Each query consists of two integer numbers `L R K`, denoting that you’re asked to find the K-th order statistics on the segment `[L; R]` (What would be the k-th number in `a[i … j]` segment, if this segment was sorted?).

<details>
 <summary> Using Merge sort tree, O(log^3 N) per query </summary>

If we build merge sort tree on the elements of the array, then we can find the number of integers less than the given one in `O(log^2 N)` time by splitting the query segment into segtree segments and doing a binary search in each of them. Now for middle element we need to check whether the number of elements less than are equal to the required amount which would become `O(log^3 N)` per query.

```cpp
const int MAX_N = 1e5 + 10;

int a[MAX_N];
vector<int> t[4*MAX_N];
 
void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        // merges two sorted vectors and inserts at back of t[v]
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
              back_inserter(t[v]));
    }
}
 
int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        // number of elements <= x in [tl, tr]
        return upper_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
    }
    int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm), x) + 
               query(v*2+1, tm+1, tr, max(l, tm+1), r, x);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i=0;i<n;i++) scanf("%d", a+i);
    build(1, 0, n-1); // build merge sort tree
    sort(a, a+n);
    while(q--){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        i--;j--;
        // find small a[x] such that, a[x] >= atleast k elements in [L, R]
        // Do binary search searching min index of T: F, F, ..., F, T, T, ...
        int low = 0, high = n-1;
        while(low < high){
            int mid = (low + high)/2;
            if(query(1, 0, n-1, i, j, a[mid]) < k) low = mid + 1;
            else high = mid;
        }
        printf("%d\n", a[low]);
    }
	return 0;
}
```

Iterative version

```cpp
const int MAX_N = 1e5 + 10;

int n, q;
int a[MAX_N];
vector<int> t[4*MAX_N];
 
void build() {
    for(int i=0;i<n;i++) t[i+n] = vector<int>(1, a[i]);
    for(int i=n-1;i>0;i--) 
        merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(),
              back_inserter(t[i]));
}
 
int query(int l, int r, int x) { // [l, r)
    int res = 0;
    for(l+=n, r+=n; l<r; l>>=1, r>>=1){
        if(l&1){
            res += upper_bound(t[l].begin(), t[l].end(), x) - t[l].begin();
            l++;
        }
        if(r&1){
            r--;
            res += upper_bound(t[r].begin(), t[r].end(), x) - t[r].begin();
        }
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i=0;i<n;i++) scanf("%d", a+i);
    build(); // build merge sort tree
    sort(a, a+n);
    while(q--){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        i--; // query for [i, j)
        // find small a[x] such that, a[x] >= atleast k elements in [L, R]
        // Do binary search searching min i for true F, F, ..., F, T, T, ...
        int low = 0, high = n-1;
        while(low < high){
            int mid = (low + high)/2;
            if(query(i, j, a[mid]) < k) low = mid + 1;
            else high = mid;
        }
        printf("%d\n", a[low]);
    }
	return 0;
}
```
</details> 

<details>
  <summary> Using Merge sort tree, O(log^2 N) per query </summary>
	
For `O(log^2 N)` per query, we can sort the integers and save their positions in the merge sort tree and then apply a trick we have in finding the K-th order statistics in the segtree with nonnegative integers. Since the numbers are sorted and we store the positions in the segment tree, all the numbers in positions of the left half are strictly less than numbers at positions in right half. So now we need to check whether the number of positions in the left subtree from `[L, R]` are less than equal to `K`(this can be calculated by two binary searches query(R) - query(L-1)), if so then our answer is in the left half, if not we go to the right child of segment tree. The time complexity will be `O(log^2 N)` because depth of segment tree is `O(log N)` and we need two binary searches for each node.

![image](https://user-images.githubusercontent.com/19663316/120347119-a1bc4100-c319-11eb-867f-38fa793e7465.png)

Solution Idea:
  - At first take input and store the input in a pair array where first element of i_th pair is the value a_i  and second
     element of i_th pair is i.
  - Sort the pair array with with ascending order of a_i
  - Build a merge sort tree using the second element of each pair of sorted pair array.
  - Now for each query i,j,k at first check how many number in range i to j inclusive are present in left subtree of current
    node in merge sort tree. Let the value is x. So if x<=k then it's sure that the answer is in the left subtree. So we will
    go to left subtree of current node with k. Otherwise we will go to right subtree of current node with k-x;
  - In this manner when we reach to a leaf node we can say that this node contains the index of our answer.

```cpp
const int MAX_N = 1e5 + 10;

int a[MAX_N];
vector<int> t[4*MAX_N];
 
void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        // merges two sorted vectors and inserts at back of t[v]
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
              back_inserter(t[v]));
    }
}

int query(int v, int tl, int tr, int l, int r, int k){
    if(tl == tr) return a[tl];
    // number of positions <= index r in left subtree
    int val = upper_bound(t[2*v].begin(), t[2*v].end(), r) - t[v*2].begin();
    // remove positions <= l-1
    val -= upper_bound(t[2*v].begin(), t[2*v].end(), l-1) - t[v*2].begin();
    int tm = (tl+tr)/2;
    if(val >= k) return query(v*2, tl, tm, l, r, k);
    else return query(v*2+1, tm+1, tr, l, r, k-val);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pair<int, int>> V(n);
    vector<int> A(n);
    for(int i=0;i<n;i++){
        scanf("%d", &V[i].first);
        V[i].second = i;
        A[i] = V[i].first;
    }
    sort(V.begin(), V.end());
    for(int i=0;i<n;i++) a[i] = V[i].second;
    build(1, 0, n-1);

    while(m--){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        i--;j--;
        int idx = query(1, 0, n-1, i, j, k);
        printf("%d\n", A[idx]);
    }
	return 0;
}
```
</details>

<details>
  <summary>Using Persistent Segment Tree, O(logN) per query </summary>
	
Let's our numbers are in range [1, N], if not we can re-index(use coordindate compression) the numbers, the size will not exceed N. Say we build a segment tree on range `[i:j]` using the frequence of numbers. To find the `k-th` element, we will descend the Segment Tree, starting at the root vertex, and moving each time to either the left or the right child, depending on which segment contains `k-th` element. So if we have segment tree for the range `[i, j]` then we can answer the query in `O(log N)` time per query.

If we build persistent segment trees, incrementing frequency[i] for every i. Then value of `node[i, j]` can be computed by using `node[1, j] - node[1, i-1]`, traversing the j-th version tree and (i-1)-th version tree simultaneously.

```cpp
const int nax = 1e5 + 10;
const int lg = 21;

int st[lg*nax], L[lg*nax], R[lg*nax], root[lg*nax];
int node;

int leaf(int val){
    int i = ++node;
    st[i] = val;
    L[i] = R[i] = 0; // null
    return i;
}

int parent(int l, int r){
    int i = ++node;
    L[i] = l; R[i] = r;
    st[i] = st[l] + st[r];
    return i;
}

int build(int l, int r){
    if(l == r) return leaf(0);
    int m = (l+r)/2;
    return parent(build(l, m), build(m+1, r));
}

int update(int v, int tl, int tr, int pos){
    if(tl == tr) return leaf(st[v] + 1); // increment the value
    int tm = (tl + tr)/2;
    if(pos <= tm) return parent(update(L[v], tl, tm, pos), R[v]);
    else return parent(L[v], update(R[v], tm+1, tr, pos));
}

// node2 is r, node1 is l-1
int query(int node1, int node2, int tl, int tr, int k){
    if(tl == tr) return tl;
    int tm = (tl + tr)/2;
    int val = st[L[node2]] - st[L[node1]];
    if(k <= val)
        return query(L[node1], L[node2], tl, tm, k);
    else
        return query(R[node1], R[node2], tm+1, tr, k - val);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> V(n);

    // Coordinate compression or Re-indexing
    map<int,int> M, N;
    for(int i=0;i<n;i++){
        scanf("%d", &V[i]);
        M[V[i]] = 0;
    }
    int pos = 1;
    for(pair<int,int> x:M) M[x.first] = pos++;
    for(pair<int,int> x:M) N[x.second] = x.first; // pos to original value

    // build persistent segment tree
    root[0] = build(0, n-1);
    for(int i=1;i<=n;i++){
        root[i] = update(root[i-1], 1, n, M[V[i-1]]);
    }

    while(m--){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        pos = query(root[i-1], root[j], 1, n, k);
        printf("%d\n", N[pos]);
    }
	return 0;
}
```
</details>

#### COT - SPOJ

Given a Tree, We have to answer Q queries of the form : Find `k-th` minimum weight on the path from node `u` to node `v`.

<details>
	<summary>Persistent Segment Tree, O(log N) per query </summary>

Note that the technique used in MKTHNUM of finding k-th order statistics will also work for trees.

Suppose that we root the tree at x, then we can find the k-th order statistic by constructing persistent segment tree on each node - using the frequency of elements from root to u. Then we can find whether answer is present in left subtree by using `f(u, x) + f(v, x) – f(lca(u, v), x) – f(parent(lca(u, v)), x) ≤ k`

```cpp
#include <bits/stdc++.h>
using namespace std;

const int nax = 1e5 + 10;
const int LG = 18;

int node = 0, n;
vector<int> V(nax); // value on node
vector<int> Adj[nax];
int depth[nax], par[nax][LG];
int st[21*nax], L[21*nax], R[21*nax], root[21*nax];

void dfs(int u, int p){
    depth[u] = depth[p] + 1;
    par[u][0] = p;
    for(int i=0; par[u][i]!=0; i++){
        par[u][i+1] = par[par[u][i]][i];
    }

    for(int v:Adj[u]) if(v != p) dfs(v, u);
}

int up(int v, int dh){
    for(int k=LG-1;k>=0;k--){
        if(dh < (1<<k)) continue;
        v = par[v][k];
        dh -= 1 << k;
    }
    return v;
}

int LCA(int u, int v){
    if(depth[v] > depth[u]) swap(u, v);
    u = up(u, depth[u] - depth[v]);
    if(v==u) return v;
    for(int k=LG-1;k>=0;k--){
        if(par[v][k] != par[u][k]){
            v = par[v][k];
            u = par[u][k];
        }
    }
    return par[v][0];
}

int leaf(int val){
    int v = ++node;
    L[v] = R[v] = 0; // null
    st[v] = val;
    return v;
}

int parent(int l, int r){
    int v = ++node;
    L[v] = l; R[v] = r;
    st[v] = st[l] + st[r];
    return v;
}

int build(int l, int r){
    if(l == r) return leaf(0);
    int m = (l+r)/2;
    return parent(build(l, m), build(m+1, r));
}

int update(int v, int l, int r, int pos, int val = 1){
    if(l == r){
        return leaf(st[v] + 1);
    }
    int m = (l+r)/2;
    if(pos <= m) return parent(update(L[v], l, m, pos, val), R[v]);
    else return parent(L[v], update(R[v], m+1, r, pos, val));
}

// build persistent segment tree
void seg_dfs(int u, int p){
    root[u] = update(root[p], 1, n, V[u]); // increase counter of value at u
    for(int v:Adj[u]) if(v != p) seg_dfs(v, u);
}

int query(int u, int v, int lca, int plca, int l, int r, int k){
    if(l==r) return l;
    // number of children in left subchild
    int t = st[L[u]] + st[L[v]] - st[L[lca]] - st[L[plca]];
    int m = (l+r)/2;
    if(k <= t) return query(L[u], L[v], L[lca], L[plca], l, m, k);
    else return query(R[u], R[v], R[lca], R[plca], m+1, r, k-t);
}

int main() {
    int m;
    scanf("%d %d", &n, &m);

    // coordinate compression
    map<int,int> M, rM; // re-index
    for(int i=1;i<=n;i++){ scanf("%d", &V[i]); M[V[i]] = 1; }
    int id = 1;
    for(auto &it: M){
        it.second = id++;
        rM[it.second] = it.first;
    }
    for(int i=1;i<=n;i++) V[i] = M[V[i]];

    for(int i=1;i<n;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }
    dfs(1, 0); // root the tree at 1

    // build persistent segment tree
    root[0] = build(1, n);
    seg_dfs(1, 0);

    while(m--){
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        int lca = LCA(u, v), plca = par[lca][0];
        u = root[u], v = root[v], lca = root[lca], plca = root[plca];
        int ans = query(u, v, lca, plca, 1, n, k);
        printf("%d\n", rM[ans]);
    }
	return 0;
}
```
</details>

#### SORTING - CodeChef

Alice uses the following pseudocode when she needs to sort a permutation of N positive integers:

```pascal
procedure Sort(list A) defined as:
   list less, greater
   if length(A) <= 1 then return A
   pivot := A(length(A)+1) / 2
   for i := 1 to length(A) do:
      Increment(comparison_count)
      if Ai < pivot then append Ai to less else if Ai > pivot append Ai to greater
      end if
   end for
   return concatenate(Sort(less), pivot, Sort(greater) )
```

And now we are interested in the number of comparisons that will be made during the sorting of the given permutation of integers A with the provided code. So, we ask you to find the value of the variable comparison_count after such a sorting.

source: https://discuss.codechef.com/t/sorting-editorial/3048

<details>
  <summary> Using Persistent Segment Tree</summary>

Observation: every time the list `A[]` is given to the sorting function, `A[]` always consists of the permutation of the numbers in some range `[L; R]`. Initially, it’s `[1; N]`, then it’s `[1; pivot-1]` and `[pivot+1; N]` and so on.

Another observation: the relative order of numbers in every possible list A[] given to the sorting will not change.

So, we just have to calculate the middle number by position (i.e. `(R-L+2)/2-th` number) among all the numbers with values in the range `[L; R]` in order to get pivot.

For this, we generally use the concept of the “rank-query”. The rank query basically asks, what is the k-th least element in a given set, for a queried k. If the set contained the positions of the elements in `[L; R]`, then the `(R-L+2)/2-th` element is what we are looking for.

This is generally done by using a `‘1’` at the value of the element in the set, and then the k-th element is got by just asking what is the first position to have `k 1’s` to the left of it (inclusive). This data structure is generally implemented by a BIT or a segment tree, but in this problem we will see how using a segment tree is of use to us.

Lets define `Pos(x)` = position in original array where element x is,

	Set(a, b) = the set {Pos(a), Pos(a+1), …, Pos(b)}.
	
We are generally interested in `Set(L, R)` and finding the `(R-L+2)/2-th` element, but notice: `Set(1, a-1)` is a subset of `Set(1, b)` and `Set(a, b) = Set(1, b) \ Set(1, a-1)`

Thus, if just define `S(x) = Set(1, x)`, we would get that given `(L, R)`, we need to find the `(R-L+2)/2-th` element in `S(b) \ S(a-1)`.

Using our concept of ones to denote positions, set difference where one set is subset of the other is now just finding the first position x where `(number of 1’s to the left of x in S) - (number of 1’s to the left of x in S(L-1)) = (R-L+2)/2` !!

Notice now, that once we have N+1 segment trees (each segment tree corresponds to a set S(x)), we would be done, because traversal for a given query (L, R, k) is merely : go to left child with (L, R, k) if number of ones in left child® - number of ones in left child(L) <= k, else go to right child with query (L, R, k - #ones).

Pseudo Code

```python
Root[0] = Empty segment Tree
for i in 1 to N
	Root[i] = Root[i-1].insert(Pos[i])
Answer = f(1, N)

f(L, R)
	if(R <= L) return 0
	x = getKth(Root[L-1], Root[R], (R-L+2)/2)
	pivot = A[x]
	return (R-L+1) + f(L, pivot-1) + f(pivot+1, R)

getKth(Lnode, Rnode, k)
	if(Lnode is a single position)
		return Lnode's position
	ones = Rnode.leftchild.ones - Lnode.leftchild.ones
	if(ones <= k)
		return getKth(Lnode.leftchild, Rnode.leftchild, k)
	else
		return getKth(Lnode.rightchild, Rnode.rightchild, k - ones)
```

Since N is as large as 5 * 10^5, the recursion stack would be too large, to overcome this issue we convert the implementation to a non-recursive manner.

In fact, since the [L; R] intervals being queried are independent of each other (subproblems don’t even overlap), we need not worry about in which order we query the intervals, just that we need to query all the relevant ones. Thus, we can modify our DFS-like recursive implementation into a BFS-like version using queues. 

```cpp
// Problem SORTING. Fastest setter's 100-point solution
// O(logN)-per-query. Overall complexity: O(N log N)

#include <stdio.h>

#define maxn 1111111

struct node{ // node of the persistent segment tree
	int L,R,sum; // left and right bounds and the sum in the segment
	node*hL,*hR; // left and right sons
	node(){}
	node(int L,int R):L(L),R(R),sum(0){}
}all[20000000];
int tot;

typedef node * pnode;

pnode root[maxn];
int a[maxn],pos[maxn],n,i;
long long ans;

pnode create(int L,int R){ // create persistent segment tree
	pnode ret=&all[tot++];
	ret->L=L,ret->R=R;
	ret->hL=ret->hR=NULL;
	if(L<R){
		ret->hL=create(L,(L+R)/2); // create left son
		ret->hR=create((L+R)/2+1,R); // create right son
	}
	return ret;
}

pnode change(pnode t,int j){ //	create a new version with the j-th number equal to one and all other numbers equal to the numbers in the version t
	pnode ret=&all[tot++];
	ret->L=t->L;ret->R=t->R;
	ret->hL=t->hL,ret->hR=t->hR;
	ret->sum=t->sum+1; // increase the amount of ones in the semgment
	if(t->L<t->R)
		if(t->hL->R>=j)ret->hL=change(ret->hL,j);else ret->hR=change(ret->hR,j); // standard thing
	return ret;
}

int getkth(pnode low,pnode high,int key){ // get the k-th number
	if(low->L==low->R)return low->L; // if the size of the range equals to one the the number is found
	if(high->hL->sum-low->hL->sum>=key) 
		return getkth(low->hL,high->hL,key);else // if the amount of one in the left son is enough, go to the left son
		return getkth(low->hR,high->hR,key-(high->hL->sum-low->hL->sum)); // otherwise go to the right son and subtract the amount of numbers in the left son
		
}

int qL[2222222],qR[2222222],q1,q2;

void solve(int L,int R){ // simulate the QuickSort
	qL[q1]=L,qR[q1]=R;++q1;q2=0;
	while(q1!=q2){ // BFS is used here
		L=qL[q2];R=qR[q2];
		if(R-L+1>=2){
			int median=a[getkth(root[L-1],root[R],(R-L+2)/2)]; // get the pivot in O(logN) time
			ans+=R-L+1;
			qL[q1]=L,qR[q1]=median-1;++q1; // add [L; pivot)
			qL[q1]=median+1,qR[q1]=R;++q1; // add (pivot; R]
		}
		++q2;
	}
}

int main (int argc, char * const argv[]) {
	scanf("%d",&n); // size of the permutation
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	root[0]=create(1,n); // create the first version
	for(i=1;i<=n;i++)root[i]=change(root[i-1],pos[i]); // create additional N versions
	solve(1,n);
	printf("%lld\n",ans);
    return 0;
}
```
</details>	

<details>
	<summary> O(log^2 N) per query</summary>
	
```cpp
// Problem SORTING, another setter's 100-point solution
// O(log^2N)-per-query, O(N log^2 N) overall complexity
// Merge sort tree is used

#include <cstdio>

#define maxn 500010

long long ret;
int sr[20][maxn],a[maxn],n,i;
struct node{
	int l,r;
}tree[maxn*4];

void init(int lv,int pos,int l,int r){ // build the merge sort tree
	tree[pos].l=l,tree[pos].r=r;
	if(l<r){ 
		int mid=(l+r)/2; // like in the usual segment tree
		init(lv+1,pos+pos,l,mid); // build the left son
		init(lv+1,pos+pos+1,mid+1,r); // build the right son
		int j,hl=l,hr=mid+1;
		for(j=l;j<=r;j++)if(hr>r||(hl<=mid&&sr[lv+1][hl]<sr[lv+1][hr]))sr[lv][j]=sr[lv+1][hl++];else sr[lv][j]=sr[lv+1][hr++]; // do the MergeSort
	}else sr[lv][l]=a[l];
}

int getbs(int lv,int pL,int pR,int L,int R){ // calculate amount of numbers in the range [L; R] on the sorted segment [lv][pL..pR]
	if(sr[lv][pL]>R)return 0; // if the smallest number is too big
	if(sr[lv][pR]<L)return 0; // if the biggest number is too small
	int l=pL,r=pR,mid;
	while(l<r){ // find the first number in the segment
		mid=(l+r)/2;
		if(sr[lv][mid]<L)l=mid+1;else r=mid;
	}
	if(sr[lv][l]>R)return 0; // if there're no numbers in the segment [L; R]
	int rt=l;
	l=pL,r=pR;
	while(l<r){ // find the last number in the segment
		mid=(l+r+1)/2;
		if(sr[lv][mid]>R)r=mid-1;else l=mid;
	}
	if(l<rt)return 0; // if there're no numbers in the segment [L; R]
	return l-rt+1; // return the amount of numbers
}

int query(int lv,int pos,int L,int R,int kth){ // get the k-th number in the range [L; R] in the segment
	if(tree[pos].l==tree[pos].r)return tree[pos].l; // if we have detected the number, return it
	int lf=getbs(lv+1,tree[pos+pos].l,tree[pos+pos].r,L,R); // the amount of the numbers in the range [L; R] in the left son
	if(lf>=kth)return query(lv+1,pos+pos,L,R,kth);else return query(lv+1,pos+pos+1,L,R,kth-lf); // if the amount in the left son is enough, we go to the left son. otherwise we go to the right son
}

int q1,q2,qL[maxn*4],qR[maxn*4];

void solve(int l,int r){ // simulate the sorting
	qL[q1]=l,qR[q1]=r;q1=1;q2=0;
	while(q1!=q2){ // here, we use BFS instead of the DFS
		l=qL[q2];r=qR[q2];++q2;
		ret+=r-l+1;
		int pivot=a[query(0,1,l,r,(r-l+2)/2)]; // calculating the pivot in O(log^2N)
		// now, split the segment into two small segments: 
		if(l<pivot-1){ // [L; pivot)
			qL[q1]=l;
			qR[q1]=pivot-1;
			++q1;
		}
		if(pivot+1<r){ // (pivot; R]
			qL[q1]=pivot+1;
			qR[q1]=r;
			++q1;
		}
	}
}

int main(){
	scanf("%d",&n); // size of the permutation
	for(i=1;i<=n;i++)scanf("%d",&a[i]); // the permutation itself
	init(0,1,1,n); // building the segment tree
	solve(1,n); 
	printf("%lld\n",ret);
	return 0;
}
```
</details>

<details>
	<summary> Without using a persistent data structures.</summary>

By alex_2oo8

We will maintain the same segment tree like in above solution, but not persistent. When we will sort a range [L,R] we will have a segment tree for the Set(L,R).
So, the pseudocode looks like this:

```python
sort(L, R, Root):
    if (R - L + 1 <= 1) return 0;
    ans = R - L + 1;
    pivot = getKth(Root, (R-L+2)/2);
    if (pivot - L < R - pivot)
        for i = L to pivot
            Root.remove(Pos[i]);
        ans += sort(pivot + 1, R, Root);
        Root = Empty Segment Tree
        for i = L to pivot - 1
            Root.add(Pos[i]);
        ans += sort(L, pivot - 1, Root);
    else
        for i = pivot to R
            Root.remove(Pos[i]);
        ans += sort(L, pivot - 1, Root);
        Root = Empty Segment Tree
        for i = pivot + 1 to R
            Root.add(Pos[i]);
        ans += sort(pivot + 1, R, Root);
    return ans;
```    

submission: https://www.codechef.com/viewsolution/2576301

```pascal
program SORTING;

type
  tTreeRec = record
    l, r, lSon, rSon, sum, x: longint;
  end;

  tRec = record
    l, r: longint;
  end;

var
  n, runLatterCnt: longint;
  w: array[1..500000] of longint;
  ans: int64;
  t: array[0..10000000] of tTreeRec;
  tw: longint = 0;
  runLatter: array[1..1000000] of tRec;
  runNow: tRec;

// new node in segment tree
function new(l, r: longint): longint;
begin
  Inc(tw);
  t[tw].l := l;
  t[tw].r := r;
  t[tw].lSon := 0;
  t[tw].rSon := 0;
  t[tw].sum := 0;

  exit(tw);
end;

// update in segment tree
procedure add(s, x, d, val: longint);
var
  m: longint;
begin
  Inc(t[s].sum, d);

  if (t[s].l = t[s].r) then // leaf node
  begin
    t[s].x := val;
    exit();
  end;

  m := (t[s].l + t[s].r) div 2;
  if (x <= m) then
  begin
    if (t[s].lSon = 0) then
      t[s].lSon := new(t[s].l, m);
    add(t[s].lSon, x, d, val);
  end
  else
  begin
    if (t[s].rSon = 0) then
      t[s].rSon := new(m + 1, t[s].r);
    add(t[s].rSon, x, d, val);
  end;
end;

// query in segment tree
function getKth(s, k: longint): longint;
begin
  if (t[s].l = t[s].r) then
    exit(t[s].x);

  if (t[s].lSon = 0) or (t[t[s].lSon].sum < k) then
    exit(getKth(t[s].rSon, k - t[t[s].lSon].sum))
  else
    exit(getKth(t[s].lSon, k));
end;

var
  i, a, sz, pivot, l, r: longint;

begin
  readln(n);
  new(1, n);
  for i := 1 to n do
  begin
    read(a);
    add(1, i, +1, a);
    w[a] := i;
  end;

  ans := 0;
  runLatterCnt := 0;
  runNow.l := 1;
  runNow.r := n;

  while (runNow.l <> -1) or (runLatterCnt > 0) do
  begin
    if (runNow.l = -1) then
    begin
      runNow := runLatter[runLatterCnt];
      Dec(runLatterCnt);

      tw := 0;
      new(1, n);
      for i := runNow.l to runNow.r do
        add(1, w[i], +1, i);
    end;

    l := runNow.l;
    r := runNow.r;

    sz := r - l + 1;

    if (sz <= 1) then
    begin
      runNow.l := -1;
      continue;
    end;

    Inc(ans, sz);
    pivot := getKth(1, (sz + 1) div 2);
    add(1, w[pivot], -1, 0);
    if (pivot - l < r - pivot) then
    begin
      for i := l to pivot - 1 do
        add(1, w[i], -1, 0);

      runNow.l := pivot + 1;
      runNow.r := r;

      Inc(runLatterCnt);
      runLatter[runLatterCnt].l := l;
      runLatter[runLatterCnt].r := pivot - 1;
    end
    else
    begin
      for i := pivot + 1 to r do
        add(1, w[i], -1, 0);

      runNow.l := l;
      runNow.r := pivot - 1;

      Inc(runLatterCnt);
      runLatter[runLatterCnt].l := pivot + 1;
      runLatter[runLatterCnt].r := r;
    end;
  end;

  writeln(ans);
end.
```

The worst case is when the pivot is (R-L+2)/2 all the time and the complexity is O(N log^2 N).

Why is worst case `O(N log^2 N)`:

I can prove, that each position will be inserted and removed at most O(log N) times. At the very beginning all positions are in range of size N (Range [1,N]), if we remove some position - it means that at the next step it will be in part of size at most N/2, after second removing - N/4, after Kth - N/(2^K), so, K <= log N.

When the pivot is in the middle all the time, this algorithm will perform exactly NlogN insertions and removing from the Segment Tree, so, it is the worst case.

Here we need to implement dynamic Segment Tree (we will create nodes only when we need them), i.e. this line just creates a single node.

</details>

#### QUERY - Codechef

You are given a tree of N vertices. Each vertex is initialized to value 0. Further you are given 3 kinds of operations:
* `c X Y A B` - the “Change” operation: Along the path from X to Y increment the values by A, A+B, A+2B, etc.
* `q X Y` - the “Query” operation: Find the sum of values along the path from X to Y
* `l X` - the “Rollback” operation: Return the tree to the state it was after the X’th Change query.

The input is given in a manner that we require an online solution for the problem.

source: https://www.codechef.com/problems/QUERY

<details>
	<summary> Offline solution </summary>
	
The requirement of lastans in the input format ensured that offline solutions would not work here. There is a offline solution to the problem which does not use persistence.

Imagine versions as nodes of a graph. Now, when you have an update operation, that amounts to creating a new version-child of the current node. If you had no rollbacks, then your graph would be a chain. Now that there are rollbacks, you may branch out from an earlier version. In this case you have a tree.

Note that, if you went from a version to its child using the operation X Y A B, then you can go back from the child to its parent using the operation X Y -A -B. Thus, first you build this version-tree, and then you traverse it using a DFS. When you are in a version-node n, then solve all queries that pertain to that node before moving on.
</details>	

<details>
	<summary> Using HLD and Persistent Segment Trees </summary>

The solution describes using segment trees, heavy light decomposition, and persistence over a tree. To avoid confusion in terminology, “node” refers to the data structure component (segment tree or persistence), whereas “vertex” refers to the vertex of the Tree given in the Problem.

We develop the solution by analyzing the problem under various special cases, as follows:

1. The Tree is a chain, there are no rollback queries
2. You have a chain, but there are rollback queries
3. You have a tree, there are no rollback queries
4. Overall solution.

**Tree is a chain, there are no rollbacks**

Here, we have a segment - lets use a segment tree. Now, we wish to update the values of vertices from X to Y. Suppose we have two such operations on the same vertices: X Y A B followed by X Y C D. Then the values will be (going along the path from X to Y)

	A, A+B, A+2B, ...
	
after the first operation, and

	A + C, A+B + C+D, A+2B + C+2D, ...
	
after the second operation.

Clearly, this is equivalent to the single operation X Y A+C B+D.

Thus, let us store in our segment tree the pairs (A,B) associated with the operation. Now, when we get to a segtree-node which is completely contained in our X-Y path, we just update the A, B value of that node.

Further, while querying, we would like to return an answer when our query-node is completely contained in our required segment. Thus, we also need to store a field “sum” in our segtree which basically stores the sum of the left subtree + right subtree.

Pseduo Code

```cpp
update(node cur, 	//current node in segtree we wish to update
	int X, 		//X-val of update-segment wrt current node
	int Y,		//Y-val of update-segment wrt current node
	int A,		//A-val of operation
	int B)		//B-val of operation
	if(cur.left == X && cur.right == Y)
		cur.A += A, cur.B += B;
		return;
	mid = (cur.left + cur.right)/2;
	if(X <= min(Y, mid))
		update(ret.left, X, min(Y, mid), A, B)
	if(max(X, mid+1) <= Y)
		update(ret.right, max(X, mid+1), Y, A + max(0, mid-X+1) * B, B);
	cur.sum = findSum(cur.left) + findSum(cur.right);

findSum(node cur)
	n = cur.right - cur.left + 1;	//#elements in node
	a = cur.A;
	b = cur.B;
	return cur.sum + calc(a, b, n);

calc(a, b, n)	//returns sum of a, a+b, a+2b, a+(n-1)b
	return (n * (2 * a + (n-1) * b))/2;

query(node cur, int X, int Y, int accumA, int accumB)
// similar to update: here accumA and accumB store the sum of A-values and B-values along the path from root to the node, as this is required in finding the overall value of a node at a depth.
	if(cur.left == X && cur.right == Y)
		return cur.sum + calc(accumA, accumB, (Y-X)+1);
	ret = 0
	mid = (X+Y)/2;
	if (X <= min(mid, Y))
		ret += query(cur.left, X, min(Y, mid), accumA+cur.left.A, accumB + cur.left.B)
	if (max(mid+1, X) <= Y)
		ret += query(cur.right, max(mid+1, X), Y, accumA + cur.right.A + accumB * (size-of-left-subtree), accumB + cur.right.B)
	return ret;
```

This can be found in Setter’s Solution (lines 24 - 54), if you ignore the persistence that is introduced in the modify() function.

**You have a chain, but there are rollback queries**

Use Persistent Segment Trees, We can imagine our segment tree as a binary tree with links to left and right children. In this setting, what would a modification to the tree look like?

It would just be a path starting from the root upto a particular node! What we need to do here, is clone just the path from the root to the node, and associate the new root with the new version. Here, when the tree has N nodes, a path of length atmost log(N) is being cloned. If you compare with the linked list example, over there, in the worst case we could clone a path of size O(N). Thus, there is a huge improvement in the case of the segment tree.

So, if we were to have a global array of Version-roots, and perform our updation of the tree with cloning, we get exactly what we desire. Refer to Setter’s code : lines 42 - 62 for the description of this.

**You have a tree, and no rollback queries**

➜ Heavy-light Decomposition of Tree (HLDoT)

The heavy-light decomposition is used to break up a Tree into s set of disjoint paths, with certain useful properties. First, root the tree. Then, for each vertex x, we find the child of x having the largest subtree. Lets call that vertex y. Then the edge x-y is a heavy edge, and all other x-child_vertex edges are light edges.

The most important property of this is, from any vertex x, the path from x to the root goes through at most logN different light-edges. This is because, on this path, whenever you take a light edge, you are atleast doubling the size of the subtree rooted at the new vertex. Hence you cannot perform this “doubling” effect more than `logN` times.

If you can solve the problem for a chain using a segment tree, then there is a very good chance that you can solve the problem for a tree using HLDoT. Indeed, if you make segment trees over the heavy edges, then the answer for your path X-Y can be broken up into two paths from X to LCA(X, Y) and from Y to LCA(X, Y). Then, using that you make only logN shifts from one heavy-chain to another, you are actually making only log(N) segment-tree queries.

➜ Applying HLDoT here

Let us perform Heavy Light Decomposition of the tree here. We make chains consisting only of heavy edges. We also need to find LCA efficiently. This can be done in O(N log N) time by storing information up[x][i] = the ancestor of x which is at a height of 2^i above x. Clearly, up[x][i] = up[up[x][i-1]][i-1] (take a 2^(i-1) upward jump from the 2^(i-1)'th ancestor of x). Then,

```cpp
LCA(x, y):
if(x is ancestor of y) return x;
for(i = logN; i >= 0; i--) 
	if (up[x][i] is not an ancestor of y) x = up[x][i];
return up[x][0];
```

Now, given an update query, from X to Y, first find L = LCA(X, Y). Then, update path from X to L and from L to Y.

This is accomplished in the Setter’s code lines 195-220. Pseudocode follows. Let chain[vertex] = an identifier for the particular segment tree’s root that we require.

```cpp

change(L, x, y, a, b):	// Perform the operation X Y A B, where L = LCA(X, Y)
dist = depth[x] + depth[y] - 2depth[L] + 1
lift(x, L, a, b);	// update path x to L with parameters (a, b)
if(y is not L)
	find pL = child of L that is ancestor of y
	//update path from y to pL with parameters (a + b * (dist-1), -b)
	lift(y, pL, a + b * (dist-1), -b)

lift(low, high, a, b):
if(chain[low] = chain[high])
	Modify the chain[low]'th segtree along the path from low to high as required
else
	Let H = Head of the chain[low]'th segtree (i.e. the one nearest to the root)
	Let n = number of nodes on path from low to H
	Modify the chain[low]'th segtree along the path from low to its Head as required
	lift (parent of Head, high, a + (n-1) * b, b)
```

**Overall Solution**

The overall solution merges persistence with Heavy Light Decomposition. At the high level, it goes as follows:

1. Perform heavy-light decomposition to give you information regarding ancestry-relation between nodes, LCA, depth, and mapping vertices to chain-numbers
2. For a change operation between X and Y, for every chain along the path from X to Y, perform a persistent-change to the corresponding segment trees. For each segment tree, you have an array of the root-nodes that map versions to roots.
3. For every query operation between X and Y, do the same as step 2, except you need to accumulate queries over various segment trees, and don’t perform any modifications
4. For every rollback operation, set a global variable (that denotes your version number) to the required version.

**Complexity Analysis:**

Memory: Each update operation on a segment tree takes atmost O(logN) memory. Each update operation on the tree affects atmost O(logN) chains. Hence, memory complexity is O(N log^2 N).

Time: Updates on each segment tree take O(logN) time. There are atmost O(logN) segment trees to update on an Update Operation. Hence, O(log^2N) per update operation.
Queries behave similarly: O(log^2N) for queries as well.
Rollback operation: O(1) time to update global version-number.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define maxn 220000 // maximal number of nodes

struct node{ // node of the first persistent tree
	int add2; // add2 is the sum of all Bs, added to this node, according to the statement, B<=1000, M<=100000, so int is ok
	long long add1,sum; // sum of all As for the node, sum in the subtree
	node*l,*r; // left and right sons
};

node*init(int l,int r){ // creates the progressions persistent tree like an ordinary segtree
	node*ret=new node;
	ret->add1=ret->add2=ret->sum=0;
	if(l<r){
		ret->l=init(l,(l+r)/2);
		ret->r=init((l+r)/2+1,r);
	}
	return ret;
}

inline long long calc(long long a,long long b,long long c){ // calculate the sum a+(a+b)+(a+2*b)...+(a+(c-1)*b)
	return a*c+((c*(c-1))/2)*b;
}

long long query(node*me,int cL,int cR,int l,int r,long long sa1,long long sa2){ // query on the progressions persistent tree, quite standard
	if(cL==l&&cR==r)return me->sum+calc(sa1,sa2,cR-cL+1);
	long long ret=0;
	int mid=(cL+cR)>>1;
	if(l<=min(mid,r))ret+=query(me->l,cL,mid,l,min(mid,r),sa1+me->l->add1,sa2+me->l->add2);
	if(max(mid+1,l)<=r)ret+=query(me->r,mid+1,cR,max(mid+1,l),r,sa1+me->r->add1+sa2*(mid-cL+1),sa2+me->r->add2);
	return ret;
}

inline long long get(node*me,int cL,int cR){ // calculates the sum of the subtree for some node
	return me->sum+calc(me->add1,me->add2,cR-cL+1);
}

node*modify(node*me,int cL,int cR,int l,int r,long long a,long long b){ // progressions persistent tree modify
	node*ret=new node; // clone the current vertice
	ret->l=me->l,ret->r=me->r; // clone the current vertice
	ret->sum=me->sum,ret->add1=me->add1,ret->add2=me->add2; //clone the current vertice
	if(cL==l&&cR==r){ // then, usual segment tree modifying follow
		ret->add1+=a,ret->add2+=b;
		return ret;
	}
	int mid=(cL+cR)>>1;
	if(l<=min(r,mid))ret->l=modify(ret->l,cL,mid,l,min(r,mid),a,b);
	if(max(l,mid+1)<=r)ret->r=modify(ret->r,mid+1,cR,max(l,mid+1),r,a+max(0,mid-l+1)*b,b);
	ret->sum=get(ret->l,cL,mid)+get(ret->r,mid+1,cR);
	return ret; // clonned node should be returned
}

struct infNode{ // persistent array
	int l,r,x;
	infNode*le,*ri;
};

infNode*changeRoot[maxn];

infNode*initInfNode(int l,int r){ // create the persistent array like an ordinary segtree
	infNode*ret=new infNode;
	ret->l=l,ret->r=r,ret->x=0;
	if(l!=r){
		ret->le=initInfNode(l,(l+r)/2);
		ret->ri=initInfNode((l+r)/2+1,r);
	}
	return ret;
}

int infnodeGet(infNode*me,int j){ // query on a persistent array, doesn't differ from a query on a segtree
	if(me->l==me->r)return me->x;
	if(me->le->r>=j)return infnodeGet(me->le,j);else return infnodeGet(me->ri,j);
}

infNode*infnodeUpdate(infNode*me,int j,int x){ // updates some value in the persistent array and returns the new version
	infNode*ret=new infNode;  // clone the current vertice
	ret->l=me->l,ret->r=me->r; // clone the current vertice
	ret->le=me->le,ret->ri=me->ri; // clone the current vertice
	ret->x=me->x; // clone the current vertice
	if(ret->l==ret->r){ // then, ordinary modifying follows
		ret->x=x;
		return ret;
	}
	if(ret->le->r>=j)ret->le=infnodeUpdate(ret->le,j,x);else ret->ri=infnodeUpdate(ret->ri,j,x);
	return ret; // the return clonned vertice
}

vector<node*>root[maxn];
vector<int>version[maxn],refreshed[maxn],chg;
vector<pair<int,int> >queries[maxn],precalc[maxn];
int n,m,i,j,x,y,f[maxn*2],t[maxn*2],p[maxn*2],ii,up[maxn][20],subtree[maxn],chain[maxn],chains,chainSize[maxn],go_back=-1,lnk[maxn],modifies;
int tin[maxn],tout[maxn],timer,place[maxn],aa,bb,L,depth[maxn],pred[maxn],ver,changes,old_ver,pr[maxn],X[maxn],Y[maxn],AA[maxn],BB[maxn];
pair<int,int>a[maxn];
bool changing;
long long lastans;
char ch[maxn];

void addedge(int x,int y){ // add an edge to the tree
	t[++ii]=y;
	p[ii]=f[x];
	f[x]=ii;
}

int ex[maxn],ey[maxn],o[maxn];

void readIn(){
	scanf("%d%d",&n,&m); // amount of vertices and queries
	for(i=1;i<n;i++)scanf("%d%d",&ex[i],&ey[i]);
	for(i=1;i<n;i++)o[i]=i;
	for(i=1;i<n;i++){
		j=rand()%(n-1)+1;
		swap(o[i],o[j]);
	}
	for(i=1;i<n;i++){
		addedge(ex[o[i]],ey[o[i]]);
		addedge(ey[o[i]],ex[o[i]]);
	}
}

void dfs(int k){ // DFS, used to build LCA, and calculate sizes of subtrees.
	subtree[k]=1;
	tin[k]=++timer; // important for LCA calculation
	int q=f[k];
	while(q){
		if(!subtree[t[q]]){
			depth[t[q]]=1+depth[k]; 
			up[t[q]][0]=k; // important for LCA calculation
			for(int j=1;j<20;j++)up[t[q]][j]=up[up[t[q]][j-1]][j-1]; // important for LCA calculation
			dfs(t[q]);
			subtree[k]+=subtree[t[q]]; // calculate the size of the subtree, it will be used in hldot construction
		}
		q=p[q];
	}
	a[k]=make_pair(subtree[k],k);
	tout[k]=++timer; // important for LCA calculation
}

void givechain(int k){ // greedily build the hldot. take the son with the heaviest subtree
	chain[k]=chains;
	place[k]=++chainSize[chains];
	int q=f[k],mx=0;
	while(q){
		if(subtree[t[q]]<subtree[k])mx=max(mx,subtree[t[q]]);
		q=p[q];
	}
	q=f[k];
	while(q){
		if(subtree[t[q]]==mx){
			givechain(t[q]);
			break;
		}
		q=p[q];
	}
}

void build_dot(){
	for(i=0;i<20;i++)up[1][i]=1;
	dfs(1); // at first, run the DFS
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(i=1;i<=n;i++)if(!chain[a[i].second]){ // lauch the hldot building
		pred[++chains]=up[a[i].second][0];
		givechain(a[i].second);
		root[chains].push_back(init(1,chainSize[chains])); 
		version[chains].push_back(0);
	}
}

inline bool anc(int x,int y){ // checks whether X is ancestor of Y
	return (tin[x]<=tin[y]&&tout[x]>=tout[y]);
}

inline int LCA(int x,int y){ // compute the LCA for X and Y
	if(anc(x,y))return x;
	for(int i=19;i+1;i--)if(!anc(up[x][i],y))x=up[x][i];
	return up[x][0];
}

node*getCurrentRoot(int chain){ // returns actual version for the chain
	if(version[chain].back()==changes&&changing)return root[chain][version[chain].size()-1]; // if we're modifying now, and it was already changed, then take the last version
	if(version[chain].back()>go_back)return root[chain].back(); // also, if it's clear that the last version can be taken
	int now=infnodeGet(changeRoot[ver],chain); // otherwise, we use the persistent array (persistent arrays form the tree, btw) to get the current last version
	int l=0,r=version[chain].size()-1,mid; // index of the version is now known, we should find the root with this index
	while(l<r){
		mid=(l+r+1)>>1;
		if(version[chain][mid]>now)r=mid-1;else l=mid;
	}
	return root[chain][l]; // ... and return this root
}

void lift(int low,int high,long long a,long long b){ // modifying for the case when high is the ancestor of low
	if(chain[low]==chain[high]){ // case when it's necessary to modify only one chain
		long long amount=place[low]-place[high];
		node*newroot=modify(getCurrentRoot(chain[low]),1,chainSize[chain[low]],place[high],place[low],a+amount*b,-b);
		root[chain[low]].push_back(newroot); // remember the new version
		version[chain[low]].push_back(changes); // remember the new version
		chg.push_back(chain[low]); // remember the new version
	}else{ // otherwise, the whole prefix should be modified, and then lift should be called again
		long long amount=place[low]-1;
		node*newroot=modify(getCurrentRoot(chain[low]),1,chainSize[chain[low]],1,place[low],a+amount*b,-b);
		root[chain[low]].push_back(newroot); // again, remember the new version
		version[chain[low]].push_back(changes); // remember the new version	
		lift(pred[chain[low]],high,a+b*place[low],b); // run lift again. generally, it will be called till the moment chain[a]=chain[b]
		chg.push_back(chain[low]); // remember the new version
	}
}

void change(int L,int x,int y,long long a,long long b){ // more general version of changing. it's not necessary for the X to be an ancestor for Y
	// split it to the two cases: [x; L], [y; L)
	long long dist=depth[x]+depth[y]-2*depth[L]+1;
	lift(x,L,a,b); // [x; L]
	if(y!=L){ // [y; L)
		int pL=y,remain=depth[y]-depth[L]-1;
		for(j=19;j+1;j--)if(remain&(1<<j))pL=up[pL][j];
		lift(y,pL,a+b*(dist-1),-b);
	}
}

long long getsum(int low,int high){ // question query for the case when high is an ancestor of low
	// same logic as in lift
	if(chain[low]==chain[high]){
		node*root=getCurrentRoot(chain[low]);
		return query(root,1,chainSize[chain[low]],place[high],place[low],root->add1,root->add2);
	}else{
		node*root=getCurrentRoot(chain[low]);		
		return query(root,1,chainSize[chain[low]],1,place[low],root->add1,root->add2)+getsum(pred[chain[low]],high);
	}
	// notice, that you don't have to save any versions because you don't change anything
}

long long query(int L,int x,int y){ // more general case for quetion query
	if(L==x)return getsum(y,L); // if x is LCA
	if(L==y)return getsum(x,L); // or if y is LCA
	// otherwise, split it into two queries: [x; L] and [y; L)
	long long ret=getsum(x,L); // [x; L]
	int pL=y,remain=depth[y]-depth[L]-1;
	for(j=19;j+1;j--)if(remain&(1<<j))pL=up[pL][j];
	return ret+getsum(y,pL); // [y; L)
}

void upd_changed(){ // write all the updates in the persistent array
	for(j=0;j<chg.size();j++){
		infNode*tmp=infnodeUpdate(changeRoot[changes],chg[j],changes);
		changeRoot[changes]=tmp;
	}
}

int used[maxn],visited;

int main (int argc, char * const argv[]) {
	srand(time(NULL));
	readIn(); // read data
	build_dot(); // build the decomposition
	changeRoot[0]=initInfNode(1,chains); // build the version 0 of the persistent array
	for(i=1,changes=0,ver=0;i<=m;i++){
		ch[i]=getchar(); // get the type of the query
		while(ch[i]!='c'&&ch[i]!='q'&&ch[i]!='l')ch[i]=getchar(); // get the type of the query
		changing=false;
		if(ch[i]=='c'){ // changing query
			scanf("%d%d%d%d",&X[i],&Y[i],&AA[i],&BB[i]);
			X[i]=(X[i]+lastans)%n+1; // get actual X
			Y[i]=(Y[i]+lastans)%n+1; // get actual Y
			pr[++changes]=ver; 	
			changeRoot[changes]=new infNode; // create a new node in versions tree
			changeRoot[changes]=changeRoot[ver]; // create a new node in versions tree
			changing=true;
			x=X[i],y=Y[i],aa=AA[i],bb=BB[i];
			L=LCA(x,y); // get LCA
			chg.clear();
			change(L,x,y,aa,bb); // do the change
			upd_changed(); // update persistent array
			ver=changes; // update the current version's index
			++modifies;
		}else if(ch[i]=='q'){
			scanf("%d%d",&X[i],&Y[i]);
			X[i]=(X[i]+lastans)%n+1; // get actual X
			Y[i]=(Y[i]+lastans)%n+1; // get actual Y
			x=X[i],y=Y[i];
			L=LCA(x,y); // get LCA
			lastans=query(L,x,y); // answer the query
			printf("%lld\n",lastans);
		}else if(ch[i]=='l'){
			scanf("%d",&X[i]);
			X[i]=(X[i]+lastans)%(modifies+1); // get actual version
			ver=X[i]; 
			go_back=changes;
		}
	}
	return 0;
}
```
</details>
