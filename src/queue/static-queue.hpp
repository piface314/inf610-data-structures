#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include "queue.hpp"
#include <sstream>

template <typename T>
class StaticQueue : public Queue<T> {
private:
    T *array;
    size_t n_max, n, front, back;
public:
    StaticQueue(size_t n_max) {
        this->n = this->front = this->back = 0;
        this->n_max = n_max;
        this->array = new T[n_max];
    }
    ~StaticQueue() {
        delete array;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("queue is empty");
        return array[front];
    }

    // O(1)
    void enqueue(T item) {
        if (n == n_max)
            throw std::runtime_error("queue is full");
        ++n;
        array[back] = item;
        back = (back + 1) % n_max;
    }

    // O(1)
    T dequeue() {
        if (empty())
            throw std::runtime_error("queue is empty");
        --n;
        T removed = array[front];
        front = (front + 1) % n_max;
        return removed;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        if (size()) ss << peek(); else ss << "_";
        ss << "...] : StaticQueue[" << front << "," << back << "](";
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