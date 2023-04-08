#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

template <typename T>
class List {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T lookup(size_t i) = 0;
    virtual void insert(size_t i, T item) = 0;
    virtual T remove(size_t i) = 0;
    virtual std::string to_string() = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, List<T>& list) {
    return os << list.to_string();
}

void test_list(List<int> &list);

#endif