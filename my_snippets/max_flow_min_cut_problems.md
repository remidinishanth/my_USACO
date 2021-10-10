### F. Chests and Keys

source: https://codeforces.com/contest/1519/problem/F

![](images/mflow_p_1.png)

**Solution:**

Clearly, if the sum of the coins in all the chests > cost of buying all the keys, then Bob always gains positive profit and answer is `-1`.

Observation: Note that here `n`, `m`, `aᵢ` and `bⱼ` are small.

Firstly, let's try to find some naive solution for this problem. Let's iterate on the subset of locks Alice puts on the chests. After choosing the subset of locks, how to check whether Bob can gain positive profit? We can iterate on the subset of keys he can buy as well, but in fact, this problem has a polynomial solution.

Brute force solution is to iterate over each pair of (chest, lock) and decide whether we have to put this lock on the chest or not. We have `mn = 36` number of pairs, So `2^36` will time out.

Constriants are small, can we use dp? We will need to store a lot of information in each state.

We have to minimise the cost paid by Alice, how about modelling as as flow problem and minimize the cost we have to pay? Motivation for this is Project and tools problem. Source: Neal

![](images/mflow_p_2.png)

![](images/mflow_p_4.png)

Consider the flow network as follows:
* Each chest and each key represents a vertex
* `n` arcs from the source to the chests(each having capacity `aᵢ`)
* `m` arcs from the vertices representing the keys to the sink(each with capacity `bⱼ`)
* For each chosen lock, an arc from the respective chest-vertex to the respective key-vertex with infinite capacity.

![](images/mflow_p_5.png)

If we find the minimum cut from the source to the sink, then Bob's profit is `sum(aᵢ) - min_cut`.
