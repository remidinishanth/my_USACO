## Dynamic Connectivity Problem

* Graph connectivity problem: Given an undirected graph G, preprocess the graph so that queries of the form "are nodes u and v connected?" can be answered efficiently.
* Dynamic connectivity problem: Maintain an undirected graph G so that edges may be inserted or deleted and connectivity queries can be answered effciently.

### Dynamic connectivity in Forests

* Consider the special-case of the dynamic connectivity problem: Maintain an undirected forest F so that edges may be inserted an deleted and connectivity queries can be answered efficiently.
* Each deleted edge splits a tree in two; each added edge joins two trees and never closes a cycle.
* We can use Euler Tour trees data structure for dynamic connectitivy in forests. High-level idea: Instead of storing the trees in the forest, store their Euler tours.
  * Each edge insertion or deletion translates into a set of manipulations on the Euler tours of the trees in the forest.
  * Checking whether two nodes are connected can be done by checking if they're in the same Euler tour.

Goal: Support these three operations:
* link(u, v): Add in edge {u, v}. The assumption is that u and v are in separate trees.
* cut(u, v): Cut the edge {u, v}. The assumption is that the edge exists in the tree.
* are-connected(u, v): Return whether u and v are connected.

### REF
* https://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/17/Small17.pdf
