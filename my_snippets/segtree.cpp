//e-maxx

//Point Update Range Sum
int n, t[4*MAXN];
int a[MAXN];

// call this function with parameters v = 1, tl = 0, tr = n-1
void build (int v=1, int tl=0, int tr=n-1) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build (v*2, tl, tm);
		build (v*2+1, tm+1, tr);
		t[v] = t[v*2] + t[v*2+1];
	}
}

//main program should pass v=1, t1=0,tr=n-1 in addtion to l and r
int sum (int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return sum (v*2, tl, tm, l, min(r,tm))
		+ sum (v*2+1, tm+1, tr, max(l,tm+1), r);
}

//Point Update
void update (int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		t[v] = new_val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update (v*2, tl, tm, pos, new_val);
		else
			update (v*2+1, tm+1, tr, pos, new_val);
		t[v] = t[v*2] + t[v*2+1];
	}
}




//In case of search of max/min and no. of times it occurs

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



//Counting the number of zeros, search k zero
//Store in t[] the no. of zeros in that segment same as above
//now the problem of finding a position k, the occurrence of zero in the array

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

//Assume a[] contains only non-negative numbers
//Use similar trick to find i such that sum of first i elements is >=x
//Searching for an array prefix with a given amount


//Range update and point Query
//Addition on segment without lazy propogation

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



//Assignment on segments
//Painting a segment - Changing all elements in a segment to some value
//Range Update Point Query

//Version 1

 void push ( int v ) {
	if ( t [ v ] ! = - 1 ) {
		t [ v * 2 ] = t [ v * 2 + 1 ] = t [ v ] ;
		t [ v ] = - 1 ;
	}
}
 
void update ( int v, int tl, int tr, int l, int r, int color ) {
	if ( l > r )
		return ;
	if ( l == tl && tr == r )
		t [ v ] = color ;
	else {
		push ( v ) ;
		int tm = ( tl + tr ) / 2 ;
		update ( v * 2 , tl, tm , l, min ( r, tm ) , color ) ;
		update ( v * 2 + 1 , tm + 1 , tr, max ( l, tm + 1 ) , r, color ) ;
	}
}
 
int get ( int v, int tl, int tr, int pos ) {
	if ( tl == tr )
		return t [ v ] ;
	push ( v ) ; // Lazy propogation, updating only when we require
	int tm = ( tl + tr ) / 2 ;
	if ( pos <= tm )
		return get ( v * 2 , tl, tm , pos ) ;
	else
		return get ( v * 2 + 1 , tm + 1 , tr, pos ) ;
} 

//Version 2 emaxx english
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

//Lazy propagation
//Adding on segments, querying for maximum
//Range update and Range query

void push(int v) {
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
