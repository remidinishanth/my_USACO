* Use member initialization lists for struct constructor

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

Handy for graph edges

![image](https://user-images.githubusercontent.com/19663316/118325069-86cb8d80-b520-11eb-908d-bd7d318667da.png)
