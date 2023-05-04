#include "solver.cpp"
#include "stress.cpp"
#include "lazy_initializer.cpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  Stdin.tie(0);
  Stdout << std::setiosflags(std::ios::fixed);
  Stdout << std::setprecision(15);

  for(var &task : dalt::delay_tasks) {
    task();
  }

#ifdef STRESS
  stress::Stress();
#else
  SolveMulti(Stdin, Stdout);
#endif
  return 0;
}