## String Hashing in Competitive Programming

**What is hashing?**

A hash function is any function that can be used to map digital data of arbitrary size to digital data of fixed size, with slight differences in input data producing very big differences in output data. [Wiki](https://en.wikipedia.org/wiki/Hash_function)

So basically for a string  `S = s1,s2,...s𝑛`  we want to assign to it a unique number which can be calculated from information stored in `S`. We can store, say, the sum of characters in `S`. But two different strings may evaluate to the same hash. So, we have to define intelligent hashes, so that minimal collisions(a collision occurs if two different strings evaluate to same hash) occurs.

So, usually we define our  `ℎ𝑎𝑠ℎ(𝑆) = (∑ 𝑆𝑖 𝑝^𝑖) % 𝑀𝑂𝐷` , because it's intuitive that a hash should depend on length and also on the order of the characters in the string. Here note that we can easily calculate this  `ℎ𝑎𝑠ℎ(𝑆)` for a string of length `𝑁` in  `𝑂(𝑁)`.

Intelligent choices of `p` and `𝑀𝑂𝐷` help us avoid collisions. We will try to use `p, 𝑀𝑂𝐷` as primes and `p` greater than number of distinct elements in our language. Some values we generally use `p = 26, MOD = 10^9 + 7`

Another good method is to store hash modulo two primes `𝑀𝑂𝐷1` and `𝑀𝑂𝐷2` which surely results in lesser collisions. Also, we should choose `𝑀𝑂𝐷` such that  `𝑀𝑂𝐷*𝑀𝑂𝐷`  doesn't result into overflow in C/C++.

```cpp
long long compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}
```

Precomputing the powers of p might give a performance boost.

## Problems

#### 1 Palindromic substring

You have a string `𝑆` of length `N`. You are given `𝑄` queries of form `𝐿𝑖, 𝑅𝑖`. For each query, print `"YES"`, if substring denoted by `𝑆𝐿𝑖, 𝑆𝐿𝑖+1...𝑆𝑅𝑖` is a palindrome. Both `𝑁, 𝑄 ≤ 10^5`.

Because of the given constraints, Obviously we need something better than bruteforce. Hashing is useful here. How?
Note that you can calculate hash of any substring in logarithmic time. How? Let's try to calculate  `𝐻𝑎𝑠ℎ(𝑆[𝐿,𝑅])`. Let F(R) be the hash for prefix `S[0:R]` then

![image](https://user-images.githubusercontent.com/19663316/118243777-6e298c00-b4bc-11eb-8dc5-a50823acbde3.png)

![image](https://user-images.githubusercontent.com/19663316/118251016-b0ef6200-b4c4-11eb-8398-cc5793822e1a.png)

![image](https://user-images.githubusercontent.com/19663316/118243655-4cc8a000-b4bc-11eb-831d-06696553388a.png)

Hence Using the prefix hash array `pre[i] = Hash(S[0,i])`, we can compute `Hash(L,R)` in logarithmic time. Note that we'll need to find inverse modulo here(one reason to use prime `𝑀𝑂𝐷`).

We can precompute the inverse of every `p^i`, which allows computing the hash of any substring of `S` in `O(1)` time.

Now we got `𝐻𝑎𝑠ℎ(L,R)`, now we'll need to compute reverse hash of `S[L,R]`, If both will be equal, `S[L,R]` is a palindrome with high probability. Notice how we can similarly calculate reverse hash if we store the suffix hash of `S`.

#### 2 Number of Palindromic substrings
You have a string `𝑆` of length `𝑁`. Given an `𝑀 ≤ 𝑁`, find the number of substrings of `S` that are palindrome and are of size `𝑀`. Given that `𝑁 ≤ 10^5`.

Again, similar kind of problem. We will use sliding window here. Note that worst case `𝑂(𝑁)` substrings can have a size of `𝑀`. So, we use sliding window here. We pick the first substring of size `𝑀`(ie. substring starting at 0) and in each step keep adding one character to the string in end and removing one character from front until we reach the end of `𝑆`.

So, we have `hash(S[L,R])` and we need `hash(S[L+1,R+1])`. Is it difficult? No. We can do this in logarithmic time easily by adding `𝑆_{𝑅+1} x 𝑝^{𝑅+1}` and subtracting `SL x 𝑝^{L}` from `hash(S[L,R])` and dividing by `𝑝`. Don't forget the modular arithmetic involved here!

#### 3 Largest substring which occurs atleast twice
Given a string `𝑆`, find the size of substring of largest size which occurs atleast twice in the string.

Interesting thing to note is that if a substring `𝑝` occurs atleast twice in `𝑆`, all its substrings(which are of lesser length) will always occur atleast twice in `𝑆`. So, we can apply binary search on the answer.

For each size, say `𝑀`  that we consider, we again find all substrings of size `M` using sliding window and check if any substring occurs twice. Complexity will be  `𝑂(𝑁 (𝑙𝑜𝑔𝑁)^2)`.

There are various problems which can always be solved by high order data structures like suffix arrays and trees, but hashing simplifies the solutions a great deal. Usually it's difficult to generate anti-hash tests and solutions pass.

Check out this informational post: [Anti-hash test](https://codeforces.com/blog/entry/4898) - Codeforces Read in comments also. You can try this problem using string hashing: [Problem - H - Codeforces](https://codeforces.com/contest/245/problem/H)

source: https://threadsiiithyderabad.quora.com/String-Hashing-for-competitive-programming

#### 4 Search for duplicate strings in an array of strings

**Problem:** Given a list of `n` strings `si`, each no longer than `m` characters, find all the duplicate strings and divide them into groups.

From the obvious algorithm involving sorting the strings, we would get a time complexity of `O(nmlogn)` where the sorting requires `O(nlogn)` comparisons and each comparison take `O(m)` time. However, by using hashes, we reduce the comparison time to O(1), giving us an algorithm that runs in `O(nm + nlogn)` time.

We calculate the hash for each string, sort the hashes together with the indices, and then group the indices by identical hashes.

```cpp
vector<vector<int>> group_identical_strings(vector<string> const& s) {
    int n = s.size();
    vector<pair<long long, int>> hashes(n);
    for (int i = 0; i < n; i++)
        hashes[i] = {compute_hash(s[i]), i};

    sort(hashes.begin(), hashes.end());

    vector<vector<int>> groups;
    for (int i = 0; i < n; i++) {
        if (i == 0 || hashes[i].first != hashes[i-1].first)
            groups.emplace_back(); // Inserts a new vector at the end
        groups.back().push_back(hashes[i].second);
    }
    return groups;
}
```

#### 5 Determine the number of different substrings in a string

**Problem:** Given a string `s` of length `n`, consisting only of lowercase English letters, find the number of different substrings in this string.

To solve this problem, we iterate over all substring lengths `l = 1...n`. For every substring length l we construct an array of hashes of all substrings of length l multiplied by the same power of p. The number of different elements in the array is equal to the number of distinct substrings of length l in the string. This number is added to the final answer.

For convenience, we will use h[i] as the hash of the prefix with i characters, and define h[0]=0.

```cpp
int count_unique_substrings(string const& s) {
    int n = s.size();

    const int p = 31;
    const int m = 1e9 + 9;
    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++)
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

    int cnt = 0;
    for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
            long long cur_h = (h[i + l] + m - h[i]) % m;
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}
```

## Hashing and Probability of Collision

source: https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html

[Problem D](http://codeforces.com/contest/763/problem/D) of Codeforces #395 required hashes of rooted trees. In this post I give some examples of good hashes and bad hashes, and then construct a good hash for rooted trees.

The most well-known hash in competitive programming is probably the rolling-hash of strings. The following problem looks stupid, but let's solve it using rolling hash anyway.

**Problem 1.** You are given two strings s, t of lengths N (<= 10^5) that consist of lowercase letters. Determine if they are the same.

Let `MOD = 10^9+7`. Choose an integer `r` uniformly at random from the interval `[0, MOD)`. Compute the sum of `r^i * s[i]` over all `i`. This is called the rolling hash of `s`. We can consider it as a polynomial of `r`, let's denote it as `S(r)`. Similarly, define `T(r)`. The hash collision happens when `s` and `t` are different strings (thus S and T are different polynomials), but unluckily S(r) = T(r). Here we use [Schwartz-Zippel lemma](https://en.wikipedia.org/wiki/Schwartz%E2%80%93Zippel_lemma): 

Let `P(x_1, ..., x_k)` be a non-zero (multi-variable) polynomial on a finite field `F_MOD`. If the variables are chosen independently and uniformly at random, the probability that `P(x_1, ..., x_k) = 0` is at most `D/MOD`, where `D` is the total degree of the polynomial.

In the case of rolling hash, we are only interested in single-variable polynomials. From the lemma above, we can prove that the collision probability is at most `N/MOD (<= 1/10^4)`. Thus I'd say this is a "good hash". My intuition tells that in practice the probability is as small as `1/MOD`, but that looks at least very hard to prove. Let me give an interesting example that shows the intuition is not always correct. In the lemma F_MOD must be a field, and MOD must be a prime. What happens if the modulo is not prime, for example 2^64 (this would simplify the implementation). It turns out that the rolling hash doesn't work well for a certain case if the modulo is 2^64. [Detailed description on Codeforces](https://codeforces.com/blog/entry/4898).

**Problem 2.** You are given two graphs G, H with N (<= 10^3) vertices and M (<= 10^4) edges. Determine if they are isomorphic.

For each vertex v in the graph and an integer d, define the level-d hash for v, h(d, v). When d = 0, define h(0, v) = 1. Otherwise, let x_1, ..., x_k be the sorted list of level-(d-1) hashes of vertices adjacent to v, and define h(d, v) as the sum of x_i * r^i modulo MOD. Compute the level-N hashes of the two graphs for each vertex, sort them, and compare them.

Petr: For graph isomorphism, it's easy to break such hashing: take two non-isomorphic regular (all degrees the same) graphs.
![image](https://user-images.githubusercontent.com/19663316/118253744-e47fbb80-b4c7-11eb-9c40-b66b01283fe8.png)


However there's no theoretical guarantee under this hash and I think most people agree that this doesn't look valid as an intended solution of a problem in a contest (graph isomorphism is a well-known difficult problem). I'd say this is a "bad hash".

OK, now we want to construct a good hash for rooted trees. Before that, let's try an easier version. Hashes for (multi)sets.

**Problem 3.** You are given two (multi)sets A = {a_1, ...., a_n} and B = {b_1, ..., b_n}. n <= 10^5 and each element is in the interval `[0, MOD)`. Determine if they are the same.

One possible solution is to sort the input and then compute the rolling hash of it. Can you find a linear-time hash? The solution is indeed very simple. Let's take a random integer r from the interval `[0, MOD)`, and compute the hash (r+a_1)(r+a_2)...(r+a_n). This is a polynomial of r of degree n, so again from Schwartz-Zippel lemma, the collision probability is at most n/MOD.

**Problem 4.** You are given two rooted trees with n vertices. Determine if they are isomorphic.

Like previous examples, we assign a polynomial for a rooted tree, and evaluate the polynomial for random variables. However, unlike previous examples, this time we use multi-variable polynomials. We define the polynomial P(G) for a rooted tree G as follows. If G is a single leaf, P(G) = 1. Otherwise, let d be the depth of the tree, k be the number of children of the root of G, and G_1, G_2, ..., G_d be the subtrees corresponding to those children. Define P(G) = (x_d + P(G_1))(x_d + P(G_2))...(x_d + P(G_k)). See the picture for an example. (x_1, x_2, x_3 are replaced with x, y, z).

![image](https://user-images.githubusercontent.com/19663316/118252879-e1380000-b4c6-11eb-94ae-981eefa369bd.png)

This way we get a multi-variable polynomial over d variables of degree l, where l is the number of leaves in the tree. We can prove that two polynomials that correspond to non-isomorphic trees are different (by using the uniqueness of factorization of the ring of polynomials). Thus, if we evaluate this polynomial for random variables, we get a good hash with collision probability at most l/MOD!

TODO: https://codeforces.com/blog/entry/60442

## Improve no-collision probability

Quite often the above mentioned polynomial hash is good enough, and no collisions will happen during tests. Remember, the probability that collision happens is only `≈ 1/m`. For `m = 10^9+9` the probability is `≈ 10^−9` which is quite low. But notice, that we only did one comparison. What if we compared a string s with `10^6` different strings. The probability that at least one collision happens is now `≈ 10^−3`. And if we want to compare `10^6` different strings with each other (e.g. by counting how many unique strings exists), then the probability of at least one collision happening is already `≈ 1`. It is pretty much guaranteed that this task will end with a collision and returns the wrong result.

There is a really easy trick to get better probabilities. We can just compute two different hashes for each string (by using two different `p`, and/or different `m`, and compare these pairs instead. If m is about `10^9` for each of the two hash functions than this is more or less equivalent as having one hash function with `m ≈ 10^18`. When comparing `10^6` strings with each other, the probability that at least one collision happens is now reduced to `≈ 10^−6`.

## Polynomial hashes

source: https://codeforces.com/blog/entry/17507

Short version

```cpp

typedef unsigned long long ull;

const int N = 1e5;
const int P = 239017;

char s[N + 1];
ull h[N + 1], deg[N + 1];

void init() {
  int n = strlen(s);
  deg[0] = 1, h[0] = 0;
  forn(i, n) {
    h[i + 1] = h[i] * P + s[i];
    deg[i + 1] = deg[i] * P;
  }
}

ull getHash( int i, int len ) {
  return h[i + len] - h[i] * deg[len];
}
```

Long version

```cpp
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

typedef long long ll;
typedef unsigned long long ull;

struct num {
  static const int MA = 1e9 + 7, MB = 1e9 + 9;

  int a, b;

  num() { }
  num( int x ) : a(x), b(x) { }
  num( int a, int b ) : a(a), b(b) { }

  num operator + ( const num &x ) const { return num((a + x.a) % MA, (b + x.b) % MB); }
  num operator - ( const num &x ) const { return num((a + MA - x.a) % MA, (b + MB - x.b) % MB); }
  num operator * ( int x ) const { return num(((ll)a * x) % MA, ((ll)b * x) % MB); }
  num operator * ( const num &x ) const { return num(((ll)a * x.a) % MA, ((ll)b * x.b) % MB); }
  bool operator == ( const num &x ) const { return a == x.a && b == x.b; }

  explicit operator ll () const { return (ll)a * MB + b + 1; } // > 0
};

template <class hash_t>
struct StrComparator {
  static const int P;
  static vector<hash_t> deg;

  int n;
  const char *s;
  hash_t *h;

  StrComparator( int n, const char *s ) : n(n), s(s) {
    h = new hash_t[n + 1];
    h[0] = 0;
    forn(i, n)
      h[i + 1] = h[i] * P + s[i];
    deg.reserve(n);
    while (sz(deg) <= n)
      deg.push_back(*deg.rbegin() * P);      
  }

  hash_t substr( int i, int len ) const { return h[i + len] - h[i] * deg[len]; }

  int lcp( int i, int j ) {
    int L = 0, R = n - max(i, j);
    while (L < R) {
      int M = (L + R + 1) / 2;
      if (substr(i, M) == substr(j, M))
        L = M;
      else
        R = M - 1;
    }
    return L;
  }

  int cmp( int a, int b ) {
    int LEN = n - max(a, b), L = lcp(a, b);
    return L < LEN ? (int)s[a + L] - s[b + L] : b - a;
  }

  bool operator() ( int i, int j ) { return cmp(i, j) < 0; }
};
template <class hash_t> vector <hash_t> StrComparator<hash_t>::deg(1, hash_t(1));
template <class hash_t> const int StrComparator<hash_t>::P = max(239, rand());

//   StrComparator<num> h(n, s);

/**
 * Usage:
 *   StrComparator<num> h(length, s); // int length, char *s
 *   h.substr(0, 3) == h.substr(1, 3); // comparison for equality of substrings O(1)
 *   h.cmp(2, 3); // comparision for suffixes O(logn)
 *
 *   int p[n]; forn(i, n) p[i] = i;
 *   sort(p, p + n, h); // sort suffixes, for suf.array O(nlog^2n)
 */
```

source: http://acm.math.spbu.ru/~sk1/algo/hash/hash.cpp.html and http://acm.math.spbu.ru/~sk1/algo/hash/HashStrComparator_simple.cpp.html

**Common part:**
```cpp
const int P = 239017; // If you take a simple modulo, use rand() here!
// s - string, n - its length
```

**First way:**
```cpp
// deg[] = {1, P, P^2, P^3, ...}
// h[] = {0, s[0], s[0]*P + s[1], s[0]*P^2 + s[1]*P + s[2], ...}
unsigned long long h[n + 1], deg[n + 1];
h[0] = 0, deg[0] = 1;
for (int i = 0; i < n; i++) {
  h[i + 1] = h[i] * P + s[i];
  deg[i + 1] = deg[i] * P;
}
auto get_hash = [&]( int l, int r ) { // [l..r]
  return h[r + 1] - h[l] * deg[r - l + 1];
};
```

**Second way:**
```cpp
// deg[] = {1, P, P^2, P^3, ...}
// h[] = {s[0], s[0] + s[1]*P, s[0] + s[1]*P + s[2]*P^2, ...}
unsigned long long h[n], deg[n];
h[0] = s[0], deg[0] = 1;
for (int i = 1; i < n; i++) {
  deg[i] = deg[i - 1] * P;
  h[i] = h[i - 1] + s[i] * deg[i];
}
auto get_hash = [&]( int l, int r ) { // [l..r]
  if (l == 0)
    return h[r];
  return h[r] - h[l - 1];
};
```

There are two differences

![image](https://user-images.githubusercontent.com/19663316/118372843-26485900-b5d1-11eb-8579-1a42a24caebd.png)

In the first method, to compare two strings `[l1..r1]` and `[l2..r2]`, just write `get_hash(l1, r1)` == `get_hash(l2, r2)`. That is, the get_hash function honestly returns a hash. You can, for example, find the number of different substrings by putting all the hashes into a hash table.

In the second case, the get_hash function actually returns not a hash, but a hash multiplied by some power of `P`, so you have to write it like this `deg[r2] * get_hash(l1, r1) == deg[r1] * get_hash(l2, r2)`(on e-maxx, the truth is a little worse). And using hashes will not work otherwise. You can modify the function `get_hash`, use an honest hash `true_hash(l, r) = deg[n - r - 1] * get_hash(l, r)`, but this method has a drawback - we assume that we know the maximum string length. This is not always convenient, and sometimes it is not true with online solutions.

The second method also has a modulo variation. It is definitely not necessary to write that way.

**Where to start the h array ? With 0 or with s[0] ?**

If we start at `0`, we end up with shorter, faster code (yes, yes, it takes time for the if to execute!). When evaluating the speed, notice that there will be the same number of multiplications.

If we start at `s[0]`, then we get an array of length `n` , that is, we save `O(1)` memory.

Which is best, decide for yourself. I advertise the first option to everyone. If there are constructive comments or alternative versions, I will be glad to hear.

**Choosing a simple module**

A special hello to everyone who says "the number P can be chosen by anyone." P must be larger than the size of the alphabet. If so, then the hash computed without taking modulo, as a long number, is injective. Otherwise, already at the stage of computation without a module, there may be collisions. Examples of how not to do: alphabet "a..z", P = 13 , ASCII alphabet 33..127, P = 31 .

## CF Problems

### Div 1C. Double Profiles

https://codeforces.com/contest/154/problem/C

The social network contains `n` registered profiles, numbered from `1` to `n`. Some pairs there are friends (the "friendship" relationship is mutual, that is, if `i` is friends with `j`, then `j` is also friends with `i`). Let's say that profiles `i` and `j` `(i ≠ j)` are doubles, if for any profile `k (k ≠ i, k ≠ j)` one of the two statements is true: either `k` is friends with `i` and `j`, or `k` isn't friends with either of them. Also, `i` and `j` can be friends or not be friends.

Your task is to count the number of different unordered pairs `(i, j)`, such that the profiles `i` and `j` are doubles. Note that the pairs are unordered, that is, pairs `(a, b)` and `(b, a)` are considered identical.

**Input**
The first line contains two space-separated integers `n` and `m (1 ≤ n ≤ 10^6, 0 ≤ m ≤ 10^6)`, — the number of profiles and the number of pairs of friends, correspondingly.

Next `m` lines contains descriptions of pairs of friends in the format `"v u"`, where `v` and `u` `(1 ≤ v, u ≤ n, v ≠ u)` are numbers of profiles that are friends with each other. It is guaranteed that each unordered pair of friends occurs no more than once and no profile is friends with itself.

**Output**
Print the single integer — the number of unordered pairs of profiles that are doubles.

**Solution**

It is necessary in the graph to count the number of pairs of verties that have the same set of neighbours up to these vertices themselves(These vertices can be friends too). You can calculate the number of pairs of vertices whose sets coincide exactly by hashing these sets and sorting the hashes (yes, hashes are the author's solution). How to adapt this method for the case when there is an edge between the vertices?

Note that the pairs who are friends to each other are no more than number of edges, so if we know how to compute hash changes when adding/removing one vertex to the set(for example, using the polynomial hash of the row of the graph Adjacency matrix), we can iterate over all the edges and check each pair directly.

Alternatively, we can calculate the second variant of the hash for each vertex by including that vertex, assuming there is a loop at each vertex. Then the pair of sets will coincide just when the vertices are doubles and there is an edge between them. After that, we count the number of pairs in the same way as in the first case.

It was not possible to sort hashes, but sort adjacency lists for each vertex. Due to the fact that their total size is 2M. this could also pass, but it required careful implementation, since the restrictions were great. The complexity of the solution with hashes is `O(M + N log N)`.

**Sorting Adjacency list in `O(N+M)` time.**

It is well-known fact that any algorithm which correctly sorts a set of `k` numbers using comparisons will require atleast `klogk` comparisons (in the worst and in the average cases). So this suggests that if we want to sort the Adjacency list `Adj[vi]` of length `degree(vi) = di` for vertex `vi` it takes `O(di log di)` time. So the sorting of all lists will take `Σ O(di log di)` which is superlinear, i.e. greater than `O(n+m)`.

Here size of |V| is fixed, instead of comparision based sorting, even if we use bucket sort algorithm, Sorting `Adj[vi]` takes `O(N)`, so in total we would require `O(N^2)` steps.

The idea is to create the list SortedAdj(vi) simultaneously, Bucket sorting takes `O(n+di)` time. Starting from `i = 0,1,...` For every vertex `vj` in `Adj(vi)`,  we append `vi` to `SortedAdj(vj)`. This runs in `O(N+M)` time.

![image](https://user-images.githubusercontent.com/19663316/118373918-e4221600-b5d6-11eb-8734-4abd478eedfe.png)


## Random number generator

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
int getRand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
``` 
