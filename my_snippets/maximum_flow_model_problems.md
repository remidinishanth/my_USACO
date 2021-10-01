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

### Disjoint paths

Many graph problems can be solved by reducing them to the maximum flow
problem. Our first example of such a problem is as follows: we are given a
directed graph with a source and a sink, and our task is to find the maximum
number of disjoint paths from the source to the sink.

![](images/mflow_53.png)

![](images/mflow_54.png)
![](images/mflow_55.png)
