#ifndef STATIC_LLIST_H
#define STATIC_LLIST_H

#include "list.hpp"
#include "../stack/static-stack.hpp"
#include <sstream>


template <typename T>
class StaticLinkList : public List<T> {
private:
    T *array;
    size_t *next;
    StaticStack<size_t> free;
    size_t n, n_max;
    size_t first, last;
public:
    StaticLinkList(size_t n_max) : free(n_max) {
        this->n = this->first = this->last = 0;
        this->n_max = n_max;
        this->array = new T[n_max];
        this->next = new size_t[n_max];
        for (size_t i = 0; i < n_max; ++i)
            next[i] = n_max + 1, free.push(n_max - i - 1);
    }

    ~StaticLinkList() {
        delete array;
        delete next;
    }

    size_t size() { return n; }
    virtual bool empty() { return n == 0; }

    // Worst Case: O(n), Best Case: O(1)
    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        if (i == n - 1)
            return array[last];
        size_t j = first;
        while (i--)
            j = next[j];
        return array[j];
    }
    
    // Worst Case: O(n), Best Case: O(1)
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        if (n == n_max)
            throw std::runtime_error("list is full");
        size_t k = free.pop();
        array[k] = item;
        next[k] = n_max;
        if (i == 0) {
            if (n++ == 0)
                last = k;
            else
                next[k] = first;
            first = k;
        } else if (i == n) {
            next[last] = k;
            last = k;
            ++n;
        } else {
            size_t j = first;
            while (--i)
                j = next[j];
            next[k] = next[j];
            next[j] = k;
            ++n;
        }
    }
    
    // Worst Case: O(n), Best Case: O(1)
    T remove(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        if (n == 0)
            throw std::runtime_error("list is empty");
        size_t removed;
        if (i == 0) {
            removed = first;
            first = next[first];
        } else {
            size_t j = first;
            while (--i)
                j = next[j];
            removed = next[j];
            next[j] = next[removed];
            if (removed == last)
                last = j;
        }
        --n;
        free.push(removed);
        next[removed] = n_max + 1;
        return array[removed];
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0, k = first; i < n; ++i, k = next[k])
            ss << (i ? ",": "") << array[k];
        ss << "] : StaticLinkList[" << first << "," << last << "](";
        for (size_t i = 0; i < n_max; ++i)
            if (next[i] < n_max)
                ss << (i ? ",(" : "(") << array[i] << "|" << next[i] << ")";
            else if (next[i] == n_max)
                ss << (i ? ",(" : "(") << array[i] << "|\xB6)";
            else
                ss << (i ? ",_" : "_");
        ss << ")";
        return ss.str();
    }
};

#endif