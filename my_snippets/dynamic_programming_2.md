### Knapsack Problems

The term knapsack refers to problems where a set of objects is given, and subsets with some properties have to be found. Knapsack problems can often be solved using dynamic programming.

In this section, we focus on the following problem: Given a list of weights `[w1,w2,...,wn]`, determine all sums that can be constructed using the weights. 

This problem is also known as subset sum problem.  Given a set of integers and an integer S, is there a (non-empty) subset that has a sum equal to S?

For example, if the weights are [1,3,3,5], the following sums are possible:

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|
| X | X |   | X | X | X | X | X | X | X |    | X  | X  |

In this case, all sums between 0...12 are possible, except 2 and 10. For example, the sum 7 is possible because we can select the weights [1,3,3].

Subproblems: possible(x,k) = true if we can construct a sum x using the first k weights.

Relate:

	possible(x,k) = possible(x−wk,k −1) V possible(x,k −1)

The formula is based on the fact that we can either use or not use the weight wk
in the sum. If we use wk, the remaining task is to form the sum x−wk using the
first k−1 weights, and if we do not use wk, the remaining task is to form the sum
x using the first k −1 weights.

Let W denote the total sum of the weights. The following O(nW) time dynamic programming solution corresponds to the recursive function:

```cpp
possible[0][0] = true;
for (int k = 1; k <= n; k++) {
    for (int x = 0; x <= W; x++) {
	if (x-w[k] >= 0) possible[x][k] |= possible[x-w[k]][k-1];
	    possible[x][k] |= possible[x][k-1];
    }
}
```

However, here is a better implementation that only uses a one-dimensional array `possible[x]` that indicates whether we can construct a subset with sum x. The trick is to update the array from right to left for each new weight:

```cpp
possible[0] = true;
for (int k = 1; k <= n; k++) {
    for (int x = W; x >= 0; x--) {
	if (possible[x]) possible[x+w[k]] = true;
    }
}
```

### Using Bitsets for faster solutions

Problem is: we have n numbers, calculate how many distinct numbers we can form by sum some of these numbers.

For example if we have set {17, 23, 40}, we can form {0, 17, 23, 40, 57, 63, 80}.

Dp solution is obvious:

```cpp
dp[0] = 1;
for(int i = 0; i < n; i++)
    for(int j = maxv - 1; j >= a[i]; j--)  // maxv is some number bigger than sum of a[i]'s
        dp[j] |= dp[ j - a[i] ];
cout << count(dp, dp + maxv, 1) << '\n';
```

Now how to optimize it? bitset can store bits and do operations 32 times faster like this:

```cpp
bitset<maxv> dp;
dp.set(0);
for(int i = 0; i < n; i++)
    dp |= dp << a[i];
cout << dp.count() << '\n';
```
source: https://codeforces.com/blog/entry/45576?#comment-302358

## Survey of knapsack problems
http://www.algonotes.com/en/knapsacks/

### Standard Knapsacks

We begin with probably the simplest formulation. We have a set of `n` items, each of them is described by its weight (sometimes called size or something similar); the `i-th` item has weight `wi` . We also have a knapsack of weight limit `M` and we are asked to find a subset of items of total weight as large as possible, but less than or equal to the limit (so that the selected items can fit into the knapsack). This is called 0-1 knapsack problem.

The dynamic programming is rather straightforward here. We denote by `d[i,j]` a Boolean value which says whether exists a subset of total weight exactly `j` when we are allowed to use items number `{1, 2, … , i}` . Thus variables satisfy `0 ≤ i ≤ n , 0 ≤ j ≤ M`. Of course `d[0, j] = [j == 0]` , since without any items, we can only obtain an empty subset.

For `i ≥ 1` we consider two cases: either we do not take the `i-th` item to the subset (so the weight j can be realized only if `d[i − 1, j]` is true), or we take it, but only if its weight is no bigger than `j` and `d[i − 1, j − w[i]]` is true:

```d[i, j] = d[i−1, j] or d[i−1, j − w[i]]⋅[j ≥ w[i]]```

The answer is the biggest value j ≤ M for which `d[n, j]` is true. The code is quite simple:
```cpp
#include <cstdio>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N = 1000, MAXM = 1000;
int n, M, w[N];
bool d[N+1][MAXM+1];

int knapsack() {
  REP(j, M+1) d[0][j] = j==0;
  REP(i, n) {
    REP(j, M+1) {
      d[i+1][j] = d[i][j];  /* rewrite */
      if (j >= w[i]) {
        d[i+1][j] |= d[i][j - w[i]];
      }
    }
  }
  return last_max_element(d[n], d[n]+M+1) - d[n];
}
```

