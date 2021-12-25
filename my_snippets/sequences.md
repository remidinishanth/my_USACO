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

### Solution Idea:

We consider the correspondence between a resulting integer sequence with a sequence of operations. 

In order to make a non-empty sequence, we may take the following greedy approach: repeat adding the 1st and the 2nd leftmost values until the 1st value of the desired sequence is obtained, then repeat adding the 2nd and the 3rd leftmost values until the 2nd value of the desired sequence is obtained, ... , and so on. 

A suffix of A that does not correspond to any element of the desired sequence may remain, but in that case, the desired sequence can be obtained if and only if the sum of elements in the suffix is 0. 

Since the sequence of operations in this greedy method and the resulting array correspond one-by-one, so it is sufficient to find the number of possible sequences of operations.

### Dynamic Programming solution:

We use DP (Dynamic Programming). Let `DP[i]` be the number of suffixes of sequences of operations of the greedy algorithm such that the first `i` elements of `A` correspond to the elements of desired sequence. 

Then, for the maximum `j(<i)` such that `A[j] + A[j+1] + ⋯ + A[i] = 0`, it holds that `DP[i] = DP[j] + DP[j+1] + ⋯ + DP[i−1]`. 

For each `k(<j)`, the sum of elements from `A[k]` through `A[j−1]` is equal to that of `A[k]` through `A[i]`(that is `A[k] + ... + A[j-1] = A[k] + ... + A[i]`), and in the greedy algorithm the former correspond to an element, so there is no transition from `DP[i]` to `DP[k]`.

In order to find `j`, compute the cumulative sums of `A` from the left, and for each cumulative sum manage the largest index less than `i` with a data structure like a map. Also, compute the cumulative sums of DP from the left so as to find `DP[i]` in an `O(1)` time each.

The answer is the sum of `DP[k]` for `k(>0)` such that `A[k] + A[k+1] + ⋯ + A[N] = 0`. The total time complexity is `O(NlogN)` or `O(N)`.

### Other ways of finding the answer:

If `A[j] + A[j+1] + ⋯ + A[i] = 0` then `preSum[j-1] = preSum[i]`.

From the editorial, then `DP[i] = DP[j] + DP[j+1] + ⋯ + DP[i−1]`, then using prefix sums `preDP` we get `DP[i] = preDP[i-1] - preDP[j-1]`, then `preDP[i] = preDP[i-1] + DP[i]` which is nothing but `preDP[i] = 2*preDP[i-1] - preDP[j-1]`

Check Japanese Editorial: https://atcoder.jp/contests/abc230/editorial/3082 and https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd

Also https://atcoder.jp/contests/abc230/editorial/3034
