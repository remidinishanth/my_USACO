## Number Theory Basics

![](images/mobius_1.png)
![](images/mobius_2.png)
![](images/mobius_3.png)
![](images/mobius_4.png)
![](images/mobius_5.png)
![](images/mobius_6.png)

source: Factors. Brilliant.org. Retrieved 00:56, August 18, 2021, from https://brilliant.org/wiki/factors/

## Mobius Function

An arithmetical function, or number-theoretic function is a complex-valued function defined for all positive integers. It can be viewed as a sequence of complex numbers.

In number theory, a multiplicative function is an arithmetic function `f(n)` of a positive integer `n` with the property that `f(1) = 1` and `f(ab) = f(a)f(b)` whenever `a` and `b` are coprime; `gcd(a, b) = 1`. `f(n) = f(n * 1) = f(n) f(1)` hence we need the condition that `f(1) = 1`.

![](images/mobius_7.png)

source: https://crypto.stanford.edu/pbc/notes/numbertheory/mult.html

https://codeforces.com/blog/entry/53925
https://discuss.codechef.com/t/a-dance-with-mobius-function/11315 and https://codeforces.com/contest/1559/problem/E based on https://codeforces.com/blog/entry/93788?#comment-829004



```cpp
vector<int> smallest_factor;
vector<int8_t> smallest_power;
vector<int8_t> mobius;
vector<bool> prime;
vector<int> primes;
 
// Note: this sieve is O(n).
void sieve(int maximum) {
    maximum = max(maximum, 1);
    smallest_factor.assign(maximum + 1, 0);
    smallest_power.assign(maximum + 1, 0);
    mobius.assign(maximum + 1, 0);
    prime.assign(maximum + 1, true);
    mobius[1] = 1;
    prime[0] = prime[1] = false;
    primes = {};
 
    for (int i = 2; i <= maximum; i++) {
        if (prime[i]) {
            smallest_factor[i] = i;
            smallest_power[i] = 1;
            mobius[i] = -1;
            primes.push_back(i);
        }
 
        for (int p : primes) {
            if (p > smallest_factor[i] || i * p > maximum)
                break;
 
            prime[i * p] = false;
            smallest_factor[i * p] = p;
            smallest_power[i * p] = smallest_factor[i] == p ? int8_t(smallest_power[i] + 1) : 1;
            mobius[i * p] = smallest_factor[i] == p ? 0 : int8_t(-mobius[i]);
        }
    }
}
```

source: neal https://codeforces.com/contest/1559/submission/125955092

```cpp
const int X = 2.1e5;

bitset<X> is_prime;
vector<int> pr;
vector<int> mu(X, 0);

void init() {
    is_prime.flip();
    is_prime[0] = is_prime[1] = false;
    mu[1] = 1;
    for (int i = 2; i < X; i++) {
        if (is_prime[i]) {
            pr.push_back(i);
            mu[i] = -1;
        }
        for (int p: pr) {
            if (i * p >= X) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
            } else {
                mu[i * p] = -mu[i];
            }
            if (i % p == 0) break;
        }
    }
}
```

source: ksun48 https://codeforces.com/contest/1559/submission/125949764

Also checkout https://codeforces.com/blog/entry/8989?#comment-214114
