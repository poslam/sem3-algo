#include <iostream>
#include "persistent_tree.h"

bool tests() {
    lab2::persistent_tree tree1({1, 2, 3});

    if(tree1.get_elem(0, 0) != 1) return false;
    if(tree1.get_elem(0, 1) != 2) return false;
    if(tree1.get_elem(0, 2) != 3) return false;

    if(tree1.get_sum(0, 0, 2) != 6) return false;
    if(tree1.get_sum(0, 0, 1) != 3) return false;
    if(tree1.get_sum(0, 0, 0) != 1) return false;
    if(tree1.get_sum(0, 1, 2) != 5) return false;

    lab2::persistent_tree tree2({1, 2, 3, 4, 5});

    if(tree2.get_sum(0, 2, 4) != 12) return false;

    tree2.set_elem(0, 0, 6);

    if(tree2.get_elem(0, 0) != 1) return false;
    if(tree2.get_elem(1, 0) != 6) return false;

    if(tree2.get_sum(0, 0, 2) != 6) return false;
    if(tree2.get_sum(1, 0, 2) != 11) return false;

    return true;
}

int main() {
    std::cout << (tests() == true ? "true" : "false");

    return 0;
}