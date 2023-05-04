#pragma once
#include "solver.cpp"
#include "stress_external_member.cpp"
namespace stress {
String StressFormatInput(const String &s) {
  if (s.size() <= 100) {
    return s;
  }
  return s.substr(0, 100) + "...";
}

void Stress() {
  const int R = 10000;
  std::mt19937 mt(0);
  for (int i = 1; i <= R; i++) {
    Stderr << "The " << i << "-th Testcase" << std::endl;
    StringStream input;
    StressGenerate(i, mt, input);
    String in = input.str();
    Stderr << "INPUT:\n" << StressFormatInput(in) << std::endl;
    StringStream solver_out;
    StringStream stress_out;
    StringStream solver_in = StringStream(in);
    StringStream stress_in = StringStream(in);
    StressSolve(stress_in, stress_out);
    SolveMulti(solver_in, solver_out);
    StringStream checker_input = StringStream(in);
    StringStream check_stress_out = StringStream(stress_out.str());
    StringStream check_solver_out = StringStream(solver_out.str());
    String match_res =
        StressMatch(checker_input, check_stress_out, check_solver_out);
    if (match_res != "") {
      Stderr << "\nexpect:\n" << stress_out.str() << std::endl;
      Stderr << "\nactual:\n" << solver_out.str() << std::endl;
      Stderr << "\nerror: " << match_res << std::endl;
      Stderr << "FAIL!" << std::endl;
      exit(1);
    }
  }

  Stderr << "PASS!" << std::endl;
  exit(0);
}
}