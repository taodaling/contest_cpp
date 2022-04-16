#pragma once
#include "common.cpp"
#include "polynomial.cpp"
namespace dalt {
namespace math {
  //for i <= k, ret[i] = {n \choose i}
  template<class C>
  enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>> 
  EnumerateCombination(i64 n, int k) {
    //[x^i](1+x)^n = {n\choose i}
    using P = poly::Polynomial<C>;
    using T = typename C::Type;
    auto modulus = C::modulus;
    auto phi = C::phi;
    auto res = P(Vec<T>{1, 1}).powmod_fast(n % modulus, n % phi, n, k + 1);
    auto vec = Move(res.data);
    vec.resize(k + 1);
    return vec;
  }
}
}  // namespace dalt