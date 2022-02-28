#pragma once
#include "collection.cpp"
#include "polygon2.cpp"
#include "sort.cpp"
namespace dalt {
namespace geo2 {
// O(n\log_2n)
template <class T>
struct ConvexHull : public Polygon<T> {
  ConvexHull(Polygon<T> polygon, bool include_same_line = false,
             bool is_convex = false)
      : Polygon<T>(Move(polygon)) {
    using Pt = typename Polygon<T>::Pt;
    auto& data = Polygon<T>::data;
    if (is_convex) {
      return;
    }
    int n = data.size();
    if (n <= 1) {
      return;
    }
    for (int i = 1; i < n; i++) {
      if (data[i] >= data[0]) {
        continue;
      }
      Swap(data[0], data[i]);
    }
    auto first = data[0];
    SortByPolarAngleAround<T> sorter(first);
    Sort(data.begin() + 1, data.end(), [&](auto& a, auto& b) {
      int sign = sorter.compare(a, b);
      if (sign < 0 || sign == 0 && Pt::dist2(first, a) < Pt::dist2(first, b)) {
        return true;
      }
      return false;
    });
    if (!include_same_line) {
      i32 shrink_size = 2;
      int wpos = 1;
      for (int i = 1; i < n; i++) {
        int l = i;
        int r = i;
        Pt far = data[l];
        while (r + 1 < n && Pt::orient(first, data[l], data[r + 1]) == 0) {
          r++;
          if (Pt::dist2(first, far) < Pt::dist2(first, data[r])) {
            far = data[r];
          }
        }
        data[wpos++] = far;
        i = r;
      }
      data.resize(wpos);
    } else {
      int r = n - 1;
      int l = r;
      while (l - 1 > 0 && Pt::orient(first, data[l], data[l - 1]) == 0) {
        l--;
      }
      Reverse(data.begin() + l, data.begin() + r + 1);
    }
    // Debug(data);
    Deque<Pt> stack;
    stack.push_back(data[0]);
    for (int i = 1; i < n; i++) {
      while (Size(stack) >= 2) {
        auto last = PopBack<Pt>(stack);
        auto& second = stack.back();
        int sign = Pt::cross(second, data[i], last).sign();
        if (sign < 0 || include_same_line && sign == 0) {
          stack.push_back(last);
          break;
        }
      }
      stack.push_back(data[i]);
    }
    data.clear();
    data.insert(data.begin(), All(stack));
  }
};
}  // namespace geo2
}  // namespace dalt