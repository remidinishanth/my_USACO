TODO https://codeforces.com/blog/entry/47764

TODO https://apps.topcoder.com/forums/?module=Thread&threadID=700080&start=0

## Expected Number DP

### J Sushi Atcoder
https://atcoder.jp/contests/dp/tasks/dp_j

There are `N((1 ≤ N ≤ 300)` dishes, numbered `1,2,...,N`. Initially, for each `i(1 ≤ i ≤ N)`, Dish `i` has `ai(1 ≤ ai ≤ 3)` pieces of sushi on it.

Taro will perform the following operation repeatedly until all the pieces of sushi are eaten:
* Roll a die that shows the numbers `1,2, … ,N` with equal probabilities, and let `i` be the outcome. If there are some pieces of sushi on Dish `i` , eat one of them; if there is none, do nothing.

Find the expected number of times the operation is performed before all the pieces of sushi are eaten.

**Input**
```
N
a1 a2 ... aN
```

#### Solution

If we choose our subproblem or DP state to be something like `dp(r1,r2,...,rN)` where `ri` is the number of remaining sushi in `i-th` dish, the number of dp states will be `O(4^N)` because `0 ≤ ri ≤ 3` and `0 ≤ i ≤ N`

So instead of considering each `i-th` dish seperately we can combine them and use the state `dp(i,j,k)`, where `i` denotes number of dishes with `1 sushi`, `j` denotes number of dishes with `2 sushi` and `k` denotes number of dishes with `3 sushi`, `(N-i-j-k)` will be number of dishes with `0 sushi` left.
