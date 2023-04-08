#include "list.hpp"


void test_list(List<int> &list) {
    std::cout << list << std::endl;
    
    std::cout << "Inserting 3, 1, 4, 1 at end:\n";
    list.insert(list.size(), 3);
    list.insert(list.size(), 1);
    list.insert(list.size(), 4);
    list.insert(list.size(), 1);
    std::cout << list << std::endl;
    
    std::cout << "Removing from end:\n";
    list.remove(list.size()-1);
    std::cout << list << std::endl;

    std::cout << "Inserting 0 at begin:\n";
    list.insert(0, 0);
    std::cout << list << std::endl;

    std::cout << "Inserting 9, 7, 5 at 2:\n";
    list.insert(2, 9);
    list.insert(2, 7);
    list.insert(2, 5);
    std::cout << list << std::endl;

    std::cout << "Element at 3?:\n";
    std::cout << list.lookup(3) << std::endl;

    std::cout << "Removing from begin and 2:\n";
    list.remove(0);
    list.remove(2);
    std::cout << list << std::endl;

    std::cout << std::endl;
}