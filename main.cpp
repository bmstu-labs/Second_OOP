#include "tree.hpp"

#include <iostream>
int main() {
    Tree<int> a;
    for (int i = 0; i < 5; i++) {
        a.insert(i);
    }

    for (auto i : a.to_array()) {
        std::cout << i << std::endl;
    }

    return 0;
}