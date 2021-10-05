### TODO 
https://codeforces.com/blog/entry/74684

### Use member initialization lists for struct constructor

```cpp
#include <iostream>

class Foo {
public:
  int bar;
  Foo(int num): bar(num) {};
};

struct Edge{
  int to, c;
  Edge(int to, int c): to(to), c(c) {}
};

int main(void) {
  std::cout << Foo(42).bar << std::endl;
  return 0;
}
```

Handy for graph edges, source: https://atcoder.jp/contests/abc197/submissions/21333042

```cpp
struct Edge{
    int to, c;
    Edge(int to, int c): to(to), c(c) {}
};
```

![image](https://user-images.githubusercontent.com/19663316/118325069-86cb8d80-b520-11eb-908d-bd7d318667da.png)

Also if you want to sort based on properties in struct

```cpp
struct bot{
	int x, d;
};

// inside main
vector<bot> a(n);
forn(i, n) scanf("%d", &a[i].x);
forn(i, n){
    char c;
    scanf(" %c", &c);
    a[i].d = c == 'L' ? -1 : 1;
}
		
vector<int> ord(n);
iota(ord.begin(), ord.end(), 0);
sort(ord.begin(), ord.end(), [&a](int x, int y){
    return a[x].x < a[y].x;
});
```

source: https://codeforces.com/blog/entry/90793 Problem C

If `LLONG_MAX` or `INT_MAX` is not available in the online judge then use `INT32_MAX` instead of `INT_MAX` and the following for `long long`

```cpp
#define LLONG_MAX INT64_MAX
#define LLONG_MIN INT64_MIN

const ll inf = 1LL << 62;
```

or use `#include <climits> // all useful constants`

To convert from string to int while reading input, use `stringstream`

```cpp
stringstream numToString;
numToString << 5;
string val;
numToString >> val; // val is now the string "5"
```

```cpp
stringstream stringToNum;
stringToNum << "5";
int val;
stringToNum >> val; // val is now the integer 5
```

Just as with `cin`, you can use a `stringstream` to determine what type the next
word is. If you try to read from a `stringstream` into an `int` but the next word
is not an integer, the expression will evaluate to `false`:

```cpp
stringstream ss;
ss << "notaninteger";
int val;
if (ss >> val) {
    cout << "read an integer!" << endl;
} else {
    cout << "next word was not an integer" << endl;
}
```

To use custom comparator while comparing pairs to sort `vector<pair<int,int>>`
```cpp
bool sort_cmp(const pair<int, int> &a, const pair<int,int> &b){
    int s1 = a.second - a.first;
    int s2 = b.second - b.first;
    return s1 > s2;
}
```

### Multiset

Removing one element from multiset

```cpp
auto itr = my_multiset.find(value);
if(itr!=my_multiset.end()){
    my_multiset.erase(itr);
}
```

If we know element is in multiset

```cpp
multiset<int> s;
s.erase(s.lower_bound(value));
```

Never use `count` with multiset, if you find existence, use `S.find(x) != S.end()` instead

source: https://stackoverflow.com/questions/9167745/in-stdmultiset-is-there-a-function-or-algorithm-to-erase-just-one-sample-unic

### Pairs unpacking

```cpp
vector<tuple<int,int,int>> g(100);
int x,y,z; tie(x,y,z) = g[19];

auto[x, y, z] = g[i]; // C++17, structured binding declaration
auto& [x, y, z] = g[i]; // to get references

pair<int,int> f(); // function that returns a pair<int,int>
auto [x, y] = f();
```

### Multiplying long long modulo

```cpp
scau_bi
乘法取模优化
inline long long multi(long long x,long long y,long long mod)//mod long long 
{
    long long tmp=(x*y-(long long)((long double)x/mod*y+0.5)*mod);
    return tmp<0 ? tmp+mod : tmp;
}
```

source: https://www.cnblogs.com/bibibi/p/9613151.html

### Random shuffle

```cpp
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

// inside main
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  shuffle(order.begin(), order.end(), rng);
```

source: https://codeforces.com/contest/1523/submission/117881477

### Printing with precision in CPP, Faster IO
```cpp
  // Fast IO
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  // printing till x digits
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(6);
  
  // Just in single line
  cout << fixed << setprecision(15) << ans << '\n';
  
  // Another way
  double d = 3.14159265358979;
  cout.precision(17);
  cout << "Pi: " << fixed << d << endl;
```

### C++ Tricks for competitive programming

* Getting rid of "includes": Just use `#include <bits/stdc++.h>`
* Useful inbuilt functions:
  * `__gcd(a, b)`: Returns the `𝐺𝐶𝐷` of `a` and `b`
  * `__builtin_popcount(x)`: Returns the number of set bits in `x`
* Initializer Lists: These make STL containers easy to initialize, for eg:
  * `vector<int> odd_nos = {1, 3, 5, 7, 9};`
  * `pair<int, string> p = {1, “Hi”}; // Equiv. to p=make_pair(1, "Hi")`
  * `map<int, string> m = { {1, “This”}, {2, “is”}, {3, “awesome”} };`
  * `for(parity : {0,1}){ ... }`
* Finding min and max of multiple variables:
```cpp
// Long Way: 
 
int max_of_3 = max(a, max(b, c)); 
int max_of_4 = max(max(a, b), max(c, d)); 
 
// Easier Way - Can be extended to any number of variables: 
 
int max_of_3 = max({a, b, c}); 
int max_of_4 = max({a, b, c, d}); 
```
* Range-based for loops: Makes it much simpler to iterate through containers.
```cpp
// Old Way: 
for(auto it=container.begin(), it!=container.end(); it++) 
	  cout<<*it<<" "; 
 
// Alternatively: 
for(int i=0;i<container.size();i++) //If the container is a vector 
	  cout<<container[i]<<" "; 
 
// Easier Way: 
for(auto &it:container) //Using & also allows us to modify the elements 
	  cout<<it<<" "; 

```
* Tie and Swap:
  * Tie makes it easier to initialize multiple variables in a single line
  ```cpp
  // Initializes a with -1, b with 1, etc 
  tie(a, b, c, d) = make_tuple(-1, 1, -2, 2); 
  ```
  * Swap enables swapping of variables, and even containers with a single statement
  ```cpp
  // x, y can be two integers, or two vectors, or any two containers 
  swap(x, y); 
  ```
`emplace_back` is faster than `push_back` because it just construct value at the end of vector but push_back construct it somewhere else and then move it to the vector.  
```cpp
#define mt make_tuple
#define eb emplace_back
typedef tuple<int,int,int> State; // operator< defined

int main(){
  int a,b,c;
  tie(a,b,c) = mt(1,2,3); // assign
  tie(a,b) = mt(b,a); // swap(a,b)

  vector<pair<int,int>> v;
  v.eb(a,b); // shorter and faster than pb(mp(a,b))

  // Dijkstra
  priority_queue<State> q;
  q.emplace(0,src,-1);
  while(q.size()){
    int dist, node, prev;
    tie(dist, ode, prev) = q.top(); q.pop();
    dist = -dist;
    // ~~ find next state ~~
    q.emplace(-new_dist, new_node, node);
  }
}
```
* Macros
  * If you are tired of typing some statement like `push_back` again and again, you can just use `#define pb push_back`, and type `pb` in your code.
  * Getting the name of the argument in macro using #, and using it to debug your program: `#define trace(x) cerr<<#x<<": "<<x<<" "<<endl;`

source: https://qr.ae/pGvblN

* Printing newlines: `" \n"` is a char*, `" \n"[0]` is `' '` and `" \n"[1]` is `'\n'`.
```cpp
for(i = 1; i <= n; i++) {
    for(j = 1; j <= m; j++)
        cout << a[i][j] << " ";
    cout << "\n";
}
is equivalent to this:

for(i = 1; i <= n; i++)
    for(j = 1; j <= m; j++)
        cout << a[i][j] << " \n"[j == m];
```

### Using C++ Lambdas

Use case:
```cpp
// define a special-purpose custom printing function
void print_it (int i)
{
 cout << ":" << i << ":";
}
...
// apply print_it to each integer in the list
for_each(int_list.begin(), int_list.end(), print_it);
cout << endl;
```

Using lambdas

```cpp
for_each(int_list.begin(), int_list.end(), [](int i){cout << ":" << i << ":";} );
cout << endl;
```

We could store the above example lambda in a variable,
and then call it using the syntax that we would also use a function pointer or function object, as follows: 

```cpp
auto func1 = [](int i) {cout << ":" << i << ":";};
func1(42); // prints ":42:"

auto f = [] (int a, int b) -> int { return a + b; };
cout << f(1, 2); // prints "3"
```

* Lambdas `[capture list](parameters) -> return value { body }`. Shortcuts: There are two shortcut capture specifications that might be useful on occasion:
  * [=] capture all variables currently in local block scope by copy of their current values
  * [&] capture all variables currently in local block scope by reference 

* You can use lambdas in `for_each`, `sort` and many more STL functions:
```cpp
vector<int> v = {3, 1, 2, 1, 8};
sort(begin(v), end(v), [] (int a, int b) { return a > b; });
for (auto i: v) cout << i << ' '; // Output: 8 3 2 1 1
```

### What’s the syntax / semantics for a “function template”?

Consider this function that swaps its two integer arguments:

```cpp
void swap(int& x, int& y)
{
  int tmp = x;
  x = y;
  y = tmp;
}
```

If we also had to swap floats, longs, Strings, Sets, and FileSystems, we’d get pretty tired of coding lines that look almost identical except for the type. Mindless repetition is an ideal job for a computer, hence a function template:

```cpp
template<typename T>
void swap(T& x, T& y)
{
  T tmp = x;
  x = y;
  y = tmp;
}
```

Every time we used `swap()` with a given pair of types, the compiler will go to the above definition and will create yet another “template function” as an instantiation of the above. Unlike template classes, template functions usually do not need to be explicit about the parameters over which they are instantiating. The compiler can usually determine them automatically. E.g.,

```cpp
int main()
{
  int         i,j;  /*...*/  swap(i,j);  // Instantiates a swap for int
  float       a,b;  /*...*/  swap(a,b);  // Instantiates a swap for float
  char        c,d;  /*...*/  swap(c,d);  // Instantiates a swap for char
  std::string s,t;  /*...*/  swap(s,t);  // Instantiates a swap for std::string
  // ...
}
```

Note: A “template function” is the instantiation of a “function template”.

source: https://isocpp.org/wiki/faq/templates

### What’s the syntax / semantics for a “class template”?

Consider a container class Array that acts like an array of integers:

```cpp
// This would go into a header file such as "Array.h"
class Array {
public:
  Array(int len=10)                  : len_(len), data_(new int[len]) { }
 ~Array()                            { delete[] data_; }
  int len() const                    { return len_;     }
  const int& operator[](int i) const { return data_[check(i)]; }  // Subscript operators often come in pairs
  int&       operator[](int i)       { return data_[check(i)]; }  // Subscript operators often come in pairs
  Array(const Array&);
  Array& operator= (const Array&);
private:
  int  len_;
  int* data_;
  int  check(int i) const
    {
      if (i < 0 || i >= len_)
        throw BoundsViol("Array", i, len_);
      return i;
    }
};
```

Repeating the above over and over for Array of float, of char, of std::string, of Array-of-std::string, etc, would become tedious. Instead, you add the template<typename T> before the class definition (the T can be any identifier you want, T is just the most commonly used one, especially in examples). Then, instead of using int or float or char where referring to the data type, you use T instead. Also, instead of just referring to the class as Array, it’s Array<T> when referring to the template, or Array<int>, Array<float>, etc. when referring to a specific instantiation.

```cpp
// This would go into a header file such as "Array.h"
template<typename T>
class Array {
public:
  Array(int len=10)                : len_(len), data_(new T[len]) { }
 ~Array()                          { delete[] data_; }
  int len() const                  { return len_;     }
  const T& operator[](int i) const { return data_[check(i)]; }
  T&       operator[](int i)       { return data_[check(i)]; }
  Array(const Array<T>&);
  Array(Array<T>&&);
  Array<T>& operator= (const Array<T>&);
  Array<T>& operator= (Array<T>&&);
private:
  int len_;
  T*  data_;
  int check(int i) const {
    assert(i >= 0 && i < len_);
    return i;
  }
};
```

Just as with a normal class, you can optionally define your methods outside the class:

```cpp
template<typename T>
class Array {
public:
  int len() const;
  // ...
};
template<typename T>
inline      // See below if you want to make this non-inline
int Array<T>::len() const
{
  // ...
}
```

Unlike template functions, template classes (instantiations of class templates) need to be explicit about the parameters over which they are instantiating:

```cpp
int main()
{
  Array<int>           ai;
  Array<float>         af;
  Array<char*>         ac;
  Array<std::string>   as;
  Array<Array<int>>    aai;
  // ...
}
```

Note that prior to C++11, a space was required between the two >’s in the last example. Without this space, the C++98/C++03 compiler would see a >> (right-shift) token instead of two >’s. Aren’t you lucky that it is no longer the case in C++11?

Look at https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates

Summary: Stroustrup originally used class to specify types in templates to avoid introducing a new keyword. Some in the committee worried that this overloading of the keyword led to confusion. Later, the committee introduced a new keyword typename to resolve syntactic ambiguity, and decided to let it also be used to specify template types to reduce confusion, but for backward compatibility, class kept its overloaded meaning. [REF](https://stackoverflow.com/questions/213121/use-class-or-typename-for-template-parameters?noredirect=1&lq=1)

TODO: https://discuss.codechef.com/t/c-oops-concepts/74361
