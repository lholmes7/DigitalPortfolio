#include <iostream>
#include "TreeUtils.hpp"

void printInt(int x) {
    std::cout << x << " ";
}

int main() {
    Tree<int> t = { 10, 5, 15, 3, 7, 12, 18 };

    std::cout << "Inorder: ";
    t.inorder(printInt);
    std::cout << "\n";

    std::cout << "Level-order: ";
    level_order_traversal<int>(t, printInt);
    std::cout << "\n";

    Tree<int> pruned = prune(t);

    std::cout << "Pruned inorder: ";
    pruned.inorder(printInt);
    std::cout << "\n";

    std::cout << "Pruned level-order: ";
    level_order_traversal<int>(pruned, printInt);
    std::cout << "\n";

    return 0;
}
