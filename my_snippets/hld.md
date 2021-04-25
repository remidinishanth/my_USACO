# Heavy-light decomposition

The heavy-light (H-L) decomposition of a rooted tree is a method of partitioning of the vertices of the tree into 
disjoint paths (all vertices have degree two, except the endpoints of a path, with degree one) that gives important 
asymptotic time bounds for certain problems involving trees.

## Two school of thoughts

* The heavy-light decomposition of a tree T=(V,E) is a coloring of the tree's edges. Each edge is either heavy or light. 
  To determine which, consider the edge's two endpoints: one is closer to the root, and one is further away. 
  If the size of the subtree rooted at the latter is more than half that of the subtree rooted at the former, the edge is heavy. 
  Otherwise, it is light.

* For each vertex that isn’t a leaf, find the edge that leads to the child with the largest subtree (breaking ties arbitrarily) and call it heavy.
