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

// This algo tries to find and then eliminate augmenting paths
// starting from free vertices on the left set

// O(VE) as code runs V times and each DFS takes O(E) time

// source: CP3 Augmenting Path Algorithm for Max Cardinality Bipartite Matching

// Hopcroft Karp’s algorithm can solve the MCBM problem in O(√V E)
