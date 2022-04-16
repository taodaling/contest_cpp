#include <iostream>
using namespace std;

struct S {
  static int val;
  struct B{
    B() {
      S::val = 1;
    }
  } b;
};
int S::val;

int main() {
  cout << S::val << endl;
  return 0;

}