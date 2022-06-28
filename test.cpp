#include <iostream>
using namespace std;

#define IsBool(param, ret_type)       \
  template <bool OnlyWhenArg = param> \
  enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>
#define IsBoolStatic(param, ret_type) \
  template <bool OnlyWhenArg = param> \
  static enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>

template<bool P, bool S>
struct A {
  // IsBool(P, int) add(int a, int b) {
  //   return a;
  // }
  // IsBool(S, int) add(int a, int b) {
  //   return b;
  // }
  IsBool(!(P || S), int) add(int a, int b) {
    return a + b;
  }
  IsBool(P, int) add(int a, int b) {
    return a;
  }

};

int main() {
  A<false, false> a;
  cout << a.add(1, 2);
  return 0;
}