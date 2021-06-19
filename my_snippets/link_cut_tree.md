## Dynamic Connectivity Problem

* Graph connectivity problem: Given an undirected graph G, preprocess the graph so that queries of the form "are nodes u and v connected?" can be answered efficiently.
* Dynamic connectivity problem: Maintain an undirected graph G so that edges may be inserted or deleted and connectivity queries can be answered effciently.

Dynamic connectivity in forests can be solved by Euler tour trees.

Goal: Support these three operations:
* link(u, v): Add in edge {u, v}. The assumption is that u and v are in separate trees.
* cut(u, v): Cut the edge {u, v}. The assumption is that the edge exists in the tree.
* are-connected(u, v): Return whether u and v are connected.
* compute(u, root): compute some function on path from u to root

![](images/Link_cut_tree_1.png)

## Link/cut tree

A link/cut tree is a data structure for representing a forest, a set of rooted trees, and offers the following operations:

* Add a tree consisting of a single node to the forest.
* Link: Attach a node to another node as its child.
* Cut: Given a node in one of the trees, disconnect it (and its subtree) from the tree of which it is part.
* Given a node, find the root of the tree to which it belongs. By doing this operation on two distinct nodes, one can check whether they belong to the same tree.

All of these operations are supported by link/cut trees in O(log n) amortized time where n is the size of the tree.

![](images/Link_cut_tree_2.png)

**Structure:** We take a tree where each node has an arbitrary degree of unordered nodes and split it into paths. We call this the represented tree. These paths are represented internally by auxiliary trees (here we will use splay trees, nodes are stored by depth), where the nodes from left to right represent the path from root to the last node on the path. Nodes that are connected in the represented tree that are not on the same preferred path (and therefore not in the same auxiliary tree) are connected via a path-parent pointer. This pointer is stored in the root of the auxiliary tree representing the path.

![](images/Link_cut_tree_6.png)

### Preferred path decomposition

Preferred child of node v:
* None if last access in v's subtree was v
* w if last access was in child w's subtree

Preferred path = chain of preferred edges, preferred paths partitions represented tree into paths.

![](images/Link_cut_tree_4.png)

### Auxiliary trees

Represent each preferred path by a splay tee keyed on **depth**
* root of aux. tree stores path parent - path's top node's parent in represented tree
* aux trees + path parent pointers = tree of auxiliary trees

![](images/Link_cut_tree_5.png)

![](images/Link_cut_tree_3.png)

### Access/Expose

The Expose(v)/Access(v) operation is an extended splay operation that brings v to the root of the auxiliary/virtual tree without changing the structure of the rooted tree. The important parts of this operation are to make sure that the path from v to the root is preferred(solid) and that the splay tree representing the path to which v belongs is rooted at v.

![](images/Link_cut_tree_7.png)

After performing an access to node v, it will no longer have any preferred children, and will be at the end of the path. Since nodes in the auxiliary tree are keyed by depth, this means that any nodes to the right of v in the auxiliary tree must be disconnected. In a splay tree this is a relatively simple procedure; we splay at v, which brings v to the root of the auxiliary tree. We then disconnect the right subtree of v, which is every node that came below it on the previous preferred path. The root of the disconnected tree will have a path-parent pointer, which we point to v.

We now walk up the represented tree to the root R, breaking and resetting the preferred path where necessary. To do this we follow the path-parent pointer from v (since v is now the root, we have direct access to the path-parent pointer). If the path that v is on already contains the root R (since the nodes are keyed by depth, it would be the left most node in the auxiliary tree), the path-parent pointer will be null, and we are done the access. Otherwise we follow the pointer to some node on another path w. We want to break the old preferred path of w and reconnect it to the path v is on. To do this we splay at w, and disconnect its right subtree, setting its path-parent pointer to w. Since all nodes are keyed by depth, and every node in the path of v is deeper than every node in the path of w (since they are children of w in the represented tree), we simply connect the tree of v as the right child of w. We splay at v again, which, since v is a child of the root w, simply rotates v to root. We repeat this entire process until the path-parent pointer of v is null, at which point it is on the same preferred path as the root of the represented tree R.

![](images/Link_cut_tree_8.png)
![](images/Link_cut_tree_9.png)

### Find Root

