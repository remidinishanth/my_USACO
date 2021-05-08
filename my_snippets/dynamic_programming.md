# Dynamic Programming

Dynamic Programming (from now on abbreviated as DP) is perhaps the most challenging
problem-solving technique among Divide and Conquer, Greedy and complete search paradigms.

The key skills that we have to develop in order to master DP are the abilities to determine the problem states and to determine the relationships or transitions between current
problems and their sub-problems.

You can think in terms of 5 steps as Erik Demaine describes
1. Define Subproblems
2. Relate Subproblems solutions recursively
    * State topological order to argue relations are acyclic and form a DAG
3. Identify Base Cases
4. Solve the original problem
5. Analyze the running time

Existence of recursive solution implies that subproblems are decomposable(this property is often called optimal substructure property, it is a property of recursion, not just DP).
