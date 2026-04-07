#include "SmartTree.hpp"
#include <iostream>
#include <string>

int main() {
    Tree<std::string> tree("root");

    if (!tree.isEmpty()) {
        std::cout << "Tree is not empty.\n";
    }

    if (tree.isLeaf()) {
        std::cout << "Tree is a leaf node.\n";
    }

    return 0;
}
