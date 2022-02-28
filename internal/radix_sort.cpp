#include "common.cpp"
namespace dalt {
// verified by:
//  - https://www.luogu.com.cn/problem/P1177
template <class F, class T, i32 BIT_8 = 1>
enable_if_t<is_integral_v<T>, void> RadixSortMapper(
    F* begin, i32 n, const Mapper<F, T>& mapper) {
  static_assert(BIT_8 >= 1 && BIT_8 <= 2);
  static const i32 BUF_SIZE = 1 << 8 * BIT_8;
  static const i32 BUF_MASK = BUF_SIZE - 1;
  static i32 CNT[BUF_SIZE];
  static Vec<F> BUF;
  BUF.resize(n);
  auto sort = [&](auto data, auto output, i32 shift, i32 n) {
    memset(CNT, 0, sizeof(CNT));
    for (int i = 0; i < n; i++) {
      CNT[(mapper(data[i]) >> shift) & BUF_MASK]++;
    }
    for (int i = 1; i < BUF_SIZE; i++) {
      CNT[i] += CNT[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      output[--CNT[(mapper(data[i]) >> shift) & BUF_MASK]] = data[i];
    }
  };
  i32 round = sizeof(T) / BIT_8 / 2;
  if (round == 0) {
    sort(begin, BUF.data(), 0, n);
    std::memcpy(begin, BUF.data(), n);
    return;
  }
  for (int i = 0; i < round; i++) {
    sort(begin, BUF.data(), i * 2 * BIT_8 * 8, n);
    sort(BUF.data(), begin, (i * 2 + 1) * BIT_8 * 8, n);
  }
}
template <class T, i32 BIT_8 = 1>
enable_if_t<is_integral_v<T>, void> RadixSort(T* begin, i32 n) {
  static_assert(BIT_8 >= 1 && BIT_8 <= 2);
  static const i32 BUF_SIZE = 1 << 8 * BIT_8;
  static const i32 BUF_MASK = BUF_SIZE - 1;
  static i32 CNT[BUF_SIZE];
  static Vec<T> BUF;
  BUF.resize(n);
  auto sort = [&](auto data, auto output, i32 shift, i32 n) {
    memset(CNT, 0, sizeof(CNT));
    for (int i = 0; i < n; i++) {
      CNT[(data[i] >> shift) & BUF_MASK]++;
    }
    for (int i = 1; i < BUF_SIZE; i++) {
      CNT[i] += CNT[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      output[--CNT[(data[i] >> shift) & BUF_MASK]] = data[i];
    }
  };
  i32 round = sizeof(T) / BIT_8 / 2;
  if (round == 0) {
    sort(begin, BUF.data(), 0, n);
    std::memcpy(begin, BUF.data(), n);
    return;
  }
  for (int i = 0; i < round; i++) {
    sort(begin, BUF.data(), i * 2 * BIT_8 * 8, n);
    sort(BUF.data(), begin, (i * 2 + 1) * BIT_8 * 8, n);
  }
}

template <class F, class T>
enable_if_t<is_integral_v<T>, void> RadixSortMapperAdjust(
    F* begin, i32 n, const Mapper<F, T>& mapper) {
  if (sizeof(T) == 1) {
    RadixSortMapper<F, T, 1>(begin, n, mapper);
    return;
  }
  i32 round1 = sizeof(T);
  i32 round2 = sizeof(T) / 2;
  if ((i64)round1 * (n + (1 << 8)) <= (i64)round2 * (n + (1 << 16))) {
    RadixSortMapper<F, T, 1>(begin, n, mapper);
  } else {
    RadixSortMapper<F, T, 2>(begin, n, mapper);
  }
}
template <class T>
enable_if_t<is_integral_v<T>, void> RadixSortAdjust(T* begin, i32 n) {
  if (sizeof(T) == 1) {
    RadixSort<T, 1>(begin, n);
    return;
  }
  i32 round1 = sizeof(T);
  i32 round2 = sizeof(T) / 2;
  if ((i64)round1 * (n + (1 << 8)) <= (i64)round2 * (n + (1 << 16))) {
    RadixSort<T, 1>(begin, n);
  } else {
    RadixSort<T, 2>(begin, n);
  }
}
}  // namespace dalt