FindRoot refers to finding the root of the represented tree that contains the node v. Since the access subroutine puts v on the preferred path, we first execute an access. Now the node v is on the same preferred path, and thus the same auxiliary tree as the root R. Since the auxiliary trees are keyed by depth, the root R will be the leftmost node of the auxiliary tree. So we simply choose the left child of v recursively until we can go no further, and this node is the root R. The root may be linearly deep (which is worst case for a splay tree), we therefore splay it so that the next access will be quick.

### Path
For this operation we wish to do some aggregate function over all the nodes (or edges) on the path from root R to node v (such as "sum" or "min" or "max" or "increase", etc.). To do this we access v, which gives us an auxiliary tree with all the nodes on the path from root R to node v. The data structure can be augmented with data we wish to retrieve, such as min or max values, or the sum of the costs in the subtree, which can then be returned from a given path in constant time.

![](images/Link_cut_tree_10.png)

### Cut
Here we would like to cut the represented tree at node v. First we access v. This puts all the elements lower than v in the represented tree as the right child of v in the auxiliary tree. All the elements now in the left subtree of v are the nodes higher than v in the represented tree. We therefore disconnect the left child of v (which still maintains an attachment to the original represented tree through its path-parent pointer). Now v is the root of a represented tree. Accessing v breaks the preferred path below v as well, but that subtree maintains its connection to v through its path-parent pointer.

### Link
If v is a tree root and w is a vertex in another tree, link the trees containing v and w by adding the edge(v, w), making w the parent of v. To do this we access both v and w in their respective trees, and make w the left child of v. Since v is the root, and nodes are keyed by depth in the auxiliary tree, accessing v means that v will have no left child in the auxiliary tree (since as root it is the minimum depth). Adding w as a left child effectively makes it the parent of v in the represented tree.

![](images/Link_cut_tree_11.png)

```python
Switch-Preferred-Child(x, y):
  path-parent(right(x)) = x
  right(x, y)


Access(v):
  Switch-Path-Parent(v, null)
  while (v is not root)
    w = path-parent(v)
    splay(w)
    Switch-Path-Parent(w, v)
    path-parent(v) = null
    v = w
  splay(v)


Link(v, w):
  Access(v)
  Access(w)
  left(v) = w
  
  
Cut(v):
  Access(v)
  left(v) = null
```  

### Demonstration of Expose/Access

Assume that splay trees are built on values of nodes.

1. Step 1 consists of walking from from v to the root of the auxiliary trees, Whenever the walk enters a splay tree(preferred path/solid edges) at some node w, a SPLAY(w) operation is performed, bringing w to the root of that tree. Note that at the end of step 1 of an Expose(v) operation, v will be
connected to the root of the auxiliary/virtual tree only by dashed edges.
2. Splicing(Changing preferred child): Step 2 consists of walking from v to the root of the virtual tree exchanging along the way each middle edge with the left subtree of the parent. A middle child of a node w and its left child can be exchanged (without changing the rooted tree) only if w is the root of its splay tree. This justifies our execution of step 1 first since at the end of step 1 all edges from v to the root are middle edges. Note that after performing this operation on every edge to the root of the virtual tree, there will be a solid path from the root of the rooted tree to the node being exposed.
3. Step 3 consists of walking from v to the root in the virtual tree, splaying v to the root.

![](images/Link_cut_tree_14.png)

Say we do `expose(15)` in the following rooted tree.

![](images/Link_cut_tree_12.png)
![](images/Link_cut_tree_13.png)
![](images/Link_cut_tree_15.png)

## Applications

* Link/cut trees can be used to solve the dynamic connectivity problem for acyclic graphs. Given two nodes x and y, they are connected if and only if `FindRoot(x) = FindRoot(y)`. Another data structure that can be used for the same purpose is Euler tour tree.
* In solving the maximum flow problem, link/cut trees can be used to improve the running time of Dinic's algorithm from `O(V^2E)` to `O(VE log V)`.

## REF
* https://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/17/Small17.pdf
* https://en.wikipedia.org/wiki/Link/cut_tree
* https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-854j-advanced-algorithms-fall-2008/lecture-notes/lec8.pdf
* https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-851-advanced-data-structures-spring-2012/calendar-and-notes/MIT6_851S12_Lec19.pdf
