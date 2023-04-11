#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H

#include "deque.hpp"
#include <sstream>

template <typename T>
class DequeNode {
public:
    T item;
    DequeNode<T> *next, *prev;
    DequeNode() : next(NULL), prev(NULL) {}
    DequeNode(T item) : item(item), next(NULL), prev(NULL) {}
    ~DequeNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class LinkedDeque : public Deque<T> {
private:
    DequeNode<T> *head, *last;
    size_t n;
public:
    LinkedDeque() {
        this->head = this->last = new DequeNode<T>();
        this->n = 0;
    }
    ~LinkedDeque() {
        delete head;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek_front() {
        if (empty())
            throw std::runtime_error("deque is empty");
        return head->next->item;
    }

    // O(1)
    T peek_back() {
        if (empty())
            throw std::runtime_error("deque is empty");
        return last->item;
    }

    // O(1)
    void enqueue_front(T item) {
        if (n == 0)
            return enqueue_back(item);
        DequeNode<T> *inserted = new DequeNode<T>(item);
        head->next->prev = inserted;
        inserted->next = head->next;
        inserted->prev = head;
        head->next = inserted;
        ++n;
    }

    // O(1)
    void enqueue_back(T item) {
        DequeNode<T> *inserted = new DequeNode<T>(item);
        last->next = inserted;
        inserted->prev = last;
        last = inserted;
        ++n;
    }

    // O(1)
    T dequeue_front() {
        if (empty())
            throw std::runtime_error("deque is empty");
        DequeNode<T> *removed = head->next;
        if (removed->next != NULL)
            removed->next->prev = head;
        head->next = removed->next;
        if (head->next == NULL)
            last = head;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    // O(1)
    T dequeue_back() {
        if (empty())
            throw std::runtime_error("deque is empty");
        DequeNode<T> *removed = last;
        removed->prev->next = NULL;
        last = removed->prev;
        --n;
        T item = removed->item;
        delete removed;
        return item;   
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        if (size())
            ss << peek_front() << "..." << peek_back();
        else
            ss << "_..._";
        ss << "] : LinkedDeque(<@->";
        for (DequeNode<T> *current = head->next; current != NULL; current = current->next)
            ss << "<" << current->item << "-> ";
        ss << ")";
        return ss.str();
    }
};


#endif