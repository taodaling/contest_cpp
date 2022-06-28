#pragma once
#include "common.cpp"
namespace dalt {
#define CLASS_ID -202206092222
template <class T, class C = Less<T>, i64 ID = 0, i64 CID = 0>
struct LeftistTree {
  using Self = LeftistTree<T, C, ID, CID>;
  Self *left;
  Self *right;
  int dist;
  static Self *NIL;
  static C comp;
  T key;

 public:
  LeftistTree(T _key) : key(_key) {
    dist = 0;
    left = right = NIL;
  }
  static void Register(C comp = C(), T nil = T()) {
    if (NIL) {
      delete NIL;
    }
    NIL = new Self(nil);
    NIL->left = NIL->right = NIL;
    NIL->dist = -1;
    NIL->key = nil;
  }
  static Self* Merge(Self* a, Self *b) {
    if (a == NIL) {
      return b;
    } else if (b == NIL) {
      return a;
    }
    if (comp(b->key, a->key)) {
      Swap(a, b);
    }
    a->right = Merge(a->right, b);
    if (a->left->dist < a->right->dist) {
      Swap(a->left, a->right);
    }
    a->dist = a->right->dist + 1;
    return a;
  }
  bool empty() const {
    return this == NIL;
  }
  Self *pop() {
    auto ans = Merge(left, right);
    left = right = NIL;
    return ans;
  }

  T peek() const {
    return key;
  }

  Vec<T> to_vec() const {
    Vec<T> ans;
    auto dfs = [&](auto& rec, const Self *root) {
      if(root == NIL) {
        return;
      }
      ans.push_back(root->key);
      rec(rec, root->left);
      rec(rec, root->right);
    };
    dfs(dfs, this);
    //Sort(All(ans), comp);
    return ans;
  }
};
template <class T, class C, i64 ID, i64 CID>
LeftistTree<T, C, ID, CID> *LeftistTree<T, C, ID, CID>::NIL = NULL;
template <class T, class C, i64 ID, i64 CID>
C LeftistTree<T, C, ID, CID>::comp;
#undef CLASS_ID
}