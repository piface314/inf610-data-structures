#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <string>

template <typename T>
class Deque {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T peek_front() = 0;
    virtual T peek_back() = 0;
    virtual void enqueue_front(T item) = 0;
    virtual void enqueue_back(T item) = 0;
    virtual T dequeue_front() = 0;
    virtual T dequeue_back() = 0;
    virtual std::string to_string() = 0;
    friend std::ostream& operator<<(std::ostream& os, Deque<T>& deque) {
        return os << deque.to_string();
    }
};

void test_deque(Deque<char> &deque);

#endif