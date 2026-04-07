#pragma once
#include <memory>
#include <functional>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class Tree {
private:
    struct Node {
        std::shared_ptr<Node> _lft;
        T _val;
        std::shared_ptr<Node> _rgt;
        std::weak_ptr<Node> _parent;

        Node(std::shared_ptr<Node> lft, T val, std::shared_ptr<Node> rgt)
            : _lft(lft), _val(val), _rgt(rgt) {
        }
    };
    std::shared_ptr<Node> _root;
    explicit Tree(std::shared_ptr<Node> node) : _root(node) {}
public:
    Tree() : _root(nullptr) {}
    Tree(const Tree& other) = default;
    Tree& operator=(const Tree& other) = default;
    Tree(Tree&& other) = default;
    Tree& operator=(Tree&& other) = default;
    ~Tree() = default;
    Tree(Tree lft, T val, Tree rgt) {
        auto node = std::make_shared<Node>(lft._root, val, rgt._root);
        if (node->_lft) node->_lft->_parent = node;
        if (node->_rgt) node->_rgt->_parent = node;
        _root = node;
    }
    Tree(std::initializer_list<T> init) {
        Tree t;
        for (T val : init)
            t = t.insert(val);
        *this = t;
    }
    bool isEmpty() const {
        return !_root;
    }
    size_t size() const {
        if (!_root) return 0;
        return 1 + Tree(_root->_lft).size() + Tree(_root->_rgt).size();
    }
    T root() const {
        if (!_root) throw std::runtime_error("Empty tree");
        return _root->_val;
    }
    Tree left() const {
        return Tree(_root ? _root->_lft : nullptr);
    }
    Tree right() const {
        return Tree(_root ? _root->_rgt : nullptr);
    }
    template <typename Compare = std::greater<T>>
    Tree insert(T x, Compare comp = std::greater<T>()) const {
        if (!_root)
            return Tree(std::make_shared<Node>(nullptr, x, nullptr));
        if (comp(_root->_val, x)) {
            Tree newLeft = Tree(_root->_lft).insert(x, comp);
            auto newRoot = std::make_shared<Node>(newLeft._root, _root->_val, _root->_rgt);
            if (newRoot->_lft) newRoot->_lft->_parent = newRoot;
            if (newRoot->_rgt) newRoot->_rgt->_parent = newRoot;
            return Tree(newRoot);
        }
        else {
            Tree newRight = Tree(_root->_rgt).insert(x, comp);
            auto newRoot = std::make_shared<Node>(_root->_lft, _root->_val, newRight._root);
            if (newRoot->_lft) newRoot->_lft->_parent = newRoot;
            if (newRoot->_rgt) newRoot->_rgt->_parent = newRoot;
            return Tree(newRoot);
        }
    }
    template <typename Compare = std::greater<T>>
    bool member(T x, Compare comp = std::greater<T>()) const {
        if (!_root) return false;
        if (_root->_val == x) return true;
        if (comp(_root->_val, x))
            return Tree(_root->_lft).member(x, comp);
        else
            return Tree(_root->_rgt).member(x, comp);
    }
    template<typename Compare = std::greater<T>>
    bool find(T x, Tree& subtreeWhereFound, Compare comp = std::greater<T>()) const {
        if (!_root) return false;
        if (_root->_val == x) {
            subtreeWhereFound = *this;
            return true;
        }
        if (comp(_root->_val, x))
            return Tree(_root->_lft).find(x, subtreeWhereFound, comp);
        else
            return Tree(_root->_rgt).find(x, subtreeWhereFound, comp);
    }
    void preorder(std::function<void(T)> visit) const {
        if (!_root) return;
        visit(_root->_val);
        Tree(_root->_lft).preorder(visit);
        Tree(_root->_rgt).preorder(visit);
    }
    void inorder(std::function<void(T)> visit) const {
        if (!_root) return;
        Tree(_root->_lft).inorder(visit);
        visit(_root->_val);
        Tree(_root->_rgt).inorder(visit);
    }
    void postorder(std::function<void(T)> visit) const {
        if (!_root) return;
        Tree(_root->_lft).postorder(visit);
        Tree(_root->_rgt).postorder(visit);
        visit(_root->_val);
    }
    T parentValue() const {
        if (!_root) throw std::runtime_error("Empty tree");
        if (_root->_parent.expired()) throw std::runtime_error("No parent");
        return _root->_parent.lock()->_val;
    }
};