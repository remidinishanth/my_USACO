### Graph problems

#### Degree Set codeforces
* https://codeforces.com/contest/976/problem/D Degree set

**Solution:**

We prove that the answer always always exists by constructing it.

* Graph for `n = 0` is a single vertex;
* Graph for `n = 1` is a clique of `d1 + 1` vertices;
* Graph for some `(d1, d2, ..., dk)` is obtained from the graph `(d2 - d1, d3 - d1, ..., dk - 1 - d1)` by adding `(dk - dk - 1)` vertices initially connected to nothing and `d1` vertices connected to all previously mentioned ones.

The vertices connected to nothing got degrees `d1`, the vertices from the previous step increased their degrees by `d1` and finally there appeared vertices of degree `dk`. The number is vertices is `dk + 1` as needed.

If we only have degrees `{d1, d2}` in the set, then we have have complete graph with `d1` nodes and then add `(d2 - d1 + 1)` nodes connecting to `d1` nodes of complete graph.
This way we will have `(d2 - d1 + 1)` nodes with degree `d1` and `d1` vertices with degree `(d1 - 1 + d2 - d1 + 1) = d2`


**Intuition and Analysis:**

Every node of degree `d[n]` must be connected to all other nodes, How many such nodes can exist? There should be `>= 1` and `<= d[1]`.  

Let's assume that there exists `d[1]` nodes with degree `d[n]`, the node of degree `d[1]` has all sides connected to the point of degree `d[n]`, so we have `d[1]` points with degree `d[n]`, at this time, the degree of all nodes is equivalent to `d[1]`.

Then we subtract `d[1]` from all `d[2]~d[n-1]`, so we convert it into a sub-problem, but this sub-problem requires that the number of points is exactly the current maximum degree + 1, also That is `d[n-1]-d[1]+1`. 

We know that the graph we have constructed so far has `d[n-1] - d[1] + 1` points in addition to `d[1]` points with the largest degree, then we only need to take `d[n] - d[n-1]` points of degree `d[1]` will do. 

The rest are all recursive, and if the boundary is no point, it will return, or if there is only one degree, it will be a complete graph.

Solution: https://blog.csdn.net/m0_37809890/article/details/80153601

Recursive Solution:

```cpp
const int nax = 1e6 +  10;
int n, cnt, u[nax], v[nax];
vi degree;

inline void solve(int l, int r, int vl, int vr) {
    if(l > r) return;
    if(l == r) {
        // create a complete graph between [vl, vr]
        for(int i = vr; i > vl; --i)
            for(int j = vl; j < i; j++)
                // add edge between i and j
                cnt++, u[cnt] = i, v[cnt] = j;
        return;
    }

    // create degree[l] vertices of degree[r] from (vr - w, vr]
    int w = degree[l];
    for(int  i = vr; i > vr - w; --i)
        for(int j = vl; j < i; j++)
            cnt++, u[cnt] = i, v[cnt] = j;

    // Solve the subproblem
    int nxtl = vl + degree[r] - degree[r-1], nxtr = vr - degree[l];
    // (degree[l+1] - degree[l], ..., degree[r-1] - degree[l])
    for(int i = l + 1; i < r; i++)
        degree[i] -= degree[l];
    solve(l + 1, r - 1, nxtl, nxtr);
}

int main() {
    int n; scanf("%d", &n);
    degree = vi(n+1);
    for(int i=1; i <= n; i++) scanf("%d", &degree[i]);
    solve(1, n, 1, degree[n] + 1);
    // print all the edges
    printf("%d\n", cnt);
    for(int i=1; i <= cnt; i++)
        printf("%d %d\n", u[i], v[i]);
    return 0;
}

```

Iterative Solution

```cpp
int main() {
    int n; scanf("%d", &n);
    vi degree(n+1);
    for(int i=1; i <= n; i++) scanf("%d", &degree[i]);
    // degree is already sorted
    int total_vertices = degree.back() + 1;
    int l = 1, r = n, ready = 0;
    int edges = 0;
    for(int i = 1; i < total_vertices; i++){
        if(degree[l] <= ready) l++, r--;
        else if(ready + total_vertices - i == degree[r]) {
            // connecting all the vertices from [i + 1, total_vertices] to i
            // now the degree of this i will be degree[r]
            ready++;
            // number of new edges added
            edges += total_vertices - i;
        }
    }
    printf("%d\n", edges);
    l = 1; r = n; ready = 0;
    for(int i = 1; i < total_vertices; i++){
        debug() << imie(l) imie(r) imie(degree[l]) imie(degree[r]) imie(ready) imie(total_vertices - i);
        if(degree[l] <= ready) l++, r--;
        else if(ready + total_vertices - i == degree[r]) {
            for(int j = i + 1; j <= total_vertices; j++) printf("%d %d\n", i, j);
            ready++;
        }
    }
    return 0;
}
```

In case we have Degree Set as `{1, 2, 3, 6, 9}`.

The construction is as follows:

Now sure why it works:

```
5
1 2 3 6 9
15
 [l: 1]  [r: 5]  [degree[l]: 1]  [degree[r]: 9]  [ready: 0]  [total_vertices - i: 9]
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
 [l: 1]  [r: 5]  [degree[l]: 1]  [degree[r]: 9]  [ready: 1]  [total_vertices - i: 8]
 [l: 2]  [r: 4]  [degree[l]: 2]  [degree[r]: 6]  [ready: 1]  [total_vertices - i: 7]
 [l: 2]  [r: 4]  [degree[l]: 2]  [degree[r]: 6]  [ready: 1]  [total_vertices - i: 6]
 [l: 2]  [r: 4]  [degree[l]: 2]  [degree[r]: 6]  [ready: 1]  [total_vertices - i: 5]
5 6
5 7
5 8
5 9
5 10
 [l: 2]  [r: 4]  [degree[l]: 2]  [degree[r]: 6]  [ready: 2]  [total_vertices - i: 4]
 [l: 3]  [r: 3]  [degree[l]: 3]  [degree[r]: 3]  [ready: 2]  [total_vertices - i: 3]
 [l: 3]  [r: 3]  [degree[l]: 3]  [degree[r]: 3]  [ready: 2]  [total_vertices - i: 2]
 [l: 3]  [r: 3]  [degree[l]: 3]  [degree[r]: 3]  [ready: 2]  [total_vertices - i: 1]
9 10
```

Degree of vertices = `{9, 1, 1, 1, 6, 2, 2, 2, 3, 3}`.
