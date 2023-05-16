#pragma once
#include "common.cpp"
using namespace dalt;
#include "modint.cpp"
using Mi = ModInt998244353;
#include "matrix.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  Vec<i64> A(N);
  in >> A;

  var mock_once = [&]() {
    Vec<i64> cnt(N);
    int time = 0;
    while(true) {
      time++;
      int pt = random_choice(0, N - 1);
      bool ok = true;
      for(int i = 0; i < N; i++) {
        cnt[i] += 1;
        if(i == pt) {
          cnt[i] = 0;
        }
        if(cnt[i] < A[i]) {
          ok = false;
        }
      }
      if(ok) {
        return time;
      }
    }
  };
  var mock = [&]() {
    long sum = 0;
    for(int i = 0; i < 10000; i++) {
      sum += mock_once();
    }
    Debug(sum / double(10000));
  };

  DebugRun(
    //mock();
  );

  Vec<i64> stage(N);
  for(int i = 1; i < N; i++) {
    stage[i] = A[i] - A[i - 1];
    Assert(stage[i] >= 0);
  }
  Reverse(stage.begin() + 1, stage.end());
  using Mat = math::Matrix<Mi>;
  Mat last_ans(1, Vec<Mi> {0, 1, 1});
  Mat pre_sum(1, Vec<Mi>(3));
  for(int i = 1; i < N; i++) {
    Debug(i);
    pre_sum += last_ans;
    Mat T(3, Vec<Mi> {
      N, 0, -Mi(N) - pre_sum[0][0],
      0, N, -pre_sum[1][0],
      0, 0, 0,
    });
    T /= N - i;
    Debug(T.to_vec());
    T[2][2] = 1;
    Mat compress_T = T.pow(stage[i]);
    last_ans = compress_T * last_ans;
    Debug(last_ans.to_vec());
  }
  var a = last_ans[0][0];
  var b = last_ans[1][0];
  //a + xb = 0
  //x = -a / b;
  var x = -a / b;
  out << x << '\n';
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