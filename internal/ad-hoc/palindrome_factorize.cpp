#pragma once
#include "../eertree.cpp"
namespace dalt {
namespace adhoc {
/// @brief credited to https://arxiv.org/pdf/1506.04862.pdf
/// @param N length of s
/// @param s string
/// @return ret[i] is the minimum factorization number of pre(s, i + 1)
Vec<Pair<int, int>> FactorizePalindrome(int N, const Indexer<int> &s) {
  seq::Eertree tree(N);
  using Node = seq::Eertree::Node;
  Vec<Node*> max_suf;
  max_suf.reserve(N);
  for (int i = 0; i < N; i++) {
    tree.push_back(s(i));
    max_suf.push_back(tree.back_build_last);
  }
  var &all = tree.all;
  Vec<int> diff(Size(all));
  Vec<Node*> series_link(Size(all));
  for (int i = 0; i < Size(all); i++) {
    var &node = all[i];
    diff[i] = node->len;
    diff[i] -= node->fail->len;
    series_link[i] = node->fail;
    if (node->fail->id >= 0 && diff[i] == diff[node->fail->id]) {
      series_link[i] = series_link[node->fail->id];
    }
  }
  Vec<Pair<int, int>> tree_mem(N);
  Vec<Pair<int, int>> ans(N);
  int n;
  var get_min = [&](Node *v) {
    int index = n - (series_link[v->id]->len + diff[v->id]);
    tree_mem[v->id] = MakePair(index < 0 ? 0 : ans[index].first, index);
    if(v->fail->id >= 0 && diff[v->id] == diff[v->fail->id]) {
      tree_mem[v->id] = Min(tree_mem[v->id], tree_mem[v->fail->id]);
    }
    return MakePair(tree_mem[v->id].first + 1, tree_mem[v->id].second);
  };
  int inf = (int)2e9;
  for(n = 0; n < N; n++) {
    var best = MakePair(inf, -1);
    for(var node = max_suf[n]; node->id >= 0; node = series_link[node->id]) {
      best = Min(best, get_min(node));
    }
    ans[n] = best;
  }
  return ans;
}
/// @brief credited to https://arxiv.org/pdf/1506.04862.pdf
/// @param N length of s
/// @param s string
/// @return ret[i].first is the minimum even factorization number of pre(s, i + 1), ret[i].second is the minimum odd factorization number of pre(s, i + 1)
Vec<Pair<int, int>> FactorizePalindrome2(int N, const Indexer<int> &s) {
  seq::Eertree tree(N);
  using Node = seq::Eertree::Node;
  Vec<Node *> max_suf;
  max_suf.reserve(N);
  for (int i = 0; i < N; i++) {
    tree.push_back(s(i));
    max_suf.push_back(tree.back_build_last);
  }
  var &all = tree.all;
  Vec<int> diff(Size(all));
  Vec<Node *> series_link(Size(all));
  for (int i = 0; i < Size(all); i++) {
    var &node = all[i];
    diff[i] = node->len;
    diff[i] -= node->fail->len;
    series_link[i] = node->fail;
    if (node->fail->id >= 0 && diff[i] == diff[node->fail->id]) {
      series_link[i] = series_link[node->fail->id];
    }
  }
  Vec<Pair<int, int>> tree_mem(N);
  Vec<Pair<int, int>> ans(N);
  int n;
  int inf = (int)2e9;
  var get_min = [&](Node *v) {
    int index = n - (series_link[v->id]->len + diff[v->id]);
    tree_mem[v->id] = index < 0 ? MakePair(0, inf) : ans[index];
    if (v->fail->id >= 0 && diff[v->id] == diff[v->fail->id]) {
      tree_mem[v->id].first = Min(tree_mem[v->id].first, tree_mem[v->fail->id].first);
      tree_mem[v->id].second = Min(tree_mem[v->id].second, tree_mem[v->fail->id].second);
    }
    return tree_mem[v->id];
  };
  for (n = 0; n < N; n++) {
    Pair<int, int> best = MakePair(inf, inf);
    for (var node = max_suf[n]; node->id >= 0; node = series_link[node->id]) {
      var min = get_min(node);
      best.first = Min(best.first, min.first);
      best.second = Min(best.second, min.second);
    }
    ans[n] = MakePair(best.second + 1, best.first + 1);
  }
  for(int i = 0; i < N; i++) {
    if(ans[i].first >= inf) {
      ans[i].first = -1;
    }
    if(ans[i].second >= inf) {
      ans[i].second = -1;
    }
  }
  return ans;
}
}  // namespace adhoc
}  // namespace dalt