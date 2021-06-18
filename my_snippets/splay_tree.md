                              CS61B: Lecture 36
                          Wednesday, April 23, 2014

Today's reading:  Goodrich & Tamassia, Section 10.3.

SPLAY TREES
===========
A splay tree is a type of balanced binary search tree.  Structurally, it is
identical to an ordinary binary search tree; the only difference is in the
algorithms for finding, inserting, and deleting entries.

All splay tree operations run in O(log n) time _on_average_, where n is the
number of entries in the tree.  Any single operation can take Theta(n) time in
the worst case.  But any sequence of k splay tree operations, with the tree
initially empty and never exceeding n items, takes O(k log n) worst-case time.

Although 2-3-4 trees make a stronger guarantee (_every_ operation on a 2-3-4
tree takes O(log n) time), splay trees have several advantages.  Splay trees
are simpler and easier to program.  Because of their simplicity, splay tree
insertions and deletions are typically faster in practice (sometimes by a
constant factor, sometimes asymptotically).  Find operations can be faster or
slower, depending on circumstances.

Splay trees are designed to give especially fast access to entries that have
been accessed recently, so they really excel in applications where a small
fraction of the entries are the targets of most of the find operations.

Splay trees have become the most widely used basic data structure invented in
the last 30 years, because they're the fastest type of balanced search tree for
many applications.

* Balanced binary search tree
* All operations: O(log n) time on average(Note: there is not randomization involved)
* Single operation: θ(n) worst-case time, where n is # of items in tree
* Any sequence of k ops, starting from empty tree, never > n items in tree, all operations takes O(k log n) worst-case time. Few operations might be slow but many operations are faster and hence they balance out.
* Fast access to entries accessed recently.

Tree Rotations
--------------
Like many types of balanced search trees, splay trees are kept balanced with the help of structural changes called _rotations_.  There are two   
types--a left rotation and a right rotation--and each is the other's reverse.  Suppose that X and Y are binary tree nodes, and A, B, and C are subtrees.  A rotation transforms either of the configurations illustrated above to the other.  Observe that the binary search tree invariant is preserved:  keys in A are less than or equal to X; keys in C are greater than or equal to Y; and keys in B are >= X and <= Y.

```
        Y                             X     
       / \        rotate left        / \    
      X   ^      <------------      ^   Y   
     / \ /C\                       /A\ / \  
    ^  ^         ------------>         ^  ^ 
   /A\/B\         rotate right        /B\/C\
```

Rotations are also used in AVL trees and red-black trees, which are discussed by Goodrich and Tamassia.

Unlike 2-3-4 trees, splay trees are not kept perfectly balanced, but they tend
to stay reasonably well-balanced most of the time, thereby averaging O(log n)
time per operation in the worst case (and sometimes achieving O(1) average
running time in special cases).

* Splay trees are not kept perfectly balanced. One reason why they have O(n) worst case time for some operations.

Splay Tree Operations
---------------------
[1]  Entry find(Object k);

The find() operation in a splay tree begins just like the find() operation in
an ordinary binary search tree:  we walk down the tree until we find the entry
with key k, or reach a dead end (a node from which the next logical step leads
to a null pointer).

However, a splay tree isn't finished its job.  Let X be the node where the
search ended, whether it contains the key k or not.  We _splay_ X up the tree
through a sequence of rotations, so that X becomes the root of the tree.  Why?
One reason is so that recently accessed entries are near the root of the tree,
and if we access the same few entries repeatedly, accesses will be very fast.
Another reason is because if X lies deeply down an unbalanced branch of the
tree, the splay operation will improve the balance along that branch.

When we splay a node to the root of the tree, there are three cases that
determine the rotations we use.

**Case 1:**  X is the right child of a left child (or the left child of a right child):  let P be the parent of X, and let G be the grandparent of X.  We first rotate X and P left, and then rotate X and G right, as illustrated at right.    
                                      
The mirror image of this case-- where X is a left child and P is a right child--uses the same rotations in mirror image:  rotate X and P right, then X and G left.  Both the case illustrated below and its mirror image are called the "zig-zag" case.

```
      G               G               X     
     / \             / \             / \    
    P   ^           X   ^           P   G   
   / \ /D\  ==>    / \ /D\  ==>    / \ / \  
  ^  X            P  ^            ^  ^ ^  ^ 
 /A\/ \          / \/C\          /A\/BVC\/D\
    ^  ^        ^  ^                        
   /B\/C\      /A\/B\     Zig-Zag
```

**Case 2:** X is the left child of a left child (or the right child of a right child):  the ORDER of the rotations is REVERSED from case 1.  We   
start with the grandparent, and rotate G and P right.Then, we rotate P and X right.(Note: In case 1, we rotated X and P first) 

The mirror image of this case-- where X and P are both right children--uses the same rotations in mirror image:
rotate G and P left, then P and X left.  Both the case illustrated above and its mirror image are called the "zig-zig" case.

We repeatedly apply zig-zag and zig-zig rotations to X; each pair of rotations raises X two levels higher in the tree. Eventually, either X will reach the
root (and we're done), or X will become the child of the root.  One more case handles the latter 
circumstance.


```
          G               P               X       
         / \             / \             / \      
        P   ^           X   G           ^   P     
       / \ /D\  ==>    / \ / \    ==>  /A\ / \    
      X  ^            ^  ^ ^  ^            ^  G   
     / \/C\          /A\/BVC\/D\          /B\/ \  
    ^  ^                                     ^  ^ 
   /A\/B\                       Zig-Zig     /C\/D\

```

**Case 3:** X's parent P is the root:  we rotate X and P so that X becomes the root.  This is called the "zig" case.

```
      P             X     
     / \           / \    
    X   ^         ^   P   
   / \ /C\  ==>  /A\ / \  
  ^  ^               ^  ^ 
 /A\/B\     Zig     /B\/C\
```

TODO: https://codeforces.com/contest/899/submission/44463457

REF: https://people.eecs.berkeley.edu/~jrs/61b/lec/36
