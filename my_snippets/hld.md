# Heavy-light decomposition

The heavy-light (H-L) decomposition of a rooted tree is a method of partitioning of the vertices of the tree into 
disjoint paths (all vertices have degree two, except the endpoints of a path, with degree one) that gives important 
asymptotic time bounds for certain problems involving trees.

The heavy-light decomposition of a tree T=(V,E) is a coloring of the tree's edges. Each edge is either heavy or light. 

## Motivation

Suppose we are given a tree where each node is having some value, we want to answer queries like sum of values on nodes on the path from u to v.

We can calculate LCA and find the answer by breaking path(u,v) into path(u, lca) and path(lca, v), now Calc(u,v) = Calc(u, root) + Calc(v, root) - 2 Calc(root, LCA(u,v)).

But say we also have an update query set(v,x) where we are given node v and value x, and we need to update the value of node v to x. Now we can use LCA to answer efficiently.

Say instead of a tree, we just have a chain(set of nodes connected one after another), we can support both calc(u,v) and set(v,x) by using BIT/Segment tree.

![image](https://user-images.githubusercontent.com/19663316/115997295-42735e80-a600-11eb-9d0c-84b492d83964.png)

## Basic idea

We will divide the tree into vertex-disjoint chains (meaning no two chains has a node in common) in such a way that to move from any node in the tree to the root node, we will have to change at most log N chains. To put it in another words, if the path from any node to root can be broken into pieces such that the each piece belongs to only one chain, then we will have no more than log N pieces.

We already know that queries in each chain can be answered with O(log N) complexity and there are at most log N chains we need to consider per path. So on the whole we have O( log^2 N ) complexity solution.

## Two school of thoughts

* For each vertex that isn’t a leaf, find the edge that leads to the child with the largest subtree (breaking ties arbitrarily) and call it heavy.

* To determine which, consider the edge's two endpoints: one is closer to the root, and one is further away. 
  If the size of the subtree rooted at the latter is more than half that of the subtree rooted at the former, the edge is heavy. 
  Otherwise, it is light.


![image](https://user-images.githubusercontent.com/19663316/115995981-24efc600-a5fb-11eb-8722-7233db484cfc.png)

In the first case, we'll have many heavy edges and hence our code will run faster, in second case we might have not any heavy edges for some trees.

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
