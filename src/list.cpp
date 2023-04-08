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

    std::cout << "Inserting M at end and Z at begin:\n";
    list.insert(list.size(), 'M');
    list.insert(0, 'Z');
    std::cout << list << std::endl;

    std::cout << "Inserting X, L, R at next to last:\n";
    list.insert(list.size()-1, 'X');
    list.insert(list.size()-1, 'L');
    list.insert(list.size()-1, 'R');
    std::cout << list << std::endl;

    std::cout << "Element at 3?:\n";
    std::cout << list.lookup(3) << std::endl;
    std::cout << "Element at previous from last?:\n";
    std::cout << list.lookup(list.size() - 2) << std::endl;

    std::cout << "Removing from begin and 2:\n";
    list.remove(0);
    list.remove(2);
    std::cout << list << std::endl;

    std::cout << "Removing all:\n";
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.remove(0);
    std::cout << list << std::endl;

    std::cout << "Inserting P, Q at end:\n";
    list.insert(list.size(), 'P');
    list.insert(list.size(), 'Q');
    std::cout << list << std::endl;

    std::cout << std::endl;
}