The time complexity is `O(n M)`. The space complexity is the same, but can be easily reduced to `O(M)`, using the standard DP trick of storing only two last rows of array d (since the calculations in the row only refers to values in the previous row). But here we can do even better. Observe that line with a comment just rewrites `row i` to `row i + 1` , and then in next two lines we improve some cells. Moreover during improvement we use only cells with lower `j` , so we can store everything in one row, as long as we iterate over it backwards:

```cpp
bool d[MAXM+1];

int knapsack() {
  REP(j, M+1) d[j] = j==0;
  REP(i, n) {
    for (int j = M; j >= w[i]; --j) {
      d[j] |= d[j - w[i]];
    }
  }
  return last_max_element(d, d+M+1) - d;
}
```

If we want, we can utilize the above optimization to write the recurrence formula in a slightly more readable way, by removing row indices:

```dnew[j] = d[j] or d[j − w[i]]⋅[j ≥ w[i]]```

Note also that we solve more general problem: our array `d[j]` is true if we can choose a subset of items such that its total weight is exactly `j` . We will call it a knapsack structure. It will allow us to answer in constant time queries of form: is there a subset of total weight exactly `j` , where `0 ≤ j ≤ M` . The space complexity of the structure is `O(M)` and we can build it in `O(nM)`.

#### Unlimited amount of items of each kind

We can also think about items not as single entities, but as various kinds, from which we can take multiple items. The simplest variant is when we can take unlimited amount of items of each kind. This is called unbounded knapsack problem. It is easy to adapt the previous algorithm. Just observe that if we consider taking an item of the `i-th` type, the remaining place `j − w[i]` can still contain this kind of item, therefore the main recurrence is replaced by

```d[i,j] = d[i−1,j] or d[i,j−w[i]]⋅[j ≥ w[i]]```

It is also easy to change code which uses one row. Now we can immediately use the values of improved cells, so we only need to change the direction of the inner loop:
```cpp
  REP(i, n) {
    for (int j = w[i]; j <= M; ++j) {
      d[j] |= d[j - w[i]];
    }
  }
```
This gives us O (nM) algorithm for the unbounded knapsack problem.

#### Limited amount of items of each kind

Same section is also described in `Bounded Knapsack` below

A little bit harder variant is when we limit number of items we can take from each kind. Denote by `bi` number of items of the `i-th` kind. This is called bounded knapsack problem. Of course the naive approach would be to copy each item `bi` times and use the first algorithm for 0-1 knapsack. If `bi ≤ B`, then this would use time `O(nMB)`, which is not very fast.

But copying each item `bi` times is quite wasteful. We do not need to examine each item separately, since they are indistinguishable anyway, but we need some method to allow us to take any number of such items between `0` and `bi` , or in other words a bunch of items of total weight from the set `{0 , wi , 2wi , … , bi.wi }`.

In order to do it more efficiently, we will group the items in “packets”. It is clearer to see how to do it if we assume that `bi = 2^k − 1` for some k . Then we can form k packets of sizes `wi , 2 wi , 4 wi , … , 2^(k − 1) wi`. Now if we want to take some packets of total weight `j wi` , we just take packets based on set bits in binary representation of `j` . In general case when `2^k ≤ bi < 2^k + 1` we add an additional packet of size `r = ( bi − 2^(k − 1) + 1 ) wi`. If we take this packet, the remaining weight `bi.wi − r` is smaller than `2^k wi` , so it can be covered by choosing from the first `k` packets.

Therefore for the elements of the `i-th` type we will have `O(log bi)` packets, so the algorithm (0-1 knapsack on these packets) will run in time `O(n M logB )` .

But we can do faster. Let's consider adding the `i-th` type. Observe that the recurrence formula is as follows:

```dnew[j] = or( d[j], d[j−wi], d[j−2wi], …, d[j−bi.wi] ),```

where for notational simplicity we assume that `d[⋅]` is false for negative indices. That means that the new value is true if there is at least one true value among `bi` values which we get starting from index `j` an jumping backwards every other `wi -th` index. Note that for `wi = 1` we could just ask that “Is there is at least one true value among the last `bi + 1` values”. Such condition would be very easy to check, by maintaining the index `jr` of the most recent true value; then the condition is true if `j − jr ≤ bi`.

