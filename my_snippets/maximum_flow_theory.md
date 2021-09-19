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

## REF:

* CS261 Stanford Time Roughgarden 2016 http://timroughgarden.org/w16/l/l1.pdf