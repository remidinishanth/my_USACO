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

You are given an array of integers and a set of queries. Each query consists of two integer numbers `L R K`, denoting that you’re asked to find the K-th order statistics on the segment `[L; R]`. (Kth element in sorted range `[i, j]`)

<details>
 <summary> Using Merge sort tree </summary>

If we build merge sort tree on the elements of the array, then we can find the number of integers less than the given one in `O(log^2 N)` time by splitting the query segment into segtree segments and doing a binary search in each of them. Now for middle element we need to check whether the number of elements less than are equal to the required amount which would become `O(log^3 N)` per query.

For `O(log^2 N)` per query, we can sort the integers and save their positions in the merge sort tree and then apply a trick we have in finding the K-th order statistics in the segtree with nonnegative integers. Since the numbers are sorted and we store the positions in the segment tree, all the numbers in positions of the left half are strictly less than numbers at positions in right half. So now we need to check whether the number of positions in the left subtree from `[L, R]` are less than equal to `K`(this can be calculated by two binary searches query(R) - query(L-1)), if so then our answer is in the left half, if not we go to the right child of segment tree. The time complexity will be `O(log^2 N)` because depth of segment tree is `O(log N)` and we need two binary searches for each node.

![image](https://user-images.githubusercontent.com/19663316/120347119-a1bc4100-c319-11eb-867f-38fa793e7465.png)


</details> 
