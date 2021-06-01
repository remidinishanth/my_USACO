Given an array of integers, find the minimum number of operations to make it non-increasing, where each operation can increment or decrement one value.

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int N; cin >> N;

    priority_queue<ll> s;
    ll y = 0;

    for(int i = 0; i < N; i++) {
        ll v; cin >> v;

        y += v;

        s.push(-v);
        s.push(-v);

        y += s.top();
        s.pop();

    }

    cout << y << '\n';
    return 0;
}
```

source: ecnerwala https://codeforces.com/blog/entry/90956#comment-794463
