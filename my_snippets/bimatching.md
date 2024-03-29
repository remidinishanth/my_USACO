TODO: https://codeforces.com/contest/1721/problem/F

Check this out: https://codeforces.com/blog/entry/78255

### Matching or independent edge set

Berge's lemma states that **a matching M is maximum if and only if there is no augmenting path with respect to M**.

Finding a matching in a bipartite graph can be treated as a network flow problem.

Kőnig's theorem states that, in bipartite graphs, the **maximum matching is equal in size to the minimum vertex cover**. Via this result, the minimum vertex cover, maximum independent set, and maximum vertex biclique problems may be solved in polynomial time for bipartite graphs.

* Kuhn's algorithm is a direct application of Berge's lemma. It is essentially described as follows:

  * First, we take an empty matching. Then, while the algorithm is able to find an augmenting path, we update the matching by alternating it along this path and repeat the process of finding the augmenting path. As soon as it is not possible to find such a path, we stop the process - the current matching is the maximum.

```cpp
vi match, vis;

int Aug(int v) { // return 1 if an augmenting path is found
    if (vis[v]) return 0;
    vis[v] = 1;
    for (int j = 0; j < (int) Adj[v].size(); j++) {
        int r = Adj[v][j];
        if (match[r] == -1 || Aug(match[r])) {
            match[r] = v;
            return 1;
        }
    }
    return 0;
}

// left set vertices are from [1..n]
// right set vertices are from [n+1..n+m]

// in main
// build unweighted bipartite graph with directed edge left->right set
int MCBM = 0;
match.assign(V, -1);
for (int v = 0; v < n; v++) {
    vis.assign(n, 0);
    MCBM += Aug(v);
}
```

* This algorithm will keep doing this process of finding augmenting paths and eliminating them until there is no more augmenting path.

* This algo tries to find and then eliminate augmenting paths starting from free vertices on the left set

* `O(VE)` as code runs `V` times and each DFS takes `O(E)` time

* Hopcroft Karp’s algorithm can solve the MCBM problem in `O(√V E)`

source: CP3 Augmenting Path Algorithm for Max Cardinality Bipartite Matching

Also check implementation at https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html


