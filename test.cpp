// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

struct A {
  using Type = int;
};
struct B: public A{

};
template<class T>
enable_if_t<is_same_v<int, typename T::Type>, void> Add(vector<T>& data, typename T::Type val) {

}


int main() {
  vector<B> vec;
  Add<B>(vec, 1);
  return  0;
}