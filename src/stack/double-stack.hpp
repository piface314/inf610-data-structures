#ifndef DOUBLE_STACK_H
#define DOUBLE_STACK_H

#include "stack.hpp"
#include <sstream>


template <typename T>
class DoubleStack : public Stack<T> {
private:
    T *array;
    size_t n_left, n_right, n_max;
public:
    DoubleStack(size_t n_max) {
        this->array = new T[n_max];
        this->n_left = this->n_right = 0;
        this->n_max = n_max;
    }

    ~DoubleStack() {
        delete array;
    }

    size_t size() { return n_left; }
    size_t size_r() { return n_right; }
    bool empty() { return n_left == 0; }
    bool empty_r() { return n_right == 0; }
    bool full() { return n_left + n_right == n_max; }

    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("left stack is empty");
        return array[n_left-1];
    }

    // O(1)
    T peek_r() {
        if (empty_r())
            throw std::runtime_error("right stack is empty");
        return array[n_max-n_right];
    }
    
    // O(1)
    void push(T item) {
        if (full())
            throw std::runtime_error("stack is full");
        array[n_left++] = item;
    }

    // O(1)
    void push_r(T item) {
        if (full())
            throw std::runtime_error("stack is full");
        array[n_max - (++n_right)] = item;
    }
    
    // O(1)
    T pop() {
        if (empty())
            throw std::runtime_error("left stack is empty");
        return array[--n_left];
    }

    // O(1)
    T pop_r() {
        if (empty_r())
            throw std::runtime_error("right stack is empty");
        return array[n_max - (n_right--)];
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "DoubleStack(";
        for (size_t i = 0; i < n_max; ++i)
            if (n_left <= i && i < n_max - n_right)
                ss << (i ? ",_" : "_");
            else
                ss << (i ? "," : "") << array[i];
        ss << ")";
        return ss.str();
    }
};

#endif