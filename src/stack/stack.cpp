#include "stack.hpp"

void test_stack(Stack<char> &stack) {
    std::cout << stack << std::endl;
    
    std::cout << "Pushing C, A, T, S:\n";
    stack.push('C');
    stack.push('A');
    stack.push('T');
    stack.push('S');
    std::cout << stack << std::endl;
    
    std::cout << "Popping 1:\n";
    stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing M and Z:\n";
    stack.push('M');
    stack.push('Z');
    std::cout << stack << std::endl;

    std::cout << "Element at top?:\n";
    std::cout << stack.peek() << std::endl;

    std::cout << "Popping 2:\n";
    stack.pop();
    stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing X, L, R:\n";
    stack.push('X');
    stack.push('L');
    stack.push('R');
    std::cout << stack << std::endl;

    std::cout << "Popping all:\n";
    while (stack.size() > 0)
        stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing P and Q:\n";
    stack.push('P');
    stack.push('Q');
    std::cout << stack << std::endl;

    std::cout << std::endl;
}