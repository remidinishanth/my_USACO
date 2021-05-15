e-maxx english https://cp-algorithms.com/data_structures/segment_tree.html

### Point Update Range Sum

Here is a visual representation of such a Segment Tree over the array `a=[1, 3, −2, 8, −7]`:

![image](https://user-images.githubusercontent.com/53462873/118096629-3accfb80-b3ef-11eb-9ddf-a0f0c926cabd.png)

It is easy to see that, the root vertex is at index `1`, the left child of a vertex at index `i` is stored at index `2i`, and the right one at index `2i+1`.

Let `v` be the index of the current vertex, and the boundaries `tl` and `tr` of the current segment, let `tm = (tl+tr)/2` then we can build segment tree recursively as follows.

![image](https://user-images.githubusercontent.com/53462873/118097415-4967e280-b3f0-11eb-9e6c-02f7aed9dee2.png)


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

//main program should pass v=1, t1=0,tr=n-1 in addtion to l and r
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm)) +
        sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

//Point Update
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

In case of search of max/min and no. of times it occurs

```cpp
pair<int,int> t[4*MAXN]; //pair<maximum, number of times it occurs in the subtree>
 
pair<int,int> combine (pair<int,int> a, pair<int,int> b) {
	if (a.first > b.first)
		return a;
	if (b.first > a.first)
		return b;
	return make_pair (a.first, a.second + b.second);
}
 
void build (int v, int tl, int tr) {
	if (tl == tr)
		t[v] = make_pair (a[tl], 1);
	else {
		int tm = (tl + tr) / 2;
		build (v*2, tl, tm);
		build (v*2+1, tm+1, tr);
		t[v] = combine (t[v*2], t[v*2+1]);
	}
}
 
pair<int,int> get_max (int v, int tl, int tr, int l, int r) {
	if (l > r)
		return make_pair (-INF, 0);
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return combine (
		get_max (v*2, tl, tm, l, min(r,tm)),
		get_max (v*2+1, tm+1, tr, max(l,tm+1), r)
	);
}
 
void update (int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		t[v] = make_pair (new_val, 1);
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update (v*2, tl, tm, pos, new_val);
		else
			update (v*2+1, tm+1, tr, pos, new_val);
		t[v] = combine (t[v*2], t[v*2+1]);
	}
}
```


Counting the number of zeros, search `k-th` zero. Store in t[] the no. of zeros in that segment. Now we get find the `k-th` as follows:

```cpp
 int find_kth ( int v, int tl, int tr, int k ) {
	if ( k > t [ v ] ) // k-th zero does not exist
		return - 1 ;
	if ( tl == tr )
		return tl ;
	int tm = ( tl + tr ) / 2 ;
	if ( t [ v * 2 ] >= k )
		return find_kth ( v * 2 , tl, tm , k ) ;
	else
		return find_kth ( v * 2 + 1 , tm + 1 , tr, k - t [ v * 2 ] ) ;
}
```

Assume a[] contains only non-negative numbers. We can use similar trick to find `i` such that sum of first `i` elements is `≥ x`. Searching for an array prefix with a given amount

#### Searching for the first element greater than a given amount.

The task is as follows: for a given value `x` and a specified segment `a[l…r]`, find the smallest `i` in the range `a[l…r]`, such that `a[i]` is greater than `x`.

This task can be solved using binary search over max prefix queries with the Segment Tree. However, this will lead to a `O(log^2 n)` solution.

Instead, we can use the same idea as in the previous sections, and find the position by descending the tree: by moving each time to the left or the right, depending on the maximum value of the left child. Thus finding the answer in `O(logn)` time.

```cpp
int get_first(int v, int tl, int tr, int l, int r, int x) {
    if(tl > r || tr < l) return -1;
    if(l <= tl && tr <= r) {
        if(t[v] <= x) return -1;
        while(lv != rv) {
            int mid = tl + (tr-tl)/2;
            if(t[2*v] > x) { // max of left child > x, go to left child
                v = 2*v;
                tr = mid;
            }else {
                v = 2*v+1;
                tl = mid+1;
            }
        }
        return tl;
    }

    int mid = tl + (tr-tl)/2;
    int rs = get_first(2*v, tl, mid, l, r, x);
    if(rs != -1) return rs;
    return get_first(2*v+1, mid+1, tr, l ,r, x);
}
```


### Range update and point Query
Addition on segment without lazy propogation

