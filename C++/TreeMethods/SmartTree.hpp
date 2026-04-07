#pragma once

#include <memory>
#include <utility>  

template <typename T>
class Tree {
private:
    T data;
    std::shared_ptr<Tree<T>> left;
    std::shared_ptr<Tree<T>> right;

public:
    Tree() = default;

    Tree(const T& value) : data(value), left(nullptr), right(nullptr) {}

    Tree(const T& value, const Tree<T>& leftTree, const Tree<T>& rightTree)
        : data(value),
        left(std::make_shared<Tree<T>>(leftTree)),
        right(std::make_shared<Tree<T>>(rightTree)) {
    }

    const T& getData() const { return data; }
    std::shared_ptr<Tree<T>> getLeft() const { return left; }
    std::shared_ptr<Tree<T>> getRight() const { return right; }

    bool isEmpty() const {
        return left == nullptr && right == nullptr && data == T{};
    }

    bool isLeaf() const {
        return !left && !right;
    }
};
