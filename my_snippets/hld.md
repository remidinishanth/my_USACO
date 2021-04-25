# Heavy-light decomposition

The heavy-light (H-L) decomposition of a rooted tree is a method of partitioning of the vertices of the tree into 
disjoint paths (all vertices have degree two, except the endpoints of a path, with degree one) that gives important 
asymptotic time bounds for certain problems involving trees.

The heavy-light decomposition of a tree T=(V,E) is a coloring of the tree's edges. Each edge is either heavy or light. 

## Two school of thoughts

* For each vertex that isn’t a leaf, find the edge that leads to the child with the largest subtree (breaking ties arbitrarily) and call it heavy.

* To determine which, consider the edge's two endpoints: one is closer to the root, and one is further away. 
  If the size of the subtree rooted at the latter is more than half that of the subtree rooted at the former, the edge is heavy. 
  Otherwise, it is light.


![image](https://user-images.githubusercontent.com/19663316/115995981-24efc600-a5fb-11eb-8722-7233db484cfc.png)

In the first case, we'll have many heavy edges and hence our code will run faster, in second case we might have not any heavy edges for some trees.

### Psuedo code to calculate heavy edges

```python
def go(x):
  sz = 1
  for y in children(x):
    y_sz = go(y)
    sz += y_sz
    if y_sz > max:
      max = y_sz
      heavy(x) = y
  return sz
```
