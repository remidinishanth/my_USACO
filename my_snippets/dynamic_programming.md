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

Dynamic programming can be generally used to solve the following type of problems:
  * Count something(combinatorics), often the number of ways
  * Minimize or maximize certain value
  * Yes/No questions, whether something is possible.

The key skills that we have to develop in order to master DP are the abilities to determine the problem states and to determine the relationships or transitions between current
problems and their sub-problems.

You can think in terms of SRT - BOT steps as Erik Demaine describes
1. Define **Subproblems**
2. **Relate** Subproblems solutions recursively
    * **Topological** order on subproblems to guarantee acyclic relation, subproblems relations should form a DAG
3. Identify **Base** Cases - State solitions for all (reachable) independent subproblems where relations break down
4. Solve the **original** problem
5. Analyze the running **time**
    * no of	subproblems . time/subproblem

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

We'll need to find topological ordering between the subproblems defined in the above recursion and solve in this order.

`reachable[g][rem]` defines can we buy garments starting from g with `rem` amount.

```cpp
int main(){
    int i, j, TC, M, C;
    int price[25][25];                     // price[g (<= 20)][model (<= 20)]
    bool reachable[25][210];    // reachable table[g (<= 20)][money (<= 200)]
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d %d", &M, &C);
        for (i = 0; i < C; i++) {
          scanf("%d", &price[i][0]);               // we store K in price[i][0]
          for (j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
        }

        memset(reachable, false, sizeof reachable);         // clear everything
        reachable[C][0] = true; // base case

        for(i=C-1;i>=0;i--){ // garment i
            for(int rem=0;rem<=M;rem++){ // remanining amount to shop
                for(int model=1;model <= price[i][0]; model++){
                    if(rem >= price[i][model]){ // can buy this model
                        reachable[i][rem] |= reachable[i+1][rem - price[i][model]];
                    }
                }
            }
        }

        for(j=M;j!=-1 && !reachable[0][j];j--);

        if (j == -1) printf("no solution\n");         // last row has on bit
        else            printf("%d\n", j);
    }
    return 0;
}
```

CP3 defines these steps as follows:

1. Determine the required set of parameters that uniquely describe the problem (the state). This step is similar to what we have discussed in recursive backtracking and top-down DP earlier.
2. If there are N parameters required to represent the states, prepare an N dimensional DP table, with one entry per state. This is equivalent to the memo table in top-down DP. However, there are differences. In bottom-up DP, we only need to initialize some cells of the DP table with known initial values (the base cases). Recall that in topdown DP, we initialize the memo table completely with dummy values (usually -1) to indicate that we have not yet computed the values.
3. Now, with the base-case cells/states in the DP table already filled, determine the cells/states that can be filled next (the transitions). Repeat this process until the DP table is complete. For the bottom-up DP, this part is usually accomplished through iterations, using loops (more details about this later).

We describe the state of a subproblem with two parameters: The current garment g and the current money. This state formulation is essentially equivalent to the state in the top-down DP above, except that we have reversed the order to make g the first parameter (thus the values of g are the row indices of the DP table so that we can take advantage of *cache-friendly* row-major traversal in a 2D array). Then, we initialize a 2D table (boolean matrix) `reachable[g][money]` of size 20 × 201. Initially, only cells/states reachable by buying any of the models of the first garment g=0 are set to true (in the first row). 

Topological Ordering for the following test case

Suppose we have the following test case A with M = 20, C = 3:\
Price of the 3 models of garment g=0 → 6 4 <ins>8</ins> // the prices are not sorted in the input\
Price of the 2 models of garment g=1 → 5 <ins>10</ins>\
Price of the 4 models of garment g=2 → <ins>1</ins> 5 3 5

