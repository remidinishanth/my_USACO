We will look at different data structures for trees and when to use them:
* Euler Tour Tree
  * Way to linearize tree into an array, subtree of the original tree becomes subarray  
  * Queries & Updates involving subtrees
* HLD
  * Partition our tree into set of heavy and light paths, any path from u to v can be partitioned into atmost 2 lg(n) different splits.
  * Path queries and path updates
  * Path and Subtree queries: We can even combine Euler tour into HLD construction, first go to heavy child and then other children. [REF](https://codeforces.com/blog/entry/53170)
* Centroid Decomposition
* Reachability tree (Used rarely)
  * Update (x, d, v) - Start at x, traverse all the edges whose length ≤ d, add v to all the nodes visited. 
