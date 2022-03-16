#pragma once
#include "common.cpp"
using namespace dalt;
#include "function.cpp"
#include "kth_term_of_inverse_polynomial.cpp"
#include "modint.cpp"
#include "ntt.cpp"
#include "binary.cpp"
using Mi = ModInt998244353;
using namespace poly;
struct SmallConv {
  using Type = Mi;
  static Vec<Mi> conv(const Vec<Mi>& a, const Vec<Mi> &b) {
    if(Size(a) > Size(b)) {
      return conv(b, a);
    }
    if(Size(a) == 1) {
      return Vec<Mi> {a[0] * b[0], a[0] * b[1]};
    }
    return Vec<Mi>{a[0] * b[0], a[0] * b[1] + a[1] * b[0], a[1] * b[1]};
  }
};
using Poly = Polynomial<BruteForceConv<Mi>>;
namespace dalt{
  namespace poly {
template<>
struct is_convolution<SmallConv> {
  const static bool value = true;
};
  }
}
void SolveOne(IStream &in, OStream &out) {
  Timer timer("SolveOne");
  int N;
  i64 M;
  in >> N >> M;
  Vec<Mi> A(N);
  Vec<Mi> AS(N);
  Vec<Mi> C(N);
  Vec<i64> B(N);
  Vec<Poly> ps(N);

  for(int i = 0; i < N; i++) {
    in >> A[i] >> B[i];
    B[i]++;
    ps[i] = Poly(Vec<Mi>{1, -A[i]});
    AS[i] = A[i].pow(B[i]);
  }
  auto prod = Poly::product(ps);
  for (int i = 0; i < N; i++) {
    C[i] = 1;
    Mi x = A[i].possible_inv().value();
    for(int j = 0; j < N; j++) {
      if(i == j) { 
        continue;
      } 
      C[i] *= ps[j].apply(x);
    }
    //Debug(i);
    //Debug(C[i]);
    C[i] = C[i].possible_inv().value();
  }
  Poly one = Poly(1);
  auto kth_term = [&](i64 k) -> Mi {
    Mi ans = 0;
    for(int i = 0; i < N; i++) {
      ans += C[i] * A[i].pow(k);
    } 
    //ans = KthTermOfInversePolynomial(h, ReverseIndexer(h, BinaryIndexer(k)), one, prod);
    //DebugFmtln("%d-th term [%d] = %d", k, h, ans);
    return ans;
  };
  Mi sum = 0;
  for(int i = 0; i < 1 << N; i++) {
    Mi prod = 1;
    i64 atleast = 0;
    for(int j = 0; j < N; j++) {
      if(KthBit(i, j)) {
        prod *= AS[j];
        atleast += B[j];
      }
    }
    if (atleast > M) {
      continue;
    }

    prod *= kth_term(M - atleast);
    //Debug(i);
    //Debug(prod);
    if(CountBit(i) % 2 == 1) {
      prod = -prod;
    }
    sum += prod;
  }
  out << sum << '\n';
  timer.stop();
}

void SolveMulti(IStream &in, OStream &out) {
  int num_of_input = 1;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(in, out);
  }
}