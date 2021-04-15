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
