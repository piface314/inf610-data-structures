#ifndef STATIC_DEQUE_H
#define STATIC_DEQUE_H

#include "deque.hpp"
#include <sstream>

template <typename T>
class StaticDeque : public Deque<T> {
private:
    T *array;
    size_t n_max, n, front, back;
    size_t prev(size_t i) { return i == 0 ? n_max-1 : (i-1) % n_max; }
    size_t next(size_t i) { return (i + 1) % n_max; }
public:
    StaticDeque(size_t n_max) {
        this->n = this->front = this->back = 0;
        this->n_max = n_max;
        this->array = new T[n_max];
    }
    ~StaticDeque() {
        delete array;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek_front() {
        if (empty())
            throw std::runtime_error("deque is empty");
        return array[front];
    }

    // O(1)
    T peek_back() {
        if (empty())
            throw std::runtime_error("deque is empty");
        return array[prev(back)];
    }

    // O(1)
    void enqueue_front(T item) {
        if (n == n_max)
            throw std::runtime_error("deque is full");
        front = prev(front);
        array[front] = item;
        ++n;
    }

    // O(1)
    void enqueue_back(T item) {
        if (n == n_max)
            throw std::runtime_error("deque is full");
        ++n;
        array[back] = item;
        back = next(back);
    }

    // O(1)
    T dequeue_front() {
        if (empty())
            throw std::runtime_error("deque is empty");
        --n;
        T removed = array[front];
        front = next(front);
        return removed;
    }

    // O(1)
    T dequeue_back() {
        if (empty())
            throw std::runtime_error("deque is empty");
        back = prev(back);
        T removed = array[back];
        --n;
        return removed;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        if (size())
            ss << peek_front() << "..." << peek_back();
        else
            ss << "_..._";
        ss << "] : StaticDeque[" << front << "," << back << "](";
        for (size_t i = 0; i < n_max; ++i)
            if (n == n_max || (front <= back ? front <= i && i < back : front <= i || i < back))
                ss << (i ? "," : "") << array[i];
            else
                ss << (i ? ",_" : "_");
        ss << ")";
        return ss.str();
    }
};


#endif