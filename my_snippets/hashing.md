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

### 1

You have a string `𝑆` of length `N`. You are given `𝑄` queries of form `𝐿𝑖, 𝑅𝑖`. For each query, print `"YES"`, if substring denoted by `𝑆𝐿𝑖, 𝑆𝐿𝑖+1...𝑆𝑅𝑖` is a palindrome. Both `𝑁, 𝑄 ≤ 10^5`.

Because of the given constraints, Obviously we need something better than bruteforce. Hashing is useful here. How?
Note that you can calculate hash of any substring in logarithmic time. How? Let's try to calculate  `𝐻𝑎𝑠ℎ(𝑆[𝐿,𝑅])`. Let F(R) be the hash for prefix `S[0:R]` then

![image](https://user-images.githubusercontent.com/19663316/118243777-6e298c00-b4bc-11eb-8dc5-a50823acbde3.png)

![image](https://user-images.githubusercontent.com/19663316/118251016-b0ef6200-b4c4-11eb-8398-cc5793822e1a.png)

![image](https://user-images.githubusercontent.com/19663316/118243655-4cc8a000-b4bc-11eb-831d-06696553388a.png)

Hence Using the prefix hash array `pre[i] = Hash(S[0,i])`, we can compute `Hash(L,R)` in logarithmic time. Note that we'll need to find inverse modulo here(one reason to use prime `𝑀𝑂𝐷`).

We can precompute the inverse of every `p^i`, which allows computing the hash of any substring of `S` in `O(1)` time.

Now we got `𝐻𝑎𝑠ℎ(L,R)`, now we'll need to compute reverse hash of `S[L,R]`, If both will be equal, `S[L,R]` is a palindrome with high probability. Notice how we can similarly calculate reverse hash if we store the suffix hash of `S`.

### 2
You have a string `𝑆` of length `𝑁`. Given an `𝑀 ≤ 𝑁`, find the number of substrings of `S` that are palindrome and are of size `𝑀`. Given that `𝑁 ≤ 10^5`.

Again, similar kind of problem. We will use sliding window here. Note that worst case `𝑂(𝑁)` substrings can have a size of `𝑀`. So, we use sliding window here. We pick the first substring of size `𝑀`(ie. substring starting at 0) and in each step keep adding one character to the string in end and removing one character from front until we reach the end of `𝑆`.

So, we have `hash(S[L,R])` and we need `hash(S[L+1,R+1])`. Is it difficult? No. We can do this in logarithmic time easily by adding `𝑆_{𝑅+1} x 𝑝^{𝑅+1}` and subtracting `SL x 𝑝^{L}` from `hash(S[L,R])` and dividing by `𝑝`. Don't forget the modular arithmetic involved here!

### 3
Given a string `𝑆`, find the size of substring of largest size which occurs atleast twice in the string.

Interesting thing to note is that if a substring `𝑝` occurs atleast twice in `𝑆`, all its substrings(which are of lesser length) will always occur atleast twice in `𝑆`. So, we can apply binary search on the answer.

For each size, say `𝑀`  that we consider, we again find all substrings of size `M` using sliding window and check if any substring occurs twice. Complexity will be  `𝑂(𝑁 (𝑙𝑜𝑔𝑁)^2)`.

There are various problems which can always be solved by high order data structures like suffix arrays and trees, but hashing simplifies the solutions a great deal. Usually it's difficult to generate anti-hash tests and solutions pass.

Check out this informational post: [Anti-hash test](https://codeforces.com/blog/entry/4898) - Codeforces Read in comments also. You can try this problem using string hashing: [Problem - H - Codeforces](https://codeforces.com/contest/245/problem/H)

source: https://threadsiiithyderabad.quora.com/String-Hashing-for-competitive-programming

### 4 Search for duplicate strings in an array of strings

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

## Hashing and Probability fo Collision

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
