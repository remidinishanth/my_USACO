Think Binary search as prefix of False and suffix of True or the
other way around, then you are asked to find the boundary that is the 
first True or the first False

Look at the middle answer, if it is satisfied go to a possible better
answer, otherwise go to a half containing answer.

```cpp
void binary_search(){
	L=0, R=N-1;
	while L <=R :
		mid = L + (R-L)/2
		if a[mid]==target:
			return mid
		if a[mid]<target:
			L=mid+1
		else:
			R=mid-1
	return -1
}

void lower_bound(){
	L=0,R=N-1;
	ans=-1;
	while L<=R:
		mid=L+(R-L)/2
		if a[mid]>=target:
			// better values to the leftmost
			ans=mid // a[mid]
			R=mid-1 // look for better values
		else:
			L=mid+1
	return ans
}
```

source: <https://apps.topcoder.com/forums/?module=Thread&threadID=670168&start=0>

Problem:
You want to find the smallest x in the given interval [a,b] such that some propety P(x) holds. 
You know that if P(x) and y>x, then also P(y). You also know that P(b) holds. 
This could be either an interval of integers, or of real numbers.

The most common application of binary search is the following. You have a non-decreasing function f, and a constant C. 
You have to find the smallest x for which f(x) = C (or, if there is none, the smallest x for which f(x) ≥ C). 
In this case, your property P(x) is "f(x) ≥ C".

Solution:

If [a,b] is an interval of integers:

```cpp
int l = a, r = b;
while(l < r) {
  int m = (l+r) >> 1; // take the center of the interval
  // replace the interval [a,b] with either [a,m] or [m+1,b],
  // depending on whether P(m) is already satisfied
  if(P(m)) r = m; else l = m+1;
  }
x=l;
```

If [a,b] is an interval of real numbers:

```cpp
double l = a, r = b;
for(int iterations=0; iterations<100; iterations++) {
  double m = (a+b)/2;
  if(P(m)) r = m; else l = m;
  }
x=l;
```

Discussion:

If you don't know that P(b) holds, use "b+1" for the upper bound. Note that P(x) is never checked for x which is 
the upper bound of the interval (since it is assumed to be true), thus, the binary search will either return the 
correct number, or "b+1", which means that there is no x in [a,b] for which P(x) is satisfied.

The most common and easiest use of this technique is looking for a certain value 'k' in a sorted array. 
In this case, if a[x] ≥ k and y>x, then also a[y] ≥ k, which means that we can use a[x] ≥ k as P(x). 
However, there are very many programming problems where such a P(x) property could be found.

Remember the code shown above well, especially the integer case. Make sure that your binary search works for 
intervals [a,a+1]—there are two possible answers for this problem, and after one step of binary search we should 
always have an interval [x,x] with a single possible answer. 
If you change one of the three places "m=(l+r)>>1", "r=m", "l=m+1", even by adding or subtracting one to the right 
side of one of the assignments, the result will probably fail (one of two subintervals is likely to be either 
nonsense [a,a-1], which means that there is an error, or [a,a+1] again, which means that the algorithm loops infinitely).


Problem: Unimodal functions
You have a function f in an interval [a,b] of real numbers, and you want to find the x for which 
f(x) is maximized. You know that the function f is unimodal: it is strictly increasing in the 
interval [a,x], and strictly decreasing in the interval [x,b].

Solution:
If we are working with an interval of integers, not an interval of reals, simply use binary search 
(see "binary search" recipe). (The property P(x) we are working with is the following one: f(x) > f(x+1).)

For reals, use the following algorithm, known as ternary search:

```cpp
double l = a, r = b;
 
for(int i=0; i<200; i++) {
  double l1 = (l*2+r)/3;
  double l2 = (l+2*r)/3;
  if(f(l1) > f(l2)) r = l2; else l = l1;
}
 
x = l;
```

Discussion:
This works because after each step the interval [a,b] is reduced to 2/3 of its previous size. 
After 200 steps, we will know the answer up to an error of at most (2/3)^200 of the original interval

source: <https://apps.topcoder.com/forums/?module=Thread&threadID=670169&start=0>

Also go thru <https://www.topcoder.com/community/competitive-programming/tutorials/binary-search/>

I'm sure there have been tutorials etc about this trick but since people are talking about binary search, I want to add this. I like to use iterative binary search that looks like this:

```cpp
int ans = 0;
for (int k = 1 << MAX_LG; k != 0; k /= 2) {
  if (!has_some_property(ans + k)) {
    ans += k;
  }
}
```

This assumes 0 doesn't have "some property". In the end, ans will be the largest integer that doesn't have "some property".

Using this, I have been able to avoid guessing about one-off errors for 6 years already. It is short to write, intuitive and generalizes well to floats and bigints. I'm not sure exactly what your "trick 8" accomplishes, but I suspect iterative binary search also makes that unnecessary.

In case of float: `for (double k = MAX_N; k > EPS; k /= 2)`

source: <https://codeforces.com/blog/entry/84150?#comment-716582>
