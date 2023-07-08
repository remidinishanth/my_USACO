Todo: https://leetcode.com/problems/put-marbles-in-bags/editorial/

Solution:

<img width="826" alt="image" src="https://github.com/remidinishanth/my_USACO/assets/19663316/9bc02752-82e0-43c2-aaf2-1853c42b6c57">

<img width="801" alt="image" src="https://github.com/remidinishanth/my_USACO/assets/19663316/0ce5671e-bdcd-4f7e-9fe1-3e5aa96ede7e">

```cpp
    long long putMarbles(vector<int>& weights, int k) {
        // We collect and sort the value of all n - 1 pairs.
        int n = weights.size();
        vector<int> pairWeights(n - 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            pairWeights[i] += weights[i] + weights[i + 1];
        }
        
        sort(pairWeights.begin(), pairWeights.end());
        
        // Get the difference between the largest k - 1 values and the 
        // smallest k - 1 values.
        long long answer = 0;
        for (int i = 0; i < k - 1; ++i) {
            answer += pairWeights[n - 2 - i] - pairWeights[i];
        }

        return answer;
    }
```
