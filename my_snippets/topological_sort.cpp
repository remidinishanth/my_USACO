// Kahn’s algorithm - It looks like a ‘modified BFS’. 
	
// For implementing topsort, We use an algorithm called Kahn's Algorithm. 
// The algorithm is implemented by selecting a node with in-degree equal to 0, 
// pushing the node into the topological order and removing all edges attached to it. 
// (In-degree is the number of edges that come into a node). 
// The process is repeated until all nodes are added into the topological order. 
// If the process terminates before all nodes are added then it means there is a cycle in the graph.

enqueue vertices with zero incoming degree into a (priority) queue Q;
while (Q is not empty) {
	vertex u = Q.dequeue(); put vertex u into a topological sort list;
	remove this vertex u and all outgoing edges from this vertex;
	if such removal causes vertex v to have zero incoming degree
		Q.enqueue(v); 
}


/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

// source Benq: https://codeforces.com/contest/1344/submission/79163958
 
template<int SZ> struct TopoSort {
	int N, in[SZ];
	vi res, adj[SZ];
	void ae(int x, int y) { adj[x].pb(y), in[y] ++; }
	bool sort(int _N) {
		N = _N; queue<int> todo;
		FOR(i,1,N+1) if (!in[i]) todo.push(i);
		while (sz(todo)) {
			int x = todo.front(); todo.pop(); res.pb(x);
			trav(i,adj[x]) if (!(--in[i])) todo.push(i);
		}
		return sz(res) == N;
	}
};
// Usage
TopoSort<MX> T;
F0R(i,m) { T.ae(j,k); }
if (!T.sort(n)) { return -1; }

// Source: ffao https://codeforces.com/contest/1344/submission/79215689

vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority queue for lexic. smallest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(-i);
	while (!q.empty()) {
		int i = -q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(-x);
	}
	return ret;
}

// Source: CP3

vi ts; // global vector to store the toposort in reverse order
void dfs2(int u) { // different function name compared to the original dfs
  dfs_num[u] = VISITED;
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    ii v = AdjList[u][j];
    if (dfs_num[v.first] == UNVISITED)
      dfs2(v.first);
  }
  ts.push_back(u); // that’s it, this is the only change
}

// inside int main()
ts.clear();
memset(dfs_num, UNVISITED, sizeof dfs_num);
for (int i = 0; i < V; i++) // this part is the same as finding CCs
if (dfs_num[i] == UNVISITED)
dfs2(i);
reverse(ts.begin(), ts.end());
// We can check like this
for (int i = 0; i < n; ++i) {
  in_order[ts[i]] = i;
}
for (auto [u, v] : edges) {
  if (in_order[u] > in_order[v]) {
    cout << "-1\n";
    return 0;
  }
}

// source tourist: https://codeforces.com/contest/1344/submission/79163314
template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };
 
  vector<edge> edges;
  vector<vector<int>> g;
  int n;
 
  graph(int _n) : n(_n) {
    g.resize(n);
  }
 
  virtual int add(int from, int to, T cost) = 0;
};
 
template <typename T>
class digraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;
 
  digraph(int _n) : graph<T>(_n) {
  }
 
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
 
  digraph<T> reverse() const {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    return rev;
  }
};
 
template <typename T>
vector<int> find_topsort(const digraph<T> &g) {
  vector<int> deg(g.n, 0);
  for (int id = 0; id < (int) g.edges.size(); id++) {
    deg[g.edges[id].to]++;
  }
  vector<int> x;
  for (int i = 0; i < g.n; i++) {
    if (deg[i] == 0) {
      x.push_back(i);
    }
  }
  for (int ptr = 0; ptr < (int) x.size(); ptr++) {
    int i = x[ptr];
    for (int id : g.g[i]) {
      auto &e = g.edges[id];
      int to = e.to;
      if (--deg[to] == 0) {
        x.push_back(to);
      }
    }
  }
  if ((int) x.size() != g.n) {
    return vector<int>();
  }
  return x;
}

// Usage: digraph<int> g(n); edge g.add(x, y); vector<int> order = find_topsort(g);


