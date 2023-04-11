#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>

template <typename T>
class Heap {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T peek() = 0;
    virtual void push(T item) = 0;
    virtual T pop() = 0;
    virtual std::string to_string() = 0;
    friend std::ostream& operator<<(std::ostream& os, Heap<T>& heap) {
        return os << heap.to_string();
    }
};

void test_heap(Heap<char> &heap);

#endif