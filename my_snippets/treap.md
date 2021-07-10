A Cartesian tree or deramid (Treap) is a data structure that combines a **binary search tree** and a **binary heap**. Hence its second name: treap (tree + heap) and deramid (tree + pyramid).

![](images/Treap_node1.png)

More strictly, this is a binary tree whose nodes contain two values, a key and a priority. It is also a binary search tree by key and a heap by priority. Assuming that all keys and all priorities are different, we find that if a tree item contains (x₀, y₀), then all elements (x, y) in the left subtree are such that x < x₀, all the elements in the right subtree are such that x > x₀, as well as the left and right subtree have: y < y₀. For example

![](images/treap_example2.png)

* **Cartesian Tree** : A Cartesian Tree is just a binary tree on a sequence of pairs that is heap-ordered on one of the elements of each pair , and BST-ordered on the other element.
* **Treap** : In a Cartesian Tree, if we assign random values to each heap-ordered element, then the expected height of the resulting tree is  𝑂(𝑙𝑜𝑔𝑁).

![](images/treap_example6.png)

**Theorem-1:** Given a set of nodes i.e  `(Bᵢ, Hᵢ)`  pairs (with distinct Hᵢ's), only a unique cartesian tree would exist for these nodes irrespective of their order of insertion.

Proof: For a given set of nodes , the node with maximum priority would form the root of the cartesian tree. All the nodes with key less than(equal to) the B𝑟𝑜𝑜𝑡  would lie in the left subtree of root and all the nodes with key greater than  B𝑟𝑜𝑜𝑡  will lie in the right subtree. Now inductively the left and right subtrees can be built.

**Theorem-2:** Random assignment of Hᵢ values in a Cartesian Tree helps maintain the height of the tree to be approximately O(𝑙𝑜𝑔 n).

Intuition: In a simple BST , the height of the BST depends upon the choice of the root . The closer the root lies to the median of the given data, the better would be the height . Say we insert (a₁, a₂, ..., aₙ), any element can become the root `aᵢ` if it has maximum priority, since the elements ≤ aᵢ go to left subtree and remaining go to right subtree, we can think of it like quick sort algorithm. Therefore the height will be O(𝑙𝑜𝑔 n).

### Motivation

* If we build a binary search tree with totally random values, the resulting tree is (with high probability) within a constant factor of balanced. Approximately `4.3 ln n`.
* Moreover, the average depth of a given node is often very low. Approximately `2 ln n`.
* If we structure the BST as if it were a random tree, we get (with high probability) a very good data structure!
* In a Cartesian Tree, if we assign random values to each heap-ordered element , then the expected height of the resulting tree is  `𝑂(𝑙𝑜𝑔 n)` . This is the entire idea behind Treaps.

### Comaprision with other BSTs
* Compared with AVL and red-black trees, it is simpler to implement and easy to understand. In Treap, the height is not deterministic like other balanced BST's like AVL, red-black trees.
* Compared with the Splay tree, it is usually used for the ordered set, BST performance is far better than Splay. Splay trees are useful for link cut trees. Splay will break in case you need persistence.
* Maybe some people want to say SBT(size balanced tree) replaces treaps, I haven't implemented SBT, it is said to be faster. SBT rebalanced by examining the sizes of each node's subtrees, this makes it very convenient to implement the select-by-rank and get-rank operations that implement an order statistic tree. [PEG](http://wcipeg.com/wiki/Size_Balanced_Tree)
* However, Binary search trees such as SBT, Splay trees, and the rotating version of Treap, cannot easily implement 'persistent operations'.  Let's take a look at the rotating Treap. Now we should know why it can't be persisted, right? If it is rotated, the original parent-child relationship will be destroyed, the original path and tree form will be destroyed, which is unacceptable for persistence. If Treap becomes non-rotating, then we can find that as long as it can be persisted, Merge and Split can be made persistent.

## Rotating version of Treaps

In a BST there are two simple operations that allows us to modify the tree and keep the BST property, the right and left rotations.

![](images/treap_rotation.png).

### Insertion

Inserting an element based on rotations. Say we want to insert an element (9, 41). The first step is to ignore the priorities and insert like a BST, We can search the position where it has to be inserted based on the key. Even though BST property is being preserved, the heap property is not. We will use rotations to fix the heap property.

![](images/treap_example4.png)

* Insertion into a treap is a combination of normal BST insertion and heap insertion.
* First, insert the node doing a normal BST insertion. This places the value into the right place.
* Next, bubble the node upward in the tree by rotating it with its parent until its value is smaller than its parent.

### Deletion

* In general, removing a node from a BST is quite difficult because we have to make sure not to lose any nodes. Deleting internal nodes split the tree.
* However, removing leaves is very easy, since they have no children.
* It would seem that, since a treap has extra structure on top of that of a BST, that removing from a treap would be extremely hard.
* However, it's actually quite simple:
  * To maintain the heap property, it’s easy to see that we have to rotate the tree from the children with higher priority.
  * Once the node is a leaf, delete it.

## Split and Merge

Treap supports two basic and unique operations: split and merge , both in O(H) where H is height of treap i.e O(logN).

![](images/treap_example5.png)

Split

![](images/treap_split3.png)

Merge

![](images/Treap_merge1.png)

### Split

* split(T,X):  It splits a given treap T into two different treaps L and R such that L contains all the nodes with Bᵢ ≤ X and R contains all the nodes with Bᵢ > X. The original treap T is destroyed/doesn’t exist anymore after the split operation.

![](images/treap_split1.png)


![](images/treap_split2.png)

![](images/treap_split5.png)

If the key we want to split is greater than root X then

![](images/treap_split4.png)

If the key we want to split is less than root X then 

![](images/treap_split6.png)

```python
def split(t: Treap, k: int) -> ⟨Treap, Treap⟩:
  if t == None
    return ⟨None, None⟩     
  else if k > t.x 
    ⟨t1, t2⟩ = split(t.right, k)
    t.right = t1
    return ⟨t, t2⟩
  else 
    ⟨t1, t2⟩ = split(t.left, k)
    t.left = t2
    return ⟨t1, t⟩
```

### Merge

* merge(L,R): The merge operation merges two given treaps L and R into a single treap T and L and R are destroyed after the operation. A very important assumption of the merge operation is that the largest value of L is less than the smallest value of R (where value refers to the Bᵢ values of the particular node). Hence we observe that two treaps obtained after a split operation can always be merged to give back the original treap.

![](images/Treap_merge5.png)

![](images/Treap_merge2.png)

If priority of X > priority of Y

![](images/Treap_merge3.png)

If priority of X < priority of Y

![](images/Treap_merge4.png)

```python
def merge(t1: Treap, t2: Treap) -> Treap:
  if t2 == None
    return t1
  if t1 == None
    return t2
  else if t1.y > t2.y
    t1.right = merge(t1.right, t2)
    return t1
  else 
    t2.left = merge(t1, t2.left)
    return t2
```

### Operations on Treap using Split and Merge(Non-rotating version)

#### Insert

* Insert(X): To insert a value X into our BST, we first chose a Y = rand(), such that (X,Y) represents the new node to be inserted in the treap. Then, keep on going down the tree like a simple BST searching for the correct pos where X should be inserted unless either the correct position is found OR we encounter the first node E s.t. priority(E) < Y . Here, call split(E,X) and attach L and R as left and right subtrees of node (X,Y).

Split once, and Merge twice.

![](images/treap_insert_sm1.png)

insert(T,k) - where k.x is the key and k.y is the priority

* Implementation #1
  1)  Let's split our tree according to the key that we want to add, that is split(T, k.x) → <T₁, T₂>
  2)  We merge the first tree with a new element, that is merge(T₁, K) → T₁
  3)  We merge the resulting tree with the second, that is merge(T₁, T₂) → T


* Implementation #2
  1)  First, we go down the tree (as in the usual binary search tree by k.x), but we stop at the first element in which the priority value turned out to be less that k.y
  2)  Now we split(T, k.x) → <T₁, T₂>, the found element(from the element along with its entire subtree).
  3)  Update T₁ and T₂ as the left and write elements of the added element.
  4)  We put the resulting tree(node with T₁ and T₂ as children) in place of the element found in step 1.

Implementation #1 uses two merge operations, In second implementation merge is not used at all.

#### Delete/Remove

* Delete(X) : Go down the tree like a BST unless node to be deleted is found. If the node is found, call merge function for it's left and right subtrees and attach the resulting tree to the parent of the node to be deleted.

Split twice and Merge once.

![](images/treap_delete_sm1.png)

remove(T, x) removes node with key x from the tree T

* Implementation #1
  1)  Let's split our tree according to the key that we want to delete, that is split(T, k.x) → <T₁, T₂>
  2)  Now we seperate the element from the left tree, the right most child of the tree T₁
  3)  We merge the resulting tree with the second, that is merge(T₁, T₂) → T

