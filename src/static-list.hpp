#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "list.hpp"
#include <sstream>


template <typename T>
class StaticList : public List<T> {
private:
    T *array;
    size_t n_max;
    size_t n;
public:
    StaticList(size_t n_max) {
        this->n = 0;
        this->n_max = n_max;
        this->array = new T[n_max];
    }

    ~StaticList() {
        delete array;
    }

    size_t size() { return n; }

    // O(1)
    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        return array[i];
    }
    
    // O(n)
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        if (n == n_max)
            throw std::runtime_error("list is full");
        for (size_t j = n++; j > i; --j)
            array[j] = array[j-1];
        array[i] = item;
    }
    
    // O(n)
    void remove(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        if (n == 0)
            throw std::runtime_error("list is empty");
        for (size_t j = i; j < n; ++j)
            array[j] = array[j+1];
        --n;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "StaticList(";
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