#include "SmartTree.hpp"
#include <queue>
#include <functional>

template <typename T>
void level_order_traversal(const Tree<T>& tree, const std::function<void(T)>& visit) {
    if (tree.isEmpty()) return;

    std::queue<Tree<T>> q;
    q.push(tree);

    while (!q.empty()) {
        Tree<T> current = q.front();
        q.pop();

        visit(current.root());

        if (!current.left().isEmpty()) q.push(current.left());
        if (!current.right().isEmpty()) q.push(current.right());
    }
}

template <typename T>
Tree<T> prune(const Tree<T>& tree) {
    if (tree.isEmpty()) return Tree<T>();
    if (tree.left().isEmpty() && tree.right().isEmpty()) return Tree<T>();
    return Tree<T>(prune(tree.left()), tree.root(), prune(tree.right()));
}
