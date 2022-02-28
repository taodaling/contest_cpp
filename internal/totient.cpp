#pragma once
#include "big_multiplicative_function.cpp"
namespace dalt {
namespace math {
#define CID -202202162000
template <class I, bool CACHE>
I TotientEval(I n) {
  static auto f = [](auto x, auto xp) { return xp - xp / x; };
  if (!CACHE) {
    return BigMultiplicativeFunctionEval<I, I>(n, f);
  } else {
    return BigMultiplicativeFunctionEval<I, I, CID>(n, f);
  }
}
#undef CID
}  // namespace math
}  // namespace dalt