But we can extend this idea for bigger values of `wi` , by maintaining an array `jr` of size `wi`, where different indices keep track of most recent true values for cells which indices have the same remainder when divided by `wi` . Maybe it is easier to explain it by providing the code:

```cpp
int jr[MAXM+1];

  REP(i, n) {
    const int w = w[i], b = b[i];
    REP(j, w) jr[j] = -infty;
    REP(j, M+1) {
      d[j] |= j - jr[j % w] <= b*w;
      if (d[j]) {
        jr[j % w] = j;
      }
    }
  }
```

The time complexity of this algorithm is `O(n M)`. The algorithm highlights quite important idea we will use when creating algorithms for more complicated variants of bounded knapsacks. The idea helps us working with recursive formulas which, when calculating `d[j]`, depend on values `d[j − kw]` for `0 ≤ k ≤ b`. The other way of thinking about this is as follows: we partition array d into w arrays `d0, d1, … , d(w−1)` by taking to array `dJ` every `w -th` element from array `d` starting from index `J` , i.e. `dJ [ j′ ] = d[ J + j′ w ]` . Then the recursive formula for `j = J + j′ w` can be written as follows:

```dnew[j] = dJnew[j′] = or( dJ[j′], dJ[j′−1], dJ[j′−2], … , dJ[j′−b] ),```

