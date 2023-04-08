#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.hpp"
#include <sstream>

template <typename T>
class StackNode {
public:
    T item;
    StackNode<T> *next;
    StackNode() : next(NULL) {}
    StackNode(T item) : item(item), next(NULL) {}
    ~StackNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class LinkedStack : public Stack<T> {
private:
    StackNode<T> *head;
    size_t n;
public:
    LinkedStack() {
        this->head = new StackNode<T>();
        this->n = 0;
    }

    ~LinkedStack() {
        delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // O(1)
    T peek() {
        if (empty())
            throw std::runtime_error("stack is empty");
        return head->next->item;
    }

    // O(1)
    void push(T item) {
        StackNode<T> *inserted = new StackNode<T>(item);
        inserted->next = head->next;
        head->next = inserted;
        ++n;
    }

    // O(1)
    T pop()  {
        if (empty())
            throw std::runtime_error("stack is empty");
        StackNode<T> *removed = NULL;
        removed = head->next;
        head->next = removed->next;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "LinkedStack(@-> ";
        for (StackNode<T> *current = head->next; current != NULL; current = current->next)
            ss << current->item << " -> ";
        ss << ")";
        return ss.str();
    }
};

#endif