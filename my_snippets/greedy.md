# Greedy paradigm

An algorithm is said to be greedy if it makes the locally optimal choice at each step with the
hope of eventually reaching the globally optimal solution. In some cases, greedy works—the
solution is short and runs efficiently. A problem must exhibit these two
properties in order for a greedy algorithm to work:

* It has optimal sub-structures. Optimal solution to the problem contains optimal solutions to the sub-problems
* It has the greedy property (difficult to prove in time-critical contest environment!).
If we make a choice that seems like the best at the moment and proceed to solve the
remaining subproblem, we reach the optimal solution. We will never have to reconsider
our previous choices

**Greedy-choice property** A locally optimal choice is globally optimal.

# Problems

## Coin change problem

Given a target amount V cents and a list of denominations of n coins,
i.e. we have coinValue[i] (in cents) for coin types i ∈ [0..n-1], what is the minimum
number of coins that we must use to represent amount V ? 

Example: If n = 4, coinValue = {25, 10, 5, 1} cents6, and
we want to represent V = 42 cents, we can use this Greedy algorithm: Select the largest
coin denomination which is not greater than the remaining amount, i.e. 42-25 = 17 → 17-10
= 7 → 7-5 = 2 → 2-1 = 1 → 1-1 = 0, a total of 5 coins. This is optimal.

However, this greedy algorithm does not work for all sets of coin denominations. Take for
example {4, 3, 1} cents. To make 6 cents with that set, a greedy algorithm would choose 3
coins {4, 1, 1} instead of the optimal solution that uses 2 coins {3, 3}.

### Solution

For the so-called canonical coin systems, a greedy algorithm of picking the largest denomination of coin which is not greater than the remaining amount to be made will produce the optimal result.

