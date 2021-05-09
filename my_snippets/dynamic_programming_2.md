### Bounded Knapsack

The bounded knapsack problem is: you are given n types of items, you have ui items of i-th type, and each item of i-th type weighs wi and costs ci. What is the maximal cost you can get by picking some items weighing at most W in total?

The best algorithm I could find on the Internet has complexity `O(W*n*log(max(ui))`. It goes like this: instead of having ui items of type i, we create several new types that are multiples of type i, for example items with weight 2*wi and cost 2*ci, then the same for 4 and so on, and declare that we have just one item of each type. We create the new types in such a way that the number of new types is logarithmic, and anything that was possible to represent using the old items is also representable using the new items and vice versa. We get a 0-1 knapsack problem with n * log(max(ui) types which leads to a dynamic programming solution with the above complexity.

However, when this problem was given at a [Codeforces contest](https://codeforces.com/problemset/problem/95/E), several people came up with a `O(W*n)` solution for this problem. First, we start with the standard dynamic programming solution: let dpk,w be the best cost that we can get by packing the total weight of w using the first k item types. Each new type is then handled as follows ![image](https://user-images.githubusercontent.com/19663316/117567140-490dd580-b0d8-11eb-934b-5bf68bc8076e.png)

This dynamic programming has `O(W*n)` states, and each state is processed in O(max(ui)).

But we can process each state in O(1) amortized time! Let's take a look at the above recurrence. First, we notice that we can separate all values of w into wk groups, based on the remainder of division on wk, and those groups can be handled separately. Then, for each group, the problem we need to solve is to find `min(ai, ai-1+c, ai-2+2*c, ..., ai-k+k*c)`. By setting `bi=ai-i*c`, this expression is transformed into `min(bi+i*c,bi-1+(i-1)*c+c, ...)`, which is just `i*c+min(bi, bi-1, ..., bi-k)`. Thus our problem is reduced to finding minimums of groups of k+1 consecutive numbers in a given array.

And this, in turn, is a well-known problem that is solvable in O(size of array) using one of the two methods: we can either maintain a sequence of incremental (from the end) minima for a segment of size k+1 and update it quickly when we shift one position to the right, or we can just separate the entire array into blocks of size k+1, and calculate the prefix and suffix minima for each block - this allows to find the minimum for any block of size k+1 by splitting it into two blocks with precomputed answers.

Is it well-known that bounded knapsack is solvable in O(W*n) worst-case?

source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html
