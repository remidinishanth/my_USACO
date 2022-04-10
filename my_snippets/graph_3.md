## TODO

* https://atcoder.jp/contests/abc247/tasks/abc247_f 
  * Given `N` cards, Each card has two numbers, one on each side. All the top numbers and all the bottom numbers are permutations of `1` to `N`
  * Find number of ways to choose some cards such that: every number `1,2,…,N` is written on at least one of the chosen cards.

Solution:
* Editorial: https://atcoder.jp/contests/abc247/editorial/3773
* Consider a graph G where `1,…,N` are vertices and there is an edge between each `(Pi, Qi)`. The original problem can be reworded as: “how many subsets E of edges are there such that it is an edge cover?” Obviously, this can be considered for each connected component.
* Since `P`,`Q` are both permutations of `(1,…,N)`, the degree of every vertex is `2`, so the graph is a set of cycles. Therefore, it is sufficient to solve the problem for a cycle.
