#pragma once
#include "suffix_automaton.cpp"
namespace dalt {
namespace seq {
template <class T = String, class C = char>
i32 LongestCommonSubstr(const Vec<T> &ss) {
  i32 min_index =
      std::min_element(All(ss),
                       [&](auto &a, auto &b) { return Size(a) < Size(b); }) -
      ss.begin();
  SuffixAutomaton<C> sa(Size(ss[min_index]));
  for (char c : ss[min_index]) {
    sa.build(c);
  }
  auto &topo = sa.topo_sort();
  Vec<i32> global_min_match(Size(topo));
  Vec<i32> cur_match(Size(topo));
  for (auto &node : topo) {
    global_min_match[node->id] = node->get_max_length();
  }
  for (int i = 0; i < Size(ss); i++) {
    if (i == min_index) {
      continue;
    }
    auto &s = ss[i];
    auto matcher = sa.matcher();
    Fill(All(cur_match), 0);
    for (char c : s) {
      matcher.match(c);
      i32 id = matcher.match_last->id;
      cur_match[id] = Max(cur_match[id], matcher.match_length);
    }
    for (auto &node : topo) {
      i32 id = node->id;
      if (node->fail) {
        i32 fid = node->fail->id;
        cur_match[fid] = Max(cur_match[fid], cur_match[id]);
      }
      global_min_match[id] = Min(global_min_match[id], cur_match[id]);
    }
  }
  auto ans = *MaxElement(All(global_min_match));
  return ans;
}
}  // namespace seq
}  // namespace dalt