* Implementation #2
  1) We go down the tree (as in the usual binary search tree by x), and look for the item to remove. 
  2) Having found the element, we can merge on it's left and right sons
  3) The result of the procedure merge is put in the place of the deleted element.

The first implementation uses split operatioin, and in the second implementation, split is not used at all.

### C++ implementation

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

struct item {
    int key, prior;
    item * l, * r;
    item() { }
    item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;

// splits into <=key and >key
void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key) // key is in left node, split left
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
}

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
}

void erase (pitem & t, int key) {
    if (t->key == key) {
        pitem th = t;
        merge (t, t->l, t->r);
        delete th;
    }
    else
        erase (key < t->key ? t->l : t->r, key);
}

pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}
```

We can maintain additional properties in the node like `count` - number of nodes in subtre. When a tree changes (nodes are added or removed etc.), `cnt` of some nodes should be updated accordingly. We'll create two functions: `cnt()` will return the current value of `cnt` or `0` if the node does not exist, and `upd_cnt()` will update the value of `cnt` for this node assuming that for its children `L` and `R` the values of `cnt` have already been updated. Evidently it's sufficient to add calls of `upd_cnt()` to the end of `insert`, `erase`, `split` and `merge` to keep `cnt` values up-to-date.

```cpp
struct item {
    int key, prior, cnt;
    item * l, * r;
    item() { }
    item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};

int cnt (pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
    if (t)
        t->cnt = 1 + cnt(t->l) + cnt (t->r);
}

void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key) // key is in left node, split left
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd_cnt(t);
}

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}
```

Using `cnt` we can support finding `k-th` element in the treap. We can also store other metadata like sum of nodes in the subtree etc. We can even add values to all nodes > some_value using lazy tag at the corresponding node.

## Applications
* A variant of treaps called Implicit Treaps can be used to perform all the operations which interval trees like segment tree and fenwick tree can (including lazy propagation).
* Idea of sparse segment tree and sparse fenwick tree to handle very large ranges and limited queries can also be extended to treaps resulting in a variant called sparse implicit treaps.
* Treaps also make a good persistent BST mainly because of their simplicity to code and a constant average number of operations upon insert/delete. In general, they are used to represent an ordered set (store and check if an element exists in the set) in O(log n) time. However, by augmenting the nodes, we can
use BBSTs for a much larger variety of problems, such as range min/max and sum queries.
* Treaps can also be extended to multiple dimensions in the form of quadtreaps which are a balanced variant of a quadtree data structure.

## Offline Building 

#### Algorithm 1 O(n log n)

Say we are given `x₁ < x₂ < .. < xₙ`, we can randomly assign priorities `y₁, y₂, .., yₙ`, now we have pairs `(xᵢ,yᵢ)`. Let's sort the elements according to priorities. Choose the first element and make it the root, all the elements less that root.x will go to left subtree and all other elements go to right child. We can do this recursively. Since the priorities are assigned randomly, the height of the tree is expected O(log n) and hence the algorithms works in O(n log n).

#### Algorithm 2 O(n log n)

let's sort the pairs in descending order and put them in the queue, We pick first two elements from the queue and merge them into a tree and put them at the end of the queue, then we do the same with next two etc.(Sorting is required because merge needs one tree's elements to be less than the other tree.) Thus, we will merge first the size 1 trees, then size 2 trees and so on. After each round the queue size is reduced by half. So the total running time will be O(n logn).

#### Algorithm 3 O(n)

Say we are given `n` nodes in sorted order then we can build the treap in O(n) time instead of O(n log n) time. The idea is to split the array into two parts, from `0` tom `mid - 1` and `mid + 1` to `n - 1` where `n` is the size of the array and `mid = n/2`. If we select the median element as our root then the left and right subtrees have roughly the same size.

![](images/treap_example1.png)

We don't have to worry about priorities, if we want to have priorities then we can assign random priroity to all nodes and heapify the tree priorities(not the array values) to satisfy the heap property.

```cpp
void heapify (pitem t) {
    if (!t) return;
    pitem max = t;
    if (t->l != NULL && t->l->prior > max->prior)
        max = t->l;
    if (t->r != NULL && t->r->prior > max->prior)
        max = t->r;
    if (max != t) {
        swap (t->prior, max->prior);
        heapify (max);
    }
}

pitem build (int * a, int n) {
    // Construct a treap on values {a[0], a[1], ..., a[n - 1]}
    if (n == 0) return NULL;
    int mid = n / 2;
    pitem t = new item (a[mid], rand ());
    t->l = build (a, mid);
    t->r = build (a + mid + 1, n - mid - 1);
    heapify (t);
    upd_cnt(t)
    return t;
}
```

Note: calling `upd_cnt(t)` is only necessary if you need the subtree sizes.

## Cartesian Tree of an array

Given a sequence of numbers (or any totally ordered objects), there exists a binary min-heap whose inorder traversal is that sequence. This is known as the Cartesian tree for that sequence.

We’ll select the minimum value of the array to become the root of the tree, let’s say it is found at position `i`. The left child will be the minimum value in the interval `[0, i-1]` and the right child will be the minimum value in the interval `[i+1, n-1]`. We continue this process recursively.

![](images/cartesian_tree_1.png)

* Relationship with Treap: If we choose the key as index of element and priority as the value of the element, the indicies follow BST property and priorities follow heap property. It’s not totally right to say that a cartesian tree is a treap because treaps have random values for y. Randomization of priorities are used to get logarithmic height(with high probability).
* A range minimum query on a sequence is equivalent to a lowest common ancestor query on the sequence's Cartesian tree. Hence, RMQ may be reduced to LCA using the sequence's Cartesian tree.
* The suffix tree of a string may be constructed from the suffix array and the longest common prefix array. The first step is to compute the Cartesian tree of the longest common prefix array.

How to construct cartesian tree?

![](images/cartesian_tree_2.png)

* We can insert one element after another from left to right. We just need to keep a pointer to the right most element and use parent pointers to traverse till the root to find the element < current element and insert it there.
* We can also do this without storing parent pointers, we just maintain a stack of the all right child from the root, pop until we find the element < current element. For each new sequence value x, the stack is popped until it is empty or its top element is smaller than x, and then x is pushed onto the stack. The following figure shows the stack after inserting element 9.

![](images/cartesian_tree_4.png)

```cpp
int n,h[MAXN];
int st[MAXN],t;
int fa[MAXN],ls[MAXN],rs[MAXN],root;

int main()
{
    for(int i=1; i<=n; i++)
    {
        while(t && h[st[t-1]] > h[i]) ls[i] = st[--t];
        if(t) rs[st[t-1]] = i;
        st[t++] = i; // push the current element onto stack
    }
    for(int i=1; i<=n; i++) fa[ls[i]] = fa[rs[i]] = i;
    for(int i=1; i<=n; i++) if(!fa[i]) root = i;
}
```

## Implicit Treap

Let's take a dynamic array data structure. In its standard implementation(example: `std::vector<int>`), we can add an element to the end of a vector, find out the value of an element at a certain position, change an element by number and delete the last element. Suppose we need a data structure with the above properties, as well as operations: add an element anywhere (with a corresponding change in the numbering of elements) and delete any element (also with a corresponding change in the numbering). Such a structure can be implemented on the basis of a Treap, the result is often called a Treap with implicit key.

Implicit treap is a simple modification of the regular treap which is a very powerful data structure. In fact, implicit treap can be considered as an array with the following procedures implemented (all in O(logN) in the online mode):

* Inserting an element in the array in any position
* Removal of an arbitrary element
* Finding sum, minimum / maximum element etc. on an arbitrary interval. Maintain any objective function and query over an arbitrary interval. (All the operations supported by a segment tree including range updates using lazy propagation).
* Addition, painting on an arbitrary interval
* Reversing elements on an arbitrary interval
* Cut an array `A[1..n]` at any position `i` such that it is divided into two different arrays `B[1..i]` , `C[i+1...n]`.
* Merge two different arrays `P[1..n₁]` , `Q[1..n₂]` into a single array `R[1..n₁,n₁+1,...n₁₊₂]`.

Implicit Treap provides the user with an array-like interface, but with Treap inside. The key idea to use build a treap with array indices as keys instead of element values.

![](images/implicit_treap_21_7_1.png)

Since we are using array index as key of BST, if we insert or delete an element indices of other elements will have to change for about O(n) nodes. This would be very slow. 

To avoid this, we will not explicitly store the index `i` as the key but we will calculate on the fly. For this we need to store auxiliary quantity `c` - subtree size - number of vertices in the subtree of our vertex. Index value is number of elements in our structure that are to the left of our element. In other words, we will consider the ordinal number of our element in the tree, reduced by one, as a key. 

![](images/implicit_treap_21_7_2.png)

How to calculate this? While going along the path from the root to a certain vertex, we sum up all such values in the left subtrees that we did not go to, increased by one. Hence the `key for a node t = sz(t->l) + sz(p->l)` for all parents of `t` such that `t` occurs in the right subtree of `p`.

Since we don't store the index explicitly and calculate it on the fly, this is named as Implicit Treap.

Split operation: Split and merge are based on index(subtree sizes), there is no explicit key which we use to split.

```python
def update(Treap t):
  t.size = 1 + t.left.size + t.right.size
  
