#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

template <typename T>
class Queue {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T peek() = 0;
    virtual void enqueue(T item) = 0;
    virtual T dequeue() = 0;
    virtual std::string to_string() = 0;
    friend std::ostream& operator<<(std::ostream& os, Queue<T>& queue) {
        return os << queue.to_string();
    }
};

void test_queue(Queue<char> &queue);

#endif