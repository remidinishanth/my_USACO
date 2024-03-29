Problems:
* https://codeforces.com/contest/543/submission/11035704

```cpp
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

const int N = 505;
int a[N];
int z[2][N][N];

int main() {
    int n, bl, bugs, md;
    scanf("%d %d %d %d", & n, & bl, & bugs, & md);
    forn(i, n) scanf("%d", & a[i]);
    z[0][0][0] = 1;

    for (int it = 1; it <= n; it++) {
        int i = it & 1;
        for (int j = 0; j <= bl; j++) {
            for (int k = 0; k <= bugs; k++) {
                z[i][j][k] = z[i ^ 1][j][k];
                if (j > 0 && k >= a[it - 1])
                    z[i][j][k] += z[i][j - 1][k - a[it - 1]];
                while (z[i][j][k] >= md) z[i][j][k] -= md;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= bugs; i++) {
        ans += z[n & 1][bl][i];
        while (ans >= md) ans -= md;
    }
    printf("%d\n", ans);
}
```

* Burst Ballons

source: https://leetcode.com/problems/burst-balloons/

Key idea: In the range `[i:j]`, we want to choose the last ballon which we want to burst, call it `k`, then we get `nums[i-1]*nums[k]*nums[j+1]` coins.

```cpp
int maxCoins(vector <int> & nums) {
    int N = nums.size();
    nums.insert(nums.begin(), 1);
    nums.insert(nums.end(), 1);

    // dp[i][j] is the maximum # of coins that can be obtained
    // by popping balloons only in the range [i,j]
    vector<vector<int>> dp(nums.size(), vector<int> (nums.size(), 0));

    // build up from shorter ranges to longer ranges
    for (int len = 1; len <= N; ++len) {
        for (int start = 1; start <= N - len + 1; ++start) {
            int end = start + len - 1;
            // calculate the max # of coins that can be obtained by
            // popping balloons only in the range [start,end].
            // consider all possible choices of final balloon to pop
            int bestCoins = 0;
            for (int final = start; final <= end; ++final) {
                int coins = dp[start][final - 1] + dp[final + 1][end]; // coins from popping subranges
                coins += nums[start - 1] * nums[final] * nums[end + 1]; // coins from final pop
                if (coins > bestCoins) bestCoins = coins;
            }
            dp[start][end] = bestCoins;
        }
    }
    return dp[1][N];
}
```

TODO: https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247567/JavaC%2B%2BPython-DP

TODO: https://leetcode.com/problems/k-inverse-pairs-array/


### Leetcode Number of Playlists problem

https://leetcode.com/problems/number-of-music-playlists/description/

Your music player contains n different songs. You want to listen to goal songs (not necessarily different) during your trip. To avoid boredom, you will create a playlist so that:

* Every song is played at least once.
* A song can only be played again only if `k` other songs have been played.

Given `n`, `goal`, and `k`, return the number of possible playlists that you can create. Since the answer can be very large, return it modulo `10^9 + 7`.


#### Solution

We're using a dynamic programming (DP) table `dp[i][j]` to represent the number of possible playlists of length `i` containing exactly `j` unique songs. 

Our goal is to calculate `dp[goal][n]`, which represents the number of ways we can make a playlist of length `goal` using exactly `n` unique songs.


To generate the DP table, we need to define the initial conditions:

* `dp[0][0]=1` This represents that there's exactly one way to create a playlist of length `0` with `0` unique songs, which is essentially an empty playlist.
* For all `i<j`, `dp[i][j]=0`. This makes sense because we can't form a playlist of length `i` with `j` unique songs when `i<j`. There just aren't enough slots in the playlist to accommodate all the unique songs.


```cpp
class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        int md = 1e9 + 7;
        vector<vector<long>> dp(goal+1, vector<long>(n+1));

        dp[0][0] = 1;
        for(int i=0;i<=goal;i++){
            for(int j=1;j<=min(i, n);j++){
                // i-th song is new
                dp[i][j] = (dp[i-1][j-1] * (n - (j - 1))) % md;

                // repeat previously played song
                // We can only repeat if there are at least k+1 unique songs - pigeon-hole principle
                // for every possible way, we can choose one of (j - k) song in last position
                if(j > k){
                    dp[i][j] = (dp[i][j] + dp[i-1][j] * (j - k)) % md;
                }
            }
        }
        return dp[goal][n];
    }
};
```

