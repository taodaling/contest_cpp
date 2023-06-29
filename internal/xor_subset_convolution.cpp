#include "bitwise_convolution.cpp"
#include "modint.cpp"
#include "combination.cpp"
namespace dalt {
template <class T>
void XorSubsetConvolutionDedup(Vec<Vec<T>> &conv, T total) {
  int K = Size(conv) - 1;
  int N = Size(conv[0]);
  
  math::Combination<T> fact(K + 1);
  var comb = [&](T a, int b) {
    T ans = fact.inv_fact[b];
    while(b > 0) {
      ans *= a;
      a -= 1;
      b--;
    }
    return ans;
  };
  for (int i = 2; i <= K; i++) {
    //Debug(i);
    //Debug(conv[i]);
    // dedup
    Vec<int> state(i + 1);
    var dfs = [&](var &dfs, int offset, int sum, int used) {
      if (sum > i) {
        return;
      }
      if (offset > i) {
        if (sum != i || used != i || state[0] == 0) {
          return;
        }
        // dedup
        T perm = fact.fact[i];
        for(int j = 2; j <= i; j++) {
          for(int t = 0; t < state[j]; t++) {
            perm *= fact.inv_fact[j];
          }
        }
        int oddCnt = 0;
        for (int j = 1; j <= i; j += 2) {
          oddCnt += state[j];
        }
        T factor = 1;
        T oddRemain = oddCnt;
        T evenRemain = total - oddCnt;
        for (int j = 1; j <= i; j += 2) {
          factor *= comb(oddRemain, state[j]);
          oddRemain -= state[j];
        }
        for (int j = 2; j <= i; j += 2) {
          factor *= comb(evenRemain, state[j]);
          evenRemain -= state[j];
        }
        factor *= perm;
        for (int j = 0; j < N; j++) {
          conv[i][j] -= conv[oddCnt][j] * factor;
        }
        return;
      }
      for (int j = 0; j + used <= i && offset * j + sum <= i; j++) {
        state[offset] = j;
        dfs(dfs, offset + 1, sum + offset * j, j + used);
      }
    };
    dfs(dfs, 0, 0, 0);
    for(int j = 0; j < N; j++) {
      conv[i][j] *= fact.inv_fact[i];
    }
  }
}

// ret[j][i] means how many subsets (size j) exists that xor sum of it is i
// O(K |counts| (P(K) + log |counts|)) where P is the partition function
template <class T>
Vec<Vec<T>> XorSubsetConvolutionAllTier(Vec<T> counts, int K) {
  static_assert(is_modint_v<T>);
  Assert(CountBit(Size(counts)) == 1);
  T total = 0;
  for(var x : counts) {
    total += x;
  }
  Assert(K >= 1);
  using Xor = fwt::Xor<T>;
  using IXor = fwt::IXorFast<T>;
  IXor::Register(T(1) / T(2));
  Vec<Vec<T>> conv(K + 1);
  conv[0].resize(Size(counts));
  conv[0][0] = 1;
  conv[1] = counts;

  fwt::BitwiseTransform<Xor>(conv[1], 0, Size(conv[1]) - 1);
  for (int i = 2; i <= K; i++) {
    conv[i].resize(Size(counts));
    for (int j = 0; j < Size(counts); j++) {
      conv[i][j] = conv[i - 1][j] * conv[1][j];
    }
  }
  conv[1] = counts;
  for(int i = 2; i <= K; i++) {
    fwt::BitwiseInverse<IXor>(conv[i], 0, Size(conv[i]) - 1);
  }
  XorSubsetConvolutionDedup(conv, total);
  return Move(conv);
}
// ret[i] means how many subsets (size k) exists that xor sum of it is i
// O( |counts| (K * P(K) + log |counts|)) where P is the partition function
template <class T>
Vec<T> XorSubsetConvolutionLastTier(Vec<T> counts, int K) {
  static_assert(is_modint_v<T>);
  Assert(CountBit(Size(counts)) == 1);
  Assert(K >= 1);
  T total = 0;
  for (var x : counts) {
    total += x;
  }
  using Xor = fwt::Xor<T>;
  using IXor = fwt::IXorFast<T>;
  IXor::Register(T(1) / T(2));
  Vec<Vec<T>> conv(K + 1);
  conv[0].resize(Size(counts));
  conv[0][0] = 1;
  conv[1] = counts;
  fwt::BitwiseTransform<Xor>(conv[0], 0, Size(conv[0]) - 1);
  fwt::BitwiseTransform<Xor>(conv[1], 0, Size(conv[1]) - 1);
  for (int i = 2; i <= K; i++) {
    conv[i].resize(Size(counts));
    for (int j = 0; j < Size(counts); j++) {
      conv[i][j] = conv[i - 1][j] * conv[1][j];
    }
  }
  XorSubsetConvolutionDedup(conv, total);
  fwt::BitwiseInverse<IXor>(conv[K], 0, Size(conv[K]) - 1);
  return Move(conv[K]);
  }
  }  // namespace dalt