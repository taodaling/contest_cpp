#pragma once
#include "../common.cpp"
namespace dalt {
template <class T, class E> T PowBinaryLift(T x, E n) {
  if (n == 0) {
    return 1;
  }
  auto ans = PowBinaryLift(x, n / 2);
  ans = ans * ans;
  if (n & 1) {
    ans = ans * x;
  }
  return ans;
}
template <class T> Vec<T> InverseBatch(Vec<T> batch) {
  int n = int(batch.size());
  Vec<T> origin = batch;
  T fact = 1;
  for (int i = 0; i < n; i++) {
    if (origin[i] == T(0)) {
      continue;
    }
    T val = batch[i];
    batch[i] = fact;
    fact = fact * val;
  }
  T inv_fact = T(1) / fact;
  for (int i = n - 1; i >= 0; i--) {
    if (origin[i] == T(0)) {
      continue;
    }
    batch[i] = batch[i] * inv_fact;
    inv_fact = inv_fact * origin[i];
  }
  return batch;
}
#define DefineStdMathRealFunction(name, stdname)                               \
  f32 name(f32 x) { return stdname ## f(x); }                                    \
  f64 name(f64 x) { return stdname (x); }                                     \
  f80 name(f80 x) { return stdname ## l(x); }

DefineStdMathRealFunction(Sin, sin);
DefineStdMathRealFunction(Cos, cos);
DefineStdMathRealFunction(Asin, asin);
DefineStdMathRealFunction(Acos, cos);
DefineStdMathRealFunction(Tan, tan);
DefineStdMathRealFunction(Atan, atan);
i64 Round(f32 x) { return roundf(x); }
i64 Round(f64 x) { return round(x); }
i64 Round(f80 x) { return roundl(x); }
} // namespace dalt