Ferris Wheel https://cses.fi/problemset/task/1090/

```cpp
int main() {
    int n, x; scanf("%d %d", &n, &x);
    multiset<int> S;
    REP(i, n){
        int y; scanf("%d", &y);
        S.insert(y);
    }
    int ans = 0;
    while(!S.empty()){
        ans++;
        auto it = S.begin();
        int a = *it;
        S.erase(it);
        it = S.upper_bound(x - a);
        if(it != S.begin()){
            it--;
            S.erase(it);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

Using two pointers

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

// Variables used for the current problem
int n, x, p[maxn], i, j, ans;
// Keeps track of the number of children who have had their own gondola
bool have_gondola_yet[maxn];

void solve() {
    cin >> n >> x;
    for (int i = 0; i < n; ++i) cin >> p[i];
    sort(p, p + n);
    i = 0;
    j = n - 1;
    while (i < j) {
        if (p[i] + p[j] > x) {
            // If the total weight of two children exceeds x
            // Then we move to the lighter child.
            --j;
        } else { // If it satisfies the condition.
            ++ans; // Increment the number of gondolas used
            // Mark that they have had their gondola
            have_gondola_yet[i] = have_gondola_yet[j] = true;
            ++i;
            --j; //Move to the next children.
        }
    }
    for (int i = 0; i < n; ++i) {
        // Calculate the number of children not having gondolas yet
        // to get the total number of gondolas needed for the problem.
        ans += have_gondola_yet[i] == false;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```

Distinct Value Queries https://cses.fi/problemset/task/1734

Sort the queries in a specific order before answering them.

Answer queries in order of the right indices. Use a BIT to keep track of indices that contain distinct values. For every value, update the latest index for it and answer all queries at the current index. This ensures later indices are included in the BIT to accurately answer queries.

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MX = 4e5 + 5;

int bit[MX];
int n, q, sol[MX];
vector<pair<int, int>> query[MX];
vector<int> x(MX);
map<int, int> fst;

int qry (int i) {
	int res = 0;
	for (; i; i -= i&(-i)) {
		res += bit[i];
	}
	return res;
}

void upd (int i, int val) {
	for (; i <= n; i += i&(-i)) {
		bit[i] += val;
	}
}

int main () {
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		query[a].push_back(make_pair(b, i));
	}
	for (int i = n; i >= 1; i--) {
		int z = x[i - 1];
		if (fst.count(z)) upd(fst[z], -1);
		fst[z] = i;
		upd(i, 1);
		for (auto t : query[i]) {
			sol[t.second] = qry(t.first);
		}
	}
	for (int i = 0; i < q; i++) {
		cout << sol[i] << '\n';
	}
}
```
