# Heavy-light decomposition

The heavy-light (H-L) decomposition of a rooted tree is a method of partitioning the vertices of the tree into 
disjoint paths (all vertices have degree two, except the endpoints of a path, with degree one) that gives important 
asymptotic time bounds for certain problems involving trees.

The heavy-light decomposition of a tree T=(V, E) is a coloring of the tree's edges. Each edge is either heavy or light. 

## Motivation

Suppose we are given a tree where each node is having some value, we want to answer queries like the sum of values on nodes on the path from u to v.

We can calculate LCA and find the answer by breaking path(u,v) into path(u, lca) and path(lca, v), now Calc(u,v) = Calc(u, root) + Calc(v, root) - 2 Calc(root, LCA(u,v)).

But say we also have an update query set(v,x) where we are given node v and value x, and we need to update the value of node v to x. Now we can use LCA to answer efficiently.

Say instead of a tree, we just have a chain(set of nodes connected one after another), we can support both calc(u,v) and set(v,x) by using BIT/Segment tree.

![image](https://user-images.githubusercontent.com/19663316/115997295-42735e80-a600-11eb-9d0c-84b492d83964.png)

Key: HLD supports updating the tree node/edge values unlike the LCA sparse array approach, but the tree structure is fixed.

## Basic idea

We will divide the tree into vertex-disjoint chains (meaning no two chains has a node in common) in such a way that to move from any node in the tree to the root node, we will have to change at most log N chains. To put it in other words, if the path from any node to root can be broken into pieces such that each piece belongs to only one chain, then we will have no more than log N pieces.

We already know that queries in each chain can be answered with O(log N) complexity and there are at most log N chains we need to consider per path. So on the whole we have O( log^2 N ) complexity solution.

## Two school of thoughts

* For each vertex that isn’t a leaf, find the edge that leads to the child with the largest subtree (breaking ties arbitrarily) and call it heavy.

* To determine which, consider the edge's two endpoints: one is closer to the root, and one is further away. 
  If the size of the subtree rooted at the latter is more than half that of the subtree rooted at the former, the edge is heavy. 
  Otherwise, it is light.


![image](https://user-images.githubusercontent.com/19663316/115995981-24efc600-a5fb-11eb-8722-7233db484cfc.png)

In the first case, we'll have many heavy edges and hence our code will run faster, in the second case we might have not any heavy edges for some trees.

![image](https://user-images.githubusercontent.com/19663316/115997083-6e421480-a5ff-11eb-93f1-42cd4a97a50c.png)

Based on the subtree sizes, mark the edges as heavy, breaking ties arbitrarily.

![image](https://user-images.githubusercontent.com/19663316/115997107-7bf79a00-a5ff-11eb-8fcc-3d46478b2954.png)

Consider some node, if you choose heavy edge and go down, we will have heavy paths. Using these, our tree nodes can be split into heavy paths, along with some single leaf nodes(these can be thought of as paths of size 1).

Now the key idea about this setup is that any path on the tree will pass through at most 𝑂(log n) light edges. By extension, each path also passes through at most 𝑂(log n) vertical chains.

### Proof

One useful idea for the proof of this claim is that you can break any path 𝑢 -> 𝑣 on a tree into two (possibly non-existent) components: the path from 𝑢 up to 𝑙𝑐𝑎(𝑢,𝑣) and the path from 𝑣 up to 𝑙𝑐𝑎(𝑢,𝑣), where 𝑙𝑐𝑎(𝑢,𝑣) is the lowest common ancestor of 𝑢 and 𝑣. Because 𝑙𝑐𝑎(𝑢,𝑣) is an ancestor of both 𝑢 and 𝑣, both of these separate paths will also be vertical chains themselves. So now let's prove that both of these vertical chains only pass through 𝑂(log n) light edges.

Consider some vertex `v` in some vertical chain. Let the size of its subtree be `x` and its parent be `p`. If the edge from `v` to `p` is light, then there must be some other child `u` of `p` with subtree size `y`, where `y ≥ x`. Then when we move up to `p`, the size of `p`'s subtree is at least `x+y ≥ 2x`. So whenever we move up a light edge, the size of our current subtree is at least doubled. Because the size of a subtree can't be more than `n`, we end up moving up a light edge at most 𝑂(log n) times.

### Psuedo code to calculate heavy edges

```python
def go(x):
  sz = 1
  for y in children[x]:
    y_sz = go(y)
    sz += y_sz
    if y_sz > max:
      max = y_sz
      heavy[x] = y
  return sz
```
### Psuedo code for segment trees on chains

Instead of using many small segments trees(one for each chain), we can just use one segment tree.

We first recursively build for the heavy node and then for all other subtrees.

```python
def go2(x):
  p.append(x)
  if not children[x].empty():
    go2(heavy[x])
    for y in children[x]:
      if y!=heavy[x]:
        go2(x)
```

![image](https://user-images.githubusercontent.com/19663316/115999338-f11b9d00-a608-11eb-9c6c-148742a297aa.png)

If you look at array p, it can be breaked into heavy chains segments. For two nodes within a chain, we can directly query segment tree to find the result.

![image](https://user-images.githubusercontent.com/19663316/115999408-363fcf00-a609-11eb-8412-3e89d89d4288.png)


We don't need any special code to calculate LCA, we can leverage HLD code to do it. From each node let's have a pointer to the top node in the heavy path. For node u let's call this top node of chain as top[u]

![image](https://user-images.githubusercontent.com/19663316/115999560-e6153c80-a609-11eb-8a08-f9b03b66f407.png)

```python
while True:
  x = top[u]
  y = top[v]
  if x==y:
    # u and v belong to same heavy chain
    res += sum(u,v) # sum is code to segment tree
    break
  if d[x] > d[y]: # d[x] is depth from the root
    res += sum(u,x)
    u = x.parent
  else:
    res += sum(y,v)
    v = y.parent
```

<details>
  <summary>CPP implementation</summary>
  
```cpp
template <class T, int V>
class HeavyLight {
  int parent[V], heavy[V], depth[V];
  int root[V], treePos[V];
  SegmentTree<T> tree;

  template <class G>
  int dfs(const G& graph, int v) {
    int size = 1, maxSubtree = 0;
    for (int u : graph[v]) if (u != parent[v]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      int subtree = dfs(graph, u);
      if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
      size += subtree;
    }
    return size;
  }

  template <class BinaryOperation>
  void processPath(int u, int v, BinaryOperation op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) swap(u, v);
    op(treePos[u], treePos[v] + 1);
  }

public:
  template <class G>
  void init(const G& graph) {
    int n = graph.size();
    fill_n(heavy, n, -1);
    parent[0] = -1;
    depth[0] = 0;
    dfs(graph, 0);
    for (int i = 0, currentPos = 0; i < n; ++i)
      if (parent[i] == -1 || heavy[parent[i]] != i)
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          treePos[j] = currentPos++;
        }
    tree.init(n);
  }

  void set(int v, const T& value) {
    tree.set(treePos[v], value);
  }

  void modifyPath(int u, int v, const T& value) {
    processPath(u, v, [this, &value](int l, int r) { tree.modify(l, r, value); });
  }

  T queryPath(int u, int v) {
    T res = T();
    processPath(u, v, [this, &res](int l, int r) { res.add(tree.query(l, r)); });
    return res;
  }
};

// source: https://codeforces.com/blog/entry/22072
```
</details>


*Extra care must be taken in processPath if the binary operation isn't commutative, you'll need two segment trees, one for downward sums and one for upward sums.*

## REF

* <https://blog.anudeep2011.com/heavy-light-decomposition/>
* <https://codeforces.com/blog/entry/81317>
* <https://codeforces.com/blog/entry/22072>
* <https://apps.topcoder.com/forums/?module=Thread&threadID=796128&start=0&mc=8>
