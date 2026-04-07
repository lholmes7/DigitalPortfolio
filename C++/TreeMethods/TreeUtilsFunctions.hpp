#pragma once
#include "SmartTree.hpp"

template <typename T>
int countNodes(const Tree<T>& tree) {
    if (tree.isEmpty()) return 0;
    return 1 + countNodes(tree.left()) + countNodes(tree.right());
}

template <typename T>
int countInternalNodes(const Tree<T>& tree) {
    if (tree.isEmpty()) return 0;
    if (tree.left().isEmpty() && tree.right().isEmpty()) return 0;
    return 1 + countInternalNodes(tree.left()) + countInternalNodes(tree.right());
}

template <typename T>
void computeExternalPathLength(const Tree<T>& tree, int depth, int& total) {
    if (tree.isEmpty()) return;

    if (tree.left().isEmpty() && tree.right().isEmpty()) {
        total += depth;
    }
    else {
        computeExternalPathLength(tree.left(), depth + 1, total);
        computeExternalPathLength(tree.right(), depth + 1, total);
    }
}
