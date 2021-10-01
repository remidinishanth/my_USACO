How to recognize max-flow problems? Often they are hard to detect and usually boil down to maximizing the movement of something from a location to another. We need to look at the constraints when we think we have a working solution based on maximum flow – they should suggest at least an `O(N³)` approach. If the number of locations is large, another algorithm (such as dynamic programming or greedy), is more appropriate.

If the problem description sugggest multiple sources and/or sunks. We can convert this to a network that has a unique source and sink. We can just add node(call it super-source) and add edge with infinite capacity to every source.

![](images/mflow_67.png)

Say we have restriction of some node(say a city is only allowed some maximum amount of water), we can create an edge between two vertices with this capacity.

![](images/mflow_66.gif)

## Flow Graph Modeling

* Recognizing that the problem is indeed a Network Flow problem(this will get better after you solve more Network Flow problems).
* Constructing the appropriate flow graph (i.e. if using our code shown earlier: Initiate the residual matrix res and set the appropriate values for ‘s’ and ‘t’).
* Running the Edmonds Karp’s code on this flow graph.


### Bipartite matching

The maximum matching problem asks to find a maximum-size set of node pairs in an undirected graph such that each pair is connected with an edge and
each node belongs to at most one pair.

There are polynomial algorithms for finding maximum matchings in general graphs, but such algorithms are complex and rarely seen in programming
contests. However, in bipartite graphs, the maximum matching problem is much easier to solve, because we can reduce it to the maximum flow problem.

![](images/mflow_56.png)
![](images/mflow_57.png)

Hall’s theorem can be used to find out whether a bipartite graph has a matching
that contains all left or right nodes. If the number of left and right nodes is the
same, Hall’s theorem tells us if it is possible to construct a perfect matching
that contains all nodes of the graph.

![](images/mflow_58.png)
![](images/mflow_59.png)

![](images/mflow_60.png)
![](images/mflow_61.png)

#### Kőnig’s theorem

A minimum node cover of a graph is a minimum set of nodes such that each edge of the graph has at least one endpoint in the set. In a general graph, finding a minimum node cover is a NP-hard problem. However, if the graph is bipartite, Konig’s theorem ˝ tells us that the size of a minimum node cover and the size of a maximum matching are always equal. Thus, we can calculate the size of a minimum node cover using a maximum flow algorithm.

![](images/mflow_62.png)
![](images/mflow_63.png)

![](images/mflow_64.png)

![](images/mflow_65.png)

### Disjoint paths

Many graph problems can be solved by reducing them to the maximum flow
problem. Our first example of such a problem is as follows: we are given a
directed graph with a source and a sink, and our task is to find the maximum
number of disjoint paths from the source to the sink.

![](images/mflow_53.png)

![](images/mflow_54.png)
![](images/mflow_55.png)
