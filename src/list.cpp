#include "list.hpp"


void test_list(List<char> &list) {
    std::cout << list << std::endl;
    
    std::cout << "Inserting C, A, T, S at end:\n";
    list.insert(list.size(), 'C');
    list.insert(list.size(), 'A');
    list.insert(list.size(), 'T');
    list.insert(list.size(), 'S');
    std::cout << list << std::endl;
    
    std::cout << "Removing from end:\n";
    list.remove(list.size()-1);
    std::cout << list << std::endl;

    std::cout << "Inserting Z at begin:\n";
    list.insert(0, 'Z');
    std::cout << list << std::endl;

    std::cout << "Inserting X, L, R at 2:\n";
    list.insert(2, 'X');
    list.insert(2, 'L');
    list.insert(2, 'R');
    std::cout << list << std::endl;

    std::cout << "Element at 3?:\n";
    std::cout << list.lookup(3) << std::endl;

    std::cout << "Removing from begin and 2:\n";
    list.remove(0);
    list.remove(2);
    std::cout << list << std::endl;

    std::cout << std::endl;
}