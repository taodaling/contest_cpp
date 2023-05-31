#include "common.cpp"
#include "optional.cpp"
namespace dalt {
template <int N>
struct GuassEliminationMod2 {
 public:
  // R[0] x[0] + ... + R[N - 1] x[N - 1] = R[N]
  using R = std::bitset<N + 1>;

 private:
  Array<R, N + 1> mat;
  int rank;
 public:
  GuassEliminationMod2() {}
  bool add_clause(R e) {
    for (int i = 0; i <= N; i++) {
      if (e[i]) {
        if (mat[i][i]) {
          e ^= mat[i];
        } else {
          mat[i] = e;
          rank++;
          return true;
        }
      }
    }
    return false;
  }
  int get_rank() const {
    return rank;
  }
  bool has_solution() const {
    return !mat[N][N];
  }
  Optional<R> get_solution() const {
    if(!has_solution()) {
      return {};
    }
    R ans;
    ans[N] = true;
    for(int i = N - 1; i >= 0; i--) {
      ans[i] = true;
      if(!mat[i][i]) {
        ans[i] = false;
        continue;
      }
      if((ans & mat[i]).count() & 1) {
        ans[i] = false;
      }
    }
    ans[N] = false;
    return ans;
  }
};
}