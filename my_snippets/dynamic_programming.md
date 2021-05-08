# Dynamic Programming

Dynamic Programming (from now on abbreviated as DP) is perhaps the most challenging
problem-solving technique among Divide and Conquer, Greedy and complete search paradigms.

* Similar in some respects to both divide and conquer and backtracking
* Divide and conquer recap:
   * Split the problem into *independent* subproblems
   * Solve each subproblem recursively
   * Combine the solutions to subproblems into a solution for the given problem
* Dynamic programming:
   * Split the problem into *overlapping* subproblems
   * Solve each subproblem recursively
   * Combine the solutions to subproblems into a solution for the given problem
   * Don’t compute the answer to the same subproblem more than once

The key skills that we have to develop in order to master DP are the abilities to determine the problem states and to determine the relationships or transitions between current
problems and their sub-problems.

You can think in terms of SRT - BOT steps as Erik Demaine describes
1. Define **Subproblems**
2. **Relate** Subproblems solutions recursively
    * **Topological** order on subproblems to guarantee acyclic relation, subproblems relations should form a DAG
3. Identify **Base** Cases - State solitions for all (reachable) independent subproblems where relations break down
4. Solve the **original** problem
5. Analyze the running **time**

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

Dynamic programming formulation
```cpp
map<problem, value> memory;

value dp(problem P) {
  if (is_base_case(P)) {
    return base_case_value(P);
  }
  
  if (memory.find(P) != memory.end()) {
    return memory[P];
  }
  
  value result = some value;
  for (problem Q in subproblems(P)) {
    result = combine(result, dp(Q));
  }
  
  memory[P] = result;
  return result;
}
```

### Subproblem design trick

Subproblem design is the hard part, when we are given sequences, often use
- prefixes S[:i] for all i, O(n)
- suffiixes S[i:] for all i, O(n)
- substring S[i:j] for all i<j, O(n^2)

### Relation trick

Identify part of the subproblem solution that, if you knew, reduces the subproblem to smaller subproblem(s).
- locally brute force to find best choice
- guessing perspective:
   - allow "guesing" part of subproblem solution
   - assume relation algorithm makes correct guess
   - in analysis, multiply realtion running time by # possible guesses (brute force)
- key for efficiency: design subproblems so that they are few possible choices/guesses to brute force. 