![image](https://user-images.githubusercontent.com/19663316/117550854-4079b880-b060-11eb-9e04-c39793b57a31.png)

Top-down version
```cpp
int main() {
  int i, j, k, TC, M, C;
  int price[25][25];                     // price[g (<= 20)][model (<= 20)]
  bool reachable[25][210];    // reachable table[g (<= 20)][money (<= 200)]
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (i = 0; i < C; i++) {
      scanf("%d", &price[i][0]);               // we store K in price[i][0]
      for (j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
    }

    memset(reachable, false, sizeof reachable);         // clear everything
    for (i = 1; i <= price[0][0]; i++)       // initial values (base cases)
      if (M - price[0][i] >= 0)      // to prevent array index out of bound
        reachable[0][M - price[0][i]] = true;  // using first garment g = 0

    for (i = 1; i < C; i++)                   // for each remaining garment
      for (j = 0; j < M; j++) if (reachable[i - 1][j]) // a reachable state
        for (k = 1; k <= price[i][0]; k++) if (j - price[i][k] >= 0)
          reachable[i][j - price[i][k]] = true;   // also a reachable state

    for (j = 0; j <= M && !reachable[C - 1][j]; j++); // the answer in here

    if (j == M + 1) printf("no solution\n");         // last row has on bit
    else            printf("%d\n", M - j);
} } // return 0;
```

There is an advantage for writing DP solutions in the bottom-up fashion. For problems where we only need the last row of the DP table (or, more generally, the last updated slice of all the states) to determine the solution—including this problem, we can optimize the memory usage of our DP solution by sacrificing one dimension in our DP table. For harder DP problems with tight memory requirements, this **‘space saving trick’** may prove to be useful, though the overall time complexity does not change.

```cpp
// space saving trick
int main() {
  int i, j, k, TC, M, C, cur;
  int price[25][25];
  bool reachable[2][210]; // reachable table[ONLY TWO ROWS][money (<= 200)]
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (i = 0; i < C; i++) {
      scanf("%d", &price[i][0]);
      for (j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
    }
    memset(reachable, false, sizeof reachable);
    for (i = 1; i <= price[0][0]; i++)
      if (M - price[0][i] >= 0)
        reachable[0][M - price[0][i]] = true;
    cur = 1;                                      // we start with this row
    for (i = 1; i < C; i++) {
      memset(reachable[cur], false, sizeof reachable[cur]);    // reset row
      for (j = 0; j < M; j++) if (reachable[!cur][j])        // notice !cur
        for (k = 1; k <= price[i][0]; k++) if (j - price[i][k] >= 0)
          reachable[cur][j - price[i][k]] = true;
      cur = !cur;                                      // flip the two rows
    }
    for (j = 0; j <= M && !reachable[!cur][j]; j++);         // notice !cur
    if (j == M + 1) printf("no solution\n");         // last row has on bit
    else            printf("%d\n", M - j);
} } // return 0;
```

## Classical Examples

### Max 1D Range sum

Given an array arr[0], arr[1], . . . , arr[n − 1] of integers, find the interval with the highest sum.  In other words,
find the maximum Range Sum Query (RSQ) between two indices i and j in [0..n-1], that is: A[i] + A[i+1] + A[i+2] +...+ A[j] 

### Attempt 1
If we choose a[i:j] as subproblem,

Notice that ∑a[i:j] = ∑a[i:j-1] + a[j],  ∑a[i:j] = ∑a[0:j] - ∑a[0:i-1]

We can use prefix sums to optimize s[i] = ∑a[0:i], we get O(N^2) solution

### Attempt 2
Solution: Choose sub-problem as dp[i] = max. sum sub-array ending at a[i]

Optimal sub-structure: if the max. sub-array includes a[i], it starts with the max sum sub-array ending at a[i] 

Relating subproblems: dp[i] = max(dp[i - 1] + a[i], a[i]), So we keep adding to the current element to sub-array
until the sub-array sum becomes negative

Solution to orginal problem will be max{dp[i]} for 0 ≤ i < n

Can also be written in memory efficient way as follows

```cpp
int main() {
  int n = 9, A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 };   // a sample array A
  int running_sum = 0, ans = 0;
  for (int i = 0; i < n; i++)                                       // O(n)
    if (running_sum + A[i] >= 0) {  // the overall running sum is still +ve
      running_sum += A[i];
      ans = max(ans, running_sum);          // keep the largest RSQ overall
    }
    else        // the overall running sum is -ve, we greedily restart here
      running_sum = 0;      // because starting from 0 is better for future
                           // iterations than starting from -ve running sum
  printf("Max 1D Range Sum = %d\n", ans);                    // should be 9
} // return 0;
```

### Longest Increasing Subsequence (LIS)

Given a sequence {A[0], A[1],..., A[n-1]},, find the longest subsequence that strictly increases.  Example:
n = 8, A = {−7, 10, 9, 2, 3, 8, 8, 1}. The length-4 LIS is {-7, 2, 3, 8}.

### Attempt:

- Subproblems: L(i) = LIS(A[i:])
- Relate L(i) ?= max{L(i+1) don't include A[i], 1+L(i+1) include A[i]}
  * How can we guarantee increasing subsequence?
  * No way to constrain smaller subproblem...

### Subproblem constraints

Solve a more specific problem(add constraints) to enable relation

### Solution

- Subproblems: L(i) = LIS of A[i:] such that starts with (includes) A[i]
- Relate L(i) = max {1+L(j) | i < j ≤ |A|, A[i] < A[j]} U {1} (increase impossible)
  * nonconstant branching(like DAG Shortest paths but unlike other DPs)
- Topological ordering: for i = |A|, ..., 0
- Base case: L(|A|) = 0
- Original problem: max{L(i) | 0 <= i < |A|}
  * Where to start? guess/brute-force options
- Time: O(n) subproblems * O(n) non-recursive work in relation = O(n^2)  

Can also be solved using subproblem L[:i], which is simple to code

![image](https://user-images.githubusercontent.com/19663316/117561454-a4c66780-b0b4-11eb-9c35-1d5cbbdd35e6.png)

```cpp
vector<int> A(n);
//read A
vector<int> lis(n);
for(int i = 0; i < n; i++){
  int res = 1; // base case
  for(int j = 0; j < i; j++){
    if(A[j] < A[i]){
      res = max(res, 1 + lis[i]};
    }
  }
  lis[i] = res;
}
int mx = 0;
for(int i = 0; i < n; i++){
  mx = max(mx, lis[i]);
}
// mx is answer
```

We can find the longest subsequence by storing the predecessor information(arrows in the image) and tracing the arrows from index k that contain the highest value of LIS(k).

We can speed up LIS DP to O(n logn) by computing max in relation via memo table data structure.

### Faster solution

The LIS problem can also be solved using the output-sensitive O(n log k) Greedy + Divide & Conquer algorithm (where k is the length of the LIS) instead of O(n^2) by maintaining an array that is always sorted and therefore amenable to binary search.

Let array L be an array such that **L(i) represents the smallest ending value of all length-i LISs found so far**. Though this definition is slightly complicated, it is easy to see that it is always ordered — L(i-1) will always be smaller than L(i) as the second-last element of any LIS (of length-i) is smaller than its last element. As such, we can binary search array L to determine the longest possible subsequence we can create by appending the current element A[i]—simply find the index of the last element in L that is less than A[i].

Using the same example `n = 8`, `A = {−7, 10, 9, 2, 3, 8, 8, 1}` , we will update array L step by step using this algorithm:
* Initially, at `A[0] = -7`, we have `L = {-7}`.
* We can insert `A[1] = 10` at `L[1]` so that we have a length-2 LIS, `L = {-7, 10}`.
* For `A[2] = 9`, we replace `L[1]` so that we have a ‘better’ length-2 LIS ending: `L = {-7, 9}`. This is a greedy strategy. By storing the LIS with smaller ending value, we maximize our ability to further extend the LIS with future values.
* For `A[3] = 2`, we replace `L[1]` to get an ‘even better’ length-2 LIS ending: `L = {-7, 2}`.
* We insert `A[4] = 3` at `L[2]` so that we have a longer LIS, `L = {-7, 2, 3}`.
* We insert `A[5] = 8` at `L[3]` so that we have a longer LIS, `L = {-7, 2, 3, 8}`.
* For `A[6] = 8`, nothing changes as `L[3] = 8`. `L = {-7, 2, 3, 8}` remains unchanged.
* For `A[7] = 1`, we improve `L[1]` so that `L = {-7, 1, 3, 8}`. This illustrates how the array L is not the LIS of A. This step is important as there can be longer subsequences in the future that may extend the length-2 subsequence at `L[1] = 1`.
* The answer is the largest length of the sorted array `L` at the end of the process.

CP3 solution

```cpp
#define MAX_N 100000

void print_array(const char *s, int a[], int n) {
  for (int i = 0; i < n; ++i) {
    if (i) printf(", ");
    else printf("%s: [", s);
    printf("%d", a[i]);
  }
  printf("]\n");
}

void reconstruct_print(int end, int a[], int p[]) {
  int x = end;
  stack<int> s;
  for (; p[x] >= 0; x = p[x]) s.push(a[x]);
  printf("[%d", a[x]);
  for (; !s.empty(); s.pop()) printf(", %d", s.top()); // to reverse the sequence
  printf("]\n");
}

int main() {
  int n = 11, A[] = {-7, 10, 9, 2, 3, 8, 8, 1, 2, 3, 4};
  int L[MAX_N], L_id[MAX_N], P[MAX_N];
  // P[] stores the predecessors such that we can reconstruct the subsequence

  int lis = 0, lis_end = 0;
  for (int i = 0; i < n; ++i) {
    int pos = lower_bound(L, L + lis, A[i]) - L;
    L[pos] = A[i];
    L_id[pos] = i;
    P[i] = pos ? L_id[pos - 1] : -1;
    if (pos + 1 > lis) {
      lis = pos + 1;
      lis_end = i;
    }

    printf("Considering element A[%d] = %d\n", i, A[i]);
    printf("LIS ending at A[%d] is of length %d: ", i, pos + 1);
    reconstruct_print(i, A, P);
    print_array("L is now", L, lis);
    printf("\n");
  }

  printf("Final LIS is of length %d: ", lis);
  reconstruct_print(lis_end, A, P);
  return 0;
}
```

Using vector<int>
  
```cpp
vi p;                                            // predecessor array

void print_LIS(int i) {                          // backtracking routine
  if (p[i] == -1) { printf("%d", A[i]); return; }// base case
  print_LIS(p[i]);                               // backtrack
  printf(" %d", A[i]);
}

int memo[10010];                                 // old limit: up to 10^4

int LIS(int i) {                                 // O(n^2) overall
  if (i == 0) return 1;
  int &ans = memo[i];
  if (ans != -1) return ans;                     // was computed before
  ans = 1;                                       // LIS can start anywhere
  for (int j = 0; j < i; ++j)                    // O(n) here
    if (A[j] < A[i])                             // increasing condition
      ans = max(ans, LIS(j)+1);                  // pick the max
  return ans;
}

int main() {
  // note: A[n-1] must be set as the largest value ("INF")
  // so that all LIS (that can start anywhere) will end at n-1
  srand(time(NULL));
  int n = 10+rand()%11;                          // [10..20]
  // read n, A

  // early 2000 problems usually accept O(n^2) solution
  memset(memo, -1, sizeof memo);
  printf("LIS length is %d\n\n", LIS(n-1));      // with O(n^2) DP

  // 2020s problems will likely only accept O(n log k) solution
  // new limit: n can be up to 200K
  int k = 0, lis_end = 0;
  vi L(n, 0), L_id(n, 0);
  p.assign(n, -1);

  for (int i = 0; i < n; ++i) {                  // O(n)
    int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
    L[pos] = A[i];                               // greedily overwrite this
    L_id[pos] = i;                               // remember the index too
    p[i] = pos ? L_id[pos-1] : -1;               // predecessor info
    if (pos == k) {                              // can extend LIS?
      k = pos+1;                                 // k = longer LIS by +1
      lis_end = i;                               // keep best ending i
    }
  }
    
  print_LIS(lis_end);
}
```

Using cpp set
```cpp
set<int> st;
set<int>::iterator it;
...
st.clear();
for(i = 0; i < n; i++)
{
  st.insert(a[i]); it=st.find(A[i]);
  it++; if(it!=st.end()) st.erase(it);
}
cout<<st.size()<<endl;
```

### 0-1 Knapsack

Problem: Given n items, each with its own value Vi and weight Wi, ∀i ∈ [0..n-1], and a maximum knapsack size S, compute the maximum value of the items that we can carry, if we can either ignore or take a particular item (hence the term 0-1 for ignore/take).

Example: n = 4, V = {100, 70, 50, 10}, W = {10, 4, 6, 12}, S = 12.\
If we select item 0 with weight 10 and value 100, we cannot take any other item. Not optimal.\
If we select item 3 with weight 12 and value 10, we cannot take any other item. Not optimal.\
If we select item 1 and 2, we have total weight 10 and total value 120. This is the maximum.

```cpp
const int MAX_N = 1010;
const int MAX_W = 40;

int N, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

int dp(int id, int remW) {
  if ((id == N) || (remW == 0)) return 0;        // two base cases
  int &ans = memo[id][remW];
  if (ans != -1) return ans;                     // computed before
  if (W[id] > remW) return ans = dp(id+1, remW); // no choice, skip
  return ans = max(dp(id+1, remW),               // has choice, skip
                   V[id]+dp(id+1, remW-W[id]));  // or take
}

// dp(0, MW); solution to original problem
```

Bottom-up
```cpp
// inside main
      for (int i = 1; i<= N; ++i) // Values are stored from 1 to N
        scanf("%d %d", &V[i], &W[i]);
      for (int i = 0; i <= N;  ++i) C[i][0] = 0;
      for (int w = 0; w <= MW; ++w) C[0][w] = 0;
      for (int i = 1; i <= N; ++i)
        for (int w = 1; w <= MW; ++w) {
          if (W[i] > w) C[i][w] = C[i-1][w];
          else          C[i][w] = max(C[i-1][w], V[i] + C[i-1][w-W[i]]);
        }
      ans += C[N][MW];
```
Note: The top-down version of this DP solution is often faster than the bottom-up
version. This is because not all states are actually visited, and hence the critical DP states
involved are actually only a (very small) subset of the entire state space. Remember: The
top-down DP only visits the required states whereas bottom-up DP visits all distinct states.
