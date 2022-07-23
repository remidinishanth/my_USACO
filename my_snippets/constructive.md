### Graph problems

#### Degree Set codeforces
* https://codeforces.com/contest/976/problem/D Degree set

Solution: https://blog.csdn.net/m0_37809890/article/details/80153601

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
