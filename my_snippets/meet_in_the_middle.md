## 4sum (popular interview question)

Given A, an array of integers, find out if there are any four numbers in the array that sum up to zero (the same element can be used multiple times). 

For example given `A = [2, 3, 1, 0, -4, -1]` a solution is `3 + 1 + 0 - 4 = 0` or `0 + 0 + 0 + 0` = 0.

### Solution

The naive algorithm checks all four number combinations. This solution takes `O(n^4)`.

A slightly improved algorithm brute forces through all `n^3` three number combinations and efficiently checks if `-(a + b + c)` is in the original array using a hash table. This algorithm is `O(n^3)`.

If `a + b + c + d = 0`, then `a + b = -(c + d)` this is what meet in the middle does. Now we store n^2 sums `a + b` in a hash set S. Then iterate through all `n^2` combinations for `c` and `d` and check if S contains `-(c + d)`.

```cpp
def 4sum(A):
  sums = {}
  for a in A:
    for b in A:
      sums[a + b] = (a, b)
 
  for c in A:
    for d in A:
      if -(c + d) in sums:
        print(sums[-(c + d)][0], sums[-(c + d)][1], c, d)
        return
 
  print("No solution.")
```

source: https://www.infoarena.ro/blog/meet-in-the-middle
