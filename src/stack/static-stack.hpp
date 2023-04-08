#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include "stack.hpp"
#include <sstream>


template <typename T>
class StaticStack : public Stack<T> {
private:
    T *array;
    size_t n, n_max;
public:
    StaticStack(size_t n_max) {
        this->array = new T[n_max];
        this->n = 0;
        this->n_max = n_max;
    }

    ~StaticStack() {
        delete array;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("stack is empty");
        return array[n-1];
    }
    
    // O(1)
    void push(T item) {
        if (n == n_max)
            throw std::runtime_error("stack is full");
        array[n++] = item;
    }
    
    // O(1)
    T pop() {
        if (empty())
            throw std::runtime_error("stack is empty");
        return array[--n];
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "StaticStack(";
        for (size_t i = 0; i < n_max; ++i)
            if (i < n)
                ss << (i ? "," : "") << array[i];
            else
                ss << (i ? ",_" : "_");
        ss << ")";
        return ss.str();
    }
};

#endif