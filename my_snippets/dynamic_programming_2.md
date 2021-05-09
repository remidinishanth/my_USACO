### Bounded Knapsack

The bounded knapsack problem is: you are given n types of items, you have ui items of i-th type, and each item of i-th type weighs wi and costs ci. What is the maximal cost you can get by picking some items weighing at most W in total?

The best algorithm I could find on the Internet has complexity `O(W*n*log(max(ui))`. It goes like this: instead of having ui items of type i, we create several new types that are multiples of type i, for example items with weight `2*wi` and cost `2*ci`, then the same for 4 and so on, and declare that we have just one item of each type. We create the new types in such a way that the number of new types is logarithmic, and anything that was possible to represent using the old items is also representable using the new items and vice versa. We get a 0-1 knapsack problem with `n * log(max(ui)` types which leads to a dynamic programming solution with the above complexity.

However, when similar problem was given at a [Codeforces contest](https://codeforces.com/problemset/problem/95/E), several people came up with a `O(W*n)` solution for this problem. First, we start with the standard dynamic programming solution: let `dp[k,w]` be the best cost that we can get by packing the total weight of w using the first k item types. Each new type is then handled as follows: `dp[k][w] = min(dp[k-1,w], dp[k-1,w-wk]+ck, ..., dp[k-1,w-uk*wk]+uk*ck)`. This dynamic programming has `O(W*n)` states, and each state is processed in `O(max(ui))`.

But we can process each state in O(1) amortized time! Let's take a look at the above recurrence. First, we notice that we can separate all values of w into wk groups, based on the remainder of division on wk, and those groups can be handled separately. Then, for each group, the problem we need to solve is to find `min(a[i], a[i-1]+c, a[i-2]+2*c, ..., a[i-k]+k*c)`. By setting `bi=ai-i*c`, this expression is transformed into `min(bi+i*c,b[i-1]+(i-1)*c+c, ...)`, which is just `i*c+min(bi, b[i-1], ..., b[i-k])`. Thus our problem is reduced to finding minimums of groups of k+1 consecutive numbers in a given array.

And this, in turn, is a well-known problem that is solvable in O(size of array) using one of the two methods: we can either maintain a sequence of incremental (from the end) minima for a segment of size k+1 and update it quickly when we shift one position to the right, or we can just separate the entire array into blocks of size k+1, and calculate the prefix and suffix minima for each block - this allows to find the minimum for any block of size k+1 by splitting it into two blocks with precomputed answers.

Is it well-known that bounded knapsack is solvable in O(W*n) worst-case?

source: https://petr-mitrichev.blogspot.com/2011/07/integral-bounded-knapsack-problem.html

### Elaborate explanation

In the above DP, `dp[k][w] = max(dp[k-1,w], dp[k-1,w-wk]+ck, dp[k-1, w-2*wk]+2*ck..., dp[k-1,w-uk*wk]+uk*ck)`

An interesting observation is that we only deal with every wk-th element from the previous array to decide on any element in the current array.

Let us for a minute ignore the fact that we have only a fixed number of items of each type and instead assume that we have an infinite number of items of each type. Let us assume that item i weighs 3 and costs 9. If we make that assumption, we see that the best solution at DPk, 12 is represented by taking the maximum of the cells colored in green below.

![image](https://user-images.githubusercontent.com/19663316/117568034-3f866c80-b0dc-11eb-92ac-bf7348b72b01.png)

What we have essentially done is added: `0*9` to `dp[k-1, 12]`, `1*9` to `dp[k-1, 9]`, `2*9` to `dp[k-1, 6]`, `3*9` to `dp[k-1, 3]` and `4*9` to `dp[k-1, 0]`.

The problem has reduced to finding the maximum value among all the values of the array that is formed by picking every wk-th element from the previous best solution and adding some multiple of ck to it.

### CF Problem

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

#### Input
The first line contains two integers n and m (1 ≤ n, m ≤ 10^5). They are the number of islands and the number of roads correspondingly. Next m lines contain road descriptions. Each road is defined by the numbers of islands that it connects: that is, by two integers u and v (1 ≤ u, v ≤ n). Some roads can connect an island with itself; there can be more than one road between a pair of islands. Numbers in each line are separated by exactly one space character.

#### Output
If there's no solution, output the only number "-1" (without the quotes). Otherwise, output the minimum number of roads r that need to be built to get a lucky region.

#### Solution

Let's first find the different sizes of regions(connected components), we might have more than one component of a particular size.

Let A[i] - sorted array of sizes of different connection components, C[i] – number of connection components of size A[i], This is similar to Bounded knapsack problem.

```cpp
const int maxn = 100000+10; // 1e5 + 10
const int oo=100000000; // 1e8
int que[maxn];
int qid[maxn];
int opt[maxn];
int tmp[maxn];
bool lucky[maxn];

template<int um> class UF {
	public:
	vector<int> par,rank,cnt;
	UF() {par=rank=vector<int>(um,0); cnt=vector<int>(um,1); for(int i=0;i<um;i++) par[i]=i;}
	void reinit() { for(int i=0;i<um; i++) rank[i]=0,cnt[i]=1,par[i]=i;}
	int operator[](int x) {return (par[x]==x)?(x):(par[x] = operator[](par[x]));}
	int count(int x) { return cnt[operator[](x)];}
	int operator()(int x,int y) {
		if((x=operator[](x))==(y=operator[](y))) return x;
		cnt[y]=cnt[x]=cnt[x]+cnt[y];
		if(rank[x]>rank[y]) return par[x]=y;
		rank[x]+=rank[x]==rank[y]; return par[y]=x;
	}
};

int main(){
    int n,m;
    scanf("%d%d",&n, &m);
    UF<maxn> uf;
    for(int i=0;i<m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        x--;y--;
        uf(x,y);
    }
    
    lucky[0] = 1;
    for(int k=1;k<maxn;k++){
        lucky[k] = (k%10==4 || k%10==7) ? lucky[k/10] : 0;
    }
    
    map<int,int> M;
    for(int i=0;i<n;i++)
        if(uf.par[i] == i) M[uf.cnt[i]]++;

    vector<int> A,C;
    for(pair<int,int> x:M){
        A.push_back(x.first); // component size
        C.push_back(x.second); // number of such components
    }

    for(int i=1;i<=77777;i++) opt[i] = oo;

    for(int i=0;i<A.size();i++){
        for(int j=0;j<=77777;j++) tmp[j] = oo;

        // groups based on remainder mod A[i]
        for(int j=0;j<A[i];j++){
            int l=1,r=0;
            // elements in a group differ by A[i]
            for(int k=j,id=0; k<=77777; k+=A[i],id++){
                while(l<=r && id-qid[l]>C[i]) l++; // if window size >= C[i]
                if(l<=r) tmp[k] = que[l] + id;
                while(l<=r && opt[k]-id<=que[r]) r--;
                que[++r] = opt[k]-id; qid[r]=id;
            }
        }

        for(int j=0;j<=77777;j++)
            opt[j] = min(opt[j], tmp[j]);
    }


    int res=n+1;
    for(int i=1;i<=77777;i++){
        if(lucky[i]){
            res = min(res, opt[i]);
        }
    }
    if(res==n+1) printf("-1\n");
    else printf("%d\n", res-1);
    return 0;
}
```
