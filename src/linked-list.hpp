#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.hpp"
#include <sstream>

template <typename T>
class LinkedNode {
public:
    T item;
    LinkedNode<T> *next;
    LinkedNode(T item) : item(item), next(NULL) {}
    ~LinkedNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class LinkedList : public List<T> {
private:
    LinkedNode<T> *head;
    size_t n;
public:
    LinkedList() {
        this->head = NULL;
        this->n = 0;
    }

    ~LinkedList() {
        if (head != NULL)
            delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        LinkedNode<T> *node;
        for (node = head; i && node != NULL; --i, node = node->next)
            ;
        return node->item;
    }

    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        LinkedNode<T> *inserted = new LinkedNode<T>(item);
        if (i == 0) {
            inserted->next = head;
            head = inserted;
        } else {
            LinkedNode<T> *current;
            for (current = head; i-1 && current != NULL; --i)
                current = current->next;
            inserted->next = current->next;
            current->next = inserted;
        }
        ++n;
    }

    T remove(size_t i)  {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        if (n == 0)
            throw std::runtime_error("list is empty");
        LinkedNode<T> *removed = NULL;
        if (i == 0) {
            removed = head;
            head = head->next;
        } else {
            LinkedNode<T> *current;
            for (current = head; i-1 && current != NULL; --i)
                current = current->next;
            removed = current->next;
            current->next = removed->next;
        }
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        for (LinkedNode<T> *current = head; current != NULL; current = current->next)
            if (current == head)
                ss << current->item;
            else
                ss << "," << current->item;
        ss << "] : LinkedList(";
        for (LinkedNode<T> *current = head; current != NULL; current = current->next)
            ss << current->item << " -> ";
        ss << ")";
        return ss.str();
    }
};

#endif