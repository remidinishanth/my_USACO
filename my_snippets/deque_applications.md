**Problem** There are `n` robots driving along an OX axis. There are also two walls: one is at coordinate `0` and one is at coordinate `m`.

The i-th robot starts at an integer coordinate `x𝑖 (0 < x𝑖 <m)` and moves either left (towards the 0) or right with the speed of 1 unit per second. No two robots start at the same coordinate.

Whenever a robot reaches a wall, it turns around instantly and continues his ride in the opposite direction with the same speed.

Whenever several robots meet at the same integer coordinate, they collide and explode into dust. Once a robot has exploded, it doesn't collide with any other robot. Note that if several robots meet at a non-integer coordinate, nothing happens.

For each robot find out if it ever explodes and print the time of explosion if it happens and −1 otherwise.

**Input**

The first line contains a single integer `t (1 ≤ t ≤ 1000)` — the number of testcases.

Then the descriptions of `t` testcases follow.

The first line of each testcase contains two integers `n` and `m` `(1≤ n ≤3⋅10^5; 2≤ m ≤10^8)` — the number of robots and the coordinate of the right wall.

The second line of each testcase contains `n` integers `𝑥1,𝑥2,…,𝑥n (0 < x𝑖 < m)` — the starting coordinates of the robots.

The third line of each testcase contains 𝑛 space-separated characters `'L'` or `'R'` — the starting directions of the robots (`'L'` stands for left and `'R'` stands for right).

All coordinates `x𝑖` in the testcase are distinct.

**Example**

Testcase
```
7 12
1 2 3 4 9 10 11
R R L L R R R
```

![image](https://user-images.githubusercontent.com/19663316/118408544-a8a14d80-b6a3-11eb-96d0-f1539b8717e2.png)


Solution: https://codeforces.com/contest/1525/submission/116334549

Consider odd and even places separately because when they meet, they cross each other at non-integer coordinates. If something is moving left and it is not colliding with any other robot, consider as if it is starting from `-x` and moving `R`. If a robot moves to `R` and is at `x1` and another robot moves to `L` and is at `x2 (x2 > x1)`, then they meet in `(x2-x1)/2` time, because their relative velocity is `2`.

Consider robots with same parity: Once robots which are moving left and moving right collide, we will have robots moving only to one direction, assume that we consider all robots moving to the right. Now consider the rightmost two robots say they are at `y` and `x (y < x)` respectively. Then in `(m-x)` time, robot at `x` reaches `m` and robot at `y` reaches `y + x - m` which is less than `m`, now robot at `y + x - m` is moving `R` and robot at `m` is moving left, they collide
in `(m - (y + x - m))/2` time, because their relative velocity is `2`. So they meet in `m - x + (x-y)/2` time. Or simply you can think that robot which is at `x` is starting at `m + (m - x)` and moving `L`.
```cpp
/*
    author:  Maksim1744
    created: 16.05.2021 11:10:10
*/

#include "bits/stdc++.h"

using namespace std;

using ll = long long;
using ld = long double;

#define mp   make_pair
#define pb   push_back
#define eb   emplace_back

#define sum(a)     ( accumulate ((a).begin(), (a).end(), 0ll))
#define mine(a)    (*min_element((a).begin(), (a).end()))
#define maxe(a)    (*max_element((a).begin(), (a).end()))
#define mini(a)    ( min_element((a).begin(), (a).end()) - (a).begin())
#define maxi(a)    ( max_element((a).begin(), (a).end()) - (a).begin())
#define lowb(a, x) ( lower_bound((a).begin(), (a).end(), (x)) - (a).begin())
#define uppb(a, x) ( upper_bound((a).begin(), (a).end(), (x)) - (a).begin())

template<typename T>             vector<T>& operator--            (vector<T> &v){for (auto& i : v) --i;            return  v;}
template<typename T>             vector<T>& operator++            (vector<T> &v){for (auto& i : v) ++i;            return  v;}
template<typename T>             istream& operator>>(istream& is,  vector<T> &v){for (auto& i : v) is >> i;        return is;}
template<typename T>             ostream& operator<<(ostream& os,  vector<T>  v){for (auto& i : v) os << i << ' '; return os;}
template<typename T, typename U> pair<T,U>& operator--           (pair<T, U> &p){--p.first; --p.second;            return  p;}
template<typename T, typename U> pair<T,U>& operator++           (pair<T, U> &p){++p.first; ++p.second;            return  p;}
template<typename T, typename U> istream& operator>>(istream& is, pair<T, U> &p){is >> p.first >> p.second;        return is;}
template<typename T, typename U> ostream& operator<<(ostream& os, pair<T, U>  p){os << p.first << ' ' << p.second; return os;}
template<typename T, typename U> pair<T,U> operator-(pair<T,U> a, pair<T,U> b){return mp(a.first-b.first, a.second-b.second);}
template<typename T, typename U> pair<T,U> operator+(pair<T,U> a, pair<T,U> b){return mp(a.first+b.first, a.second+b.second);}
template<typename T, typename U> void umin(T& a, U b){if (a > b) a = b;}
template<typename T, typename U> void umax(T& a, U b){if (a < b) a = b;}

#ifdef HOME
#define SHOW_COLORS
#include "C:/C++ libs/print.cpp"
#else
#define show(...) void(0)
#define mclock    void(0)
#define shows     void(0)
#define debug  if (false)
#endif

void test_case(int test) {
    int n, m;
    cin >> n >> m;
    vector<int> ans(n, -1);
    vector<pair<pair<int, char>, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first.first;
        v[i].second = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first.second;
    }
    sort(v.begin(), v.end());
    vector<deque<pair<int, int>>> cur(2);
    for (auto [xd, i] : v) {
        auto [x, d] = xd;
        if (d == 'R') {
            cur[x % 2].eb(x, i);
        } else {
            if (!cur[x % 2].empty()) {
                auto [xx, ii] = cur[x % 2].back();
                cur[x % 2].pop_back();
                ans[i] = ans[ii] = abs(x - xx) / 2;
            } else {
                cur[x % 2].emplace_front(-x, i);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        while (cur[i].size() >= 2) {
            auto [x, j] = cur[i].back();
            cur[i].pop_back();
            auto [xx, jj] = cur[i].back();
            cur[i].pop_back();
            ans[j] = ans[jj] = (m - x) + (x - xx) / 2;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T;
    cin >> T;
    for (int test = 1; test <= T; ++test) {
        test_case(test);
    }

    return 0;
}
```
