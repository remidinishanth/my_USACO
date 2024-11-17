### Min subarray with sum >= threshold

Probably the following is the cleanest way of writing sliding window algo:

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, right = 0, sumOfCurrentWindow = 0;
        int res = INT_MAX;

        for(right = 0; right < nums.size(); right++) {
            sumOfCurrentWindow += nums[right];

            while (sumOfCurrentWindow >= target) {
                res = min(res, right - left + 1);
                sumOfCurrentWindow -= nums[left];
                left++;
            }
        }

        return res == INT_MAX ? 0 : res;
    }
};
```

This is more clear in terms of explanation
```cpp
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int ans = INT_MAX;
        for(int i=0;i<n;i++){
            sum += nums[i];
            if(sum < target) continue;
            while(sum - nums[left] >= target){
                sum -= nums[left++];
            }
            ans = min(ans, i - left+1);
        }
        if(ans == INT_MAX) return 0;
        return ans;
    }
```
