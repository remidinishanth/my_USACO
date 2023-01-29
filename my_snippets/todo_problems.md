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
class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> pre(n);
        vector<vector<LL> > suf(n, vector<LL>(n));
        for(int i = n - 1; i >= 0; --i) {
            int v = nums[i] - 1;
            // numbers less than nums[i]
            for(int j = 0; j <= v; ++j)
                ++suf[i][j];
            // add suf[i] to previous suf[i]
            // used in next iteration
            if(i > 0)
                suf[i - 1] = suf[i];
        }
        LL ans = 0;
        for(int i = 0; i < n; ++i) {
            int v = nums[i] - 1;
            if(i > 0 && v + 1 < n)
                for(int j = i + 1; j + 1 < n; ++j) {
                    int w = nums[j] - 1;
                    if(w > 0 && v > w)
                        ans += pre[w - 1] * suf[j + 1][v + 1];
                }
            for(int j = v; j < n; ++j)
                ++pre[j];
        }
        return ans;
    }
};
```
