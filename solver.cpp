#pragma once
#include "common.cpp"
using namespace dalt;
#include "factorize.cpp"
#include "math.cpp"
void SolveOne(IStream &in, OStream &out) {
  int N;
  in >> N;
  if(N == 1) {
    out << N << '\n';
    return;
  }
  if(N == 0) {
    out << 10 << '\n';
    return;
  }
  Vec<int> cnt(10);
  for(int i = 2; i < 10; i++) {
    while(N % i == 0) {
      cnt[i]++;
      N /= i;
    }
  }
  if(N > 1) {
    out << -1 << '\n';
    return;
  }
  auto get_num = [&](int k) {
    Vec<int> num = cnt;
    num[2] -= k;
    num[3] -= k;
    num[6] += k;
    num[8] += num[2] / 3;
    num[2] %= 3;
    num[4] += num[2] / 2;
    num[2] %= 2;
    num[9] += num[3] / 2;
    num[3] %= 2;
    Str s;
    for(int i = 0; i < 10; i++) {
      while(num[i] > 0) {
        num[i]--;
        s.push_back(i + '0');
      }
    }
    return s;
  };
  auto comp = [&](const Str& a, const Str& b) -> bool {
    return MakePair(Size(a), a) < MakePair(Size(b), b);
  };
  Str best = get_num(0);
  for(int i = 1; i <= Min(cnt[2], cnt[3]); i++) {
    Chmin<Str>(best, get_num(i), comp);
  }
  out << best << '\n'; 
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(in, out);
  }
}