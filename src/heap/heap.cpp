#include "heap.hpp"

void test_heap(Heap<char> &heap) {
    std::cout << heap << std::endl;
    
    std::cout << "Pushing C, A, T, S:\n";
    heap.push('C');
    heap.push('A');
    heap.push('T');
    heap.push('S');
    std::cout << heap << std::endl;
    
    std::cout << "Popping 1:\n";
    heap.pop();
    std::cout << heap << std::endl;

    std::cout << "Pushing M and Z:\n";
    heap.push('M');
    heap.push('Z');
    std::cout << heap << std::endl;

    std::cout << "Element at top?:\n";
    std::cout << heap.peek() << std::endl;

    std::cout << "Popping 2:\n";
    heap.pop();
    heap.pop();
    std::cout << heap << std::endl;

    std::cout << "Pushing X, L, R, W:\n";
    heap.push('X');
    heap.push('L');
    heap.push('R');
    heap.push('W');
    std::cout << heap << std::endl;

    std::cout << "Popping all:\n";
    while (heap.size() > 0)
        heap.pop();
    std::cout << heap << std::endl;

    std::cout << "Pushing P and Q:\n";
    heap.push('P');
    heap.push('Q');
    std::cout << heap << std::endl;

    std::cout << std::endl;
}
