# Dynamic Programming

Dynamic Programming (from now on abbreviated as DP) is perhaps the most challenging
problem-solving technique among Divide and Conquer, Greedy and complete search paradigms.

The key skills that we have to develop in order to master DP are the abilities to determine the problem states and to determine the relationships or transitions between current
problems and their sub-problems.

You can think in terms of 5 steps as Erik Demaine describes
1. Define Subproblems
2. Relate Subproblems solutions recursively
    * Topological order on subproblems to guarantee acyclic relation, subproblems relations should form a DAG
3. Identify Base Cases - State solitions for all (reachable) independent subproblems where relations break down
4. Solve the original problem
5. Analyze the running time

Existence of recursive solution implies that subproblems are decomposable(this property is often called optimal substructure property, it is a property of recursion, not just DP).

Reusing Subproblem Solutions
* **Top down**: record subproblem solutions in a memo and re-use (recursion+memoization)
   * easy to prove correct
* **Bottom up**: solve subproblems in topological sort order(usually via loops)

### Generic DP algorithm(top-down)

```python
memo = {}
def f(subprob):
   if subprob not in memo:
      memo[subprob] = base or recursive relation
   return memo[subprob]
return orginial
```

### Subproblem design trick

Subproblem design is the hard part, when we are given sequences, often use
- prefixes S[:i] for all i, O(n)
- suffiixes S[i:] for all i, O(n)
- substring S[i:j] for all i<j, O(n^2)