![image](https://user-images.githubusercontent.com/19663316/117840727-0dbb0480-b29a-11eb-91a0-92e4624c8c88.png)

thus it depends on a consecutive range of indices `dJ [ j′ − k ]` for `0 ≤ k ≤ b`. And often we can propose a faster algorithm which uses the fact that the range of indices is consecutive.

But for the basic bounded knapsack problem we can show a different algorithm of `O(n M)` complexity, which does not need additional memory. Once again let's consider adding the `i-th` type. If `d[j]` is true, we can generate subsets `j + wi , j + 2 wi , … , j + bi ⋅ wi`, thus we should set all these indices of array `d` to true. Doing it naively would need time `O(n M B)`.

But let's iterate over j decreasingly and take a closer look what happens. When examining value j , we can assume that for all values `j′ > j` if `d[ j′ ]` is true, then `d[ j′ + k′ ⋅ wi]` is also true for all `k′ ≤ bi`. So if `d[j]` is true, we iterate over `k` and set `d[j + k ⋅ wi]` to true, until we hit the cell which was already set. Of course it couldn't be set in this iteration (since then `d[j + (k − 1) ⋅ wi]` must also be set), thus the size `j + k ⋅ wi` can be obtained using elements of type smaller that `i` . But this means that when previously algorithm examined `j + k ⋅ wi`, the value `d[j + k ⋅ wi]` was true, so it also set to true all values `d[j + (k + k′) ⋅ wi]` for all `k′ ≤ bi`. Therefore we can stop our iteration over `k` . The code is as follows:

```cpp
  REP(i, n) {
    for (int j = M - w[i]; j >= 0; --j) {
      if (d[j]) {
        int k = b[i], x = j + w[i];
        while (k > 0 && x <= M && !d[x]) {
          d[x] = true;
          --k;
          x += w[i];
        }
      }
    }
  }
```

Observe that the inner while loop invokes body if some cell `d[x]` changes its value to true (the loop fills cells and stops if it finds a cell filled before). It can happen only `M` times, so total time complexity is `O(n M)`.

#### Sum of weights of items is limited

This algorithm can also help us in a slight variant of 0-1 knapsack problem in which we have a limit on the sum of weights of all items, i.e. `∑wi ≤ S`. The idea is that if `S` is small, then there cannot be many items of different weights (weights of items have to repeat). More precisely, if we have k items of different weights, their total weight must be equal to at least `1 + 2 + … + k = O(k^2)`, so the number of different weights is `O(√S)`. Thus we can utilize this fact and group items of the same weight and use algorithm for bounded knapsack problem. Thanks to that we add a bunch of items of the same weight in linear time, which results in time complexity `O(√S M)`.

Of course this is after a preprocessing phase in which we form groups. It will run in time `O(n log n)` or `O(n + W)` where `W` is the upper bound on the size of the item weight, depending how we sort the weights. Important distinction between this and all previous algorithms is that in the previous ones we added items one by one, each in time `O(M)`, and now we must enforce some order by cleverly grouping them.

Note that exactly the same algorithm works for bounded knapsack with limit on the sum of weights.

### Bounded Knapsack

The bounded knapsack problem is: you are given n types of items, you have ui items of i-th type, and each item of i-th type weighs wi and costs ci. What is the maximal cost you can get by picking some items weighing at most W in total?

The best algorithm I could find on the Internet has complexity `O(W*n*log(max(ui))`. It goes like this: instead of having ui items of type i, we create several new types that are multiples of type i, for example items with weight `2*wi` and cost `2*ci`, then the same for 4 and so on, and declare that we have just one item of each type. We create the new types in such a way that the number of new types is logarithmic, and anything that was possible to represent using the old items is also representable using the new items and vice versa. We get a 0-1 knapsack problem with `n * log(max(ui)` types which leads to a dynamic programming solution with the above complexity.

However, when similar problem was given at a [Codeforces contest](https://codeforces.com/problemset/problem/95/E), several people came up with a `O(W*n)` solution for this problem. 

First, we start with the standard dynamic programming solution: let `dp[k,w]` be the best cost that we can get by packing the total weight of w using the first k item types. DP solution is `dp[k][w] = max(dp[k-1,w], dp[k-1,w-wk]+ck, dp[k-1, w-2*wk]+2*ck..., dp[k-1,w-uk*wk]+uk*ck)`. An interesting observation is that we only deal with every `wk-th` element from the previous array to decide on any element in the current array. If we consider only `wk-th` indices then it is similar to finding maximum over some window. Thus problem can be reduced to finding the maximum value among all the values of the array that is formed by picking every `wk-th` element from the previous best solution and adding some multiple of `ck` to it. How to add this multiple of `ck` is described below.

Let's consider the CF problem. Each new type is then handled as follows: `dp[k][w] = min(dp[k-1,w], dp[k-1,w-wk]+ck, ..., dp[k-1,w-uk*wk]+uk*ck)`. Note that for this problem we are dealing with `min`. This dynamic programming has `O(W*n)` states, and each state is processed in `O(max(ui))`.

But we can process each state in `O(1)` amortized time! Let's take a look at the above recurrence. First, we notice that we can separate all values of `w` into `wk` groups, based on the remainder of division on `wk`, and those groups can be handled separately. Then, for each group, the problem we need to solve is to find `min(a[i], a[i-1]+c, a[i-2]+2*c, ..., a[i-k]+k*c)`. By setting `bi = ai-i*c`, this expression is transformed into `min(bi+i*c, b[i-1]+(i-1)*c+c, ...)`, which is just `i*c+min(bi, b[i-1], ..., b[i-k])`. Thus our problem is reduced to finding minimums of groups of `k+1` consecutive numbers in a given array.

And this, in turn, is a well-known problem that is solvable in O(size of array) using one of the two methods: we can either maintain a sequence of incremental (from the end) minima for a segment of size `k+1` and update it quickly when we shift one position to the right, or we can just separate the entire array into blocks of size `k+1`, and calculate the prefix and suffix minima for each block - this allows to find the minimum for any block of size `k+1` by splitting it into two blocks with precomputed answers.

Is it well-known that bounded knapsack is solvable in `O(W*n)` worst-case?

source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html

### CF Problem

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

#### Input
The first line contains two integers n and m (1 ≤ n, m ≤ 10^5). They are the number of islands and the number of roads correspondingly. Next m lines contain road descriptions. Each road is defined by the numbers of islands that it connects: that is, by two integers u and v (1 ≤ u, v ≤ n). Some roads can connect an island with itself; there can be more than one road between a pair of islands. Numbers in each line are separated by exactly one space character.

#### Output
If there's no solution, output the only number "-1" (without the quotes). Otherwise, output the minimum number of roads r that need to be built to get a lucky region.

#### Solution

Let's first find the different sizes of regions(connected components), we might have more than one component of a particular size.

Let A[i] - sorted array of sizes of different connection components, C[i] – number of connection components of size A[i], This is similar to Bounded knapsack problem. `Sum for all C[i]*A[i]` is equal to n. Size of A will be `O(sqrt(n))` because each entry of A[i] is unique and increasing, the smallest unique values we have is `1,2,3,...,sqrt(n)` and `for all i, C[i]=1`

To solve with `log(max(C[i]))` factor, we will need to add 
* `1,2,4,..., 2^(k-1)` if `C[i] = (2^k)-1`, i. e. `C[i] = 1 + 2 + 4 + 8 + … + 2^(k-1)`
* `1,2,4,..., 2^(k-1)`,find maximal k, which `(2^k)-1 <= C[i]` and also add `C[i]-((2^k)-1)` to set, if `C[i]` is not power of 2

For example: In case of 15, we will add `1,2,4,8` this way we can create all numbers within 1 to 15. In case of 13 we will add `1,2,4,6`, this way we can create all numbers within 1 to 13.

**Optimal solution**

We want to find `dp[i][w] = max(dp[i-1,w], dp[i-1,w-wi]+ci, dp[i-1, w-2*wi]+2*ci..., dp[i-1,w-ui*wi]+ui*ci)`. Here `ci` = cost of joining components which is single road, hence `ci = 1`. Now let's divide the groups by remainder module `A[i]`. Then, for each group, the problem we need to solve is to find `min(a[i], a[i-1]+c, a[i-2]+2*c, ..., a[i-k]+k*c) = min(a[i], a[i-1]+1, a[i-2]+2, ..., a[i-k]+k)`, By setting `bi=ai-i*c=ai-i`, this expression is transformed into `min(bi+i*c,b[i-1]+(i-1)*c+c, ...) = min(bi+i,b[i-1]+(i-1)+1, ...)`, which is just `i+min(bi, b[i-1], ..., b[i-k])`

```cpp
const int maxn = 100000+10; // 1e5 + 10
const int oo=100000000; // 1e8
int que[maxn];
int qid[maxn];
int opt[maxn];
int tmp[maxn];
bool lucky[maxn];

template<int um> class UF {
	public:
	vector<int> par,rank,cnt;
	UF() {par=rank=vector<int>(um,0); cnt=vector<int>(um,1); for(int i=0;i<um;i++) par[i]=i;}
	void reinit() { for(int i=0;i<um; i++) rank[i]=0,cnt[i]=1,par[i]=i;}
	int operator[](int x) {return (par[x]==x)?(x):(par[x] = operator[](par[x]));}
	int count(int x) { return cnt[operator[](x)];}
	int operator()(int x,int y) {
		if((x=operator[](x))==(y=operator[](y))) return x;
		cnt[y]=cnt[x]=cnt[x]+cnt[y];
		if(rank[x]>rank[y]) return par[x]=y;
		rank[x]+=rank[x]==rank[y]; return par[y]=x;
	}
};

int main(){
    int n,m;
    scanf("%d%d",&n, &m);
    UF<maxn> uf;
    for(int i=0;i<m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        x--;y--;
        uf(x,y); // to find component sizes
    }
    
    lucky[0] = 1;
    for(int k=1;k<maxn;k++){
        lucky[k] = (k%10==4 || k%10==7) ? lucky[k/10] : 0;
    }
    
    map<int,int> M;
    for(int i=0;i<n;i++)
        if(uf.par[i] == i) M[uf.cnt[i]]++;

    vector<int> A,C;
    for(pair<int,int> x:M){
        A.push_back(x.first); // component size
        C.push_back(x.second); // number of such components
    }

    for(int i=1;i<=77777;i++) opt[i] = oo; // 77777 is the largest lucky number <= maxn

    for(int i=0;i<A.size();i++){
    	// opt[j] corresponds to dp[i-1][j], tmp[j] to dp[i][j]
        for(int j=0;j<=77777;j++) tmp[j] = oo;

        // groups based on remainder mod A[i]
        for(int j=0;j<A[i];j++){
            int l=1,r=0;
            // elements in a group differ by A[i]
	    // Find optimal solution using sliding window minimum for windows of size C[i]
            for(int w=j,id=0; w<=77777; w+=A[i],id++){
	    	// array ai = opt[w]; array bi = opt[w] - id; id - index of elements in array ai, bi
                while(l<=r && id-qid[l]>C[i]) l++; // if window size >= C[i], remove elements from left
                if(l<=r) tmp[w] = que[l] + id; // if queue is not empty, optimal value is min in window
                while(l<=r && opt[w]-id<=que[r]) r--; // pop all elements greater than current value
                que[++r] = opt[w]-id; qid[r]=id;
            }
        }

        for(int j=0;j<=77777;j++)
            opt[j] = min(opt[j], tmp[j]);
    }


    int res=n+1;
    for(int i=1;i<=77777;i++){
        if(lucky[i]){
            res = min(res, opt[i]);
        }
    }
    if(res==n+1) printf("-1\n");
    else printf("%d\n", res-1);
    return 0;
}
```

source: https://codeforces.com/contest/95/submission/535779
