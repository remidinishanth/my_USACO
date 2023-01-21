 source: https://apps.topcoder.com/forums/?module=Thread&threadID=671140&start=0

First of all, gcd can be written in one line:
```cpp
int gcd(int a, int b) { return (b ? gcd(b, a%b) : abs(a)); }
// This code works well for any signed integers except the pair (0, 0).
```

If we speak of large number gcd, we should include binary algorithm as it is much easier to implement for large numbers. Here is the code for ints:

```cpp
int gcd(int a, int b) {
	if (a == 0) return b;
	if (b == 0) return a;
	if (a%2==0 && b%2==0) return gcd(a/2, b/2) * 2;
	else if (a%2 == 0) return gcd(a/2, b);
	else if (b%2 == 0) return gcd(a, b/2);
	else return (a>=b ? gcd(a-b, b) : gcd(a, b-a));
}
```

Works for nonnegative numbers only (except zero pair as always). Time is O(h^2).

I think we should make the extended Euclid algorithm clear:

```cpp
int Euclid(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = (a<0 ? -1 : 1);
		y = 0;
		return a*x;
	}
	int q = a/b;
	int r = a%b;
	int d = Euclid(b, r, y, x);
	y -= q*x;
	return d;
}
...
int x, y;
g = Euclid(a, b, x, y);
```

This code returns `g = gcd(a, b)` and also finds such `x` and `y` that: `a*x + b*y = g`

It works for any pair of signed numbers (except zero pair). Moreover, the solution it finds is almost minimal in absolute value:
```cpp
|x| <= |b|/g
|y| <= |a|/g
```
This experimental fact often allows us not to be afraid of overflow.

The solution for general diophantine equation includes a lot of cases such as `a==0` or `b==0` of `c==0 `plus signs of `a` and `b` etc. 

Do we really need to include it? The extended Euclid algorithm code is sufficient to find reciprocal element modulo `M` which 
is the most common usage.


### Applications:

https://leetcode.com/contest/biweekly-contest-96/problems/check-if-point-is-reachable/

There exists an infinitely large grid. You are currently at point `(1, 1)`, and you need to reach the point `(targetX, targetY)` using a finite number of steps.

In one step, you can move from point `(x, y)` to any one of the following points:

```cpp
(x, y - x)
(x - y, y)
(2 * x, y)
(x, 2 * y)
```

Given two integers `targetX` and `targetY` representing the X-coordinate and Y-coordinate of your final position, 
return `true` if you can reach the point from `(1, 1)` using some number of steps, and `false` otherwise.

```python
class Solution:
    def isReachable(self, targetX: int, targetY: int) -> bool:
        tx, ty = targetX, targetY
        while tx & 1 == 0:
            tx >>= 1
        while ty & 1 == 0:
            ty >>= 1
        g = math.gcd(tx, ty)
        if g == 1:
            return True
        else:
            return False
```
