#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "queue.hpp"
#include <sstream>

template <typename T>
class QueueNode {
public:
    T item;
    QueueNode<T> *next;
    QueueNode() : next(NULL) {}
    QueueNode(T item) : item(item), next(NULL) {}
    ~QueueNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class LinkedQueue : public Queue<T> {
private:
    QueueNode<T> *head, *last;
    size_t n;
public:
    LinkedQueue() {
        this->head = this->last = new QueueNode<T>();
        this->n = 0;
    }
    ~LinkedQueue() {
        delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("queue is empty");
        return head->next->item;
    }

    // O(1)
    void enqueue(T item) {
        QueueNode<T> *inserted = new QueueNode<T>(item);
        last->next = inserted;
        last = inserted;
        ++n;
    }

    // O(1)
    T dequeue() {
        if (empty())
            throw std::runtime_error("queue is empty");
        QueueNode<T> *removed = NULL;
        removed = head->next;
        head->next = removed->next;
        if (head->next == NULL) 
            last = head;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        if (size()) ss << peek(); else ss << "_";
        ss << "...] : LinkedQueue(@-> ";
        for (QueueNode<T> *current = head->next; current != NULL; current = current->next)
            ss << current->item << " -> ";
        ss << ")";
        return ss.str();
    }
};

#endif