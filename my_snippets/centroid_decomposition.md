# Centroid Decomposition

## Problem & Motivation

Given a tree, we are asked to find all the number of pairs `(u, v)` such that `dist(u, v) ≤ D`.

**Solution**

Let us fix one node of Tree by picking a vertex of the tree and call it `c`. Now let us split all the possible paths into classes: 
1) Some of the paths may not include this vertex `c`, then it will be completely inside one of the subtrees formed after removing `c`.
2) If the path includes node `c`, then we can break into two segments `u to c` and `c to v`.

![image](https://user-images.githubusercontent.com/19663316/119270642-5029fd00-bc1b-11eb-8d9c-9143a631b52e.png)
![image](https://user-images.githubusercontent.com/19663316/119270647-57510b00-bc1b-11eb-8fb4-08779a76f9a9.png)
![image](https://user-images.githubusercontent.com/19663316/119270631-3e485a00-bc1b-11eb-9722-7521a300f3af.png)

So what will do is that: We will pick a vertex `c`, remove that vertex from the tree and recursively find the number of pairs `(u, v)` in the subtree. In the end we will calculate the number of pairs which include the vertex `c`.

![image](https://user-images.githubusercontent.com/19663316/119271233-49e95000-bc1e-11eb-9e33-067163ea3e2f.png)

We will need to calculate `d[v]` which is distance from `(c, v)`, this can be precalculated in linear time. If we fix vertex `u`, then we will need to find all the vertices such that `d[v] ≤ D - d[u]`. Say we have an array of distances `d[i]` and maintain sorted order of this array and find the number of nodes `v` using binary search.

In this problem we will need to find the vertices which belong to different subtrees. We can do it in the following ways:

1. Add elements of first subtree into binary search tree form left to right and then iterate for elements `v` of second subtree and query the number of elements `u` satisfying `dist(u, v) ≤ D`.
![image](https://user-images.githubusercontent.com/19663316/119271191-1f979280-bc1e-11eb-9c30-7ad4144d959d.png)\
Then add the elements of second subtree to binary search tree and continue. Each time we consider a subtree, all the elements of previous subtrees are in our binary search tree.

2. Another way to calculate is to subtract the values we don't want to include. For a node `u` calculate all the nodes `v` of tree such that `d[v] ≤ D - d[u]` and then subtract the number of nodes which are in the same subtree as `u`.


Important thing is how to choose node `c`. Time complexity depends on how good is the node `c`, when we use divide and conquer technique we want to divide our problem into subproblems of equal size. We choose our vertex to be centroid of the tree.

A centroid is defined as a vertex such that when removed, all of the resulting subtrees have a size of at most half that of the original tree (that is, `⌊n/2⌋`).

![image](images/centorid_decomposition.gif)

Centroid of the tree is different than centre of tree(centre of a tree is simply the middle vertex/vertices of the diameter of the tree). Centre of the tree is the node such that if rooted minimizes the height of the rooted tree. The centre of the tree in the middle of the largest path in the tree. In the following image `blue` node is the centre of the tree whereas the `red` node is the centroid of the tree.

![image](https://user-images.githubusercontent.com/19663316/119272034-c3367200-bc21-11eb-9a8f-25e2805ff07e.png)


**Existence: Is there always a centroid?** Yes. Every tree has at least one centroid.

**Theorem (Jordan, 1869):** Given a tree with `N` nodes, there exists a vertex whose removal partitions the tree into components, each with at most `N/2` nodes. (i.e. For any given tree, the centroid always exists)

**Proof:** Let us chose any arbitrary vertex `a` in the tree, if `a` satisfies the property of the centroid, then we are done, else there exists one (and only one - if two such nodes exists then size of tree is `> N`) component with more than `N/2` vertices. We now consider the vertex `b` adjacent to `a` in that component and apply the same argument for `b` . We continue the same procedure unless we find the required vertex. Also, we never go back to any old vertices because the component containing them must have less than `N/2` vertices(because the subtree of `b` contains size `> N/2`). Since the no of vertices are finite, and we visit each vertex at most once, the procedure must end and hence the centroid must exist.

![image](images/centroid_decomposition2.gif)

![image](https://user-images.githubusercontent.com/19663316/119269663-6aada780-bc16-11eb-8d91-051c2db7fbe3.png)

**Finding the centroid of a tree:** One way to find the centroid is to pick an arbitrary root, then run a depth-first search computing the size of each subtree, and then move starting from root to the largest subtree until we reach a vertex where no subtree has size greater than N/2. This vertex would be the centroid of the tree.

```cpp

#include <iostream>
#include <vector>

using namespace std;

const int maxn = 200010;

int n;
vector <int> adj[maxn];
int subtree_size[maxn];

int get_subtree_size(int node, int par = -1) {
    int& res = subtree_size[node];
    res = 1;
    for (int i : adj[node]) {
	if (i == par) continue;
	    res += get_subtree_size(i, node);
	}
    return res;
}

int get_centroid(int node, int par = -1) {
    for (int i : adj[node]) {
	if (i == par) continue;
	if (subtree_size[i] * 2 > n) {
	    return get_centroid(i, node);
	}
    }
    return node;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
	int a, b;
	cin >> a >> b;
	a--; b--;
	adj[a].push_back(b);
	adj[b].push_back(a);
    }
    get_subtree_size(0);
    cout << get_centroid(0) + 1 << endl;
}

```


TODO - https://codeforces.com/blog/entry/52492?locale=en

Implementation: https://codeforces.com/contest/321/submission/3973635, https://codeforces.com/contest/321/submission/45791725, https://usaco.guide/plat/centroid?lang=cpp


![image](https://user-images.githubusercontent.com/19663316/119269676-81ec9500-bc16-11eb-9448-ab4e7968c6b9.png)


REF: 
* https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308
* https://robert1003.github.io/2020/01/16/centroid-decomposition.html 

