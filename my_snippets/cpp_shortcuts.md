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