```cpp
 void build (int v, int tl, int tr ) {
	if ( tl == tr )
		t [ v ] = a [ tl ] ;
	else {
		int tm = ( tl + tr ) / 2 ;
		build (v * 2 , tl, tm ) ;
		build (v * 2 + 1 , tm + 1 , tr ) ;
	}
}

// To make the addition query efficient, we store at each vertex in the Segment Tree how much
// we should add to all numbers in the corresponding segment
void update ( int v, int tl, int tr, int l, int r, int add ) {
	if ( l > r )
		return ;
	if ( l == tl && tr == r )
		t [ v ] + = add ;
	else {
		int tm = ( tl + tr ) / 2 ;
		update ( v * 2 , tl, tm , l, min ( r, tm ) , add ) ;
		update ( v * 2 + 1 , tm + 1 , tr, max ( l, tm + 1 ) , r, add ) ;
	}
}
 
int get ( int v, int tl, int tr, int pos ) {
	if ( tl == tr )
		return t [ v ] ;
	int tm = ( tl + tr ) / 2 ;
	if ( pos <= tm )
		return t [ v ] + get ( v * 2 , tl, tm , pos ) ;
	else
		return t [ v ] + get ( v * 2 + 1 , tm + 1 , tr, pos ) ;
} 
```

### Range Update Point Query

Assignment on segments: Painting a segment - Changing all elements in a segment to some value

Version 1 - Lazy propogation

```cpp
void push(int v) {
    if (t[v] ! = -1) {
        t[v * 2] = t[v * 2 + 1] = t[v];
        t[v] = -1;
    }
}

void update(int v, int tl, int tr, int l, int r, int color) {
    if (l > r)
        return;
    if (l == tl && tr == r)
        t[v] = color;
    else {
        push(v);  // Lazy propogation, updating only when we require
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), color);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, color);
    }
}
 
int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    push(v); // Lazy propogation, updating only when we require
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return get(v * 2, tl, tm, pos);
    else
        return get(v * 2 + 1, tm + 1, tr, pos);
}
```

Version 2 emaxx english

```cpp
void push(int v) {
    if (marked[v]) {
        t[v*2] = t[v*2+1] = t[v];
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}

void update(int v, int tl, int tr, int l, int r, int new_val) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] = new_val;
        marked[v] = true;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), new_val);
        update(v*2+1, tm+1, tr, max(tl, tm+1), tr, new_val);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return t[v];
    }
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm) 
        return get(v*2, tl, tm, pos);
    else
        return get(v*2+1, tm+1, tr, pos);
}
```

### Range update and Range query

Using Lazy propagation

#### Increment values on segments by some value, query for maximum

```cpp
void push(int v) { // This push works because we are querying for maximum, see query() below
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(tl, tm+1), tr, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INF;
    if (tl == tr)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)), 
               query(v*2+1, tm+1, tr, max(tl, tm+1), tr));
}
```

#### Range Update Range Sum Query

Update: add v to all elements `a[x], a[x+1]...a[y]`

Query: `a[x]+a[x+1]+...+a[y]`

```cpp
void push(int v, int l, int r){
    t[v] += (r - l + 1)*lazy[v];
    if(l!=r){ // if the node has children we propagate the lazy
    	lazy[v*2] += lazy[v];
    	lazy[v*2+1] += lazy[v];
    }
    lazy[v]=0;
}

void update(int v, int tl, int tr, int l, int r, int value){
    push(v, tl, tr); // This is crucial, Don't push without later merging your two children.
    // If we put this after if(l>r) then child will have lazy tag but we update t[v] = t[2*v] + t[2*v+1] and hence our code will fail
    // Once we push, we have to update our parent node with the updated value, so if child is marked lazy, we have to update it and then only update parent.
    // Otherwise use something like #define GET(node), incase of lazy, in case the node is lazy we apply the function and then get value, see segtree_struct
    if (l > r) 
        return;
    /*
    if(r < tl || l > tr) return; // out of range => exit
    If we use this then we can simply use 
    update(2*v, tl, tm, l, r, value); in the below instead of
    update(2*v, tl, tm, l, min(r,tm), value); but then we should use
    if(l <= tl && tr <= r) then we have to do node update
    */ 
    if(l == tl && tr == r){
        lazy[v] += value;
        push(v,l,r);
    }
    else{
        int tm=(tl+tr)/2;
        update(2*v, tl, tm, l, min(r, tm), value);
        update(2*v+1, tm+1, tr, max(l, tm+1), r, value);
        t[v] = t[2*v] + t[2*v+1]; // children are up to date because we always push
    }
}

ll sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    push(v, tl, tr);
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm)) +
        sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}
```
Tested with SPOJ HORRIBLE - Horrible Queries

If we don't push at the beginning, we will need to do something like this in update function

```cpp
    int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)]; // find actual value of left subtree
    int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)]; // find actual value of left subtree
    st[p] = combine(lsubtree, rsubtree);
```

