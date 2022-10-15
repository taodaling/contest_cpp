#pragma once
#include "common.cpp"
namespace dalt {
namespace seq {
  int MaximumRepresentation(int n, const Comparator<int>& cmp) {
    int i = 0;
    int j = i + 1;
    while (j < n) {
      int k = 0;
      while (k < n && !cmp((i + k) % n, (j + k) % n) &&
             cmp((j + k) % n, (i + k) % n)) {
        k++;
      }
      if (!cmp((i + k) % n, (j + k) % n)) {
        j = j + k + 1;
      } else {
        int next = j;
        j = Max(j + 1, i + k + 1);
        i = next;
      }
    }
    return i;
  }
  int MinimumRepresentation(int n, const Comparator<int>& cmp) {
    return MaximumRepresentation(n, [&](var a, var b) {
      return cmp(b, a);
    });
  }
}
}  // namespace dalt