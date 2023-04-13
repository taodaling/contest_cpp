#pragma once
#include "line2.cpp"
namespace dalt {
namespace geo2 {
//find the convex specified by lines
//lines[i] means the convex can only exist in the anticlockwise side
template <class T>
enable_if_t<is_near_value_v<T>, Optional<Vec<Line<T>>>> HalfPlaneIntersection(
    Vec<Line<T>> lines, bool close = true, bool is_anticlockwise_sort = false) {
  using L = Line<T>;
  using Pt = Point<T>;
  if (Size(lines) < 2) {
    return {};
  }
  SortByPolarAngleAround<T> sorter;
  if (!is_anticlockwise_sort) {
    Sort(All(lines), [&](const Line<T>& a, const Line<T> &b) { return sorter(a.vec, b.vec); });
  }
  int n = Size(lines);
  Deque<L> deque;
  auto insert = [&](const L& line) -> bool {
    //Debug(line);
    while (Size(deque) >= 2) {
      L tail = deque.back();
      deque.pop_back();
      auto pt = L::intersect(tail, deque.back());
      if (pt.is_none()) {
        continue;
      }
      int side = line.side(pt.value());
      if (side > 0 || (close && side == 0)) {
        deque.push_back(tail);
        break;
      }
      if (Pt::orient(line.vec, deque.back().vec) !=
          Pt::orient(tail.vec, deque.back().vec)) {
        return false;
      }
    }
    while (Size(deque) >= 2) {
      L front = deque.front();
      deque.pop_front();
      auto pt = L::intersect(front, deque.front());
      if (pt.is_none()) {
        continue;
      }
      int side = line.side(pt.value());
      if (side > 0 || (close && side == 0)) {
        deque.push_front(front);
        break;
      }
      if (Pt::orient(line.vec, deque.front().vec) !=
          Pt::orient(front.vec, deque.front().vec)) {
        return false;
      }
    }
    if (Size(deque) == 1 && Pt::orient(line.vec, deque.back().vec) == 0) {
      int side = deque.back().side(line);
      if (!(side > 0 || (close && side == 0))) {
        return false;
      }
    }
    deque.push_back(line);
    return true;
  };
  for (int i = 0; i < n; i++) {
    L& line = lines[i];
    while (i + 1 < n && sorter.compare(line.vec, lines[i + 1].vec) == 0) {
      i++;
      if (line.side(lines[i]) > 0) {
        line = lines[i];
      }
    }
    if (!insert(line)) {
      return {};
    }
    // Debug(line);
    // Debug(deque);
  }
  auto first = deque.front();
   //Debug(deque);
  deque.pop_front();
  if (!insert(first)) {
    return {};
  }
   //Debug(deque);
  Vec<Line<T>> res;
  res.insert(res.end(), All(deque));
  return res;
}
}  // namespace geo2
}  // namespace dalt