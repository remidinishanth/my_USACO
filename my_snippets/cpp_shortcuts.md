* Use member initialization lists for struct constructor

```cpp
#include <iostream>

class Foo {
public:
  int bar;
  Foo(int num): bar(num) {};
};

int main(void) {
  std::cout << Foo(42).bar << std::endl;
  return 0;
}
```
