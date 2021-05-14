## String Hashing in Competitive Programming

**What is hashing?**

A hash function is any function that can be used to map digital data of arbitrary size to digital data of fixed size, with slight differences in input data producing very big differences in output data. [Wiki](https://en.wikipedia.org/wiki/Hash_function)

So basically for a string  `S = s1,s2,...s𝑛`  we want to assign to it a unique number which can be calculated from information stored in `S`. We can store, say, the sum of characters in `S`. But two different strings may evaluate to the same hash. So, we have to define intelligent hashes, so that minimal collisions(a collision occurs if two different strings evaluate to same hash) occurs.

So, usually we define our  `ℎ𝑎𝑠ℎ(𝑆) = (∑ 𝑆𝑖 𝑝^𝑖) % 𝑀𝑂𝐷` , because it's intuitive that a hash should depend on length and also on the order of the characters in the string. Here note that we can easily calculate this  `ℎ𝑎𝑠ℎ(𝑆)` for a string of length `𝑁` in  `𝑂(𝑁)`.

Intelligent choices of `p` and `𝑀𝑂𝐷` help us avoid collisions. We will try to use `p, 𝑀𝑂𝐷` as primes and `p` greater than number of distinct elements in our language. Some values we generally use `p = 26, MOD = 10^9 + 7`

Another good method is to store hash modulo two primes `𝑀𝑂𝐷1` and `𝑀𝑂𝐷2` which surely results in lesser collisions. Also, we should choose `𝑀𝑂𝐷` such that  `𝑀𝑂𝐷*𝑀𝑂𝐷`  doesn't result into overflow in C/C++.

## Problems

### 1

You have a string `𝑆` of length `N`. You are given `𝑄` queries of form `𝐿𝑖, 𝑅𝑖`. For each query, print `"YES"`, if substring denoted by `𝑆𝐿𝑖, 𝑆𝐿𝑖+1...𝑆𝑅𝑖` is a palindrome. Both `𝑁, 𝑄 ≤ 10^5`.

Because of the given constraints, Obviously we need something better than bruteforce. Hashing is useful here. How?
Note that you can calculate hash of any substring in logarithmic time. How? Let's try to calculate  `𝐻𝑎𝑠ℎ(𝑆[𝐿,𝑅])`. Let F(R) be the hash for prefix `S[0:R]` then

![image](https://user-images.githubusercontent.com/19663316/118243777-6e298c00-b4bc-11eb-8dc5-a50823acbde3.png)

![image](https://user-images.githubusercontent.com/19663316/118243655-4cc8a000-b4bc-11eb-831d-06696553388a.png)

Hence Using the prefix hash array `pre[i] = Hash(S[0,i])`, we can compute `Hash(L,R)` in logarithmic time. Note that we'll need to find inverse modulo here(one reason to use prime `𝑀𝑂𝐷`).

Now we got `𝐻𝑎𝑠ℎ(L,R)`, now we'll need to compute reverse hash of `S[L,R]`, If both will be equal, `S[L,R]` is a palindrome. Notice how we can similarly calculate reverse hash if we store the suffix hash of `S`.

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
