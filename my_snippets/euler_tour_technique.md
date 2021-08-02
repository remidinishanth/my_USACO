![](images/ett_1.png)
![](images/ett_2.png)
![](images/ett_3.png)
![](images/ett_4.png)
![](images/ett_5.png)

source: Competitive Programmer's Handbook - CSES

## Queries on Trees:

### Path Query and Update Problems
* **Path Query:** Given two nodes x, y - compute some function f(x, y) that depends on the path between nodes x & y.
  * Eg: sum, min, max, number of distinct elements etc.
* **Point Update:** Change the value for any one edge/node in the tree.
* **Path Range Update:** Change the value of all nodes/edges on a path.
  * Eg: Add x to all nodes in a path, take mod x for all nodes in a path etc.  

### Subtree Query and Update Problems
* **Subtree Query:** Given a node x - compute some function f(x) that depends on values of nodes/edges in the subtree of x
  * Eg: sum, min, max, number of distinct elements etc.
* **Point Update:** Change the value of any one edge / node in the tree
* **Subtree Range Update:** Change the value of all nodes/edges in the subtree of a node x.
  * Eg: Add "val" to all all nodes in the subtree of node x etc. 
