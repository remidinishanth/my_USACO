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
