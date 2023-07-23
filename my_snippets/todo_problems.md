* https://open.kattis.com/problems/antiques

Today

* https://atcoder.jp/contests/abc216/tasks/abc216_g from https://codeforces.com/blog/entry/94366 and https://www.cs.huji.ac.il/course/2002/dast/slides/BellmanFord.pdf
* https://www.topcoder.com/thrive/articles/Geometry%20Concepts%20part%203:%20Using%20Geometry%20in%20Topcoder%20Problems
* https://atcoder.jp/contests/abc219/tasks/abc219_g
* https://docs.google.com/document/d/1kmHSpaZCWv3sKWDmWvUXLvWxKTZkpn15NP8h7PEURBs/edit
* Strings https://stackoverflow.com/a/57516363/8352968
Solution: ![image](https://user-images.githubusercontent.com/19663316/145713320-2bce141e-d0b0-46d8-8948-c84bdb308528.png)
* Nice question: https://leetcode.com/discuss/interview-question/981597/rubrik-oa-question-minimum-operations-to-transform-array


* https://leetcode.com/problems/data-stream-as-disjoint-intervals/solutions/2866931/data-stream-as-disjoint-intervals/?orderBy=most_votes


* https://leetcode.com/contest/weekly-contest-330/problems/count-increasing-quadruplets/

* https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/description/

### 2552. Count Increasing Quadruplets

Given a 0-indexed integer array nums of size n containing all numbers from 1 to n, return the number of increasing quadruplets.

A quadruplet `(i, j, k, l)` is increasing if:

```
0 <= i < j < k < l < n, and
nums[i] < nums[k] < nums[j] < nums[l].
```

Constraints:
```
4 <= nums.length <= 4000
1 <= nums[i] <= nums.length
```

All the integers of nums are unique. nums is a **permutation.**

```cpp

// left[i][a[j]]  means the count of "until i, < a[j]"
// right[j][a[i]] means the count of "unitl j, > a[i]"

class Solution {
public:
    long long countQuadruplets(vector<int>& a) {
        long long res = 0;
        int n = a.size();
        vector<vector<int>> left(n, vector<int>(n+1, 0));
        vector<vector<int>> right(n, vector<int>(n+1, 0));
        for (int i = 1; i < n; ++i) {
            // new array will based on the old array
            left[i] = left[i-1];
            // update all the elements greater than a[i-1]
            for (int j = a[i-1] + 1; j <= n; ++j)
                left[i][j]++;
        }
        for (int i = n-2; i >= 0; --i) {
            right[i] = right[i+1];
            for (int j = 0; j < a[i+1]; ++j)
                right[i][j]++;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = n-1; j > i; --j) {
                if (a[i] <= a[j]) continue;
                // i < j && a[i] > a[j] -- these are actual nums[k] < nums[j]
                // left[i][a[j]] means the count of "until i, < a[j]"
                // right[j][a[i]] means the count of "unitl j, > a[i]"
                res += left[i][a[j]] * right[j][a[i]];
            }
        }
        return res;
    }
};
```

**Intuition**:

`dp[j]` stores the count of all valid triplets `(i, j, k)` that satisfies `i < j < k` and `nums[i] < nums[k] < nums[j]` when using the current number as the role `j` in Quadruplets.

During iteration, we also update previous `dp[i]` by keeping track of the amount of smaller numbers in front of each new value. 

If `nums[j] < nums[i]`, the new value is a potential `k` for `j` in the future, so add its previous_small to the `dp[i]`.

```py
class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0] * n
        ans = 0
        for j in range(n):
            prev_small = 0
            for i in range(j):
                if nums[j] > nums[i]:
                    prev_small += 1
                    ans += dp[i]
                elif nums[j] < nums[i]:
                    dp[i] += prev_small
        return ans
```
