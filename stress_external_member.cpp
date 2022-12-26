#include "solver.cpp"
namespace stress {
void StressSolve(IStream &in, OStream &out) {
  int N;
  in >> N;
  int M = 5;
  Vec<Vec<int>> mat(M, Vec<int>(M));
  for(int i = 0; i < N; i++) {
    int l, d, r, u;
    in >> l >> d >> r >> u;
    for(int x = l; x < r; x++) {
      for(int y = d; y < u; y++) {
        mat[x][y]++;
      }
    }
  }
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < M; j++) {
      Stderr << mat[i][j];
    }
    Stderr << '\n';
  }
  int ans = 0;
  for(var &row : mat) {
    for(var x : row) {
      ans += x > 0;
    }
  }
  out << ans;
}

void StressGenerate(int test_id, std::mt19937 &mt, OStream &out) {
  int N = random_choice(1, 2, mt);
  out << N << '\n';
  int M = 5;

  for(int i = 0; i < N; i++) {
    int l =  random_choice(0, M - 1, mt);
    int r =  random_choice(0, M - 1, mt);
    int d =  random_choice(0, M - 1, mt);
    int u =  random_choice(0, M - 1, mt);
    if(l > r) {
      Swap(l, r);
    } 
    if(d > u) {
      Swap(d, u);
    }
    Assert(l <= r);
    Assert(d <= u);
    out << l << ' ' << d << ' ' << r << ' ' << u << '\n';
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
}