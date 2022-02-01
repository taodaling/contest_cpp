#pragma once
#include "../common.cpp"
namespace dalt {
struct CartesianTree {
  using Self = CartesianTree;
  Self *left;
  Self *right;
  int index;
  //create cartesian tree from 0..n, the smallest element becomes the root
  //return the root
  static CartesianTree *from(int n, const Comparator<int> &cmp) {
    Deque<Self *> deque;
    for (int i = 0; i < n; i++) {
      Self *self = new Self();
      self->left = self->right = NULL;
      self->index = i;

      while (!deque.empty() && cmp(self->index, deque.back()->index) > 0) {
        auto tail = deque.back();
        deque.pop_back();
        tail->right = self->left;
        self->left = tail;
      }
      deque.push_back(self);
    }
    while (Size(deque) > 1) {
      auto tail = deque.back();
      deque.pop_back();
      deque.back()->right = tail;
    }
    return deque.back();
  }
};
} // namespace dalt