#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

template <typename T>
class Stack {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T peek() = 0;
    virtual void push(T item) = 0;
    virtual T pop() = 0;
    virtual std::string to_string() = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Stack<T>& stack) {
    return os << stack.to_string();
}

void test_stack(Stack<int> &stack);

#endif