#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H

#include "list.hpp"
#include <sstream>

template <typename T>
class DLinkedNode {
public:
    T item;
    DLinkedNode<T> *next, *prev;
    DLinkedNode() : next(NULL), prev(NULL) {}
    DLinkedNode(T item) : item(item), next(NULL), prev(NULL) {}
    ~DLinkedNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class DLinkedList : public List<T> {
private:
    DLinkedNode<T> *head, *last;
    size_t n;
public:
    DLinkedList() {
        this->head = this->last = new DLinkedNode<T>();
        this->n = 0;
    }

    ~DLinkedList() {
        delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // Worst case: O(n), Best case: O(1)
    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        DLinkedNode<T> *node;
        if (i <= n - i) {
            node = head->next;
            while (i--)
                node = node->next;
        } else {
            node = last;
            while (++i < n)
                node = node->prev;
        }
        return node->item;
    }

    // Worst case: O(n), Best case: O(1)
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        DLinkedNode<T> *inserted = new DLinkedNode<T>(item);
        if (i == n) {
            last->next = inserted;
            inserted->prev = last;
            last = inserted;
        } else {
            DLinkedNode<T> *current;
            if (i <= n - i) {
                current = head;
                while (i--)
                    current = current->next;
            } else {
                current = last->prev;
                while (++i < n)
                    current = current->prev;
            }
            current->next->prev = inserted;
            inserted->next = current->next;
            inserted->prev = current;
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
        DLinkedNode<T> *removed = NULL;
        DLinkedNode<T> *current;
        if (i <= n - i) {
            current = head;
            while (i--)
                current = current->next;
        } else {
            current = last->prev;
            while (++i < n)
                current = current->prev;
        }
        removed = current->next;
        if (removed->next != NULL)
            removed->next->prev = current;
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
        for (DLinkedNode<T> *current = head->next; current != NULL; current = current->next)
            if (current == head->next)
                ss << current->item;
            else
                ss << "," << current->item;
        ss << "] : DLinkedList(<@->";
        for (DLinkedNode<T> *current = head->next; current != NULL; current = current->next)
            ss << "<" << current->item << "-> ";
        ss << ")";
        return ss.str();
    }
};

#endif