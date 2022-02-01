#pragma once
/**
 * Description: Hash Map with the same API as unordered\_map, but \tilde 3x
 * faster. Initial capacity must be a power of 2 if provided. Source: KACTL
 * Usage: ht<int,int> h({},{},{},{},{1<<16});
 */
#include "../common.cpp"
#include "hash.cpp"
namespace dalt {
namespace hash {
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
i64 Shuffle(i64 x) {
  static const uint64_t C =
      uint64_t(2e18 * constant::PI) + 71; // large odd number
  static const int RANDOM = rng();
  return __builtin_bswap64((x ^ RANDOM) * C);
}
template <class T>
struct chash { /// use most bits rather than just the lowest ones
  i64 operator()(T x) const { 
    return Shuffle(FastHash(&x, sizeof(T)));
  }
};
template <class K, class V>
using HashMap_um = std::unordered_map<K, V, chash<K>>;
template <class K, class V>
using HashMap_ht = __gnu_pbds::gp_hash_table<K, V, chash<K>>;
template <class K, class V>
OStream &operator<<(OStream &os, const HashMap_ht<K, V> &hv) {
  HashMap_um<K, V> hm;
  for (auto iter = hv.begin(); iter != hv.end(); iter++) {
    hm[iter->first] = iter->second;
  }
  os << hm;
  return os;
}
} // namespace hash
} // namespace dalt