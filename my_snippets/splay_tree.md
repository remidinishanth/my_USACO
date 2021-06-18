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

* Balanced binary search tree with the additional property that recently accessed elements are quick to access again.
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

**Case 1: Zig-Zag**  X is the right child of a left child (or the left child of a right child):  let P be the parent of X, and let G be the grandparent of X.  We first rotate X and P left, and then rotate X and G right, as illustrated at right.    
                                      
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

![](images/Splay_tree_1.png)

```

       z               [x]               y
      / \              / \              / \
     y   D            /   \            A   z       (A < y < B < x < z < D)
    / \         ->   y     z    <-        / \
   A  [x]           / \   / \           [x]  D
      / \          A   B C   D          / \
     B   C                             B   C
```

**Case 2: Zig-Zig** X is the left child of a left child (or the right child of a right child):  the ORDER of the rotations is REVERSED from case 1.  We start with the grandparent, and rotate G and P right.Then, we rotate P and X right.(Note: In case 1, we rotated X and P first) 

The mirror image of this case-- where X and P are both right children--uses the same rotations in mirror image:
rotate G and P left, then P and X left.  Both the case illustrated above and its mirror image are called the "zig-zig" case.

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
![](images/Splay_tree_2.png)

```
      z             x
     / \           / \
    y   D         A   y
   / \      <->      / \                (A < x < B < y < C < z < D)
 [x]  C             B  [z]
 / \                   / \
A   B                 C   D
```