#### Why we need O(4n) space?

Consider the Minimum segment tree for the array `[1, 3, −2, 8, −7]`

![image](https://user-images.githubusercontent.com/53462873/118101284-0eb47900-b3f5-11eb-8211-bcc98e07a3f0.png)

If we add one more element to the array `[1, 3, −2, 8, −7, 5]`, in this case till `13` elements which is greater than `2*n = 12`

![image](https://user-images.githubusercontent.com/53462873/118101476-491e1600-b3f5-11eb-9775-e740ec5b473c.png)

### OOP style CP4

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = conquer(lsubtree, rsubtree);
    }
  }

public:
  SegmentTree(int sz) : n(sz), A(n), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};

int main() {
  vi A = {18, 17, 13, 19, 15, 11, 20, 99};       // make n a power of 2
  SegmentTree st(A);

  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // 11
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // 15

  st.update(5, 5, 77);                           // update A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // remains 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // now 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains 15

  st.update(0, 3, 30);                           // update A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // now 30
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains 15

  st.update(3, 3, 7);                            // update A[3] to 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // now 7
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // now 7

  return 0;
}
```

### TODO: https://codeforces.com/blog/entry/15890

### kmjp implementations

```cpp
Static ll const def = - 1LL << 50 ;
 template < class V, int NV> class SegTree_3 {
 public :
	vector <V> val, ma;
	SegTree_3 () {
		int i;
		val.resize (NV * 2 , 0 ); ma.resize (NV * 2 , 0 );
		FOR (i, NV) val [i + NV] = ma [i + NV] = def;
		for (i = NV- 1 ; i> = 1 ; i--) ma [i] = max (ma [ 2 * i], ma [ 2 * i + 1 ]);
	};
	
	V getval ( int x, int y, int l = 0 , int r = NV, int k = 1 ) {
		 if (r <= x || y <= l) return def;
		 if (x <= l && r < = y) return ma [k];
		 return val [k] + max (getval (x, y, l, (l + r) / 2 , k * 2 ), getval (x, y, (l + r) / 2 , r, k * 2 + 1 )));
	}
	
	void update ( int x, int y, V v, int l = 0 , int r = NV, int k = 1 ) {
		 if (l> = r) return ;
		 if (x <= l && r <= y) {
			val [k] + = v;
			ma [k] + = v;
		}
		else  if (l <y && x <r) {
			update (x, y, v, l, (l + r) / 2 , k * 2 );
			update (x, y, v, (l + r) / 2 , r, k * 2 + 1 );
			ma [k] = val [k] + max (ma [k * 2 ], ma [k * 2 + 1 ]);
		}
	}
};

template < class V, int NV> class SegTree_2 {
 public :
	vector <V> val;
	static V constant def = 0 ;
	V comp (V l, V r) { return __gcd (l, r);};
	
	SegTree_2 () {val = vector <V> (NV * 2 , def);};
	V getval ( int x, int y, int l = 0 , int r = NV, int k = 1 ) { // x <= i <y 
		if (r <= x || y <= l) return def;
		 if (x <= l && r <= y) return val [k];
		 return comp (getval (x, y, l, (l + r) / 2 , k * 2 ), getval (x, y, (l +) r) / 2 , r, k * 2 + 1 )));
	}
	void update ( int entry, V v) {
		entry + = NV;
		val [entry] = v;
		while (entry> 1 ) entry >> = 1 , val [entry] = comp (val [entry * 2 ], val [entry * 2 + 1 ]);
	}
};

SegTree_3 <ll, 1 << 17 > stmax;
SegTree_2 < int , 1 << 17 > stgcd;

template<class V,int NV> class SegTree_1 {
public:
	vector<V> val;
	 static V const def=1LL<<30;
	V comp(V l,V r){ return min(l,r);};
	
	SegTree_1(){val=vector<V>(NV*2,def);};
	V getval(int x,int y,int l=0,int r=NV,int k=1) { // x<=i<y
		if(r<=x || y<=l) return def;
		if(x<=l && r<=y) return val[k];
		return comp(getval(x,y,l,(l+r)/2,k*2),getval(x,y,(l+r)/2,r,k*2+1));
	}
	void update(int entry, V v) {
		entry += NV;
		val[entry]=comp(v,val[entry]); //上書きかチェック
		while(entry>1) entry>>=1, val[entry]=comp(val[entry*2],val[entry*2+1]);
	}
};
SegTree_1<int,1<<18> st;
```

source: https://codeforces.com/contest/1516/submission/113760111 & https://kmjp.hatenablog.jp/entry/2018/01/03/0930
