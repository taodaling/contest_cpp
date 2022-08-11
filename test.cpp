#include <iostream>
using namespace std;

template<class T>
enable_if_t<is_integral_v<T>, T> mod(T a, T b) {
  return a % b;
}

int main() {
  cout << mod<int>(100, 9);
  return 0;
}