// Given an array of sorted words in the alien language (or a dictionary of words in the alien language), 
// return a string containing the correct order of alphabets used in the alien language.
// If many consistent orderings are possible, return the lexicographically smallest ordering.

// We can use "Topological sort" (or Topsort) algorithm to answer this question. 
// Given a directed graph, topsort answers the question of "What comes after what".

// In question we are asked to find the alphabetical order of an Alien language and we are given a dictionary of words 
// in the alien language. Hence we can form a directed graph (like a->b->c..->z) using the dictionary and 
// then find the topological order of that graph and we have the alphabetical order in alien language!

// To produce the graph from dictionary,
// Compare first and second word, during the first instance of mismatch of letters in first and second, 
// or when first[i]!=second[i], we can form an edge from first[i] to second[i], because first[i] has more priority than second[i]. 
// The same process is done till second last-last. (If there is only 1 word, no edge is formed)

// For implementing topsort, We use an algorithm called Kahn's Algorithm. The algorithm is implemented by selecting a node with in-degree equal to 0, 
// pushing the node into the topological order and removing all edges attached to it. 
// (In-degree is the number of edges that come into a node). The process is repeated until all nodes are added into the topological order.
// If the process terminates before all nodes are added then it means there is a cycle in the graph.

// Since we want lexicographicaly smallest ordering, we will always remove edges from the lexicographically smallest node with in-degree 0.

#include<vector>  // For vector
#include<string>  // For string
#include<set>	  // For set

class AlienAlphabetsOrder {
    private:
        std::set < int > adj[26]; // Adjacency list
    //std::set is used so that no duplicate edges are formed. (Adjacency matrix may also be used)

    std::string answer = ""; // Final answer
    int addEdge(std::string a, std::string b) {
        //Function to add edge given two words 'a' and 'b' where 'a' appears before 'b'
        //in the dictionary

        int mn = std::min(a.length(), b.length());
        for (int i = 0; i < mn; i++) {
            if (a[i] != b[i]) {
                //As stated in editorial, we will add edge at the first instance of mismatch
                //of letters between the words
                adj[int(a[i] - 'a')].insert(int(b[i] - 'a'));
                return 0;
            }
        }
        return 0;
    }

    int kahn() {
        //Kahn's algorithm for topological sorting
        int inDegree[26] = { 0 };
        //Array to store in-degree of nodes

        for (int i = 0; i < 26; i++) {
            for (int x: adj[i]) {
                inDegree[x]++;
                // If there is an edge from i to x then in-degree of x should increase by 1
            }
        }

        std::set < int > st;
        for (int i = 0; i < 26; i++) {
            if (inDegree[i] == 0) {
                // Picking all nodes with in-degree = 0 for kahn's algorithm
                // We will then choose the lexicographically smallest node
                // Since set will automatically sort in ascending order we can easily choose the smallest node.
                st.insert(i);
            }
        }

        while (!st.empty()) {
            int cur = * st.begin();
            answer += char(cur + 'a');
            //Selected node added to topological ordering (answer string is our topological order)
            st.erase(st.find(cur));
            //Selected(smallest) node removed
            for (int x: adj[cur]) {
                //in-degree will decrease by 1 since we are removing all edges from the chosen node
                inDegree[x]--;

                if (inDegree[x] == 0) {
                    //As stated in editorial we again take all elements with indegree 0 and choose the smallest node
                    st.insert(x);
                }
            }
        }

        for (int i = 0; i < 26; i++) {
            //If all nodes are taken then all nodes will finally have in-degree 0 
            //Else all nodes arent taken which means there is a cycle in the graph
            if (inDegree[i] > 0) return -1;
        }
        return 0;
    }

    public:
        std::string getAlphabetOrder(std::vector < std::string > sortedWords) {
            int sz = sortedWords.size();
            for (int i = 0; i < sz - 1; i++) {
                addEdge(sortedWords[i], sortedWords[i + 1]);
            }
            if (kahn() != -1) {
                // If kahn() != -1 then it means there is no cycle in the graph and we should return answer
                return answer;
            } else {
                // If kahn() == -1 then it means there is a cycle in the graph and we should return empty string
                return "";
            }
        }
};
