## Maximum flow problem

Formally, an instance of the maximum flow problem is specified as follows:
* a directed graph G, with vertices V and directed edges E;
* a source vertex `s ∈ V`;
* a sink vertex `t ∈ V`;
* a nonnegative and **integral** capacity c(e) for each edge `e ∈ E`;

![](images/mflow_0.png)

Since the point is to push flow from s to t, we can assume without loss of generality that `s` has no incoming edges and `t` has no outgoing edges.

Given such an input, a flow is a nonnegative vector f(e) indexed by the edges of G, that satisfies two constraints:
* Capacity constraints: f(e) ≤ c(e) for every edge `e ∈ E`;
* Conservation constraints: for every vertex `v` other than `s` and `t`, ```amount of flow entering v = amount of flow exiting v```. The left-hand side is the sum of f(e) over the edge incoming to v; likewise with the outgoing edges for the right-hand side.

The objective is to compute a maximum flow — a flow with the maximum-possible value, meaning the total amount of flow that leaves `s`. (As we’ll see, this is the same as the total amount of flow that enters t.)

Let's try finding max flow using some greedy algorithm, greedy algorithms do not generally produce the best-possible solution, even though it fails, it’s still worth trying them, because the ways in which greedy algorithms break often yields insights that lead to better algorithms.

The simplest greedy approach to the maximum flow problem is to start with the all-zero flow and greedily produce flows with ever-higher value. The natural way to proceed from one to the next is to send more flow on some path from `s` to `t`.

![](images/mflow_3.png)

Note that the path search just needs to determine whether or not there is an s-t path in the subgraph of edges e with fe < ue. This is easily done in linear time using your favorite graph search subroutine, such as breadth-first or depth-first search. There may be many such paths; for now, we allow the algorithm to choose one arbitrarily. The algorithm then pushes as much flow as possible on this path, subject to capacity constraints.

![](images/mflow_4.png)

This greedy algorithm is natural enough, but does it work? That is, when it terminates with a flow, need this flow be a maximum flow? Our sole example thus far already provides a negative answer.

### Residual graphs

The second idea is to extend the naive greedy algorithm by allowing “undo” operations. For example, from the point where this algorithm gets stuck in above figure, we’d like to route two more units of flow along the edge (s, w), then backward along the edge (v, w), undoing 2 of the 3 units we routed the previous iteration, and finally along the edge (v, t). This would yield the maximum flow.

![](images/mflow_2.png)

We need a way of formally specifying the allowable “undo” operations. This motivates the following simple but important definition, of a residual network. The idea is that, given a graph G and a flow f in it, we form a new flow network G_f that has the same vertex set of G and that has two edges for each edge of G.

An edge `e = (u, v)` of G that carries flow `f(e)` and has capacity `c(e)` spawns a “forward edge” `(u, v)` of G_f with capacity `c(e) − f(e)`
(the room remaining) and a “backward edge” `(v, u)` of G_f with capacity `f(e)` (the amount of previously routed flow that can be undone).

Observe that `s-t` paths with `f(e) < c(e)` for all edges, as searched for by the naive greedy algorithm, correspond to the
special case of `s-t` paths of `G_f` that comprise only forward edges.

#### Ford-Fulkerson Algorithm

Happily, if we just run the natural greedy algorithm in the current residual network, we get a correct algorithm, the Ford-Fulkerson algorithm.

![](images/mflow_5.png)

We claim that the Ford-Fulkerson algorithm eventually terminates with a feasible flow. This follows from two invariants, both proved by induction on the number of iterations.

* Claim: (Optimality Conditions for Maximum Flow) If f is a flow in G such that the residual network Gf has no s-t path, then the f is a maximum flow. 

Corollary: The Ford-Fulkerson algorithm is guaranteed to terminate with a maximum flow. 

We'll prove this claim with Maximum-Flow/Minimum-Cut Theorem.

The Ford-Fulkerson algorithm repeatedly finds an s-t path P in the current residual graph G_f , and augments along p as much as possible subject to the capacity constraints of the residual network.

### (s,t)-Cuts

An `(s, t)-cut` of a graph `G = (V, E)` is a partition of `V` into sets `A`, `B` with `s ∈ A` and `t ∈ B`.

