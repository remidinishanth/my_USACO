## String Hashing in Competitive Programming

**What is hashing?**

A hash function is any function that can be used to map digital data of arbitrary size to digital data of fixed size, with slight differences in input data producing very big differences in output data. [Wiki](https://en.wikipedia.org/wiki/Hash_function)

So basically for a string  `S = s1,s2,...s𝑛`  we want to assign to it a unique number which can be calculated from information stored in `S`. We can store, say, the sum of characters in `S`. But two different strings may evaluate to the same hash. So, we have to define intelligent hashes, so that minimal collisions(a collision occurs if two different strings evaluate to same hash) occurs.

So, usually we define our  `ℎ𝑎𝑠ℎ(𝑆) = (∑ 𝑆𝑖 𝑝^𝑖) % 𝑀𝑂𝐷` , because it's intuitive that a hash should depend on length and also on the order of the characters in the string. Here note that we can easily calculate this  `ℎ𝑎𝑠ℎ(𝑆)` for a string of length `𝑁` in  `𝑂(𝑁)`.

Intelligent choices of `p` and `𝑀𝑂𝐷` help us avoid collisions. We will try to use `p, 𝑀𝑂𝐷` as primes and `p` greater than number of distinct elements in our language.

Another good method is to store hash modulo two primes `𝑀𝑂𝐷1` and `𝑀𝑂𝐷2` which surely results in lesser collisions. Also, we should choose `𝑀𝑂𝐷` such that  `𝑀𝑂𝐷*𝑀𝑂𝐷`  doesn't result into overflow in C/C++.

## Problems

### 1

You have a string `𝑆` of length `N`. You are given `𝑄` queries of form `𝐿𝑖, 𝑅𝑖`. For each query, print `"YES"`, if substring denoted by `𝑆𝐿𝑖,𝑆𝐿𝑖+1...𝑆𝑅𝑖` is a palindrome. Both `𝑁, 𝑄 ≤ 10^5`.

Because of the given constraints, Obviously we need something better than bruteforce. Hashing is useful here. How?
Note that you can calculate hash of any substring in logarithmic time. How? Let's try to calculate  `𝐻𝑎𝑠ℎ(𝑆[𝐿,𝑅])`. Let F(R) be the hash for prefix `S[0:R]` then

![image](https://user-images.githubusercontent.com/19663316/118243777-6e298c00-b4bc-11eb-8dc5-a50823acbde3.png)

![image](https://user-images.githubusercontent.com/19663316/118243655-4cc8a000-b4bc-11eb-831d-06696553388a.png)

Hence Using the prefix hash array `pre[i] = Hash(S[0,i])`, we can compute `Hash(L,R)` in logarithmic time. Note that we'll need to find inverse modulo here(one reason to use prime `𝑀𝑂𝐷`).

Now we got `𝐻𝑎𝑠ℎ(L,R)`, now we'll need to compute reverse hash of `S[L,R]`, If both will be equal, `S[L,R]` is a palindrome. Notice how we can similarly calculate reverse hash if we store the suffix hash of `S`.