def split(Treap t, int k) ->  ⟨Treap, Treap⟩:
  if t == None
    return ⟨None, None⟩  
  int l = t.left.size
  if l >= k
    ⟨t1, t2⟩ = split(t.left, k)
    t.left = t2
    update(t) # update count - subtree size
    return ⟨t1, t⟩
  else
    ⟨t1, t2⟩ = split(t.right, k - l - 1)
    t.right = t1
    update(t)
    return ⟨t, t2⟩
```

![](images/implicit_tree_21_7_6_2.png)

Merge two implicit treaps:

![](images/implicit_tree_21_7_6_1.png)



### C++ implementation of split and merge

Note that the key of a node is the number of nodes less than it (such nodes can be present not only in its left subtree but also in left subtrees of its ancestors). More specifically, the implicit key for some node T is the number of vertices `cnt(T→L)` in the left subtree of this node plus similar values `cnt(P→L)+1` for each ancestor P of the node T, if T is in the right subtree of P.

Now it's clear how to calculate the implicit key of current node quickly. Since in all operations we arrive to any node by descending in the tree, we can just accumulate this sum and pass it to the function. If we go to the left subtree, the accumulated sum does not change, if we go to the right subtree it increases by `cnt(T→L)+1`.

```cpp
void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    int cur_key = add + cnt(t->l); // implicit key
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}
```

Now let's consider the implementation of various operations on implicit treaps:

* **Insert element:**
Suppose we need to insert an element at position `pos`. We divide the treap into two parts, which correspond to arrays `[0..pos-1]` and `[pos..sz]`; to do this we call `split(T, T1, T2, pos)`. Then we can combine tree T1 with the new vertex by calling `merge(T1, T1, new_item)` (it is easy to see that all preconditions are met). Finally, we combine trees `T1` and `T2` back into `T` by calling `merge(T, T1, T2)`.

* **Delete element:**
This operation is even easier: find the element to be deleted `T`, perform merge of its children `L` and `R`, and replace the element `T` with the result of merge. In fact, element deletion in the implicit treap is exactly the same as in the regular treap.

* **Find sum / minimum, etc. on the interval:**
First, create an additional field `F` in the item structure to store the value of the target function for this node's subtree. This field is easy to maintain similarly to maintaining sizes of subtrees: create a function which calculates this value for a node based on values for its children and add calls of this function in the end of all functions which modify the tree.
Second, we need to know how to process a query for an arbitrary interval `[A; B]`.
To get a part of tree which corresponds to the interval `[A; B]`, we need to call `split(T, T1, T2, A)`, and then `split(T2, T2, T3, B - A + 1)`: after this `T2` will consist of all the elements in the interval `[A; B]`, and only of them. Therefore, the response to the query will be stored in the field `F` of the root of `T2`. After the query is answered, the tree has to be restored by calling `merge(T, T1, T2)` and `merge(T, T, T3)`.

* **Addition / painting on the interval:**
We act similarly to the previous paragraph, but instead of the field `F` we will store a field add which will contain the added value for the subtree (or the value to which the subtree is painted). Before performing any operation we have to "push" this value correctly - i.e. change `T→L→add` and `T→R→add`, and to clean up add in the parent node. This way after any changes to the tree the information will not be lost.

* **Reverse on the interval:**
This is again similar to the previous operation: we have to add boolean flag `rev` and set it to true when the subtree of the current node has to be reversed. "Pushing" this value is a bit complicated - we swap children of this node and set this flag to true for them.

Here is an example implementation of the implicit treap with reverse on the interval. For each node we store field called value which is the actual value of the array element at current position. We also provide implementation of the function output(), which outputs an array that corresponds to the current state of the implicit treap.

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    pitem l, r;
    // add extra variables here
    bool rev;
    item(int v){
        value = v;
        prior = rng();
        l = r = NULL;
        rev = false;
    }
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if(it->l)  it->l->rev ^= true;
        if(it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    upd_cnt(t);
}

// 1-based indexing, split into [1, pos] and [pos+1, n]
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push(t);
    int implicit_key = add + cnt(t->l);
    if (key <= implicit_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt(t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}

// inorder traveral
void output (pitem t) {
    if (!t)  return;
    push(t);
    output(t->l);
    printf("%d ", t->value);
    output(t->r);
}
```

