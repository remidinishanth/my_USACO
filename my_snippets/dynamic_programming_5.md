Problems:
* https://codeforces.com/contest/543/submission/11035704

```cpp
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)

const int N = 505;
int a[N];
int z[2][N][N];

int main() {
  int n, bl, bugs, md;
  scanf("%d %d %d %d", &n, &bl, &bugs, &md);
  forn(i, n) scanf("%d", &a[i]);
  z[0][0][0] = 1;

  for(int it = 1; it <= n; it++){
    int i = it & 1;
    for(int j = 0; j <= bl; j++) {
      for(int k = 0; k <= bugs; k++) {
        z[i][j][k] = z[i ^ 1][j][k];
        if (j > 0 && k >= a[it - 1])
          z[i][j][k] += z[i][j - 1][k - a[it - 1]];
        while (z[i][j][k] >= md) z[i][j][k] -= md;
      }
    }
  }

  int ans = 0;
  for(int i = 0; i <= bugs; i++) {
    ans += z[n & 1][bl][i];
    while (ans >= md) ans -= md;
  }
  printf("%d\n", ans);
}
```
