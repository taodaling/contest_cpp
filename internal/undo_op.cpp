#pragma once
#include "common.cpp"
#include "nil.cpp"
namespace dalt {
    template<class T = Nil>
    struct UndoOperation {
        T context;
        Consumer<T&> apply;
        Consumer<T&> undo;
    };
    template<class T = Nil>
    struct FlaggedCommutativeUndoOperation: UndoOperation<T> {
        bool flag;
    };
    template<class T = Nil>
    struct PriorityCommutativeUndoOperation: UndoOperation<T> {
        i64 priority;
        int offsetToBottom;
    };
}