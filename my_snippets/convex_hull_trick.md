## Dynamic Convex Hull Trick

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
