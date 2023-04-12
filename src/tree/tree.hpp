#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

template <typename K, typename T>
class Tree {
public:
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual T *search(K key) = 0;
    virtual void insert(K key, T item) = 0;
    virtual void remove(K key) = 0;
    virtual std::string to_string() = 0;
    friend std::ostream& operator<<(std::ostream& os, Tree<K,T>& tree) {
        return os << tree.to_string();
    }
};

void test_tree(Tree<char,int> &tree);

#endif