#ifndef HLINKED_LIST_H
#define HLINKED_LIST_H

#include "list.hpp"
#include <sstream>

template <typename T>
class HLinkedNode {
public:
    T item;
    HLinkedNode<T> *next;
    HLinkedNode() : next(NULL) {}
    HLinkedNode(T item) : item(item), next(NULL) {}
    ~HLinkedNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class HLinkedList : public List<T> {
private:
    HLinkedNode<T> *head, *last;
    size_t n;
public:
    HLinkedList() {
        this->head = this->last = new HLinkedNode<T>();
        this->n = 0;
    }

    ~HLinkedList() {
        delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // Worst case: O(n), Best case: O(1)
    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        HLinkedNode<T> *node = head->next;
        if (i == n - 1)
            node = last;
        else
            while (i--)
                node = node->next;
        return node->item;
    }

    // Worst case: O(n), Best case: O(1)
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        HLinkedNode<T> *inserted = new HLinkedNode<T>(item);
        if (i == n) {
            last->next = inserted;
            last = inserted;
        } else {
            HLinkedNode<T> *current;
            for (current = head; i > 0; --i)
                current = current->next;
            inserted->next = current->next;
            current->next = inserted;
        }
        ++n;
    }

    // Worst case: O(n), Best case: O(1)
    T remove(size_t i)  {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        if (n == 0)
            throw std::runtime_error("list is empty");
        HLinkedNode<T> *removed = NULL;
        HLinkedNode<T> *current;
        for (current = head; i > 0; --i)
            current = current->next;
        removed = current->next;
        current->next = removed->next;
        if (current->next == NULL) 
            last = current;
        --n;
        T item = removed->item;
        removed->next = NULL;
        delete removed;
        return item;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[";
        for (HLinkedNode<T> *current = head->next; current != NULL; current = current->next)
            if (current == head->next)
                ss << current->item;
            else
                ss << "," << current->item;
        ss << "] : HLinkedList(@-> ";
        for (HLinkedNode<T> *current = head->next; current != NULL; current = current->next)
            ss << current->item << " -> ";
        ss << ")";
        return ss.str();
    }
};

#endif