Using the ideas of a Cartesian tree by implicit key, it is possible to implement a data structure such as [Rope](https://neerc.ifmo.ru/wiki/index.php?title=Rope).

### STL rope

* Sequence with O(log(n)) random access, insert, erase at any position
* `s.push_back(x);`
* `s.insert(i,r)` // insert rope r at position i
* `s.erase(i,k)` // erase subsequence `[i,i+k)`
* `s.substr(i,k)` // return new rope corresponding to subsequence `[i,i+k)`
* `s[i]` // access ith element (cannot modify)
* `s.mutable_reference_at(i)` // access ith element (allows modification)
* `s.begin()` and `s.end()` are const iterators (use mutable_begin(), mutable_end() to allow modification)

```cpp
#include <ext/rope>
using namespace __gnu_cxx;
rope<int> s;
```

REF: https://github.com/mhunicken/icpc-team-notebook-el-vasito/commit/55b54f9d23b6ed6aaa7f72712a616580e4b018eb, https://codeforces.com/blog/entry/10355

<details>
 <summary> Implementation of treap as interval tree </summary>
 
```cpp
typedef struct node{
    int prior,size; 
    int val; // value stored in the array 
    int sum; // whatever info you want to maintain in segtree for each node 
    int lazy; // whatever lazy update you want to do 
    struct node *l,*r; 
}node;
typedef node* pnode;
int sz(pnode t){
    return t?t->size:0;
}
void upd_sz(pnode t){
    if(t)t->size=sz(t->l)+1+sz(t->r);
}
void lazy(pnode t){
    if(!t || !t->lazy) return;
    t->val += t->lazy; // operation of lazy
    t->sum += t->lazy*sz(t);
    if(t->l) t->l->lazy += t->lazy; // propagate lazy
    if(t->r) t->r->lazy += t->lazy;
    t->lazy=0;
}
void reset(pnode t){
    if(t) t->sum = t->val; // lazy already propagated
}
void combine(pnode& t,pnode l,pnode r){ // combine segtree ranges
    if(!l || !r) return void(t = l?l:r);
    t->sum = l->sum + r->sum;
}
void operation(pnode t){ // operation of segtree
    if(!t )return;
    reset(t); // node represents single element of array
    lazy(t->l);lazy(t->r); // imp: propagate lazy before combining l,r
    combine(t,t->l,t);combine(t,t,t->r);
}
void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
    if(!t) return void(l=r=NULL);
    lazy(t);
    int curr_pos = add + sz(t->l);
    if(curr_pos <= pos) // element at pos goes to "l"
        split(t->r,t->r,r,pos,curr_pos+1), l=t;
    else
        split(t->l,l,t->l,pos,add), r=t;
    upd_sz(t);
    operation(t);
}
void merge(pnode &t,pnode l,pnode r){ // result/left/right array
    lazy(l);lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior) merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd_sz(t);
    operation(t);
}
pnode init(int val){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior=rand();ret->size=1;
    ret->val=val;ret->sum=val;ret->lazy=0;
    return ret;
}
int range_query(pnode t,int l,int r){ // [l,r]
    pnode L,mid,R;
    split(t,L,mid,l-1);split(mid,t,R,r-l); // note: r-l !!
    int ans = t->sum;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}
void range_update(pnode t,int l,int r,int val){//[l,r]
    pnode L,mid,R;
    split(t,L,mid,l-1);split(mid,t,R,r-l);//note: r-l!!
    t->lazy+=val; //lazy_update
    merge(mid,L,t); 
    merge(t,mid,R); 
}     
``` 

source: Quora Tanuj Khattar
</details>

<details>
    <summary> Xuzijian implementation for RMQ & RAQ </summary>
 
```cpp
// for RMQ & RAQ 
constexpr  int INF = __INT_MAX__;

class ImplicitTreap {
    xorshift rnd;
    struct Node {
         int value, min, lazy;
         int priority, cnt;
         bool rev;
        Node * l, * r;
        Node ( int value, int priority): value (value), min (INF), lazy ( 0 ), priority (priority), cnt ( 1 ), rev ( false ), l ( nullptr ), r ( nullptr ) {}
    } * root = nullptr ;
     using Tree = Node *;

    int cnt (Tree t) {
         return t? t-> cnt: 0 ;
    }

    int get_min (Tree t) {
         return t? t-> min: INF;
    }

    void update_cnt (Tree t) {
         if (t) {
            t-> cnt = 1 + cnt (t-> l) + cnt (t-> r);
        }
    }

    void update_min (Tree t) {
         if (t) {
            t-> min = min (t-> value, min (get_min (t-> l), get_min (t-> r)));
        }
    }

    void pushup (Tree t) {
        update_cnt (t), update_min (t);
    }

    void pushdown (Tree t) {
         if (t && t-> rev) {
            t-> rev = false ;
            swap (t-> l, t-> r);
            if (t-> l) t-> l-> rev ^ = 1 ;
             if (t-> r) t-> r-> rev ^ = 1 ;
        }
        if (t && t-> lazy) {
             if (t-> l) {
                t-> l-> lazy + = t-> lazy;
                t-> l-> min + = t-> lazy;
            }
            if (t-> r) {
                t-> r-> lazy + = t-> lazy;
                t-> r-> min + = t-> lazy;
            }
            t-> value + = t-> lazy;
            t-> lazy = 0 ;
        }
        pushup (t);
    }
    
    void split (Tree t, int key, Tree & l, Tree & r) {
         if (! t) {
            l = r = nullptr ;
             return ;
        }
        pushdown (t);
        int implicit_key = cnt (t-> l) + 1 ;
         if (key <implicit_key) {
            split (t-> l, key, l, t-> l), r = t;
        } else {
            split (t-> r, key --implicit_key, t-> r, r), l = t;
        }
        pushup (t);
    }
    
    void insert (Tree & t, int key, Tree item) {
        Tree t1, t2;
        split (t, key, t1, t2);
        merge (t1, t1, item);
        merge (t, t1, t2);
    }

    void merge (Tree & t, Tree l, Tree r) {
        pushdown (l);
        pushdown (r);
        if (! l ||! r) {
            t = l? l: r;
        } else  if (l-> priority> r-> priority) {
            merge (l-> r, l-> r, r), t = l;
        } else {
            merge (r-> l, l, r-> l), t = r;
        }
        pushup (t);
    }
    
    void erase (Tree & t, int key) {
        Tree t1, t2, t3;
        split (t, key + 1 , t1, t2);
        split (t1, key, t1, t3);
        merge (t, t1, t2);
    }

    void add (Tree t, int l, int r, int x) {
        Tree t1, t2, t3;
        split (t, l, t1, t2);
        split (t2, r --l, t2, t3);
        t2-> lazy + = x;
        t2-> min + = x;
        merge (t2, t2, t3);
        merge (t, t1, t2);
    }

    int findmin (Tree t, int l, int r) {
        Tree t1, t2, t3;
        split (t, l, t1, t2);
        split (t2, r --l, t2, t3);
        int ret = t2-> min;
        merge (t2, t2, t3);
        merge (t, t1, t2);
        return ret;
    }

    void reverse (Tree t, int l, int r) {
         if (l> r) return ;
        Tree t1, t2, t3;
        split (t, l, t1, t2);
        split (t2, r --l, t2, t3);
        t2-> rev ^ = 1 ;
        merge (t2, t2, t3);
        merge (t, t1, t2);
    }

    // Shift left so that the beginning of [l, r) is m. Same specifications as std :: rotate 
    void rotate (Tree t, int l, int m, int r) {
        reverse (t, l, r);
        reverse (t, l, l + r --m);
        reverse (t, l + r --m, r);
    }

    void dump (Tree t) {
         if (! t) return ;
        pushdown (t);
        dump (t-> l);
        cout << t-> value << "" ;
        dump (t-> r);
    }
    
public :
     void insert ( int pos, int x) {
        insert (root, pos, new Node (x, rnd.random ()));
    }

    void add ( int l, int r, int x) {
        add (root, l, r, x);
    }

    int findmin ( int l, int r) {
         return findmin (root, l, r);
    }

    void erase ( int pos) {
        erase (root, pos);
    }

    void reverse ( int l, int r) {
        reverse (root, l, r);
    }

    void rotate ( int l, int m, int r) {
        rotate (root, l, m, r);
    }

    void dump () {
        dump (root);
        cout << endl;
    }
};
```

https://xuzijian629.hatenablog.com/entry/2018/12/08/000452

Monoid code is also present in the above blog.
</details>

TODO: Evolved Implicit Treap: Priority sum and pair query.

## Problems

1. How can we augment the BBST to effectively function as a min, max, and sum segment tree? In what cases can we do it the other way around?
2. SPOJ KPMATRIX: Given a NxM matrix of integers (1 ≤ N, M ≤ 250), and two integers A and B (−10⁹ ≤ A, B ≤ 10⁹), find the number of submatrices with sum between A and B.
3. SPOJ GSS6: Given an integer array of length N, apply Q operations which can be any of inserting an element, deleting an element, and finding the maximal contiguous non-empty sum in a given interval (1 ≤ N, Q ≤ 10⁵). All values in the array, as well as insertions, are between −10⁴ and 10⁴.

#### CF Edu Round 15 F T-Shirts

There are t-shirts of `n ≤ 2·10⁵` different types each has a cost `cᵢ` and quality `qᵢ`. There are `k` customers each has amount `bᵢ`, each customer wants to buy maximum possible number of highest quality t-shirts. If two shirts are having same quality they choose the cheaper one. Customer don't buy more than one same type of t-shirt. Determine the number of t-shirts each customer will buy. All customers act independently, the purchase of one does not affect the purchase of another.

source: https://codeforces.com/contest/702/problem/F

<details>
 <summary>Treap with lazy tags</summary>

* First we sort the t-shirts according to decreasing quality and increasing price.
* We can maintain the amount left for a customer in the treap using lazy propogation.
* From highest quality t-shirts to lowest quality t-shirts, we update the people who can buy by splitting the treap based on the amount left, once this is done we merge the treap nodes.

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;

struct item {
    int prior, value;
    int idx;
    int shirts; // number of shirts bought
    int lazy_shirt, lazy_cost;
    pitem l, r;

    item(int amount, int index, int s=0){
        value = amount;
        idx = index;
        shirts = s;
        prior = rng();
        l = r = NULL;
        lazy_cost = lazy_shirt = 0;
    }
};

void push(pitem t){
    if(!t) return;
    t->shirts += t->lazy_shirt;
    t->value += t->lazy_cost;
    if(t->l){
        t->l->lazy_shirt += t->lazy_shirt;
        t->l->lazy_cost += t->lazy_cost;
    }
    if(t->r){
        t->r->lazy_shirt += t->lazy_shirt;
        t->r->lazy_cost += t->lazy_cost;
    }
    t->lazy_shirt = t->lazy_cost = 0;
}


// Splits into < k and >= k
void split(pitem t, pitem & l, pitem & r, int key) {
    if (!t)
        return void( l = r = nullptr );
    push(t);
    if (key <= t->value)
        split(t->l, l, t->l, key), r = t;
    else
        split(t->r, t->r, r, key), l = t;
}

void merge(pitem &t, pitem l, pitem r){
    push(l); push(r);
    if(!l || !r)
        t = l ? l : r;
    else if(l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
}

void insert(pitem &t, pitem it){
    pitem l, r;
    split(t, l, r, it->value);
    merge(t, l, it);
    merge(t, t, r);
}

vector<int> count_shirts;

void visit(pitem &t){
    if(t == nullptr) return;
    push(t);
    visit(t->l);
    count_shirts[t->idx] = t->shirts;
    visit(t->r);
}

void tour(pitem &t, vector<array<int,3>>& V){
    if(!t) return;
    push(t);
    tour(t->l, V);
    V.push_back({t->value, t->idx, t->shirts});
    tour(t->r, V);
}

int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int,int>> shirts;
    for(int i=0;i<n;i++){
        int cost, quality;
        scanf("%d%d", &cost, &quality);
        shirts.push_back({-quality, cost});
    }
    // sort by decreasing order of quality and increasing order of price
    sort(shirts.begin(), shirts.end());
    for(int i=0;i<n;i++) shirts[i].first = -shirts[i].first;

    int k;
    vector<pair<int,int>> customers;
    scanf("%d", &k);
    for(int i=0;i<k;i++){
        int amount;
        scanf("%d", &amount);
        customers.push_back({amount, i});
    }
    sort(customers.begin(), customers.end());

    pitem treap = nullptr;
    for(int i=0;i<k;i++){
        pitem cust = new item(customers[i].first, customers[i].second);
        merge(treap, treap, cust);
    }

    for(int i=0;i<n;i++){
        int cost = shirts[i].second;
        pitem t1, t2;
        split(treap, t1, t2, cost);
        if(t2 != NULL){
            t2->lazy_shirt++;
            t2->lazy_cost -= cost;
        }
        // to merge these values have to be < the other treap
        pitem t3;
        split(t2, t2, t3, cost);
        /* while(t2 != NULL){ */
        /*     push(t2); */
        /*     pitem cur = new item(t2->value, t2->idx, t2->shirts); */
        /*     insert(t1, cur); */
        /*     merge(t2, t2->l, t2->r); */
        /* } */
        vector<array<int, 3>> res;
        tour(t2, res);
        for(auto it:res){
            pitem cur = new item(it[0], it[1], it[2]);
            insert(t1, cur);
        }
        merge(treap, t1, t3);
    }

    count_shirts = vector<int>(k);
    visit(treap);
    for(int s: count_shirts) printf("%d ", s);
    printf("\n");
    return 0;
}
```

We can also use the following insert operation but the only thing to note is to use same `<=` with split and insert. If we change the last line to `insert(it->value < t->value ? t->l : t->r, it);` then CF gives TLE.

```cpp
void insert(pitem &t, pitem it){
    push(t);
    if(!t) t = it;
    else if(it->prior > t->prior) split(t, it->l, it->r, it->value), t=it;
    else insert(it->value <= t->value ? t->l : t->r, it);
}
```

</details>

TODO: https://codeforces.com/blog/entry/92340

#### SPOJ Ordered Set

In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

* INSERT(S,x): if x is not in S, insert x into S
* DELETE(S,x): if x is in S, delete x from S 
 
and the two type of queries

* K-TH(S) : return the k-th smallest element of S
* COUNT(S,x): return the number of elements of S smaller than x

source: https://www.spoj.com/problems/ORDERSET/

<details>
 <summary>Treap with k-th element and count of elements less than x</summary>
 
```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
 
typedef struct item * pitem;
struct item {
    int prior, key, cnt;
    pitem l, r;
 
    item(int v){
        prior = rng();
        key = v;
        cnt = 1;
        l = r = NULL;
    }
};
 
int cnt (pitem it) {
    return it ? it->cnt : 0;
}
 
void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
 
// split into <key and >=key
void split(pitem t, pitem &l, pitem &r, int key){
    if(t == NULL){
        l = r = NULL;
        return;
    }
    if(t->key < key) // key in right child
        split(t->r, t->r, r, key), l = t;
    else
        split(t->l, l, t->l, key), r = t;
    upd_cnt(t);
}
 
void merge(pitem &t, pitem l, pitem r){
    if(l == NULL || r == NULL){
        t = l ? l : r;
        return;
    }
    if(l->prior > r->prior) // left child becomes root
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    upd_cnt(t);
}
 
void insert(pitem &t, pitem it){
    if(t == NULL){
        t = it;
        return;
    }
    if(t->prior < it->prior)
        split(t, it->l, it->r, it->key), t = it;
    else
        insert(t->key < it->key ? t->r : t->l, it);
    upd_cnt(t);
}
 
void erase(pitem &t, int key){
    if(t == NULL) return;
    if(t->key == key){
        pitem th = t;
        merge(t, t->l, t->r);
        delete th;
        upd_cnt(t);
        return;
    }
    erase(key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}
 
// zero indexed
int kth_element(pitem t, int k){
    while(t != NULL){
        if(cnt(t->l) == k)
            return t->key;
        if(cnt(t->l) > k) t = t->l;
        else{
            k -= cnt(t->l) + 1;
            t=t->r;
        }
    }
    return -1;
}
 
int count_less(pitem t, int key){
    pitem l, r;
    split(t, l, r, key);
    int res = cnt(l);
    merge(t, l, r);
    return res;
}
 
int main() {
    int q;
    scanf("%d", &q);
    pitem treap = NULL;
    while(q--){
        char ch;
        int x;
        scanf(" %c %d", &ch, &x);
        if(ch == 'I'){
            erase(treap, x);
            pitem it = new item(x);
            insert(treap, it);
        }
        else if(ch == 'D') erase(treap, x);
        else if(ch == 'K'){
            if(cnt(treap) < x){
                printf("invalid\n");
                continue;
            }
            printf("%d\n", kth_element(treap, x-1));
        }
        else printf("%d\n", count_less(treap, x));
    }
    return 0;
}
```
</details> 

#### Shandom Ruffle 

Given an array of size `n`, we are asked to do `shandom_ruffle` as follows `n` times using `(aᵢ, bᵢ)` during the i-th `shandom_ruffle`.

```java
shandom_ruffle(int a, int b, int[] array) {
  int bStart=b;
  while (a<bStart && b<=array.length) {
    swap(array[a], array[b]); //swap the values at indecies a and b
    a++;
    b++;
  }
}
```

https://codeforces.com/gym/102787/problem/A

<details>
 <summary> Using Implicit treap </summary>
 
Split the array at `[a, a_end]` , `[b, b_end]` and swap these while merging.
 
```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;
struct item {
    int prior, idx, cnt;
    pitem l, r;
    // add extra variables here
    item(int index){
        idx = index;
        prior = rng();
        l = r = NULL;
    }
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    upd_cnt(t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    int implicit_key = add + cnt(t->l);
    if (key <= implicit_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt(t);
}

void output(pitem t){
    if(t==NULL) return;
    output(t->l);
    printf("%d ", t->idx);
    output(t->r);
}

int main() {
    int n;
    scanf("%d", &n);
    pitem treap = NULL;
    for(int i=1;i<=n;i++){
        pitem new_item = new item(i);
        merge(treap, treap, new_item);
    }
    for(int q=0;q<n;q++){
        int a, b;
        scanf("%d %d", &a, &b);
        int aend = b-1, bend = n;
        int len = min(aend - a, bend - b);
        aend = a + len, bend = b + len;
        pitem t1, t2, t3, t4, t5;
        // split at a-1, aend, b-1, bend
        // split into t1, t2, t3, t4, t5
        // swap t2 and t4
        // merge into t1, t4, t3, t2, t5
        split(treap, treap, t5, bend);
        split(treap, treap, t4, b-1);
        split(treap, treap, t3, aend);
        split(treap, t1, t2, a-1);
        merge(treap, t1, t4);
        merge(treap, treap, t3);
        merge(treap, treap, t2);
        merge(treap, treap, t5);
    }
    output(treap);
    printf("\n");
    return 0;
}
```
</details> 

#### Sneetches and Speeches 1

Given a binary string, for each query we are given `[l, r]` and we are asked to flip the bits `s[i] ^= 1` for l ≤ i ≤ r, and we need to answer the maximum length of continous sequence of bits with same parity.

<details>
 <summary>Using Implicit treap with lazy tags</summary>

Make sure to push/propogate the lazy tags before we use the actual node values, otherwise we might be reading outdated values present in the node.

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;

struct item {
    int prior, value, cnt;
    pitem l, r;
    // add extra variables here
    int idx;
    bool rev, flip;
    int count[2], max_count[2];
    int prefix[2], suffix[2];
    item(int v, int i){
        idx = i;
        value = v;
        prior = rng();
        l = r = NULL;
        rev = false;
        flip = false;
        count[0] = count[1] = 0;
        max_count[0] = max_count[1] = 0;
        prefix[0] = prefix[1] = 0;
        suffix[0] = suffix[1] = 0;
        count[v] = max_count[v] = prefix[v] = suffix[v] = 1;
    }
};

int cnt(pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt(pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

int count(pitem it, int i){
    return it == NULL ? 0 : it->count[i];
}

int prefix(pitem it, int i){
    return it == NULL ? 0 : it->prefix[i];
}

int suffix(pitem it, int i){
    return it == NULL ? 0 : it->suffix[i];
}

int max_count(pitem it, int i){
    return it == NULL ? 0 : it->max_count[i];
}

int max_count(pitem it){
    return max(max_count(it, 0), max_count(it, 1));
}

void push(pitem &it) {
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if(it->l)  it->l->rev ^= true;
        if(it->r)  it->r->rev ^= true;
    }
    if(it && it->flip){
        it->flip = false;
        swap(it->count[0], it->count[1]);
        swap(it->suffix[0], it->suffix[1]);
        swap(it->prefix[0], it->prefix[1]);
        swap(it->max_count[0], it->max_count[1]);
        it->value ^= 1;
        if(it->l) it->l->flip ^= true;
        if(it->r) it->r->flip ^= true;
    }
}

void pull(pitem it){
    upd_cnt(it);
    if(it == NULL) return;
    push(it->l);
    push(it->r);
    for(int i=0;i<2;i++){
        // Update count
        it->count[i] = count(it->l, i) + count(it->r, i) + (it->value == i);
        // prefix
        it->prefix[i] = prefix(it->l, i);
        if(count(it->l, i) == cnt(it->l) && it->value == i)
            it->prefix[i] = max(it->prefix[i], cnt(it->l) + 1 + prefix(it->r, i));
        // suffix
        it->suffix[i] = suffix(it->r, i);
        if(count(it->r, i) == cnt(it->r) && it->value == i)
            it->suffix[i] = max(it->suffix[i], suffix(it->l, i) + 1 + cnt(it->r));
        // max_count
        it->max_count[i] = max(max_count(it->l, i), max_count(it->r, i));
        if(it->value == i)
            it->max_count[i] = max(it->max_count[i], suffix(it->l, i) + 1 + prefix(it->r, i));
    }
}

void printBT(const std::string& prefix, pitem t, bool isLeft)
{
    if( t != nullptr )
    {
        /* push(t); */
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        printf("%d: [v:%d z:%d o:%d f:%d mc:%d p0:%d s0:%d p1:%d s1:%d]\n",
            t->idx, t->value, t->count[0], t->count[1], t->flip, max_count(t), t->prefix[0], t->suffix[0], t->prefix[1], t->suffix[1]);

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), t->l, true);
        printBT(prefix + (isLeft ? "│   " : "    "), t->r, false);
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    pull(t);
}

// 1-based indexing, split into [1, pos] and [pos+1, n]
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push(t);
    int implicit_key = add + cnt(t->l);
    if (key <= implicit_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    pull(t);
}


void op(pitem &t, int l, int r){
    pitem t1, t2, t3;
    split(t, t, t3, r);
    split(t, t1, t2, l-1);
    t2->flip ^= true;
    /* printBT("", t1, false); */
    /* printBT("", t2, false); */
    /* printBT("", t3, false); */
    merge(t, t1, t2);
    merge(t, t, t3);
}


int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    string s;
    cin >> s;
    pitem treap = NULL;
    for(int i=0;i<n;i++){
        pitem cur = new item(s[i] == '1', i+1);
        merge(treap, treap, cur);
    }
    while(q--){
        int t, l, r;
        scanf("%d %d %d", &t, &l, &r);
        op(treap, l, r);
        printf("%d\n", max_count(treap));
        /* printBT("", treap, false); */
    }
    return 0;
}
```
</details> 

#### Sneetches and Speeches 3

Similar to above problem, we are given two additional type of queries, one is to sort the range `[l, r]` and the other is to reverse the range `[l, r]`. We need to answer the maximum length of continous segment of same parity for all three type of queries.

<details>
 <summary>Implicit Treap with 3 different lazy tags</summary>

Important thing in this problem is to clear the already exisiting lazy tags while setting all values to zero or all values to one.

```cpp
    // clear all the pending operations
    it->l->all_zero = true;
    // all the following ops doesn't apply anymore
    it->l->all_one = it->l->flip = it->l->rev = false;
```

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;

struct item {
    int prior, value, cnt;
    pitem l, r;
    // add extra variables here
    int idx;
    bool rev, flip, all_zero, all_one;
    int count[2], max_count[2];
    int prefix[2], suffix[2];
    item(int v, int i){
        idx = i;
        value = v;
        prior = rng();
        l = r = NULL;
        rev = false;
        flip = false;
        all_one = false;
        all_zero = false;
        count[0] = count[1] = 0;
        max_count[0] = max_count[1] = 0;
        prefix[0] = prefix[1] = 0;
        suffix[0] = suffix[1] = 0;
        count[v] = max_count[v] = prefix[v] = suffix[v] = 1;
    }
};

int cnt(pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt(pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

int count(pitem it, int i){
    return it == NULL ? 0 : it->count[i];
}

int prefix(pitem it, int i){
    return it == NULL ? 0 : it->prefix[i];
}

int suffix(pitem it, int i){
    return it == NULL ? 0 : it->suffix[i];
}

int max_count(pitem it, int i){
    return it == NULL ? 0 : it->max_count[i];
}

int max_count(pitem it){
    return max(max_count(it, 0), max_count(it, 1));
}

// lazy propogation
void push(pitem &it) {
    if(it && it->all_zero){
        it->all_zero = false;
        it->value = 0;
        it->max_count[0] = it->prefix[0] = it->suffix[0] = it->count[0] = cnt(it);
        it->max_count[1] = it->prefix[1] = it->suffix[1] = it->count[1] = 0;
        if(it->l){
            // clear all the pending operations
            it->l->all_zero = true;
            // all the following ops doesn't apply anymore
            it->l->all_one = it->l->flip = it->l->rev = false;
        }
        if(it->r){
            it->r->all_zero = true;
            it->r->all_one = it->r->flip = it->r->rev = false;
        }
    }
    if(it && it->all_one){
        it->all_one = false;
        it->value = 1;
        it->max_count[1] = it->prefix[1] = it->suffix[1] = it->count[1] = cnt(it);
        it->max_count[0] = it->prefix[0] = it->suffix[0] = it->count[0] = 0;
        if(it->l){
            it->l->all_one = true;
            it->l->all_zero = it->l->flip = it->l->rev = false;
        }
        if(it->r){
            it->r->all_one = true;
            it->r->all_zero = it->r->flip = it->r->rev = false;
        }
    }
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        swap(it->prefix[0], it->suffix[0]);
        swap(it->prefix[1], it->suffix[1]);
        if(it->l)  it->l->rev ^= true;
        if(it->r)  it->r->rev ^= true;
    }
    if(it && it->flip){
        it->flip = false;
        swap(it->count[0], it->count[1]);
        swap(it->suffix[0], it->suffix[1]);
        swap(it->prefix[0], it->prefix[1]);
        swap(it->max_count[0], it->max_count[1]);
        it->value ^= 1;
        if(it->l) it->l->flip ^= true;
        if(it->r) it->r->flip ^= true;
    }
}

void pull(pitem it){
    if(it == NULL) return;
    upd_cnt(it);
    push(it->l);
    push(it->r);
    for(int i=0;i<2;i++){
        // Update count
        it->count[i] = count(it->l, i) + count(it->r, i) + (it->value == i);
        // prefix
        it->prefix[i] = prefix(it->l, i);
        if(count(it->l, i) == cnt(it->l) && it->value == i)
            it->prefix[i] = max(it->prefix[i], cnt(it->l) + 1 + prefix(it->r, i));
        // suffix
        it->suffix[i] = suffix(it->r, i);
        if(count(it->r, i) == cnt(it->r) && it->value == i)
            it->suffix[i] = max(it->suffix[i], suffix(it->l, i) + 1 + cnt(it->r));
        // max_count
        it->max_count[i] = max(max_count(it->l, i), max_count(it->r, i));
        if(it->value == i)
            it->max_count[i] = max(it->max_count[i], suffix(it->l, i) + 1 + prefix(it->r, i));
    }
}

void printBT(const std::string& prefix, pitem t, bool isLeft)
{
    if( t != nullptr )
    {
        /* push(t); */
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        printf("%d: [v:%d z:%d o:%d f:%d mc:%d p0:%d s0:%d p1:%d s1:%d]\n",
            t->idx, t->value, t->count[0], t->count[1], t->flip, max_count(t), t->prefix[0], t->suffix[0], t->prefix[1], t->suffix[1]);

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), t->l, true);
        printBT(prefix + (isLeft ? "│   " : "    "), t->r, false);
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    pull(t);
}

// 1-based indexing, split into [1, pos] and [pos+1, n]
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push(t);
    int implicit_key = add + cnt(t->l);
    if (key <= implicit_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    pull(t);
}


void op(pitem &t, int l, int r, int type){
    pitem t1, t2, t3;
    split(t, t, t3, r);
    split(t, t1, t2, l-1);
    if(type == 1) t2->flip ^= true;
    else if(type == 2) t2->rev ^= true;
    else{
        int zeros = count(t2, 0);
        pitem t4, t5;
        split(t2, t4, t5, zeros);
        if(t4){
            t4->all_zero = true;
        }
        if(t5){
            t5->all_one = true;
        }
        merge(t2, t4, t5);
    }
    /* printBT("", t1, false); */
    /* printBT("", t2, false); */
    /* printBT("", t3, false); */
    merge(t, t1, t2);
    merge(t, t, t3);
}

void output(pitem t){
    if(t==NULL) return;
    push(t);
    output(t->l);
    /* printf("%d", t->value); */
    output(t->r);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    string s;
    cin >> s;
    pitem treap = NULL;
    for(int i=0;i<n;i++){
        pitem cur = new item(s[i] == '1', i+1);
        merge(treap, treap, cur);
    }
    while(q--){
        int t, l, r;
        scanf("%d %d %d", &t, &l, &r);
        op(treap, l, r, t);
        printf("%d\n", max_count(treap));
        /* printBT("", treap, false); */
        /* output(treap); */
        /* printf("\n"); */
    }
    return 0;
}
```
</details> 

#### Trick or Treap

The first line will contain a single integer q. `1 ≤ q ≤ 5*10⁵` q lines follow. They will look like one of the following:

- 1 y - Add a `node[q]` with value y. In this case `0 ≤ y ≤ 10⁵`.

- 2 y z - If `node[y]` and `node[z]` are in different group then merge them. Nodes y and z will already exist.

- 3 y z - If size of group of `node[y]` > z then split the group by leftmost z. Node y will already exist `0 < z`.

- 4 y - Find the sum of values of the group of `node[y]`. Node y will already exist.


<details>
 <summary>Implicit treap with parent pointers</summary>

Parent pointers are used to check whether two nodes are present in the same treap.

source: Tourist https://codeforces.com/contest/899/submission/44463469

```cpp
#include <bits/stdc++.h>
using namespace std;

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

class node {
    public:
    int id, value;
    long long sum;
    node * l;
    node * r;
    node * p;
    bool rev;
    int sz;
    // declare extra variables:
    int P; // priority

    node(int _id, int val) {
        id = _id;
        value = val;
        sum = val;
        l = r = p = NULL;
        rev = false;
        sz = 1;
        // init extra variables:
        P = rng();
    }

    void unsafe_reverse() {
        rev ^= 1;
        swap(l, r);
        pull();
    }

    // apply changes:
    void unsafe_apply() {

    }

    void push() {
        if (rev) {
            if (l != NULL) {
                l -> unsafe_reverse();
            }
            if (r != NULL) {
                r -> unsafe_reverse();
            }
            rev = 0;
        }
        // now push everything else:

    }

    void pull() {
        sz = 1;
        sum = value;
        // now init from self:

        if (l != NULL) {
            l -> p = this;
            sz += l -> sz;
            // now pull from l:
            sum += l -> sum;

        }
        if (r != NULL) {
            r -> p = this;
            sz += r -> sz;
            // now pull from r:
            sum += r -> sum;

        }
    }
};

void debug_node(node * v, string pref = "") {
    #ifdef LOCAL
    if (v != NULL) {
        debug_node(v -> r, pref + " ");
        cerr << pref << "-" << " " << v -> id << '\n';
        debug_node(v -> l, pref + " ");
    } else {
        cerr << pref << "-" << " " << "NULL" << '\n';
    }
    #endif
}

namespace treap {
    pair < node * , int > find(node * v, const function < int(node * ) > & go_to) {
        // go_to returns: 0 -- found; -1 -- go left; 1 -- go right
        // find returns the last vertex on the descent and its go_to
        if (v == NULL) {
            return {
                NULL,
                0
            };
        }
        int dir;
        while (true) {
            v -> push();
            dir = go_to(v);
            if (dir == 0) {
                break;
            }
            node * u = (dir == -1 ? v -> l : v -> r);
            if (u == NULL) {
                break;
            }
            v = u;
        }
        return {v, dir};
    }

    node* get_leftmost(node* v) {
         return find(v, [&](node*) { return -1; }).first;
    }

    node* get_rightmost(node* v) {
        return find(v, [&](node*) { return 1; }).first;
    }

    node * get_kth(node * v, int k) { // 0-indexed
        pair < node * , int > p = find(v, [ & ](node * u) {
            if (u -> l != NULL) {
                if (u -> l -> sz > k) {
                    return -1;
                }
                k -= u -> l -> sz;
            }
            if (k == 0) {
                return 0;
            }
            k--;
            return 1;
        });
        return (p.second == 0 ? p.first : NULL);
    }

    int get_position(node * v) { // 0-indexed
        int k = (v -> l != NULL ? v -> l -> sz : 0);
        while (v -> p != NULL) {
            if (v == v -> p -> r) {
                k++;
                if (v -> p -> l != NULL) {
                    k += v -> p -> l -> sz;
                }
            }
            v = v -> p;
        }
        return k;
    }

    node * get_bst_root(node * v) {
        while (v -> p != NULL) {
            v = v -> p;
        }
        return v;
    }

    pair<node*, node*> split(node* v, const function<bool(node*)>& is_right) {
        if (v == NULL) {
            return {
                NULL,
                NULL
            };
        }
        v -> push();
        if (is_right(v)) {
            pair < node * , node * > p = split(v -> l, is_right);
            if (p.first != NULL) {
                p.first -> p = NULL;
            }
            v -> l = p.second;
            v -> pull();
            return {
                p.first,
                v
            };
        } else {
            pair < node * , node * > p = split(v -> r, is_right);
            v -> r = p.first;
            if (p.second != NULL) {
                p.second -> p = NULL;
            }
            v -> pull();
            return {
                v,
                p.second
            };
        }
    }

    pair < node * , node * > split_leftmost_k(node * v, int k) {
        return split(v, [ & ](node * u) {
            int left_and_me = (u -> l != NULL ? u -> l -> sz : 0) + 1;
            if (k >= left_and_me) {
                k -= left_and_me;
                return false;
            }
            return true;
        });
    }

    node * merge(node * v, node * u) {
        if (v == NULL) {
            return u;
        }
        if (u == NULL) {
            return v;
        }
        if (v -> P > u -> P) {
            //    if (rng() % (v->sz + u->sz) < (unsigned int) v->sz) {
            v -> push();
            v -> r = merge(v -> r, u);
            v -> pull();
            return v;
        } else {
            u -> push();
            u -> l = merge(v, u -> l);
            u -> pull();
            return u;
        }
    }

    int count_left(node* v, const function<bool(node*)>& is_right) {
        if (v == NULL) {
            return 0;
        }
        v -> push();
        if (is_right(v)) {
            return count_left(v -> l, is_right);
        }
        return (v -> l != NULL ? v -> l -> sz : 0) + 1 + count_left(v -> r, is_right);
    }

    node* add(node* r, node* v, const function<bool(node*)>& go_left) {
        pair < node * , node * > p = split(r, go_left);
        return merge(p.first, merge(v, p.second));
    }

    node * remove(node * v) { // returns the new root
        v -> push();
        node * x = v -> l;
        node * y = v -> r;
        node * p = v -> p;
        v -> l = v -> r = v -> p = NULL;
        v -> push();
        v -> pull(); // now v might be reusable...
        node * z = merge(x, y);
        if (p == NULL) {
            if (z != NULL) {
                z -> p = NULL;
            }
            return z;
        }
        if (p -> l == v) {
            p -> l = z;
        }
        if (p -> r == v) {
            p -> r = z;
        }
        while (true) {
            p -> push();
            p -> pull();
            if (p -> p == NULL) {
                break;
            }
            p = p -> p;
        }
        return p;
    }

    node * next(node * v) {
        if (v -> r == NULL) {
            while (v -> p != NULL && v -> p -> r == v) {
                v = v -> p;
            }
            return v -> p;
        }
        v -> push();
        v = v -> r;
        while (v -> l != NULL) {
            v -> push();
            v = v -> l;
        }
        return v;
    }

    node * prev(node * v) {
        if (v -> l == NULL) {
            while (v -> p != NULL && v -> p -> l == v) {
                v = v -> p;
            }
            return v -> p;
        }
        v -> push();
        v = v -> l;
        while (v -> r != NULL) {
            v -> push();
            v = v -> r;
        }
        return v;
    }

    int get_size(node* v) { return (v != NULL ? v->sz : 0); }

    template < typename...T >
        void apply(node * v, T...args) {
            v -> unsafe_apply(args...);
        }

    void reverse(node* v) { v->unsafe_reverse(); }
}

using namespace treap;

node * get_root(node * v){
    while (v -> p != NULL){
        v = v->p;
    }
    return v;
}

const int nax = 5e5 + 10;

node* nodes[nax];

int main() {
    int Q;
    scanf("%d", &Q);
    for(int q=1;q<=Q;q++){
        int type, y, z;
        scanf("%d %d", &type, &y);
        if(type == 1){
            nodes[q] = new node(q, y);
        }else if(type == 2){
            scanf("%d", &z);
            node * root_y = get_root(nodes[y]);
            node * root_z = get_root(nodes[z]);
            if(root_y->id != root_z->id){
                merge(root_y, root_z);
            }
        }else if(type == 3){
            scanf("%d", &z);
            node * root_y = get_root(nodes[y]);
            if(root_y->sz > z){
                split_leftmost_k(root_y, z);
            }
        }else{
            node * root_y = get_root(nodes[y]);
            printf("%lld\n", root_y->sum);
        }
    }
    return 0;
}
```
</details>

#### Grim Treaper

Need to support three different types of operations

1. Range min `h` on `[l, r]`
2. Move segment `[l, r]` to the end
3. Range add `x` on `[l, r]`

https://codeforces.com/gym/102787/problem/D

<details>
 <summary>Treap with Segment Tree beats</summary>
 
Solution inspired from Yosupu segment tree beats https://github.com/yosupo06/library-checker-problems/blob/master/datastructure/range_chmin_chmax_add_range_sum/sol/correct.cpp 

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
 
typedef struct item * pitem;
struct item {
    int prior, idx, cnt;
    pitem l, r;
    // add extra variables here
    long long max1, max2, min1, value, sum;
    int max_count, min_count;
    long long lazy_add, lazy_update;
    item(int _i, long long _v){
        prior = rng();
        l = r = NULL;
        cnt = 1;
        idx = _i;
        sum = max1 = min1 = value = _v;
        max2 = LLONG_MIN;
        min_count = max_count = 1;
        lazy_add = 0;
        lazy_update = LLONG_MAX;
    }
};

long long cnt (pitem it) {
    return it ? it->cnt : 0;
}
 
long long max1 (pitem it) {
    return it ? it->max1 : LLONG_MIN;
}

long long max2 (pitem it) {
    return it ? it->max2 : LLONG_MIN;
}

long long min1 (pitem it) {
    return it ? it->min1 : LLONG_MAX;
}
 
long long max_count(pitem it){
    return it ? it->max_count : 0;
}

long long min_count(pitem it){
    return it ? it->min_count : 0;
}
 
long long sum(pitem it) {
    return it ? it->sum : 0;
}

void upd_cnt (pitem it) {
    if(it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void tag(pitem &it, long long v, string type){
    if(it == NULL) return;
    if(type == "add"){
        it->value += v;
        it->max1 += v;
        it->min1 += v;
        if(max2(it) != LLONG_MIN) it->max2 += v;
        it->sum += v*cnt(it);
        it->lazy_add += v;
        if(it->lazy_update != LLONG_MAX)
            it->lazy_update += v;
    } else if(type == "min"){
        if(max1(it) == min1(it) || v <= min1(it)){
            tag(it, v, "update");
            return;
        }
        it->sum -= (it->max1 - v)*max_count(it);
        it->value = min(it->value, v);
        it->max1 = v;
        if(it->lazy_update != LLONG_MAX)
            it->lazy_update = min(v, it->lazy_update);
    } else if(type == "update"){
        it->value = it->min1 = it->max1 = v;
        it->max2 = LLONG_MIN;
        it->max_count = cnt(it);
        it->lazy_add = 0;
        // max1 and min1 takes care of updating the values
        it->lazy_update = LLONG_MAX;
        it->sum = v*cnt(it);
    } else if(type == "max"){
        if(it->max1 == it->min1 || it->max1 <= v){
            tag(it, v, "update");
            return;
        }
        it->sum += (v - it->min1)*min_count(it);
        it->min1 = v;
        if(it->lazy_update != LLONG_MAX)
            it->lazy_update = max(it->lazy_update, v);
    }
}

void push(pitem &it){
    if(it == NULL) return;

    // update
    if(it->lazy_update != LLONG_MAX){
        tag(it->l, it->lazy_update, "update");
        tag(it->r, it->lazy_update, "update");
        it->lazy_update = LLONG_MAX;
        return;
    }

    // add
    if(it->lazy_add != 0) {
        tag(it->l, it->lazy_add, "add");
        tag(it->r, it->lazy_add, "add");
        it->lazy_add = 0;
    }

    // chmin
    if(it->max1 < max1(it->l)) tag(it->l, it->max1, "min");
    if(it->max1 < max1(it->r)) tag(it->r, it->max1, "min");

    //chmax
    if(it->min1 > min1(it->l)) tag(it->l, it->min1, "max");
    if(it->min1 > min1(it->r)) tag(it->r, it->min1, "max");
}

void printBT(const std::string& prefix, pitem t, bool isLeft=false)
{
    if( t != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
 
        printf("(%d): [v:%lld, m1:%lld, mi1:%lld, mc:%d, la:%lld, s:%lld]\n",
            t->idx, t->value, max1(t), min1(t), max_count(t), t->lazy_add, t->sum);
 
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), t->l, true);
        printBT(prefix + (isLeft ? "│   " : "    "), t->r, false);
    }
}

void recalc(pitem &it){
    if(it == NULL) return;
    upd_cnt(it);

    //  merge left and right childs into temp
    long long tmax1, tmax2, tmax_count;
    if(max1(it->l) > max1(it->r)){
        tmax1 = max1(it->l);
        tmax2 = max(max2(it->l), max1(it->r));
        tmax_count = max_count(it->l);
    } else if(max1(it->l) < max1(it->r)){
        tmax1 = max1(it->r);
        tmax2 = max(max1(it->l), max2(it->r));
        tmax_count = max_count(it->r);
    } else {
        tmax1 = max1(it->l);
        tmax2 = max(max2(it->l), max2(it->r));
        tmax_count = max_count(it->l) + max_count(it->r);
    }

    // Update max1, max2, max_count, sum
    if(tmax1 == it->value){
        it->max1 = it->value;
        it->max2 = tmax2;
        it->max_count = tmax_count + 1;
    }else if(tmax1 > it->value){
        it->max1 = tmax1;
        it->max2 = max(it->value, tmax2);
        it->max_count = tmax_count;
    }else if(tmax1 < it->value){
        it->max1 = it->value;
        it->max2 = tmax1;
        it->max_count = 1;
    }

    it->min1 = min({min1(it->l), min1(it->r), it->value});
    it->min_count = 0;
    if(min1(it) == it->value) it->min_count++;
    if(min1(it) == min1(it->l)) it->min_count += min_count(it->l);
    if(min1(it) == min1(it->r)) it->min_count += min_count(it->r);

    it->sum = sum(it->l) + sum(it->r) + it->value;
}

void min_with(pitem &t, long long v){
    if(t == NULL || t->max1 <= v) return;
    if(t->max2 < v && v < t->max1){
        tag(t, v, "min");
    }else{
        push(t);
        t->value = min(t->value, v);
        min_with(t->l, v);
        min_with(t->r, v);
        recalc(t);
    }
}

void range_add(pitem &t, long long v){
    if(t == NULL) return;
    tag(t, v, "add");
}

void range_update(pitem &t, long long v){
    if(t == NULL) return;
    tag(t, v, "update");
}

void merge (pitem & t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    recalc(t);
}

// 1-based indexing, split into [1..key] and [key+1..n]
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push(t);
    int implicit_key = add + cnt(t->l);
    if (key <= implicit_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    recalc(t);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    pitem treap = NULL;
    for(int i=1;i<=n;i++){
        int a; scanf("%d", &a);
        pitem cur = new item(i, a);
        merge(treap, treap, cur);
    }
    while(q--){
        int type, l, r;
        scanf("%d%d%d", &type, &l, &r);
        pitem t1 = NULL, t2 = NULL, t3 = NULL;
        split(treap, treap, t3, r);
        split(treap, t1, t2, l-1);
        if(type == 1){
            // min(a[i], h) for i in [l, r]
            int h; scanf("%d", &h);
            min_with(t2, h);
            merge(treap, t1, t2);
            merge(treap, treap, t3);
        }else if(type == 2){
            // t1, t2, t3 --> t1, t3, t2
            merge(treap, t1, t3);
            merge(treap, treap, t2);
        }else{
            // a[i] += x for i  in [l, r]
            int x; scanf("%d", &x);
            range_add(t2, x);
            merge(treap, t1, t2);
            merge(treap, treap, t3);
        }
        printf("%lld\n", treap->sum);
    }
    return 0;
}
```

Also verified using https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F, https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G, https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H and https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I
</details> 

### TODO: https://www.programmersought.com/article/51291114191/

https://codeforces.com/contest/1056/problem/G

### TODO: https://codeforces.com/contest/702/submission/57815496

https://github.com/xuzijian629/library2/blob/master/tmp.cpp

https://codeforces.com/blog/entry/10355

## Reference:
* https://threadsiiithyderabad.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-1
* https://habr.com/ru/post/101818/, https://habr.com/en/post/102006/ and https://habr.com/en/post/102364/
* https://medium.com/carpanese/a-visual-introduction-to-treap-data-structure-part-1-6196d6cc12ee
* http://memphis.is-programmer.com/posts/46317.html
* https://cp-algorithms.com/data_structures/treap.html

https://codeforces.com/blog/entry/3767 and https://ankitsultana.com/2021/03/29/persistent-treaps.html and https://codeforces.com/contest/899/submission/44463469

https://codeforces.com/blog/entry/84017


Checkout https://ekzlib.netlify.app/home
