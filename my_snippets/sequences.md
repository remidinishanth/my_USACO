### Problem: 

Given is a sequence `A` of length `N` (1 ≤ N ≤ 2×10⁵). You can do this operation any number of times: when the length of the sequence is at least `2`, choose two adjacent values, delete them, and insert their sum where they were. 

How many sequences can result from zero or more operations? Find the count modulo `998244353`.


Example:

```
3
1 -1 1
```

The following four sequences can result from zero or more operations.

```
1,−1,1
1,0
0,1
1
```

### Solution:

We consider the correspondence between a resulting integer sequence with a sequence of operations. 

In order to make a non-empty sequence, we may take the following greedy approach: repeat adding the 1st and the 2nd leftmost values until the 1st value of the desired sequence is obtained, then repeat adding the 2nd and the 3rd leftmost values until the 2nd value of the desired sequence is obtained, ... , and so on. 

A suffix of A that does not correspond to any element of the desired sequence may remain, but in that case, the desired sequence can be obtained if and only if the sum of elements in the suffix is 0. 

Since the sequence of operations in this greedy method and the resulting array correspond one-by-one, so it is sufficient to find the number of possible sequences of operations.

TODO: https://atcoder.jp/contests/abc230/editorial/3033

Also checkout: https://www.youtube.com/watch?v=dRLt9nki_MI&t=1798s

From the editorial, then `DP[i] = DP[j] + DP[j+1] + ⋯ + DP[i−1]`, then using prefix sums `preDP` we get `DP[i] = preDP[i-1] - preDP[j-1]`, then `preDP[i] = preDP[i-1] + DP[i]` which is nothing but `preDP[i] = 2*preDP[i-1] - preDP[j-1]`

Check Japanese Editorial: https://atcoder.jp/contests/abc230/editorial/3082 and https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd

Also https://atcoder.jp/contests/abc230/editorial/3034
