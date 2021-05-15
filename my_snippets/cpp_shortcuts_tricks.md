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

![image](https://user-images.githubusercontent.com/19663316/118325069-86cb8d80-b520-11eb-908d-bd7d318667da.png)

### C++ Tricks for competitive programming

* Getting rid of "includes": Just use `#include <bits/stdc++.h>`
* Useful inbuilt functions:
  * `__gcd(a, b)`: Returns the `𝐺𝐶𝐷` of `a` and `b`
  * `__builtin_popcount(x)`: Returns the number of set bits in `x`
* Initializer Lists: These make STL containers easy to initialize, for eg:
  * `vector<int> odd_nos = {1, 3, 5, 7, 9};`
  * `pair<int, string> p = {1, “Hi”}; // Equiv. to p=make_pair(1, "Hi")`
  * `map<int, string> m = { {1, “This”}, {2, “is”}, {3, “awesome”} };`
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
* Lambdas `[capture list](parameters) -> return value { body }`
```cpp
auto f = [] (int a, int b) -> int { return a + b; };
cout << f(1, 2); // prints "3"
```

  * You can use lambdas in for_each, sort and many more STL functions:
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
