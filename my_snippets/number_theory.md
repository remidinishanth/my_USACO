```cpp
bool prime(int n) {
    if (n < 2) return false;
    if (n <= 3) return true;
    if (!(n % 2) || !(n % 3)) return false;
    for (int i = 5; i * i <= n; i += 6)
        if (!(n % i) || !(n % (i + 2))) return false;
    return true;
}
```
https://atcoder.jp/contests/abc206/tasks/abc206_e

Inclusion exclusion priniciple https://dyingdown.github.io/2019/08/15/Inclusion-Exclusion-Principle/ and http://www.ryanhmckenna.com/2016/04/counting-coprime-pairs-using-inclusion.html and http://laurentmazare.github.io/2014/09/14/counting-coprime-pairs

The principle of inclusion exclusion is a very powerful idea that can be used to solve alot of problems that arise in combinatorics and number theory.

![](images/inclusion_exclusion_0.png)

![](images/inclusion_exclusion_1.png)

Let's say we want to count the number of positive integers `k` that are less than or equal to `r` and relatively prime to `n`. Task: Given two numbers `n` and `r`, count the number of integers in the interval `[1;r]` that are relatively prime to n (their greatest common divisor is 1).

Using set theoretic notation, week seek to find the cardinality of the set  `{p ∣ p ∈ {1,2,…,r}, gcd(n, p) = 1}`  where  gcd  is the greatest common divisor function. 

We will count `f(n, r)` the complement of task(the number of integers which are not relatively prime to `n`) and then exclude them from `r`. For this we will use inclusion exclusion priniciple, let's denote the prime factors of `n` as `pᵢ (1 ≤ i ≤ k)`, If we create sets for numbers divisible by each `pᵢ` then

![](images/inclusion_exclusion_2.png)

```cpp
int solve (int n, int r) {
    vector<int> p; // prime divisors of n
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            p.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p.push_back (n);

    int sum = 0;
    for (int msk=1; msk<(1<<p.size()); ++msk) {
        int mult = 1, bits = 0;
        for (int i=0; i<(int)p.size(); ++i)
            if (msk & (1<<i)) {
                ++bits;
                mult *= p[i];
            }

        int cur = r / mult; // number of divisors in [1:r]
        if (bits % 2 == 1)
            sum += cur; // inclusion
        else
            sum -= cur; // exclusion
    }

    return r - sum;
}
```

Let's define `g(primeFactors(n), m) =  m - f(n, m)` then 

![](images/inclusion_exclusion_4.png)

This expansion is exactly equivalent to the formula from the inclusion exclusion method, although it's much easier to implement. This recursive function works because once the set of prime factors have been exhausted, every combination of primes have been produced, and the associated term in the inclusion exclusion formula has the correct sign for the contribution.

In number theory, Euler's totient function counts the positive integers up to a given integer n that are relatively prime to n. 

https://codeforces.com/blog/entry/54090 and https://codeforces.com/blog/entry/53925

TODO: https://open.kattis.com/problems/coprimeintegers
