### Bounded Knapsack

The bounded knapsack problem is: you are given n types of items, you have ui items of i-th type, and each item of i-th type weighs wi and costs ci. What is the maximal cost you can get by picking some items weighing at most W in total?

The best algorithm I could find on the Internet has complexity O(W*n*log(max(ui)). It goes like this: instead of having ui items of type i, we create several new types that are multiples of type i, for example items with weight 2*wi and cost 2*ci, then the same for 4 and so on, and declare that we have just one item of each type. We create the new types in such a way that the number of new types is logarithmic, and anything that was possible to represent using the old items is also representable using the new items and vice versa. We get a 0-1 knapsack problem with n * log(max(ui) types which leads to a dynamic programming solution with the above complexity.
