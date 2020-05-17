vi match,vis;

int Aug(int v){ // return 1 if an augmenting path is found
    if(vis[v]) return 0;
    vis[v]=1;
    for(int j=0;j<(int)Adj[v].size();j++){
        int r=Adj[v][j];
        if(match[r]==-1 || Aug(match[r])){
            match[r]=v;return 1;
        }
    }
    return 0;
}

// left set vertices are from [1..n]
// right set vertices are from [n+1..n+m]

// in main
// build unweighted bipartite graph with directed edge left->right set
int MCBM=0;
match.assign(V,-1);
for(int v=0;v<n;v++){
    vis.assign(n,0);
    MCBM+=Aug(v);
}

// This algorithm will keep doing this process of finding augmenting paths and eliminating
// them until there is no more augmenting path.

// This algo tries to find and then eliminate augmenting paths
// starting from free vertices on the left set

// O(VE) as code runs V times and each DFS takes O(E) time

// source: CP3 Augmenting Path Algorithm for Max Cardinality Bipartite Matching

// Hopcroft Karp’s algorithm can solve the MCBM problem in O(√V E)


/*
NAME
Solving Maximum Bipartite Matching Problem
source: https://apps.topcoder.com/forums/?module=Thread&threadID=684427&start=0

PROBLEM
In this article we shall speak about Solving Maximum Bipartite Matching Problem. 
There is a bipartite graph containing N vertices (n vertices in left part and k = N-n vertices in right part of graph) 
and M edges. We are to find maximum bipartite matching, i.e. mark maximum number of edges, so that no one of them 
have adjacent vertices with each other. This problem can be easily solved in two ways.

SOLUTION
First way: Kuhn’s algorithm.

Chain with length k is a simple path (i.e. it contains no repeated vertices or edges) that has k edges in the 
bipartite graph. Alternating chain (in a bipartite graph, with respect to some matching) is a chain in which the 
edges alternately belong / not belong to the matching. The increasing chain (in a bipartite graph, with respect 
to a matching) is an alternating chain, whose initial and final vertices (as well as edges) do not belong to matching.

Berja’s theorem:
Matching is maximal if and only if there are no increasing chains with respect to it.

So, let’s notice that if we find an increasing chain, we can increase our matching by one. 
We will go along this increasing chain and mark edges which are not marked and unmark edges that were marked 
(first edge is not marked by definition – we will mark it, second is marked, so we will unmark it and so on). 
It is obvious that by doing this operation we will increase our matching by one, because length of increasing chain 
is always odd and because in this chain we had [k/2]+1 unmarked edges and [k/2] marked edges and after rematching 
we have [k/2] unmarked edges and [k/2]+1 marked edges in the chain.

So the main idea of the algorithm is to search increasing chains while we can and increase matching.

Well, new problem is how to find increasing chains. Kuhn’s algorithm is based on dfs (depth first search) or 
bfs (breadth first search) algorithm.

Complexity of searching an increasing chain is O(N+M) and maximum number of them is N/2, 
overall asymptotic is O(N*N + N*M) = O(NM)

Let’s see how we will search increasing chains: we shall use dfs. We will call dfs only from vertices of graph’s left part. 
From left part it goes to right only using not marked edges, and from right to left only using marked edges. 
In our implementation dfs will be called only from left graph’s vertices and will return bool – true if it found chain 
and false if not. From current vertex algorithm will go through all adjacent not marked edges to vertex from right part 
called TO. If TO has no adjacent marked edges, dfs will return true, because it is last vertex of increasing chain. 
If it has, we will call dfs from TO’s neighbor on marked edge and return true if it returned true.
*/

// Pseudocode:
bool kuhn(vertex v) 
{
        if (used[v]) return false;
        used[v] = true;
 
        for(vertex q adjacent to v) 
        {
                if((q has no pair) or kuhn(pairs[q])) 
                {
                        pairs[q] = v;
                        return true;
                }   
        }
}
find_max_matching 
{
        for(vertex v = {1,..,n}) 
        {
                used = {0};
                kuhn(v);
        }
}

