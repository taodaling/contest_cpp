#include "solver.cpp"
#include "stress.cpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  Stdin.tie(0);
  Stdout << std::setiosflags(std::ios::fixed);
  Stdout << std::setprecision(15);
#ifdef STRESS
  Stress();
#else
  SolveMulti(Stdin, Stdout);
#endif
  return 0;
}