### Matching and Vertex cover
![image](https://user-images.githubusercontent.com/19663316/189962387-fe4d35a1-38f2-4087-9db0-611cc851de10.png)

* (1 ⇒ 2) Suppose not, then there exists an augmenting path, if we include this augmenting path, we get larger matching.
* (2 ⇒ 3) Let H be the set of vertices reachable via an alternating path from unmatching vertices in L. All these paths must end in some unmatched vertices on the L(because there is no augmenting path).
  ![image](https://user-images.githubusercontent.com/19663316/189966603-ba45ace7-7a8d-4b2d-a072-ad5c8c99b44a.png)
  ![image](https://user-images.githubusercontent.com/19663316/189965224-cad4f2f2-c64d-4063-a477-f7928752d0ce.png)
  ![image](https://user-images.githubusercontent.com/19663316/189965860-64659df3-3484-416a-ae47-f2505b03286c.png)
  S = (L - H) ∪ (R ∩ H) contains exactly one vertex for every edge belong to M, if the edge belongs to H, then we are taking the right vertices otherwise we are taking the left vertices. So the size of S and size of M should be equal.
  Now we to convince ourselves that S is indeed a vertex cover. There are 4 types of edges between L and R
  * Edges going from (L ∩ H) to (R ∩ H) are covered by (R ∩ H)
  * Edges going from (L - H) to (R - H) are covered. by (L - H)
  * Edges going from (L - H) to (R ∩ H) are covered by both.
  * There cannot be edges going from (L ∩ H) to (R - H) because otherwise H could be larger.
* (3 ⇒ 1) Suppose not, then there is an edge in matching which is not between any of the vertices in the vertex cover, then it cannot be a vertex cover. For every edge in matching it has to be covered by some vertex which is part of vertex cover, vertex cover is upper bound on any matching.


<details>
	<summary> Topcoder Solving Maximum Bipartite Matching Problem </summary>
	
**NAME**
Solving Maximum Bipartite Matching Problem
	
source: https://apps.topcoder.com/forums/?module=Thread&threadID=684427&start=0

**PROBLEM**
In this article we shall speak about Solving Maximum Bipartite Matching Problem. 

There is a bipartite graph containing `N` vertices (`n` vertices in left part and `k = N-n` vertices in right part of graph) 
and ``M edges. We are to find maximum bipartite matching, i.e. mark maximum number of edges, so that no one of them 
have adjacent vertices with each other. This problem can be easily solved in two ways.

**SOLUTION**

#### First way: Kuhn’s algorithm.

Chain with length k is a simple path (i.e. it contains no repeated vertices or edges) that has k edges in the 
bipartite graph. Alternating chain (in a bipartite graph, with respect to some matching) is a chain in which the 
edges alternately belong / not belong to the matching. The increasing chain (in a bipartite graph, with respect 
to a matching) is an alternating chain, whose initial and final vertices (as well as edges) do not belong to matching.

Berja’s theorem(Berge's lemma): 
Matching is maximal if and only if there are no increasing chains with respect to it.

So, let’s notice that if we find an increasing chain, we can increase our matching by one. 
We will go along this increasing chain and mark edges which are not marked and unmark edges that were marked 
(first edge is not marked by definition – we will mark it, second is marked, so we will unmark it and so on). 
It is obvious that by doing this operation we will increase our matching by one, because length of increasing chain 
is always odd and because in this chain we had `[k/2]+1` unmarked edges and `[k/2]` marked edges and after rematching 
we have `[k/2]` unmarked edges and `[k/2]+1` marked edges in the chain.

So the main idea of the algorithm is to search increasing chains while we can and increase matching.

Well, new problem is how to find increasing chains. Kuhn’s algorithm is based on dfs (depth first search) or 
bfs (breadth first search) algorithm.

Complexity of searching an increasing chain is `O(N+M)` and maximum number of them is `N/2`, 
overall asymptotic is `O(N*N + N*M) = O(NM)`

Let’s see how we will search increasing chains: we shall use dfs. We will call dfs only from vertices of graph’s left part. 
From left part it goes to right only using not marked edges, and from right to left only using marked edges. 
In our implementation dfs will be called only from left graph’s vertices and will return bool – true if it found chain 
and false if not. From current vertex algorithm will go through all adjacent not marked edges to vertex from right part 
called TO. If TO has no adjacent marked edges, dfs will return true, because it is last vertex of increasing chain. 
If it has, we will call dfs from TO’s neighbor on marked edge and return true if it returned true.

```cpp
// Pseudocode:
bool kuhn(vertex v) {
    if (used[v]) return false;
    used[v] = true;

    for (vertex q adjacent to v) {
        if ((q has no pair) or kuhn(pairs[q])) {
            pairs[q] = v;
            return true;
        }
    }
}

find_max_matching {
    for (vertex v = {1, .., n}) {
        used = {0};
        kuhn(v);
    }
}
```

Implementation (C++):

```cpp
#include<vector>
#include<utility>

using namespace std;

class KuhnImplementation {
    public:
        int n, k;
    vector<vector<int>> g;
    vector<int> pairs;
    vector<bool> used;

    bool kuhn(int v) {
        if (used[v]) return false;
        used[v] = true;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i] - n;
            if (pairs[to] == -1 || kuhn(pairs[to])) {
                pairs[to] = v;
                return true;
            }
        }
        return false;
    }

    vector < pair < int, int > > find_max_matching(vector < vector < int > > & _g, int _n, int _k) {
        g = _g;
        //g[i] is a list of adjacent vertices to vertex i, where i is from left patr and g[i][j] is from right part
        n = _n;
        //n is number of vertices in left part of graph
        k = _k;
        //k is number of vertices in right part of graph

        pairs = vector < int > (k, -1);
        //pairs[i] is a neighbor of vertex i from right part, on marked edge
        used = vector < bool > (n, false);
        for (int i = 0; i < n; ++i) {
            fill(used.begin(), used.end(), false);
            kuhn(i);
        }

        vector < pair < int, int > > res;
        for (int i = 0; i < k; i++)
            if (pairs[i] != -1)
                res.push_back(make_pair(pairs[i], i + n));

        return res;

    }
};
```


Improved implementation:

* Let’s modify algorithm in next way. Do not clear used marks after you find one path. 
* Instead of it run a series of DFS-es over all vertices in a single phase. 
* One such phase takes strictly O(V+E) time (graph full traversal) and can find more than one increasing path at once. 
* Moreover, the first phase will behave precisely as greedy algorithm (which is also improvement). 
* After running each phase you should clear used and run the next phase. Terminate when no path is found during one phase.

```cpp
#include<vector>
#include<utility>

using namespace std;

class KuhnImplementation {
    public:
        int n, k;
    vector<vector<int>> g;
    vector<int> pairs_of_right, pairs_of_left;
    vector<bool> used;

    bool kuhn(int v) {
        if (used[v]) return false;
        used[v] = true;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i] - n;
            if (pairs_of_right[to] == -1 || kuhn(pairs_of_right[to])) {
                pairs_of_right[to] = v;
                pairs_of_left[v] = to;
                return true;
            }
        }
        return false;
    }

    vector < pair < int, int > > find_max_matching(vector < vector < int > > & _g, int _n, int _k) {
        g = _g;
        //g[i] is a list of adjacent vertices to vertex i, where i is from left patr and g[i][j] is from right part
        n = _n;
        //n is number of vertices in left part of graph
        k = _k;
        //k is number of vertices in right part of graph

        pairs_of_right = vector < int > (k, -1);
        pairs_of_left = vector < int > (n, -1);
        //pairs_of_right[i] is a neighbor of vertex i from right part, on marked edge
        //pairs_of_left[i]  is a neighbor of vertex i from left part, on marked edge
        used = vector < bool > (n, false);

        bool path_found;
        do {
            fill(used.begin(), used.end(), false);
            path_found = false;
            //remember to start only from free vertices which are not visited yet
            for (int i = 0; i < n; ++i)
                if (pairs_of_left[i] < 0 && !used[i])
                    path_found |= kuhn(i);
        } while (path_found);

        vector < pair < int, int > > res;
        for (int i = 0; i < k; i++)
            if (pairs_of_right[i] != -1)
                res.push_back(make_pair(pairs_of_right[i], i + n));

        return res;
    }
};
```

#### Second way: Maximum flow algorithm.


Solving this problem using maximum flow algorithm is obvious. We will create two new vertices: S and T. 

We will create edges from S to all vertices of left part of graph and we will create edges from all vertices of 
right part of graph to T. 

All edges capacity will be equal to 1. After that we need to find maximum flow from S to T.

All used edges between left and right parts are maximum matching. It is obvious why it works. 

It is easier to understand, especially if you understand and know how to code max flow algorithm.


Implementation:

```cpp
#include<vector>
#include<utility>
using namespace std;
 
class MaxFlowImplementation
{
public:
	vector<vector<int> > g;
	vector<bool> used;
	int n, k;
 
	bool find_path(int a, int b) 
        {
		if(a == b) return true;
		if(used[a]) return false;
		used[a] = true;
		for(int i = 0; i < n+k+2; i++) 
			if(g[a][i] > 0 && find_path(i, b))
                        {
				g[a][i]--;
				g[i][a]++;
				return true;
			}
		return false;
	}
 
	vector<pair<int, int> > find_max_matching(vector<vector<int> > &v, int _n, int _k)
        {
		//v[i] is a list of adjacent vertices to vertex i, where i is from left part and v[i][j] is from right part
		n = _n;
		//n is number of vertices in left part of graph
		k = _k;
		//k is number of vertices in right part of graph
 
		g = vector<vector<int> >(n+k+2, vector<int>(n+k+2));
		//g[i][j] = 1 if there is edge between vertex i from left part 
		//            			    and vertex j from right part
		for(int i = 0; i < v.size(); i++)
                    for(int j = 0; j < v[i].size(); j++)
                        g[i][v[i][j]] = 1;
		int S = n+k;
		int T = n+k+1; 
		for(int i = 0; i < n; i++)
			g[S][i] = 1;
		for(int i = 0; i < k; i++)
			g[n+i][T] = 1;
 
		vector<vector<int> > _g(g);
 
		used = vector<bool> (n+k+2, false);
		while(find_path(S, T))
			fill(used.begin(), used.end(), false);
 
		vector<pair<int, int> > res;
		for(int i = 0; i < n; i++)
			for(int j = n; j < n+k; j++)
				if(g[i][j] < _g[i][j])
					res.push_back(make_pair(i, j));
 
		return res;
	}
};
```						      

### DISCUSSION

Solving maximum bipartite problem can be useful to solve problems using Hungarian algorithm, minimum vertex cover, etc. 
To tell the truth, while max - flow implementation is easier to understand and implement, 
Kuhn algorithm is more effective, especially improved implementation.

Usage:
if you use Kuhn algorithm
`KuhnImplementation obj;`

or if you use max flow algorithm
`MaxFlowImplementation obj`

`return obj.find_max_matching(g, n, k).size();`

I believe that "improved version" is not a good idea of acceleration. 

There is an easy approach which works better than simply precalculating greedy matching.

* Do not clear used marks after you find one path. Instead of it run a series of DFS-es over all vertices in a single phase.
* One such phase takes strictly O(V+E) time (graph full traversal) and can find more than one increasing path at once. 
* Moreover, the first phase will behave precisely as greedy algorithm, so it supersedes you improvement. 
* After running each phase you should clear used marks and run the next phase. 
* Terminate when no path is found during one phase.

To apply this improvement to your simple implementation do the following:

1. Store pairs for vertices of left part too.

Add declaration: `vector<int> pair2;`
Add initialization: `pair2 = vector<int> (n, -1);`
Do not forget to set it in DFS:
```cpp
pairs [to] = v;
pair2 [v] = to; //added line
return true;
```
	
2. Replace your DFS(kuhn) calls code in find_max_matching with this:
	
```cpp	
    int phases = 0;
		
    bool haschanged;
    do {
      fill(used.begin(), used.end(), false);
      haschanged = false;
      //remember to start only from free vertices which are not visited yet
      for (int i = 0; i < n; ++i)
        if (pair2[i] < 0 && !used[i])
          haschanged |= kuhn (i);
      phases++;
    } while (haschanged);
```

* The full working time is O(P(N + M)) where P is number of phases. It is clear that it won't exceed min(n, k)<=V.
* This acceleration is also applicable to maxflow problem with unit capacities. Run DFS series in a single phase 
* without clearing used in between. And do not use "used" mark for source/sink.

</details>														  

Implementation Details:

Ref: https://csacademy.com/contest/archive/task/no-prime-sum/solution/
														   
```cpp
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 1e4, kMaxVal = 2e5+5;

vector<int> left_nodes, right_nodes;
vector<int> vertex[kMaxN];

bool is_prime[kMaxVal];

void Init() {
    for (int i = 2; i < kMaxVal; i += 1) {
        is_prime[i] = true;
    }

    for (int i = 2; i < kMaxVal; i += 1) {
        if (not is_prime[i]) {
            continue;
        }

        for (int64 j = 1LL * i * i; j < kMaxVal; j += i) {
            is_prime[j] = false;
        }
    }
}

bool visited[kMaxN], matched[kMaxN];
int match_pair[kMaxN];

// Kuhn's algorithm						
bool Match(int node) {
    visited[node] = true;

    // find an arbitrary matching by some simple algorithm 
    // (a simple heuristic algorithm) improve this matching
    for (auto itr : vertex[node]) {
        if (not matched[itr]) {
            matched[node] = true;
            matched[itr] = true;

            match_pair[node] = itr;
            match_pair[itr] = node;

            return true;
        }
    }

    for (auto itr : vertex[node]) {
        if (not visited[match_pair[itr]] and Match(match_pair[itr])) {
            matched[node] = true;

            match_pair[node] = itr;
            match_pair[itr] = node;

            return true;
        }
    }

    return false;
}

int main() {
    Init();
    
    int n;
    cin >> n;
    vector<int> elements(n);
    
    for (auto itr : elements) {
        cin >> itr;
        if (itr & 1) {
            left_nodes.push_back(itr);
        } else {
            right_nodes.push_back(itr);
        }
    }

    // add edges between nodes which have a prime sum
    for (int i = 0; i < (int)left_nodes.size(); i += 1) {
        for (int j = 0; j < (int)right_nodes.size(); j += 1) {
            if (not is_prime[left_nodes[i] + right_nodes[j]]) {
                continue;
            }

            int a = i;
            int b = j + left_nodes.size();
            vertex[a].push_back(b);
        }
    }
    
    // get the maximum matching
    bool ok = true;
    while (ok) {
        ok = false;
	// check if there is any augmenting path

        for (int i = 0; i < (int)left_nodes.size(); i += 1) {
            visited[i] = false;
        }

        for (int i = 0; i < (int)left_nodes.size(); i += 1) {
            if (visited[i] or matched[i]) {
                continue;
            }

            if (Match(i)) {
                ok = true;
            }
        }
    }

    // the actual elements that should be erased in order to not have
    // a prime sum
    vector<int> unselected_q;
    vector<int> selected(n, 0);
    for (int i = 0; i < (int)left_nodes.size(); i += 1) {
        if (matched[i]) {
	    // mark these candidates for vertex cover
	    // we are unmarking some of the matched during BFS below
            selected[i] = true;
        } else {
	    // un-matched vertices on the left
            unselected_q.push_back(i);
        }
    }

    // fiind all the vertices reachable from unmatched vertices on left
    while (unselected_q.size()) {
        int node = unselected_q.back();
        unselected_q.pop_back();

        for (auto itr : vertex[node]) {
            if (not selected[itr]) {
		// if the right vertex is not already choosen for vertex cover
                int oth = match_pair[itr];
                if (selected[oth]) {
                    unselected_q.push_back(oth);
                    selected[oth] = false;
                }
                selected[itr] = true;
            }
        }
    }

    // print the solution :)
    int r = 0;
    for (auto itr : selected) {
        r += itr;
    }

    cout << r << '\n';
    for (int i = 0; i < n; i += 1) {
        if (not selected[i]) {
            continue;
        }

        if (i < (int)left_nodes.size()) {
            cout << left_nodes[i] << ' ';
        } else {
            cout << right_nodes[i - (int)left_nodes.size()] << ' ';
        }
    }

    cout << '\n';

    return 0;
}
```														   
