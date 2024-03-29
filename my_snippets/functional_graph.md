Directed graphs in which every vertex has exactly one outgoing edge.

source: https://usaco.guide/silver/func-graphs?lang=cpp

### Problem:

https://leetcode.com/contest/weekly-contest-274/problems/maximum-employees-to-be-invited-to-a-meeting/

```python
class Solution:
    def maximumInvitations(self, f: List[int]) -> int:
        # functional graph
        # either table consists of one cycle
        # or multiple (two chains + cycle of two)
        # bidirectional edges 
        edges = defaultdict(list)
        n = len(f)
        for i in range(n):
            edges[f[i]].append(i)
            edges[i].append(f[i])
        seen = [False]*n
        self.l = 0
        def dfs(v, p, d):
            self.l = max(self.l, d)
            seen[v] = True
            for i in edges[v]:
                if i != p and not seen[i]:
                    dfs(i, v, d+1)
        total = 0
        best = 0
        for i in range(n):
            if seen[i]:
                continue
            if f[f[i]] == i: # cycle of two
                self.l = 0
                dfs(i, f[i], 0)
                cur = self.l
                self.l = 0
                dfs(f[i], i, 0)
                cur += self.l
                total += cur+2
        for i in range(n):
            if not seen[i]:
                dfs(i, i, 0)
                l = [i]
                j = i
                cur = 0
                s = set()
                s.add(i)
                while True:
                    j = f[j]
                    if j in s:
                        while True:
                            cur += 1
                            if l.pop() == j:
                                break
                        best = max(best, cur)
                        break
                    s.add(j)
                    l.append(j)
        return max(total, best)
```

### Planet Queries 2

https://usaco.guide/problems/cses-1160-planets-queries-ii/solution

### Find the largest cycle in graph with atmost one edge

https://leetcode.com/problems/longest-cycle-in-a-graph/description/

```cpp
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        int ans = -1;
        vector<bool> visited(n);
        for(int i=0;i<n;i++){
            if(visited[i]) continue;
            set<int> S; // to find nodes in the current cycle
            int now = i;
            while(!visited[now] && S.count(now) == 0){
                visited[now] = true;
                S.insert(now);
                now = edges[now];
                if(now == -1) break; // no outgoing edge
            }
            if(S.count(now) == 1){
                int last = now;
                int cnt = 1;
                while(edges[now] != last){
                    now = edges[now];
                    cnt++;
                }
                ans = max(ans, cnt);
            }
        }
        return ans;
    }
};
```

We can also solve it by using Kahn's algorithm

* In a directed acyclic graph, we can use Kahn's algorithm to get the topological ordering. 
* Kahn’s algorithm works by keeping track of the number of incoming edges into each node (indegree). 
* It works by repeatedly visiting the nodes with an indegree of zero and deleting all the edges associated with it leading to a decrement of indegree for the nodes whose incoming edges are deleted. 
* This process continues until no element with zero indegree can be found.

If all of the nodes are visited during Kahn's algorithm, the graph has no cycle.

After completing Kahn's algorithm, we iterate over all the unvisited nodes to determine the length of the longest cycle. 

### In functional graph, find number of nodes visited from each vertex

#### Solution:

For each node, check it's next nodes.

* We push all nodes in a stack,
until a node we have seen,
and pop nodes from stack one by one and assign it's result.

* If we meet a node j in seen set,
it means we hit a cycle.

* Calculate the position j in the stack,
we can know the length k of cycle,
then assign k to all nodes in the cycle.

For other nodes in stack,
we pop out one by one,
and we can have `res[j] = res[edges[j]] + 1`

Finally return res.

No special skill,
no count of degrees,
no topo sort,
no recursive dfs.

```cpp
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        vector<int> res(n);
        for (int i = 0, j = 0; i < n; j = ++i) {
            set<int> seen;
            vector<int> s;
            while (!seen.count(j) && res[j] == 0) {
                seen.insert(j);
                s.push_back(j);
                j = edges[j];
            }
            if (seen.count(j)) { // hit the cycle
                int k = distance(find(s.begin(), s.end(), j), s.end());
                for (j = 0; j < k; ++j) {
                    res[s.back()] = k;
                    s.pop_back();
                }
            }
            while (!s.empty()) {
                j = s.back();
                s.pop_back();
                res[j] = res[edges[j]] + 1;
            }
        }
        return res;
    }
```
