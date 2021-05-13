e-maxx english https://cp-algorithms.com/data_structures/segment_tree.html

### Point Update Range Sum

Here is a visual representation of such a Segment Tree over the array `a=[1, 3, −2, 8, −7]`:

![image](https://user-images.githubusercontent.com/53462873/118096629-3accfb80-b3ef-11eb-9ddf-a0f0c926cabd.png)

It is easy to see that, the root vertex is at index `1`, the left child of a vertex at index `i` is stored at index `2i`, and the right one at index `2i+1`.

Let `v` be the index of the current vertex, and the boundaries `tl` and `tr` of the current segment, then we can build segment tree recursively as follows.

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


Counting the number of zeros, search k zero
Store in t[] the no. of zeros in that segment same as above
now the problem of finding a position k, the occurrence of zero in the array

```cpp
 int find_kth ( int v, int tl, int tr, int k ) {
	if ( k > t [ v ] ) //k_th zero does not exist
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

Assume a[] contains only non-negative numbers. Use similar trick to find i such that sum of first i elements is ≥ x. Searching for an array prefix with a given amount


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


### Assignment on segments
Painting a segment - Changing all elements in a segment to some value

Range Update Point Query

Version 1

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

Lazy propagation

Adding on segments, querying for maximum

Range update and Range query

```cpp
void push(int v) { // This push works because we are querying for maximum, see get() below
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


// update: add v to all elements a[x], a[x+1]...a[y]a[x],a[x+1]...a[y]
// query: a[x]+a[x+1]+...+a[y]a[x]+a[x+1]+...+a[y]
// Range Update Range Sum Query

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



// kmjp

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

source: https://codeforces.com/contest/1516/submission/113760111
source: https://kmjp.hatenablog.jp/entry/2018/01/03/0930
