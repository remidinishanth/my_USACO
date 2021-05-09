### Bounded Knapsack

The bounded knapsack problem is: you are given n types of items, you have ui items of i-th type, and each item of i-th type weighs wi and costs ci. What is the maximal cost you can get by picking some items weighing at most W in total?

The best algorithm I could find on the Internet has complexity `O(W*n*log(max(ui))`. It goes like this: instead of having ui items of type i, we create several new types that are multiples of type i, for example items with weight `2*wi` and cost `2*ci`, then the same for 4 and so on, and declare that we have just one item of each type. We create the new types in such a way that the number of new types is logarithmic, and anything that was possible to represent using the old items is also representable using the new items and vice versa. We get a 0-1 knapsack problem with `n * log(max(ui)` types which leads to a dynamic programming solution with the above complexity.

However, when similar problem was given at a [Codeforces contest](https://codeforces.com/problemset/problem/95/E), several people came up with a `O(W*n)` solution for this problem. First, we start with the standard dynamic programming solution: let `dp[k,w]` be the best cost that we can get by packing the total weight of w using the first k item types. Each new type is then handled as follows: `dp[k][w] = min(dp[k-1,w], dp[k-1,w-wk]+ck, ..., dp[k-1,w-uk*wk]+uk*ck)`. This dynamic programming has `O(W*n)` states, and each state is processed in `O(max(ui))`.

But we can process each state in O(1) amortized time! Let's take a look at the above recurrence. First, we notice that we can separate all values of w into wk groups, based on the remainder of division on wk, and those groups can be handled separately. Then, for each group, the problem we need to solve is to find `min(a[i], a[i-1]+c, a[i-2]+2*c, ..., a[i-k]+k*c)`. By setting `bi=ai-i*c`, this expression is transformed into `min(bi+i*c,b[i-1]+(i-1)*c+c, ...)`, which is just `i*c+min(bi, b[i-1], ..., b[i-k])`. Thus our problem is reduced to finding minimums of groups of k+1 consecutive numbers in a given array.

And this, in turn, is a well-known problem that is solvable in O(size of array) using one of the two methods: we can either maintain a sequence of incremental (from the end) minima for a segment of size k+1 and update it quickly when we shift one position to the right, or we can just separate the entire array into blocks of size k+1, and calculate the prefix and suffix minima for each block - this allows to find the minimum for any block of size k+1 by splitting it into two blocks with precomputed answers.

Is it well-known that bounded knapsack is solvable in O(W*n) worst-case?

source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html

### Elaborate explanation

In the above DP, `dp[k][w] = max(dp[k-1,w], dp[k-1,w-wk]+ck, dp[k-1, w-2*wk]+2*ck..., dp[k-1,w-uk*wk]+uk*ck)`

An interesting observation is that we only deal with every wk-th element from the previous array to decide on any element in the current array.

Let us for a minute ignore the fact that we have only a fixed number of items of each type and instead assume that we have an infinite number of items of each type. Let us assume that item i weighs 3 and costs 9. If we make that assumption, we see that the best solution at DPk, 12 is represented by taking the maximum of the cells colored in green below.

![image](https://user-images.githubusercontent.com/19663316/117568034-3f866c80-b0dc-11eb-92ac-bf7348b72b01.png)

What we have essentially done is added: `0*9` to `dp[k-1, 12]`, `1*9` to `dp[k-1, 9]`, `2*9` to `dp[k-1, 6]`, `3*9` to `dp[k-1, 3]` and `4*9` to `dp[k-1, 0]`.

The problem has reduced to finding the maximum value among all the values of the array that is formed by picking every wk-th element from the previous best solution and adding some multiple of ck to it.

We also notice that it doesn't matter what values we add to dp[k-1, w] (for the kth item) as long as they are ck apart. Hence, if the weight of the knapsack is W and the weight of the kth item is wk, we can add the following to every wk-th element in the previous array.

![image](https://user-images.githubusercontent.com/19663316/117568185-a6a42100-b0dc-11eb-88f2-0215827d37c1.png)

If we now reintroduce the requirement that each item type will have only a bounded or fixed number of instances (i.e. uk is bounded), then the problem reduces to finding the maximum value in every window of size uk in the array we just computed. This can easily be done by pre-processing the array to maintain the largest element in every window of size uk.

However, the actual value of the cost at any cell needs to be computed by adding back any differential that we may have subtracted to ensure that every entry is ck apart and that the first entry is the one which has the maximum multiple of ck subtracted from it. For the jth array element in the current sub-array we are processing, this value will be `(W/wk - j)*ck` (since we have subtracted that much extra from those elements, we must now add it back).

Hence, we can safely say that we shall have wk different sub-problems that we shall try to solve assuming that we can use a single computation for every wkth element.

This allows us to find the value at every cell of the (k x W) matrix is amortized time O(1) (we have amortized the cost of pre-computing the wk arrays across all the element accesses). This makes the total running time of this algorithm `O(W*n)`.

### CF Problem

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

#### Solution

Let's first find the different sizes of regions(connected components), we might have more than one component of a particular size.

Let A[i] - sorted array of sizes of different connection components, C[i] – number of connection components of size A[i], This is similar to Bounded knapsack problem.