// Implementation (C++):

#include<vector>
#include<utility>
using namespace std;
 
class KuhnImplementation
{
public:
	int n, k;
	vector < vector<int> > g;
	vector<int> pairs;
	vector<bool> used;
 
 
	bool kuhn (int v) 
        {
		if (used[v])  return false;
		used[v] = true;
		for (int i = 0; i < g[v].size(); ++i) 
                {
			int to = g[v][i]-n;
			if (pairs[to] == -1 || kuhn (pairs[to])) 
                        {
				pairs [to] = v;
				return true;
			}
		}
		return false;
	}
 
	vector<pair<int, int> > find_max_matching(vector<vector<int> > &_g, int _n, int _k) 
    {
		g = _g;
		//g[i] is a list of adjacent vertices to vertex i, where i is from left patr and g[i][j] is from right part
		n = _n;
		//n is number of vertices in left part of graph
		k = _k;
		//k is number of vertices in right part of graph
 
		pairs = vector<int> (k, -1);
		//pairs[i] is a neighbor of vertex i from right part, on marked edge
		used = vector<bool> (n, false);
		for (int i = 0; i < n; ++i) 
                {
			fill(used.begin(), used.end(), false);
			kuhn (i);
		}
	
		vector<pair<int, int> > res;
		for(int i = 0; i < k; i++)
			if(pairs[i] != -1)
				res.push_back(make_pair(pairs[i], i+n));
 
		return res;
 
	}
};


// Improved implementation:

// Let’s modify algorithm in next way. Do not clear used marks after you find one path. 
// Instead of it run a series of DFS-es over all vertices in a single phase. 
// One such phase takes strictly O(V+E) time (graph full traversal) and can find more than one increasing path at once. 
// Moreover, the first phase will behave precisely as greedy algorithm (which is also improvement). 
// After running each phase you should clear used and run the next phase. Terminate when no path is found during one phase.
#include<vector>
#include<utility>
using namespace std;
 
class KuhnImplementation
{
public:
	int n, k;
	vector < vector<int> > g;
	vector<int> pairs_of_right, pairs_of_left;
	vector<bool> used;
 
 
	bool kuhn (int v) 
	{
		if (used[v])  return false;
		used[v] = true;
		for (int i = 0; i < g[v].size(); ++i) 
		{
			int to = g[v][i]-n;
			if (pairs_of_right[to] == -1 || kuhn (pairs_of_right[to])) 
			{
				pairs_of_right[to] = v;
				pairs_of_left[v] = to;
				return true;
			}
		}
		return false;
	}
 
	vector<pair<int, int> > find_max_matching(vector<vector<int> > &_g, int _n, int _k) 
	{
		g = _g;
		//g[i] is a list of adjacent vertices to vertex i, where i is from left patr and g[i][j] is from right part
		n = _n;
		//n is number of vertices in left part of graph
		k = _k;
		//k is number of vertices in right part of graph
 
		pairs_of_right = vector<int> (k, -1);
		pairs_of_left = vector<int> (n, -1);
		//pairs_of_right[i] is a neighbor of vertex i from right part, on marked edge
		//pairs_of_left[i]  is a neighbor of vertex i from left part, on marked edge
		used = vector<bool> (n, false);
 
 
		bool path_found;
		do {
			fill(used.begin(), used.end(), false);
			path_found = false;
			//remember to start only from free vertices which are not visited yet
			for (int i = 0; i < n; ++i)
				if (pairs_of_left[i] < 0 && !used[i])
					path_found |= kuhn (i);
		} while (path_found);
 
 
		vector<pair<int, int> > res;
		for(int i = 0; i < k; i++)
			if(pairs_of_right[i] != -1)
				res.push_back(make_pair(pairs_of_right[i], i+n));
 
		return res;
	}
};