In order to decide whether the coin system `𝑐1=1 < 𝑐2 < 𝑐3 < …` is canonical, it suffices to check only for each 𝑚 whether the greedy solution for ⌈𝑐{𝑚+1}/𝑐𝑚⌉𝑐𝑚 is optimal. source: [Stackoverflow](https://math.stackexchange.com/questions/3121896/what-property-of-a-coin-system-makes-it-canonical)

## Courses [duration, lastDay]
There are n different online courses numbered from 1 to n. You are given an array courses where `courses[i] = [duration_i, lastDay_i]` indicate that the ith 
course should be taken continuously for duration_i days and must be finished before or on lastDay_i.

You will start on the 1st day and you cannot take two or more courses simultaneously.

Return the maximum number of courses that you can take.

[[100,200], [200,1300], [1000,1250], [2000,3200]] -> `3` [[100, 200], [200, 1300], [2000, 3200]]

[[5,5], [4,6], [2,6]] -> `2` [[4,6], [2,6]]

source: <https://leetcode.com/problems/course-schedule-iii/>

### Solution:

Sort the courses by end time, now loop through the sorted list while maintaining a priority queue storing the duration_i,  greedily remove the largest-length 
course until the total duration.

Clearly, this greedy choice makes the number of courses used maximal for each K. When considering potential future K, 
there's never a case where we preferred having a longer course to a shorter one, so indeed our greedy choice dominates all other candidates.

```python
import heapq

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        courses.sort(key= lambda x: x[1])
        pq = []
        time_taken = 0
        for c in courses:
            time_taken += c[0]
            heapq.heappush(pq, -c[0])
            while time_taken > c[1]:
                time_taken += heapq.heappop(pq)  # Pop and return the smallest item from the heap, hence using negative values
        return len(pq)
```

### ABC 216 G 01 - Sequence

![](images/abc216g.png)

source: https://atcoder.jp/contests/abc216/tasks/abc216_g

```cpp
template<class T> struct BIT {
    int n; vector<T> data;
    void init(int _n) { n = _n; data.resize(n); }
    void add(int p, T x) { for (++p;p<=n;p+=p&-p) data[p-1] += x; }
    T sum(int l, int r) { return sum(r+1)-sum(l); }
    T sum(int r) { T s = 0; for(;r;r-=r&-r) s+=data[r-1]; return s; }
    int lower_bound(T sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1<<25; pw; pw >>= 1) {
            int npos = pos+pw;
            if (npos <= n && data[npos-1] < sum)
                pos = npos, sum -= data[pos-1];
        }
        return pos;
    }
};

BIT<int> tree;


int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<int>> V;
    for(int i=0;i<m;i++){
        int l, r, x; scanf("%d %d %d", &l, &r, &x);
        V.push_back({r,l, x});
    }
    sort(V.begin(), V.end());
    set<int> S;
    for(int i=1;i<=n;i++) S.insert(-i);
    tree.init(n+1);
    for(auto v:V){
        int r = v[0], l = v[1], x = v[2];
        debug() << imie(l) imie(r) imie(x);
        while(tree.sum(l, r) < x){
            int i = *S.lower_bound(-r);
            tree.add(-i, 1);
            S.erase(i);
        }
    }
    for(int i=1;i<=n;i++) printf("%d ", tree.sum(i, i));
    printf("\n");
    return 0;
}
```

Instead of using `set` and `lower_bound`, we can also use at stack to maintain the unused zeros 

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/fenwicktree.hpp>
using namespace std;

int main()
{
    int N, M;
    cin>>N>>M;
    vector<int> L(M), R(M), X(M);
    for (int i=0; i<M; i++)
    {
        cin >> L[i] >> R[i] >> X[i];
        L[i]--;
    }

    vector<int> I(M);
    for (int i=0; i<M; i++) I.push_back(i);
    sort(I.begin(), I.end(), [&](int x, int y){return R[x]<R[y];});

    vector<int> A(N);
    atcoder::fenwick_tree<int> FT(N);
    //  Position where 1 can be written
    vector<int> Q;
    //  Minimum position not added to Q
    int q = 0;
    for (int i: I)
    {
        for (; q<R[i]; q++)
            Q.push_back(q);

        //  Number of 1s that must be written
        int n = X[i]-FT.sum(L[i], R[i]);
        for (int j=0; j<n; j++)
        {
            int p = Q.back();
            Q.pop_back();

            A[p] = 1;
            FT.add(p, 1);
        }
    }

    for (int i=0; i<N; i++) cout << (i==0 ? "" : " ") << A[i];
    cout << endl;
}
```

### CF 753 Div 3 G

You are given array `ai` and array `bi`, We will need to remove `m` items from each of `i` (given that `ai + bi <= m`)  we want to minimize the absolute difference after removing  `| sum(ai) - sum(bi) |`

source: https://codeforces.com/contest/1607/problem/G

![](images/cf753_div3_g_7_nov.png)

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pii> dishes(n);
        ll balance = 0;
        ll max_a = 0, max_b = 0;
        ll total_eat = static_cast<long long>(n) * m;

        for (int i = 0; i < n; i++) {
            cin >> dishes[i].first >> dishes[i].second;
            balance += dishes[i].first - dishes[i].second;
            max_a += min(m, dishes[i].first);
            max_b += min(m, dishes[i].second);
        }
        ll max_delta = 2 * max_a - total_eat, min_delta = total_eat - 2 * max_b;
        ll min_a = total_eat - max_b;

        ll eat_a;
        if (balance < 0) {
            eat_a = min_a;
            if (balance - min_delta >= 0)
                eat_a = min(max_a, (total_eat + balance + 1) / 2);
        } else {
            eat_a = max_a;
            if (balance - max_delta <= 0)
                eat_a = min(max_a, (total_eat + balance + 1) / 2);
        }
        ll ans = abs(balance - 2 * eat_a + total_eat);

        cout << ans << '\n';
        ll rest_a = eat_a - min_a;
        for (int i = 0; i < n; i++) {
            ll cur_a = 0;
            if (dishes[i].second < m)
                cur_a += m - dishes[i].second;
            ll add = min(rest_a, min(m - cur_a, dishes[i].first - cur_a));
            cur_a += add;
            rest_a -= add;
            cout << cur_a << ' ' << m - cur_a << '\n';
        }
    }
}
```

### LeetCode 134. Gas Station

There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int i, j, n = gas.size();

        /*
         * If we start from i and stop before station x -> no station k from i + 1 to x - 1 can reach x.
         * Bcoz if so, i can reach k and k can reach x, then i reaches x. Contradiction.
         * Thus i can jump directly to x instead of i + 1, bringing complexity from O(n^2) to O(n).
         */
        // start from station i
        for (i = 0; i < n; i += j) {
            int gas_left = 0;
            // forward j stations
            for (j = 1; j <= n; j++) {
                int k = (i + j - 1) % n;
                gas_left += gas[k] - cost[k];
                if (gas_left < 0)
                    break;
            }
            if (j > n)
                return i;
        }

        return -1;
    }
};
```

Another solution:

Let i be the index such that the the partial sum `prefix_sum[i] = gas[0]-cost[0]+gas[1]-cost[1]+...+gas[i]-cost[i]` is the smallest, 
then the start position should be start=i+1 ( start=0 if i=n-1). 

Consider any other partial sum, for example,

`gas[0]-cost[0]+gas[1]-cost[1]+...+gas[i]-cost[i]+gas[i+1]-cost[i+1]` then `gas[i+1]-cost[i+1]>=0` because `prefix_sum[i]` is the smallest.

From this same reasoning, we can observe that 

```
 gas[i+1]-cost[i+1]>=0
 gas[i+1]-cost[i+1]+gas[i+2]-cost[i+2]>=0
 .......
 gas[i+1]-cost[i+1]+gas[i+2]-cost[i+2]+...+gas[n-1]-cost[n-1]>=0
```
 
Now what about the wrap around? If `total[i] >= 0`, then any wrap around is greater than zero is `prefix_sum[i]` is the smallest.

```
total[i] = gas[i+1]-cost[i+1]+...+gas[n-1]-cost[n-1] + gas[0]-cost[0]+gas[1]-cost[1]+...+gas[j]-cost[j]>=0
```

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int prefix_sum = 0, min_pref = 0, ans = 0;
        for(int i=0;i<gas.size();i++){
            prefix_sum += gas[i] - cost[i];
            if(prefix_sum < min_pref){
                ans = i+1; // start from next station
                min_pref = prefix_sum;
            }
        }
        if(prefix_sum < 0) return -1; // no feasible solution
        return ans;
    }
};
```

REF: https://leetcode.com/problems/gas-station/discuss/42572/Proof-of-%22if-total-gas-is-greater-than-total-cost-there-is-a-solution%22

TODO: https://leetcode.com/problems/split-array-into-consecutive-subsequences/
