#pragma once
#include "common.cpp"
using namespace dalt;
#include "modint.cpp"
using Mi = ModInt998244353;

void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  Vec<Pair<int, int>> segs(M);
  for(int i = 0; i < M; i++) {
    in >> segs[i].first >> segs[i].second;
  }
  //0 - N + 1
  Vec<Vec<int>> count(N + 2, Vec<int>(N + 2));
  for(int i = 0; i <= N + 1; i++) {
    for(int j = i; j <= N + 1; j++) {
      for(auto &seg : segs) {
        if(seg.first > i && seg.second < j) {
          count[i][j]++;
        }
      }
    }
  }
  Vec<Vec<Vec<Mi>>> dp(N + 2, Vec<Vec<Mi>>(M + 1, Vec<Mi>(2)));
  dp[0][0][1] = 1;
  for (int lastLoc = 0; lastLoc <= N + 1; lastLoc++) {
    for (int numElement = 0; numElement <= M; numElement++) {
      for (int sign = 0; sign < 2; sign++) {
        DebugFmtln("dp[%d][%d][%d] = %d", lastLoc, numElement, sign, dp[lastLoc][numElement][sign].value);
        if (dp[lastLoc][numElement][sign] == 0) {
          continue;
        }
        for(int nextLoc = lastLoc + 1; nextLoc <= N + 1; nextLoc++) {
          dp[nextLoc][numElement + count[lastLoc][nextLoc]][sign ^ 1] += dp[lastLoc][numElement][sign];
        }
      }
    }
  }
  Mi ans = 0;
  Mi inv_M = Mi(M).possible_inv();
  for(int numElement = 0; numElement < M; numElement++) {
    for(int sign = 0; sign < 2; sign++) {
      auto prob = Mi(M - numElement) * inv_M;
      auto expect = Mi(1) / prob;
      if(sign == 0) {
        expect = -expect;
      }
      auto contrib = expect * dp[N + 1][numElement][sign];
      ans += contrib;
    }
  }
  out << ans << '\n';
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}