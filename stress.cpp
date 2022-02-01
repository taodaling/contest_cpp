#pragma once
#include "solver.cpp"
#include "stress_external_member.cpp"

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
    Stderr << "INPUT:\n" << in << std::endl;
    StringStream solver_out;
    StringStream stress_out;
    StringStream solver_in = StringStream(in);
    StringStream stress_in = StringStream(in);
    StressSolve(stress_in, stress_out);
    SolveMulti(solver_in, solver_out);
    String match_res = StressMatch(stress_out.str(), solver_out.str());
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