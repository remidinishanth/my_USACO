https://atcoder.jp/contests/abc168/tasks/abc168_f

https://leetcode.com/problems/rectangle-area-ii/solution/, simple implementation: https://leetcode.com/problems/rectangle-area-ii/discuss/138206/C%2B%2B-10-lines-normalized-canvas

### Dealing with pairs of numbers.

Ref: https://atcoder.jp/contests/abc245/tasks/abc245_e

We are given chocolates and boxes which are rectangular in shape with length and width, a `chocolate[i]` fits in `box[j]` only if `chocolate[i].length <= box[i].length && chocolate[i].width <= box[i].width`. Find whether all chocolates fits in the given boxes.

#### Solution

First, make a list containing all the chocolates and all the boxes, and sort it in the decreasing order of their widths. 

If there is a chocolate and a box with the same width, order the box first. 
Prepare an empty integer sequence multiset `S=()`. 

Inspect each element as follows. 
* If the inspected element is a box `(Ci ,Di)` Add `Di` to `S`. 
* If the inspected element is a chocolate `(Ai, Bi)` Remove the smallest element of S greater than or equal to `Bi`. If there is no element to remove, the answer is No. 

If all the elements were successfully inspected, then the answer is Yes.

```cpp
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::array<int, 2>> box(m), choco(n);
    for (int i = 0; i < n; i++) {
        std::cin >> choco[i][0];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> choco[i][1];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> box[i][0];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> box[i][1];
    }
        
    std::sort(choco.begin(), choco.end(), std::greater());
    std::sort(box.begin(), box.end(), std::greater());
    
    std::multiset<int> s;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < m && box[j][0] >= choco[i][0]) {
            s.insert(box[j][1]);
            j++;
        }
        auto it = s.lower_bound(choco[i][1]);
        if (it == s.end()) {
            std::cout << "No\n";
            return 0;
        }
        s.erase(it);
    }
    
    std::cout << "Yes\n";
    
    return 0;
}
```
