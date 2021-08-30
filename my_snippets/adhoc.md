TODO: https://codeforces.com/contest/1533/problem/E and https://codeforces.com/contest/1533/problem/F

solutions: https://www.youtube.com/watch?v=ll-UwTagrU0

TODO: https://leetcode.com/problems/three-equal-parts/

Done https://atcoder.jp/contests/agc003/tasks/agc003_b Solution: https://img.atcoder.jp/data/agc/003/editorial.pdf

Divide and Conquer: https://leetcode.com/problems/beautiful-array/solution/

https://stackoverflow.com/questions/52244676/given-an-array-you-have-to-find-the-max-possible-two-equal-sum

DSU https://leetcode.com/problems/rank-transform-of-a-matrix/discuss/909212/C%2B%2B-with-picture

Strings https://codeforces.com/contest/1560/submission/126302860 Nice solution: Explanation: https://www.youtube.com/watch?v=kCMGWkJIILQ

TODO: Problems of this contest https://codeforces.com/contest/1549/submission/124567744 - D nice problem with gcd over array

Missing coin sum - https://cses.fi/problemset/task/2183, Extensions -> Math, Greedy - https://leetcode.com/problems/patching-array/discuss/280183/Detailed-Explanation-with-Example - Nice idea

```cpp
ll l = 0, r = 0;
ll ans = -1;
for(int v:V){
    if(v + l > r + 1){
        ans = r+1;
        break;
    }
    r += v;
}
```

Array filling - https://atcoder.jp/contests/abc214/editorial/2446