We repeatedly apply zig-zag and zig-zig rotations to X; each pair of rotations raises X two levels higher in the tree. Eventually, either X will reach the
root (and we're done), or X will become the child of the root. One more case handles the latter circumstance, this happens when our node is odd number of levels down from root.

**Case 3:** X's parent P is the root:  we rotate X and P so that X becomes the root.  This is called the "zig" case.

```
      P             X     
     / \           / \    
    X   ^         ^   P   
   / \ /C\  ==>  /A\ / \  
  ^  ^               ^  ^ 
 /A\/B\     Zig     /B\/C\
```

![](images/Splay_tree_3.png)

```
    y             x
   / \           / \   
 [x]  C   <->   A  [y]
 / \               / \
A   B             B   C
```

Here's an example of "find(7)".  Note how the tree's balance improves.

```
    11                     11                      11                  [7]     
   /  \                   /  \                    /  \                 / \     
  1    12                1    12                [7]   12              1   11   
 / \                    / \                     / \                  /\   / \  
0   9                  0   9                   1   9                0 5   9  12
   / \                    / \                 / \ / \                / \ / \   
  3   10  =zig-zig=>    [7]  10  =zig-zag=>  0  5 8  10   =zig=>    3  6 8  10 
 / \                    / \                    / \                 / \         
2   5                  5   8                  3   6               2   4        
   / \                / \                    / \                 
  4  [7]             3   6                  2   4                
     / \            / \                                                      
    6   8          2   4
```

By inspecting each of the three cases (zig-zig, zig-zag, and zig), you can observe a few interesting facts.  First, in none of these three cases does the depth of a subtree increase by more than two.  Second, every time X takes two steps toward the root (zig-zig or zig-zag), every node in the subtree rooted at X moves at least one step closer to the root.  As more and more nodes enter X's subtree, more of them get pulled closer to the root.
                                           
```
                    9                           1       
                   / \                         / \      
                  8   10                      0   8     
                 /                               / \    
                7            =========>         6   9   
               /              find(1)          / \   \  
              6                               4   7  10 
             /                               / \        
            5                               2   5       
           /                                 \          
          4                                   3         
         /                               
        3                                
       /                                 
      2                                  
     /                                   
    1                                    
   /                                     
  0                                      

```

A node that initially lies at depth d on the access path from the root to X moves to a final depth no greater than 3 + d/2.  In other words, all the nodes deep down the search path have their depths roughly halved.  This tendency of nodes on the access path to move toward the root prevents a splay tree from staying unbalanced for long (as the example at right illustrates).

Note: Let's see Why we rotate through Grandparent first during zig-zig step?

Say what happens when we insert 1 to 8 inorder in the splay tree? When we insert value 2, 2 becomes right child of 1 but when after splaying at 2, 2 becomes root. So splay tree becomes very unbalanced. But while building this tree, we just used only constant time per insert.

If in zig-zig step, if we didn't rotate first at the Grandparent, then our tree would've looked like

```
                    9                                      1    
                   / \                                    / \
                  8   10                                 0   10
                 /                                          /
                7                                          9
               /                                          /
              6                                          8
             /                                          /
            5                                          7
           /                 ========>                / 
          4                   find(1)                6  
         /                                          /   
        3                                          5    
       /                                          /     
      2                                          4  
     /                                          /   
    1                                          3    
   /                                          /     
  0                                          2
```

[2]  Entry min();                        
     Entry max();

These methods begin by finding the entry with minimum or maximum key, just like
in an ordinary binary search tree.  Then, they splay the node containing the
minimum or maximum key to the root.

[3]  Entry insert(Object k, Object v);

insert() begins by inserting the new entry (k, v), just like in an ordinary
binary search tree.  Then, it splays the new node to the root.

[4]  Entry remove(Object k);

An entry having key k is removed from the tree, just as with ordinary binary
search trees.  Recall that the node containing k is removed if it has zero or
one children.  If it has two children, the node with the next higher key is
removed instead.  In either case, let X be the node removed from the tree.
After X is removed, splay X's parent to the root.  Here's a sequence
illustrating the operation remove(2).

```
                      2             4               5
                     / \           / \             / \
                    1   7         1   7           4   7
                       / \   ==>     / \   ==>   /     \
                      5   8         5   8       1       8
                     /
                    4
```

In this example, the key 4 moves up to replace the key 2 at the root.  After the node containing 4 is removed(Note that node 2 is not removed, 
value of 2's node is replaced with value 4, not the node), its parent (containing 5) splays to the root.

If the key k is not in the tree, splay the node where the search ended to the root, just like in a find() operation.

Note that it is important to splay the tree after delete, because say we want to delete node 9, and we want to find min in left tree, which is 0, now say we want to delete node 0, If we don't splay we might need to travel down to 1 again. So it might be linear again. Hence we need to splay for delete operation.

```
                   9   
                  / \  
                 8   10
                /      
               7       
              /        
             6         
            /          
           5           
          /            
         4             
        /              
       3               
      /                
     2                 
    /                  
   1                   
  /                    
 0                     
```

Running time:
```
                                                                             .
                                                                            .
When do operations occur that take more than O(log n) time?                /
Consider inserting a long sequence of numbers in order:  1, 2, 3,         4   
etc.  The splay tree will become a long chain of left children (as       /    
illustrated at right).  Now, find(1) will take Theta(n) time.           3     
However, each of the n insert() operations before the find took O(1)   /      
time, so the average for this example is O(1) time per operation.     2       
                                                                     /
                                                                    1
```

Why Splaying Works
* Claim: After doing a splay at x, the average depth of any nodes on the access path to x is halved.
* Intuitively, splaying x benefits nodes near x, not just x itself.
* Each rotation done only slightly penalizes each other part of the tree (say, adding +1 or +2 depth).
* Each splay rapidly cuts down the height of each node on the access path.
* Slow growth in height, combined with rapid drop in height, is a hallmark of amortized efficiency.

The fastest implementations of splay trees don't use the bottom-up splaying
strategy discussed here.  Splay trees, like 2-3-4 trees, come in bottom-up and
top-down versions.  Instead of doing one pass down the tree and another pass
up, top-down splay trees do just one pass down.  This saves a constant factor
in the running time.

There is an interesting conjecture about splay trees called the _dynamic_
_optimality_conjecture_:  that splay trees are as asymptotically fast on _any_
sequence of operations as _any_ other type of search tree with rotations.
What does this mean?  Any sequence of splay tree operations takes amortized
O(log n) time per operation, but sometimes there are sequences of operations
that can be processed faster by a sufficiently smart data structure.  One
example is accessing the same ten keys over and over again (which a splay tree
can do in amortized O(1) time per access).  The dynamic optimality conjecture
guesses that if _any_ search tree can exploit the structure of a sequence of
accesses to achieve asymptotically faster running time, so can splay trees.

The conjecture has never been proven, but it's not clear whether it's been
disproven, either.

One special case that has been proven is that if you perform the find operation
on each key in a splay tree in order from the smallest key to the largest key,
the total time for all n operations is O(n), and not O(n log n) as you might
expect.


Splay trees provide make it extremely easy to perform the following operations:
* lookup
* insert
* delete
* predecessor / successor
* join
* split

**Lookups:** To do a lookup in a splay tree:
* Search for that item as usual BST.
* If it's found, splay it up to the root.
* Otherwise, splay the last-visited node to the root.

**Insertions:** To insert a node into a splay tree:
* Insert the node as usual.
* Splay it up to the root.

**Join:** To join two trees T₁ and T₂, where all keys in T₁ are less than the keys in T₂:
* Splay the max element of T₁ to the root.
* Make T₂ a right child of T₁.

**Split:** To split T at a key k:
* Splay the successor of k up to the root.
* Cut the link from the root to its left child.

**Delete:** To delete a key k from the tree:
* Splay k to the root.
* Delete k.
* Join the two resulting subtrees.

Contrast this with red/black trees:
* No need to store any kind of balance information.
* Only three rules to memorize.

TODO: https://codeforces.com/contest/899/submission/44463457

REF: 
* https://people.eecs.berkeley.edu/~jrs/61b/lec/36
* https://www.link.cs.cmu.edu/splay/
