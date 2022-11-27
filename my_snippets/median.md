L1 norm: Suppose we have a set 𝑆 of real numbers. Show that `∑ 𝑠 ∈ S | 𝑠 − 𝑥 |` is minimal if `x` is equal to the median.

![](images/median_1.png)

source: https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-ell-1-norm

### Applications:

![](images/median_3.png)

Solution:

![](images/median_2.png)

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
typedef long long ll;
 
#define N 100000
int n, m, a[N + 1];
vector <int> b[N + 1];
 
int main(int argc, char *argv[]) {
    ios :: sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) {
        if (i > 1 && a[i - 1] != a[i]) b[a[i - 1]].push_back(a[i]);
        if (i < m && a[i + 1] != a[i]) b[a[i + 1]].push_back(a[i]);
    }
    
    ll ans = 0LL, sum = 0LL;
    for (int i = 1; i <= n; ++i) {
        if (!b[i].size()) continue;
        sort(b[i].begin(), b[i].end());
        int y = b[i][b[i].size() >> 1];
        ll before = 0LL, after = 0LL;
        for (int j = 0; j < b[i].size(); ++j) {
            before += abs(i - b[i][j]);
            after += abs(y - b[i][j]);
        }
        ans = max(ans, before - after), sum += before;
    }
    
    cout << sum / 2 - ans << endl;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

source: https://codeforces.com/contest/433/submission/6712939


## Count of Subarrays with Median
TODO: https://leetcode.com/contest/weekly-contest-321/problems/count-subarrays-with-median-k/

Ref: https://stackoverflow.com/questions/73455237/find-the-number-of-subarrays-of-odd-lengths-that-have-a-median-equal-to-k

However 'k' is index and 1 <= k <= n where n is length of array.

We have to find how many subarrays have `arr[k]` as median, also subarray has to be odd length. This is the only hint we need.

Since subarrays are odd length it can be `(arr[k])` or (1 element on left and right), (2 elements on left and right), so on...

We can maintain smaller and bigger arrays of length n and populate them as follows:

```
 if(arr[i] < arr[k])
   smaller[i] = 1;
 else
   smaller[i] = 0;
```

for bigger elements than arr[k]:

```
 if(arr[i] > arr[k])
    bigger[i] = 1;
 else
    bigger[i] = 0;
```

This helps us to find in range `i...j` where `i <= j`, count of smaller and bigger elements with respect to `arr[k]`.

For `arr[k]` to be median in the range `[i,j]`, The following condition has to hold.

```
  Prefix Sum(smaller[j] - smaller[i - 1]) = Prefix Sum(bigger[j] - bigger[i - 1])
```  
  
In other words difference between a number of smaller and bigger elements in the range `[i, j]` is `0`.

we create new array `d` of length `n`, such that

```
  d[i] = smaller[i] - bigger[i]
```

Now problem reduces to finding the number of subarrays having a sum of `0`;

But not all subarrays having sum `0` are useful to us. We don't care about the subarrays that do not include `k`. So,

```
  ans = subarray_sum_zero(1, n, d) -  subarray_sum_zero(1, k - 1, d) - subarray_sum_zero(k + 1, n, d)
```

`subarray_sum_zero` function finds the number of subarrays in array `d`. You can find the subarray sum equals `k` using the map in linear time complexity.

overall runtime complexity is `O(n)` and space complexity is `O(n)`. It should be able pass the tests `n = 1e5`.


The following solution handles for even number too.
```cpp
class Solution {
public:
    vector<int> V;
    long long subsum(int start, int end){
        map<int, int> M;
        int rSum = 0;
        long long res = 0;
        for(int i=start;i<end;i++){
            rSum += V[i];
            if(rSum == 0 || rSum == 1) res++;
            res += M[rSum];
            res += M[rSum - 1];
            M[rSum]++;
        }
        return res;
    }
    
    int countSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), id = -1;
        vector<int> small(n), big(n);
        V = vector<int>(n);
        for(int i=0;i<n;i++){
            V[i] = (nums[i] > k) - (nums[i] < k);
            if(nums[i] == k) id = i;
        }
        return subsum(0, n) - subsum(0, id) - subsum(id+1, n);
    }
};
```
