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
