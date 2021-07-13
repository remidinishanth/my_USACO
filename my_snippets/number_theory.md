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

In number theory, Euler's totient function counts the positive integers up to a given integer n that are relatively prime to n.

https://codeforces.com/blog/entry/54090 and https://codeforces.com/blog/entry/53925

TODO: https://open.kattis.com/problems/coprimeintegers
