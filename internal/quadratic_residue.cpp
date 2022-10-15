#pragma once
#include "modint.cpp"
#include "binary.cpp"
namespace dalt {
namespace math {
  //find num x that x * x = n
  //condition: modulus is a prime number
  //time: O(\log modulus)
  template<class T>
  enable_if_t<is_modint_v<T>, Optional<T>> 
  QuadraticResidue(T n) {
    using raw_type = typename T::Type;
    if(n == T(0)) {
      return T(0);
    }
    raw_type mod = T::modulus();
    if(mod == 2) {
      return n;
    }
    if(n.pow((mod - 1) / 2) != T(1)) {
      return {};
    }
    while(true) {
      T a = T(random_choice<raw_type>(0, mod - 1));
      T w = a * a - n;
      if(w.pow((mod - 1) / 2) == T(1)) {
        continue;
      }
      raw_type pow = (mod + 1) / 2;
      T real = 1;
      T img = 0;
      for(var i = HighestOneBit(pow); i > 0; i >>= 1) {
        var next_real = real * real + img * img * w;
        var next_img = real * img * T(2);
        real = next_real;
        img = next_img;
        if(i & pow) {
          next_real = real * a + img * w;
          next_img = img * a + real;
          real = next_real;
          img = next_img;
        }
      }

      return real;
    }
  }
}
}  // namespace dalt