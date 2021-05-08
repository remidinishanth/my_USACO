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

Existence of recursive solution implies that subproblems are decomposable(this property is often called optimal substructure property - optimal solution can be constructed from optimal solutions of its subproblems), it is a property of recursion, not just DP).

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

## DP Illustration CP3

We will illustrate the concept of Dynamic Programming with an example problem: UVa
11450 - Wedding Shopping. The abridged problem statement: Given different options for
each garment (e.g. 3 shirt models, 2 belt models, 4 shoe models, . . . ) and a certain limited
budget, our task is to buy one model of each garment. We cannot spend more money than
the given budget, but we want to spend the maximum possible amount.

### Input
The input consists of two integers 1 ≤ M ≤ 200 and 1 ≤ C ≤ 20, where M is the budget
and C is the number of garments that you have to buy, followed by some information about the C garments. 

For the garment g ∈ [0..C-1], we will receive an integer 1 ≤ K ≤ 20
which indicates the number of different models there are for that garment g, followed by K
integers indicating the price of each model ∈ [1..K] of that garment g.

### Output
The output is one integer that indicates the maximum amount of money we can spend
purchasing one of each garment without exceeding the budget. 

If there is no solution due to the small budget given to us, then simply print “no solution”.

### Solution

* Subproblems -  Let's use the shop(money, g) as the state/subproblem, that is we are buying the current garment g and we have `money` left
* Relate - shop(money, g) = max(shop(money - price[g][model], g + 1)) ∀ model ∈ [1..K] of current garment g
* Base case  
  * money < 0:infeasible search, shop(money, g) = −∞
  * If g = C, last garment has been brought, shop(money, g) = M - money (this is the actual money that we spent)
* Original Problem: shop(M, 0)
* Running time: we only have 201(money from 0 to 200) * 20 (twenty garments) = 4020 states, each state has 20 models, so total time compelxity = 4020 × 20 = 80400

```cpp
// this code is similar to recursive backtracking code
// parts of the code specific to top-down DP are commented with: ‘TOP-DOWN’

int M, C, price[25][25];                 // price[g (<= 20)][model (<= 20)]
int memo[210][25];    // TOP-DOWN: dp table memo[money (<= 200)][g (<= 20)]
int shop(int money, int g) {
  if (money < 0) return -1000000000;     // fail, return a large -ve number
  if (g == C) return M - money;        // we have bought last garment, done
  if (memo[money][g] != -1) return memo[money][g]; // TOP-DOWN: memoization
  int ans = -1;   // start with a -ve number as all prices are non negative
  for (int model = 1; model <= price[g][0]; model++)      // try all models
    ans = max(ans, shop(money - price[g][model], g + 1));
  return memo[money][g] = ans; // TOP-DOWN: assign ans to table + return it
}

int main() {            // easy to code if you are already familiar with it
  int i, j, TC, score;

  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (i = 0; i < C; i++) {
      scanf("%d", &price[i][0]);                  // store K in price[i][0]
      for (j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
    }
    memset(memo, -1, sizeof memo);    // TOP-DOWN: initialize DP memo table
    score = shop(M, 0);                            // start the top-down DP
    if (score < 0) printf("no solution\n");
    else           printf("%d\n", score);
} } // return 0;
```

Instead of frequently addressing a certain cell in
the memo table, we can use a local reference variable to store the memory address of the
required cell in the memo table as shown below.

```cpp
int shop(int money, int g) {
  if (money < 0) return -1000000000;
  if (g == C) return M - money;
  int &ans = memo[money][g];                 // remember the memory address
  if (ans != -1) return ans;
  for (int model = 1; model <= price[g][0]; model++)
    ans = max(ans, shop(money - price[g][model], g + 1));
  return ans;                // ans (or memo[money][g]) is directly updated
}
```

Finding which model of garments has been brought
```cpp
void print_shop(int money, int g) { // this function does not return anything
  if (money < 0 || g == C) return;                      // similar base cases
  for (int model = 1; model <= price[g][0]; model++)   // which model is opt?
    if (shop(money - price[g][model], g + 1) == memo[money][g]) { // this one
      printf("%d - ", price[g][model]);
      print_shop(money - price[g][model], g + 1); // recurse to this one only
      break;
}   }
```

#### Bottom-Up DP

We'll need to find topological ordering between the subproblems and solve in this order.

CP3 defines these steps as follows:

1. Determine the required set of parameters that uniquely describe the problem (the state). This step is similar to what we have discussed in recursive backtracking and top-down DP earlier.
2. If there are N parameters required to represent the states, prepare an N dimensional DP table, with one entry per state. This is equivalent to the memo table in top-down DP. However, there are differences. In bottom-up DP, we only need to initialize some cells of the DP table with known initial values (the base cases). Recall that in topdown DP, we initialize the memo table completely with dummy values (usually -1) to indicate that we have not yet computed the values.
3. Now, with the base-case cells/states in the DP table already filled, determine the cells/states that can be filled next (the transitions). Repeat this process until the DP table is complete. For the bottom-up DP, this part is usually accomplished through iterations, using loops (more details about this later).
