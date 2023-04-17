#include "tree.hpp"

void test_tree(Tree<char,int> &tree) {
    std::cout << tree << std::endl;
    std::cout << "Inserting (C,2), (A,3), (T,5), (S,7), (D,41), (H,43):\n";
    tree.insert('C', 2);
    tree.insert('A', 3);
    tree.insert('T', 5);
    tree.insert('S', 7);
    tree.insert('D', 41);
    tree.insert('H', 43);
    std::cout << tree << std::endl;

    std::cout << "Removing C:\n";
    tree.remove('C');
    std::cout << tree << std::endl;

    std::cout << "Inserting (M,11) and (Z,13):\n";
    tree.insert('M', 11);
    tree.insert('Z', 13);
    std::cout << tree << std::endl;

    std::cout << "Searching A:\n";
    std::cout << *tree.search('A') << std::endl;

    std::cout << "Searching Z:\n";
    std::cout << *tree.search('Z') << std::endl;

    std::cout << "Removing S and M:\n";
    tree.remove('S');
    tree.remove('M');
    std::cout << tree << std::endl;

    std::cout << "Inserting (X,17), (L,19), (R,23), (W,29):\n";
    tree.insert('X', 17);
    tree.insert('L', 19);
    tree.insert('R', 23);
    tree.insert('W', 29);
    std::cout << tree << std::endl;

    std::cout << "Removing T, W:\n";
    tree.remove('T');
    tree.remove('W');
    std::cout << tree << std::endl;

    std::cout << "Inserting (P,31) and (Q,37):\n";
    tree.insert('P', 31);
    tree.insert('Q', 37);
    std::cout << tree << std::endl;
    
    std::cout << std::endl;
}
