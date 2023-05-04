#include "math.cpp"
#include "solver.cpp"
namespace stress {
void StressSolve(IStream &in, OStream &out) {
  Trace(generate correct result);
  int N, M, Q;
  in >> N >> M >> Q;
  struct Item {
    int l, r, x;
  };
  Vec<Item> items;
  for (int i = 0; i < Q; i++) {
    int l, r, x;
    in >> l >> r >> x;
    l--;
    r--;
    items.push_back(Item{.l = l, .r = r, .x = x});
  }
  var dfs = [&](var &dfs, Vec<int> &values) -> int {
    if (Size(values) == N) {
      for (var &item : items) {
        int max = 0;
        for (int i = item.l; i <= item.r; i++) {
          Chmax(max, values[i]);
        }
        if (max != item.x) {
          return 0;
        }
      }
      return 1;
    }
    int ans = 0;
    for (int i = 0; i <= M; i++) {
      values.push_back(i);
      ans += dfs(dfs, values);
      values.pop_back();
    }
    return ans;
  };
  Vec<int> values;
  int ans = dfs(dfs, values);
  out << ans << '\n';
}

void StressGenerate(int test_id, std::mt19937 &mt, OStream &out) {
  Trace(generating testcase);
  int N = random_choice(1, 3, mt);
  int M = random_choice(1, 3, mt);
  int Q = random_choice(1, 3, mt);
  out << N << " " << M << " " << Q << '\n';
  for (int i = 0; i < Q; i++) {
    int l = random_choice(1, N, mt);
    int r = random_choice(1, N, mt);
    int x = random_choice(1, M, mt);
    if (l > r) {
      Swap(l, r);
    }
    out << l << " " << r << " " << x << '\n';
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