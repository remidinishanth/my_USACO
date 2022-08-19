## Basics

![image](https://user-images.githubusercontent.com/19663316/117581703-e3433d00-b11b-11eb-8cd8-d355922c6b7b.png)

```
53 = 110101
28 = 11100

  110101
&  11100  // imagine padding a shorter number with leading zeros to get the same length
 -------
  010100  =  20
```

There are also bitwise shifts `<<` and `>>` operators.

```
    LEFT SHIFT                             RIGHT SHIFT
       13 =     1101                          13 =   1101
(13 << 2) =   110100                   (13 >> 2) =     11     
```

If there is no overflow, an expression `x << b` is equal to `𝑥⋅2^𝑏`, like here we had `(13 << 2) = 52`. An expression `x >> b` is equal to the floor of `𝑥/2^𝑏`.

Consider this problem: You are given 𝑁 ≤ 20 numbers, each up to 10^9. Is there a subset with sum equal to given goal S?
```cpp
for(int mask = 0; mask < (1 << n); mask++) {
	long long sum_of_this_subset = 0;
	for(int i = 0; i < n; i++) {
		if(mask & (1 << i)) {
			sum_of_this_subset += a[i];
		}
	}
	if(sum_of_this_subset == S) {
		puts("YES");
		return 0;
	}
}
puts("NO");
```

Use helpers

```cpp
inline int two(int n) { return 1 << n; } // 2^n
inline int test(int n, int b) { return (n>>b)&1; } // test whether b-th bit is on/set in n
inline void set_bit(int & n, int b) { n |= two(b); } // set bth-bit to 1
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); } // return the last on bit
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; } // number of bits turned on
```

`m & (m-1)` turns off the lowest bit that was set to 1 in a positive number 𝑚. For example, we get 24 for 𝑚=26, as 11010 changes into 11000.

Given a bitmask m, you want to efficiently iterate through all of its submasks, that is, masks s in which only bits that were included in mask m are set. https://cp-algorithms.com/algebra/all-submasks.html

```cpp
for (int s=m; s; s=(s-1)&m)
    // ... you can use s ...

// using while loop
int s = m;
while (s > 0) {
   // ... you can use s ...
   s = (s-1) & m;
}    
```

`cout << bitset<8>(x);` prints a number after converting it into a bitset, which can be printed. More about this in next section.

## Built-in functions

In C++, `__builtin_popcount(x)` returns popcount of a number — the number of ones in the binary representation of 𝑥. Use `__builtin_popcountll(x)` for long longs.

There are also `__builtin_clz` and `__builtin_ctz` (and their long long versions) for counting the number of leading or trailing zeros in a positive number. Read more [here](https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/). To compute the biggest power of 2 that is a divisor of x, e.g f(12) = 4, we can simply use `1 << __builtin_ctz(x)`. We can solve it in `O(logx)` with simple while-loops which is more intuitive.

source: https://codeforces.com/blog/entry/73558

## Motivation behind bitsets

Consider this problem: There are 𝑁 ≤ 5000 workers. Each worker is available during some days of this month (which has 30 days). 
For each worker, you are given a set of numbers, each from interval [1,30], representing his/her availability. 
You need to assign an important project to two workers but they will be able to work on the project only when they are both available. 
Find two workers that are best for the job — maximize the number of days when both these workers are available.

You can compute the intersection of two workers (two sets) in O(30) by using e.g. two pointers for two sorted sequences. 
Doing that for every pair of workers is 𝑂(𝑁<sup>2</sup>⋅30), slightly too slow.

We can think about the availability of a worker as a binary string of length 30, which can be stored in a single int. 
With this representation, we can count the intersection size in 𝑂(1) by using `__builtin_popcount(x[i] & x[j])`. The complexity becomes 𝑂(𝑁<sup>2</sup>), fast enough.

What if we are given the availability for the whole year or in general for 𝐷 days? We can handle 𝐷 ≤ 64 in a single unsigned long long, what about bigger 𝐷?

We can split 𝐷 days into convenient parts of size 64 and store the availability of a single worker in an array of 𝐷64 unsigned long longs. 
Then, the intersection can be computed in 𝑂(𝐷/64) and the whole complexity is 𝑂(𝑁<sup>2</sup>⋅𝐷/64).

```cpp
const int K = MAX_D / 64 + 1;
unsigned long long x[MAX_N][K];
int intersection(int i, int j) {
	int total = 0;
	for(int z = 0; z < K; z++) {
		total += __builtin_popcountll(x[i][z] & x[j][z]);
	}
	return total;
}
```

So, we can simulate a long binary number with multiple unsigned long longs. 
The implementation isn't that bad but doing binary shifts would be quite ugly. Turns out all of this can be done with bitsets easily.

## Bitsets

`bitset<365>` is a binary number with 365 bits available, and it supports most of binary operations. The code above changes into simple:

```cpp
bitset<MAX_D> x[MAX_N];
int intersection(int i, int j) {
	return (x[i] & x[j]).count();
}
```

Some functions differ, e.g. `x.count()` instead of `__builtin_popcount(x)` but it's only more convenient. 

You can read and print binary numbers, construct a bitset from int or string `bitset<100> a(17); bitset<100> b("1010");`.

You can even access particular bits with b[i]. Read more in C++ reference <https://en.cppreference.com/w/cpp/utility/bitset.>

```cpp
bitset<10> s;
s[1] = 1;
s[3] = 1;
s[4] = 1;
s[7] = 1;
cout << s[4] << "\n"; // 1
cout << s[5] << "\n"; // 0
```

Another way to declare above bitset is `bitset<10> s(string("0010011010"));`

Shift operators `<<`, `>>` with bitsets, useful while solving problems.

```cpp
bitset<4> b("0001");
cout << (b<<2) << "\n"; // 0100
cout << (b>>1) << "\n"; // 0010
```

Note that the size of the bitset must be a constant number. You can't read n and then declare `bitset<n> john`;. If n is up to 100, just create bitset<100>.

The complexity of bitwise operations is 𝑂(size/32) or 𝑂(size/64), it depends on the architecture of your computer.

The benefit of using bitsets is that they require less memory than ordinary arrays, because each element in a bitset only uses one bit of memory. For
example, if n bits are stored in an int array, 32n bits of memory will be used, but a corresponding bitset only requires n bits of memory. In addition, the values of a bitset can be efficiently manipulated using bit operators, which makes it possible to optimize algorithms using bit sets.

### Bonus

```cpp
bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_first()<<endl; // prints 1
```

After more research , we found `bs._Find_next(idx)`. This function returns first set bit after index `idx`. for example:
```cpp
bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_next(1)<<','<<BS._Find_next(3)<<endl; // prints 7,7
```

So this code will print all of the set bits of BS:
```cpp
for(int i=BS._Find_first();i< BS.size();i = BS._Find_next(i))
    cout<<i<<endl;
```    
Note that there isn't any set bit after idx, `BS._Find_next(idx)` will return `BS.size()`; same as calling `BS._Find_first()` when bitset is clear;

source: https://codeforces.com/blog/entry/43718

## Problems

**P1. Different numbers** — You are given a sequence of 𝑁 ≤ 10^7 numbers, each from interval [0,10<sup>9</sup>]. How many different values appear in the sequence? 
Don't use set or unordered_set because they quite slow.

<details>
  <summary>Solution</summary>
  
Create `bitset<1000000001> visited`, mark every given number `visited[x] = 1`, and print `visited.count()`. The time complexity is 𝑂(𝑁 + 𝑀𝐴𝑋_𝑋/32), space is 𝑂(𝑀𝐴𝑋_𝑋/32). This will use 128 MB memory (one billion bits).

Creating a boolean array instead would take 1GB because one element of this array takes the whole byte. Remember that bitset is more memory-optimized than a boolean array!

An alternative solution is to use `vector<bool> b(1000000001)` because it's memory-optimized too, so takes 128 MB. It doesn't have a count() method but it isn't necessary if you do `if(!b[x]) { count++; b[x] = 1; }`.
</details>

**P2 Knapsack** You are given 𝑁≤1000 items, each with some weight 𝑤𝑖. Is there a subset of items with total weight exactly 𝑊≤10<sup>6</sup>?

Standard knapsack with boolean array would be 𝑂(𝑁⋅𝑊), too slow.

```cpp
bool can[MAX_W];
int main() {
	int n, W;
	cin >> n >> W;
	can[0] = true;
	for(int id = 0; id < n; id++) {
		int x;
		cin >> x;
		for(int i = W; i >= x; i--) {
			if(can[i-x]) can[i] = true;
		}
	}
	puts(can[W] ? "YES" : "NO");
}
```

Instead of using a boolean array, let's use bitsets and binary shifting to get 𝑂(𝑁⋅𝑊/32). You don't need to know bitsets to see how this would work for 𝑊≤32 and a bitmask unsigned long long can;, and here we just do it for a longer bitmask.

```cpp
bitset<MAX_W> can;
int main() {
	int n, W;
	cin >> n >> W;
	can[0] = true;
	for(int id = 0; id < n; id++) {
		int x;
		cin >> x;
		can = can | (can << x); // or just: can |= (can << x);
	}
	puts(can[W] ? "YES" : "NO");
}
```

**P3** Problem is: we have n numbers, calculate how many distinct numbers we can form by sum some of these numbers.

For example if we have set {17, 23, 40}, we can form {0, 17, 23, 40, 57, 63, 80}.

Dp solution is obvious:

```cpp
dp[0] = 1;
for(int i = 0; i < n; i++)
    for(int j = maxv - 1; j >= a[i]; j--)  // maxv is some number bigger than sum of a[i]'s
        dp[j] |= dp[ j - a[i] ];
cout << count(dp, dp + maxv, 1) << '\n';
```

Now how to optimize it? bitset can store bits and do operations 32 times faster like this:

```cpp
bitset<maxv> dp;
dp.set(0);
for(int i = 0; i < n; i++)
    dp |= dp << a[i];
cout << dp.count() << '\n';
```

<details>
  <summary>SnackDown 2016 Online elimination round » Robot Walk.</summary>
  
  Problem: <https://www.codechef.com/SNCKEL16/problems/RWALK/>
  
  A robot is programmed to move a_0 ​ steps forward, and then turn left or right, then a_1 ​ steps forward, and then turn left or right, and so on until a_N ​ . 
  You can increase or decrease a_i ​ , but this takes one second and you must keep each a_i ​ positive. You can also choose the turning direction freely, 
  with no time cost. What is the minimum number of seconds needed so that the robot goes back exactly to its starting point? Or determine if it’s impossible.
  
  ```cpp
  // God & me
// Life is ruined and love is lost :'(
// @Yazd
#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
//#define int long long
using namespace std;
template <class T, class L> bool smax(T &x,L y){  return x < y ? (x = y, 1) : 0;  }
template <class T, class L> bool smin(T &x,L y){  return y < x ? (x = y, 1) : 0;  }
typedef pair<int, int> pii;
typedef long long ll;

const int maxv = 6e5 + 17, S = maxv / 2;
int t, n, a[maxv];
bitset<maxv> b;
int solve(int ff){
    b.reset();
    b.set(S);
    for(int i = ff; i <= n; i += 2){
	int x = a[i];
	b = (b << x) | (b >> x);
    }
    int mn = 1e9;
    for(int i = b._Find_first(); i < b.size(); i = b._Find_next(i))
	smin(mn, abs(S - i));
    return mn;
}
main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--){
	cin >> n;
	char tmp;
	for(int i = 0; i < n; i++)
	    cin >> a[i] >> tmp;
	cin >> a[n];
	if(n < 3)
	    cout << "NO\n";
	else
	    cout << solve(0) + solve(1) << '\n';
    }
    return 0;
}
  ```
  
</details>

source: <https://codeforces.com/blog/entry/45576?#comment-302358>
