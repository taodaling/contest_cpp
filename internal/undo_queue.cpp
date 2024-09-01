#pragma once
#include "undo_op.cpp"
namespace dalt {
template<class T>
class UndoQueue {
 private:
  Deque<FlaggedCommutativeUndoOperation<T>> dq;
  Deque<FlaggedCommutativeUndoOperation<T>> bufA;
  Deque<FlaggedCommutativeUndoOperation<T>> bufB;
  void pushAndDo(FlaggedCommutativeUndoOperation<T> op) {
    op.apply(op.context);
    dq.push_back(op);
  }
  void popAndUndo() {
    FlaggedCommutativeUndoOperation<T> ans = dq.back();
    dq.pop_back();
    ans.undo(ans.context);
    if (ans.flag) {
      bufA.push_back(ans);
    } else {
      bufB.push_back(ans);
    }
  }

 public:
  UndoQueue() {}

  void add(Consumer<T&> apply, Consumer<T&> undo) {
    FlaggedCommutativeUndoOperation<T> op;
    op.apply = apply;
    op.undo = undo;
    op.context = T();
    op.flag = false;
    pushAndDo(op);
  }

  FlaggedCommutativeUndoOperation<T> remove() {
    if (!dq.back().flag) {
      popAndUndo();
      while (!dq.empty() && bufB.size() != bufA.size()) {
        popAndUndo();
      }
      if (dq.empty()) {
        while (!bufB.empty()) {
          FlaggedCommutativeUndoOperation<T> ans = bufB.front();
          bufB.pop_front();
          ans.flag = true;
          pushAndDo(ans);
        }
      } else {
        while (!bufB.empty()) {
          FlaggedCommutativeUndoOperation<T> ans = bufB.back();
          bufB.pop_back();
          pushAndDo(ans);
        }
      }
      while (!bufA.empty()) {
        pushAndDo(bufA.back());
        bufA.pop_back();
      }
    }

    FlaggedCommutativeUndoOperation<T> ans = dq.back();
    dq.pop_back();
    ans.undo(ans.context);
    return ans;
  }

  int size() { return dq.size(); }

  bool empty() { return dq.empty(); }

  void clear() {
    while (!empty()) {
      popAndUndo();
    }
    bufA.clear();
    bufB.clear();
  }
};

}  // namespace dalt