## Motivation

**Problem :** [Covered Walkway](https://open.kattis.com/problems/coveredwalkway) We need to cover a walkway consisting of n(1 ≤ n ≤ 10^6) points. To cover the walkway from a point at 𝑥 to a point at 𝑦, they will charge `c + (x − y)²`, where c is a constant. Note that it is possible for x=y. If so, then the contractor would simply charge c.

**Solution :**

* Cover n points on the plane with some number of segments.
* The cost of segment (l,r) is c + (r − l)².
* Straightforward DP is O(N²) and is too slow.

Convex Hull Optimization
* Consider a data structure that hold linear functions yi(x) = ai x + bi
* Need to implement function add(ai, bi) and get(x) = mini yi(x).
* Assume that lines are added in the order of decreasing ai.
* Keep the hull of all the lines in a stack (just like in the convex hull algorithm).
 ![](images/convex_hull_trick2.png) 
* When adding a line, remove lines from the top of the stack until it’s convex.
* Add a line y = ai + b. getX(a, b) returns x coordinate of intersection of lines a and b.
  ```cpp
  while( getX(prevLast, newLine) < getX(prevLast, last))
      remove ( last )
  ```
* Get value for x: find an optimal line such that x lies between intersection with neighboring lines
* Binary search for lines in stack in O(log n).
* If, in addition, queries x are always increasing, you can keep a pointer to the current best line.
* It only moves to the right, except when the best line was deleted, so it’s O(1) amortized.

 ![](images/convex_hull_trick1.png)
 
 <details>
   <summary> Using Dynamic CHT, O(N logN) </summary>
 
 ```cpp
 #define LL long long
const LL is_query = -(1LL << 62);
struct Line {
  LL m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m > rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    return s->b - b < (m - s->m) * rhs.m;
  }
};
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {  // maintains lower hull for min
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b >= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b >= x->b;
    return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
  }
  void insert_line(LL m, LL b) {
    auto y = insert({m, b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  LL eval(LL x) {
    auto l = *lower_bound((Line){x, is_query});
    return l.m * x + l.b;
  }
};

int main() {
    int N;
    long long C;
    scanf("%d %lld", &N, &C);
    HullDynamic CHT;
    vector<long long> dp(N+1);
    // dp[j] = C + xj^2 + min(-2 * xi *xj + xi^2 + dp[i-1])
    for(int i=1;i<=N;i++){
        int x;
        scanf("%d", &x);
        if(i == 1){
            dp[i] = C;
        }else{
            dp[i] = min(C + 1ll*x*x + CHT.eval(x), C + dp[i-1]);
        }
        CHT.insert_line(-2ll*x, 1ll*x*x + dp[i-1]); // insert values
    }
    printf("%lld\n", dp[N]);
    return 0;
}
 ```
 </details>
 
 <details>
   <summary> Using CHT, O(N) </summary>
 
 Since x are increasing, we can store them in stack.
 </details>

## Convex Hull Trick

```cpp
struct convex_hull_trick {
  vector<pair<double,double> > h;
  double intersect(int i) {
    return (h[i+1].second-h[i].second) /
      (h[i].first-h[i+1].first); }
  void add(double m, double b) {
    h.push_back(make_pair(m,b));
    while (size(h) >= 3) {
      int n = size(h);
      if (intersect(n-3) < intersect(n-2)) break;
      swap(h[n-2], h[n-1]);
      h.pop_back(); } }
  double get_min(double x) {
    int lo = 0, hi = (int)size(h) - 2, res = -1;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (intersect(mid) <= x) res = mid, lo = mid + 1;
      else hi = mid - 1; }
    return h[res+1].first * x + h[res+1].second; } };
```

## Dynamic Convex Hull Trick

A data structure which maintain a some lines in `(m, b)` format where `y = m*x + b` and we can query for the minimum value for a given `x`.

Maintains lower hull for min

```cpp
#define LL long long
const LL is_query = -(1LL << 62);
struct Line {
  LL m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m > rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    return s->b - b < (m - s->m) * rhs.m;
  }
};
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {  // maintains lower hull for min
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b >= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b >= x->b;
    return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
  }
  void insert_line(LL m, LL b) {
    auto y = insert({m, b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  LL eval(LL x) {
    auto l = *lower_bound((Line){x, is_query});
    return l.m * x + l.b;
  }
};

// Usage
HullDynamic cht;
cht.insert(slope, constant);
min_val = cht.eval(x_val); // min value at point x_val
```
source: Tanuj Khattar https://pastebin.com/XF5WQ2YR

Maintains Upper hull for maximum

```cpp
const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b < (s->m - m) * x; } };
// will maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b; }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    return (x->b - y->b)*(z->m - y->m) >=
           (y->b - z->b)*(y->m - x->m); }
  void insert_line(ll m, ll b) {
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y)); }
  ll eval(ll x) {
    auto l = *lower_bound((Line) { x, is_query });
    return l.m * x + l.b; } };
```

https://github.com/SuprDewd/CompetitiveProgramming/blob/master/code/data-structures/convex_hull_trick_dynamic.cpp

## Li-Chao Tree

Li-Chao Segment Trees can be used to solve problems of the format:

You're given a set S containing function of the same "type" (ex. lines, y = ax + b). The type of function need to have the transcending property. You need to handle two type of queries:

* Add a function to S
* Answer the maximum/minimum value at x = t considering all functions in S
 
A type of function has **transcending property** if:

Given two functions f(x), g(x) of that type, if f(t) is greater than/smaller than g(t) for some x = t, then f(x) will be greater than/smaller than g(x) for x > t. In other words, once f(x) "win/lose" g(x), f(x) will continue to "win/lose" g(x).
