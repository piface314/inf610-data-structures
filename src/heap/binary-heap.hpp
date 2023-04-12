#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "heap.hpp"
#include <sstream>

template <typename T, typename C = std::less<T>>
class BinaryHeap : public Heap<T> {
private:
    T *array;
    size_t n, n_max;
public:
    BinaryHeap(size_t n_max) {
        this->n = 0;
        this->n_max = n_max;
        this->array = new T[n_max];
    }
    ~BinaryHeap() {
        delete array;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }
    
    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("heap is empty");
        return array[0];
    }

    // Worst case: O(log n), Best case: O(1)
    void push(T item) {
        if (n == n_max)
            throw std::runtime_error("heap is full");
        C more_priority;
        size_t i = n++, i_p;
        while (i) {
            i_p = (i - 1) >> 1;
            if (!more_priority(item, array[i_p]))
                break;
            array[i] = array[i_p];
            i = i_p;
        }
        array[i] = item;
    }

    // Worst case: O(log n), Best case: O(1)
    T pop() {
        if (empty())
            throw std::runtime_error("heap is empty");
        C more_priority;
        T item = array[--n];
        array[n] = array[0];
        size_t i = 0, i_c;
        while ((i_c = (i << 1) + 1) < n) {
            if (i_c + 1 < n && more_priority(array[i_c + 1], array[i_c]))
                ++i_c;
            if (more_priority(item, array[i_c]))
                break;
            array[i] = array[i_c];
            i = i_c;
        }
        array[i] = item;
        return array[n];
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "BinaryHeap(";
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