https://discuss.codechef.com/t/a-dance-with-mobius-function/11315 and https://codeforces.com/contest/1559/problem/E

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

source: https://codeforces.com/contest/1559/submission/125955092

Also checkout https://codeforces.com/blog/entry/8989?#comment-214114
