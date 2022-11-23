#include "solver.cpp"
namespace stress {
void StressSolve(IStream &in, OStream &out) {}

void StressGenerate(int test_id, std::mt19937 &mt, OStream &out) {}

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