# SYNOPSIS
A binary executable that compiles modules of C++ code.


# MOTIVATION
C++ does not have a module system. Libs and a linker do not constitute a
module system. The ideas in this project are a subset of the ideas from
[`this`](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2073.pdf), 
[`this`](http://isocpp.org/files/papers/n4214.pdf) and clang's 
[`experimental module implementation`](http://clang.llvm.org/docs/Modules.html).


# STATUS
Experimental. A work in progress.


# EXAMPLE
A modue is a discrete unit of code, encapsulated in a file. It exposes at 
least one public value, function, class, etc. Let's use the following file 
strcture as an example.

```
main.cc
helloworld.cc
awesome.cc
cc_modules/
  math/
    index.cc
```


## ./MAIN.CC
Typical entry point for most programs.

```cpp
//
// import the file "helloworld.cc" as "hello".
//
import hello "./helloworld.cc";

//
// import the module "math" as "math".
//
import math "math";

int main() {
  hello.greeting("hola");
  math.add(2, 2);
}
```
To understand how a `module` is imported, read 
[`this`](http://nodejs.org/api/modules.html#modules_loading_from_node_modules_folders).


## ./HELLOWORLD.CC
The module imported by the code in `main.cc`.

```cpp
#include <iostream>

//
// GLOBAL SCOPE
//
// Anything outside of export will be global, this will be 
// accessible from ANY file. you should not put anything here 
// unless you REALLY MEAN TO.
//

export {

  //
  // MODULE SCOPE
  //
  // Variables defined here are implicitly private, they are
  // not exported, this applies to varibles imported from other 
  // modules.
  //
  int num = 10;

  //
  // import the file "./awesome.cc" as "awesome"
  //
  import awesome "./awesome.cc";

  //
  // Variables found after the "public:" label are exported!
  //
  public:

    void doSomething(string s) {
      std::cout << s << awesome.square(num) << endl;
    }

  //
  // You can switch back and forth between public and private
  // by using the "private:" label.
  //
  private:
    int x = 0;
}
```


## ./AWESOME.CC
This file happens to be included by `helloworld.cc`.

```cpp
export {
  public:
    int square(int i) {
      return i*i;
    }
}
```


## ./CC_MODULES/MATH/INDEX.CC
```cpp
export {
  public:
    int add(int a, int b) {
      return a+b;
    }
}
```


# USAGE
It's important to tell `gcc`, `clang` (or whatever) where your 
precompiled headers can be found...

```bash
bale input.cc output.cc
```


## EXAMPLE
```bash
bale main.cc build.cc
g++ build.cc -std=c++1y -o main -include-pch cc_modues/.build
```

