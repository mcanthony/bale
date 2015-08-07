#include <iostream>

export A {

  // inlcudes get hoisted

  // introduce a second level of depth
  // in this case an implicitly private
  // instance of `B`.
  import B "./b.cc";

  // implicitly private
  int pnum1 = 10;

  // explicitly private
  int pnum2 = 10;

  // explicitly public
  public:
    void func1(std::string s) {
      std::cout << B.func() << std::endl;
      std::cout << s << pb1 << std::endl;
    }

    // a class that can be 
    // instantiated after exporting
    class c1 {
      int ci = 10;
    };

  private:
    // a few more private things...
    bool pb1;
    void func2(std::string s) {
      std::cout << s << std::endl;
    }
}

