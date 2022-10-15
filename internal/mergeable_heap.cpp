#pragma once
#include "leftist_tree.cpp"
namespace dalt {
#define CLASS_ID -202206092234
template <class T, class C = Less<T>, i64 ID = 0>
struct MergeableHeap {
  using LT = LeftistTree<T, C, ID, CLASS_ID>;
  using Self = MergeableHeap<T, C, ID>;
  LT *root;
  int size;
  static void Register(C comp = C(), T nil = T()) { LT::Register(comp, nil); }
  MergeableHeap() {
    root = LT::NIL;
    size = 0;
  }
  void add(T item) {
    root = LT::Merge(root, new LT(item));
    size++;
  }
  int get_size() const { return size; }
  T peek() const { return root->key; }
  T pop() {
    T ans = peek();
    root = root->pop();
    size--;
    return ans;
  }
  void absorb(Self &data) {
    root = LT::Merge(root, data.root);
    size += data.size;
    data.root = LT::NIL;
    data.size = 0;
  }
  Vec<T> to_vec() const { return root->to_vec(); }
};
#undef CLASS_ID
}  // namespace dalt