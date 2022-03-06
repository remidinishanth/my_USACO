We will look at different data structures for trees and when to use them:
* Euler Tour Tree
  * Way to linearize tree into an array, subtree of the original tree becomes subarray  
  * Queries & Updates involving subtrees
* HLD
  * Partition our tree into set of heavy and light paths, any path from u to v can be partitioned into atmost 2 lg(n) different splits.
  * Path queries and path updates
  * Path and Subtree queries: We can even combine Euler tour into HLD construction, first go to heavy child and then other children. [REF](https://codeforces.com/blog/entry/53170)
* Centroid Decomposition
  * Any path from u to v in the original tree can be represented as u to lca(u,v) and lca(u,v) to v. lca(u,v) is lowest common ancestor in centroid tree.
  * Find a path among all the paths with certain property - we can use divide and conquer(centroid decomposition) technique. Whenever we are decomposing using some centroid c, we consider all the paths going through this centroid. For example if we want to find the longest path in the tree, at this centroid, if we have maximum depth in each subtree, then we can combine the first max and second max.
  * For every i, query for number of paths of length i in the tree, FFT while combining in centroid decomposition. We can use any complex structures while conquer/combine step of Centroid decomposition.
  * Given (x, d) - Find all nodes reachable from x and within distance d.
* Reachability tree (Used rarely)
  * Update (x, d, v) - Start at x, traverse all the edges whose length ≤ d, add v to all the nodes visited. [REF](https://discuss.codechef.com/t/tulips-editorial/12281)
  * Query (x, d) - Sum of all values reachable from x if we only traverse edges of length ≤ d
  * Construct the “reachability tree” of the given tree. We define the reachability tree as a rooted binary tree with 2N−1 nodes(using N vertices and N - 1 edges of original tree) such that each leaf represents a node in the original tree, and each internal node represents a set of nodes in the original tree that are reachable from each other using edges up to a certain length. In other words, each internal node is associated with some value, say k, such that the leaves under it represent a maximal set of nodes in the original tree that are reachable from each other using edges of length ≤ k. This tree can be constructed in O(NlogN) time.
  * How to construct this? Consider the heaviest edge of the tree as the root node, split the tree by removing this edge. Attach the reachability tree of the components as left and right nodes of the edge we removed. If the subtree formed is a single node, attach it as a leaf node. This can be constructed recursively. Height of this tree can be upto N.
  * LCA of two nodes of this tree will give us the maximum weight of edge we need to traverse.

## TODO https://codeforces.com/blog/entry/88669
