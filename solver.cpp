#pragma once
#include "common.cpp"
using namespace dalt;
#include "modint.cpp"
using Mi = ModInt<DynamicModular<>>;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, K, P;
  in >> N >> K >> P;
  Mi::Modular::Register(P);
  MDVec<Mi, 3> prev(K + 1, MDVec<Mi, 2>(N + 1, Vec<Mi>(N + 1)));
  MDVec<Mi, 3> next = prev;
  var update = [&](MDVec<Mi, 2> &data, int b, int t, int l, int r, Mi x) {
    if(t < 0 || r < 0) {
      return;
    }
    data[t][r] += x;
    if (b > 0) {
      data[b - 1][r] -= x;
    }
    if (l > 0) {
      data[t][l - 1] -= x;
    }
    if (b > 0 && l > 0) {
      data[b - 1][l - 1] += x;
    }
  };
  prev[0][N - 1][N - 1] = Mi(1);
  for (int i = 1; i <= N; i++) {
    Debug(i);
    next = MDVec<Mi, 3>(K + 1, MDVec<Mi, 2>(N + 1, Vec<Mi>(N + 1)));
    // post sum
    Line(post sum);
    for (int l = 0; l <= K; l++) {
      for (int row = N; row >= 0; row--) {
        for (int col = N - 1; col >= 0; col--) {
          prev[l][row][col] += prev[l][row][col + 1];
        }

        if (row < N) {
          for (int col = 0; col <= N; col++) {
            prev[l][row][col] += prev[l][row + 1][col];
          }
        }
      }
    }
    if(i == N) {
      break;
    }
    Line(contribute);
    int remain = N - i;
    for (int l = 0; l <= K; l++) {
      for (int x = 0; x <= remain; x++) {
        for (int y = 0; y <= remain; y++) {
          if (prev[l][x][y] == 0) {
            continue;
          }
          // not same
          update(next[l], 0, remain - 1, 0, remain - 1, prev[l][x][y]);
          //same
          if(l < K) {
            update(next[l + 1], 0, x - 1, 0, y - 1, prev[l][x][y]);
            update(next[l + 1], x, remain - 1, y, remain - 1, prev[l][x][y]);
          }
          update(next[l], 0, x - 1, 0, y - 1, -prev[l][x][y]);
          update(next[l], x, remain - 1, y, remain - 1, -prev[l][x][y]);
        }
      }
    }

    prev.swap(next);
  }

  Mi ans = prev[K][0][0];
  out << ans;
}

void SolveMulti(IStream &in, OStream &out) {
  // std::ifstream input("in");
  int num_of_input = 1;
  // in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    // SolveOne(i + 1, input, out);
    SolveOne(i + 1, in, out);
  }
}