#include "solver.cpp"
namespace stress {
void StressSolve(int test_id, IStream &in, OStream &out) {
  int K, N, M;
  in >> K >> N >> M;
  Vec<int> data(N);
  in >> data;
  Vec<int> cnts(1 << M);
  var dfs = [&](var &dfs, int offset, int val, int take) {
    if (take > K) {
      return;
    }
    if (offset == N) {
      if (take != K) {
        return;
      }
      cnts[val]++;
      return;
    }
    dfs(dfs, offset + 1, val, take);
    dfs(dfs, offset + 1, val ^ data[offset], take + 1);
  };
  dfs(dfs, 0, 0, 0);
  for (var x : cnts) {
    out << x << ' ';
  }
}

void StressGenerate(int test_id, std::mt19937 &mt, OStream &out) {
  int K = random_choice(1, 5, mt);
  int N = random_choice(1, 10, mt);
  int M = random_choice(1, 10, mt);
  out << K << ' ' << N << ' ' << M << '\n';
  for (int i = 0; i < N; i++) {
    out << random_choice(0, (1 << M) - 1, mt) << ' ';
  }
}

String StressMatch(IStream &input, IStream &ai, IStream &bi) {
  String x, y;
  bool succ_x, succ_y;
  while (true) {
    succ_x = !(ai >> x).fail();
    succ_y = !(bi >> y).fail();
    if (!succ_x || !succ_y) {
      if (succ_x == succ_y) {
        return "";
      } else {
        return "different output format";
      }
    }
    if (x != y) {
      return "mismatch: " + x + " | " + y;
    }
  }
}
}  // namespace stress