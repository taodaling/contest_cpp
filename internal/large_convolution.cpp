#pragma once
#include "convolution.cpp"
#include "modint.cpp"
#include "ntt.cpp"
namespace dalt {
namespace poly {
template <class T, int B = 20>
struct LargeConvolution {
  const static int batch_size = 1 << B;
  const static int batch_size_2 = batch_size * 2;
  using Type = T;

  static Vec<Vec<T>> split(const Vec<T> &a) {
    Vec<Vec<T>> data((Size(a) + batch_size - 1) / batch_size,
                     Vec<T>(batch_size * 2));
    for (int i = 0; i < Size(a); i++) {
      data[i >> B][i & (batch_size - 1)] = a[i];
    }
    Timer ntt("ntt");
    for (auto &chunk : data) {
      NumberTheoryTransform(chunk, false);
    }
    ntt.stop();
    return data;
  }
  // template <class Arg = T>
  // static enable_if_t<is_same_v<Arg, T> &&
  //                        !(is_modint_v<T> && is_same_v<typename T::Type, i32>),
  //                    Vec<T>>
   static   Vec<T> conv(const Vec<T> &a, const Vec<T> &b) {
    auto a_data = split(a);
    auto b_data = split(b);
    Vec<Vec<T>> c_data(Size(a_data) + Size(b_data) - 1, Vec<T>(batch_size * 2));
    Timer dmp("DotMulPlus");
    for (int i = 0; i < Size(a_data); i++) {
      for (int j = 0; j < Size(b_data); j++) {
        DotMulPlus(a_data[i], b_data[j], c_data[i + j]);
      }
    }
    dmp.stop();
    Timer ntt("ntt");
    for (int i = 0; i < Size(c_data); i++) {
      NumberTheoryTransform(c_data[i], true);
    }
    ntt.stop();
    Vec<T> res(Size(a) + Size(b) - 1);
    for (int i = 0; i < Size(c_data); i++) {
      auto &chunk = c_data[i];
      for (int j = 0, to = i * batch_size; j < Size(chunk) && to < Size(res);
           j++, to++) {
        res[to] += chunk[j];
      }
    }
    return res;
  }
  // template <class Arg = T>
  // static enable_if_t<is_same_v<Arg, T> && is_modint_v<T> &&
  //                        is_same_v<typename T::Type, i32>,
  //                    Vec<T>>
  // conv(const Vec<T> &a, const Vec<T> &b) {
  //   auto a_data = split(a);
  //   auto b_data = split(b);
  //   Vec<u128> aggregate(batch_size * 2);
  //   Vec<T> res(Size(a) + Size(b) - 1);
  //   i32 modulus = T::modulus();

  //   for (int i = 0; i < Size(a_data) + Size(b_data); i++) {
  //     //Timer plus("plus");
  //     Fill(All(aggregate), u128());
  //     for (int j = Max(0, i - Size(b_data) + 1); j < Size(a_data) && j <= i;
  //          j++) {
  //       int k = i - j;
  //       auto &a_ref = a_data[j];
  //       auto &b_ref = b_data[k];
  //       for (int t = 0; t < batch_size_2; t++) {
  //         aggregate[t] += u64(a_ref[t].value) * u64(b_ref[t].value);
  //       }
  //     }
  //     //plus.stop();
  //     Vec<T> chunk(batch_size * 2);
  //     for (int j = 0; j < batch_size * 2; j++) {
  //       chunk[j] = aggregate[j].modular(modulus);
  //     }
  //     NumberTheoryTransform(chunk, true);
  //     for (int j = 0, to = i * batch_size; j < Size(chunk) && to < Size(res);
  //          j++, to++) {
  //       res[to] += chunk[j];
  //     }
  //   }
  //   return res;
  // }
};
}  // namespace poly
}  // namespace dalt