Such a cut buckets the edges of the graph into four categories: those with both endpoints in A, those with both endpoints in B, those sticking out of A (with tail in A and head in B), and those sticking into A (with head in A and tail in B).

![](images/mflow_6.png)

The capacity of an (s, t)-cut (A, B) is defined as sum of capacities of edges sticking out of A. Note that edges sticking in to the source-side of an (s, t)-cut to do not contribute to its capacity. A minimum cut is one with the smallest capacity.

### Optimiality Conditions for the Maximum Flow Problem

Let f be a flow in a graph G. The following are equivalent:
* f is a maximum flow of G;
* there is an `(s, t)-cut` `(A, B)` such that the value of `f` equals the capacity of `(A, B)`;
* there is no s-t path (with positive residual capacity) in the residual network G_f.

Corollary: If f is a flow in G such that the residual network Gf has no s-t path, then the f is a maximum flow.

#### Proof

**(2) ⇒ (1)**: We claim that, for every flow f and every (s, t)-cut (A, B), value of f ≤ capacity of (A, B). This claim implies that all flow values are at most all cut values; The claim implies that there no “x” strictly to the right of the “o”.

![](images/mflow_7.png)

To see why the claim yields the desired implication, suppose that (2) holds. This corresponds to an “x” and “o” that are co-located in the above figure. By the claim, no “x”s can appear to the right of this point. Thus no flow has larger value than f, as desired.

![](images/mflow_8.png)

![](images/mflow_9.png)

**(1) ⇒ (3)**: We prove the contrapositive. Suppose `f` is a flow such that `G_f` has an `s-t` path `P` with positive residual capacity. As in the Ford-Fulkerson algorithm, we augment along `P` to produce a new flow `f'` with strictly larger value. This shows that `f` is not a maximum flow.

**(3) ⇒ (2)**: This proof is constructive. The trick is to define `A = { v ∈ V : there is an s ⇝ v path in G_f}`.

Conceptually, start graph search subroutine(BFS or DFS) from `s` untill you get stuck; A is the set of vertices you get stuck at. Note that `(A, V − A)` is an `(s, t)-cut`. Certainly `s ∈ A`, so `s` can reach itself in `G_f` . By assumption, `G_f` has no `s-t` path, so `t ∉ A`. The reason is that if there
were such an edge sticking out of A, then our graph search would not have gotten stuck at A, and A would be a bigger set. 

![](images/mflow_10.png)

The above picture is of residual graph which attains maximum flow. Let's see how the edges compare to original network G.
* Every edge sticking out of A in G is saturated (meaning `f_e = c_e`). If `f_e < c_e` then we have a forward edge with positive residual capacity which is a contradiction.
* Every edge sticking into in A in G is zeroed out (f_e = 0). Otherwise `c_e - f_e > 0`, then the residual netowrk G_f would contain a forward edge of e, contradiction.

![](images/mflow_11.png)

Corollary: **(Max-Flow/Min-Cut Theorem)** In every network, maximum value of a flow = minimum capacity of an (s, t)-cut.

Corollary: Given a maximum flow, and minimum cut can be computed in linear time. Use BFS or DFS to compute, in linear time, the set A from the third part of the
proof of Theorem. The proof shows that (A, V − A) is a minimum cut.

Running time of Ford-Fulkerson Algorithm is `𝑂(𝐸𝑓)` - applies only when the edge capacities are integers.

The problem is that the algorithm can keep choosing a “bad path” over and over again. (Recall that when the current residual network has multiple s-t paths, the Ford-Fulkerson algorithm chooses arbitrarily.)

Consider the following graph:

![](images/mflow_13.png)

With each augmentation the flow increases by exactly 1 as the algorithm changes its mind about whether to use the middle edge; it takes 200 augmentations before the algorithm terminates, even though choosing the high-capacity top and bottom paths at the start could finish in 2.



Since we can do at most `𝑓`  iterations, and each iteration takes  𝑂(𝐸+𝑉)  time, the worst-case run time is `𝑂((𝐸+𝑉)𝑓)` which is `𝑂(𝐸𝑓)`.

We now focus on optimizing the running time.

### The Edmonds-Karp Algorithm: Shortest Augmenting Paths

## REF:

* CS261 Stanford Time Roughgarden 2016 http://timroughgarden.org/w16/l/l1.pdf
