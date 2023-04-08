#ifndef LLINKED_LIST_H
#define LLINKED_LIST_H

#include "list.hpp"
#include <sstream>

template <typename T>
class LLinkedNode {
public:
    T item;
    LLinkedNode<T> *next;
    LLinkedNode(T item) : item(item), next(NULL) {}
    ~LLinkedNode() {
        if (next != NULL)
            delete next;
    }
};

template <typename T>
class LLinkedList : public List<T> {
private:
    LLinkedNode<T> *head, *last;
    size_t n;
public:
    LLinkedList() {
        this->head = this->last = NULL;
        this->n = 0;
    }

    ~LLinkedList() {
        if (head != NULL)
            delete head;
    }

    size_t size() { return n; }
    bool empty() { return n == 0; }

    // Worst case: O(n), Best case: O(1)
    T lookup(size_t i) {
        if (i < 0 || i >= n)
            throw std::invalid_argument("index out of bounds");
        LLinkedNode<T> *node;
        for (node = head; i && node != NULL; --i, node = node->next)
            ;
        return node->item;
    }

    // Worst case: O(n), Best case: O(1)
    void insert(size_t i, T item) {
        if (i < 0 || i > n)
            throw std::invalid_argument("index out of bounds");
        LLinkedNode<T> *inserted = new LLinkedNode<T>(item);
        if (i == 0) {
            inserted->next = head;
            head = inserted;
            if (n == 0)
                last = head;
        } else if (i == n) {
            last->next = inserted;
            last = inserted;
        } else {
            LLinkedNode<T> *current;
            for (current = head; i-1 && current != NULL; --i)
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
        LLinkedNode<T> *removed = NULL;
        if (i == 0) {
            removed = head;
            head = head->next;
            if (head == NULL || head->next == NULL)
                last = head;
        } else {
            LLinkedNode<T> *current;
            for (current = head; i-1 && current != NULL; --i)
                current = current->next;
            removed = current->next;
            current->next = removed->next;
            if (current->next == NULL) 
                last = current;
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
        for (LLinkedNode<T> *current = head; current != NULL; current = current->next)
            if (current == head)
                ss << current->item;
            else
                ss << "," << current->item;
        ss << "] : LLinkedList(";
        for (LLinkedNode<T> *current = head; current != NULL; current = current->next)
            ss << current->item << " -> ";
        ss << ")";
        return ss.str();
    }
};

#endif