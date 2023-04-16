#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "tree.hpp"
#include <sstream>

template <typename K, typename T>
class BinNode {
public:
    K key;
    T item;
    BinNode<K,T> *lt, *rt;
    BinNode(K key, T item) : key(key), item(item), lt(NULL), rt(NULL) { }
    ~BinNode() {
        if (lt != NULL) delete lt;
        if (rt != NULL) delete rt;    
    }
};

template <typename K, typename T>
class BinTree : public Tree<K,T> {
private:
    size_t n;
    BinNode<K,T> *root;
public:
    BinTree() : n(0), root(NULL) { }
    ~BinTree() {
        if (root != NULL)
            delete root;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    T *search(K key) {
        BinNode<K,T> *current = root;
        while (current != NULL)
            if (key < current->key)
                current = current->lt;
            else if (key > current->key)
                current = current->rt;
            else
                return &current->item;
        return NULL;
    }

    void insert(K key, T item) {
        BinNode<K,T> *inserted = new BinNode<K,T>(key, item);
        BinNode<K,T> **current = &root;
        while (*current != NULL)
            if (key < (*current)->key)
                current = &(*current)->lt;
            else
                current = &(*current)->rt;
        *current = inserted;
        ++n;
    }

    void remove(K key) {
        BinNode<K,T> **current = &root, **next = NULL, *removed = NULL;
        while (*current != NULL)
            if (key < (*current)->key)
                current = &(*current)->lt;
            else if (key > (*current)->key)
                current = &(*current)->rt;
            else
                break;
        removed = *current;
        if (removed == NULL)
            return;
        if (removed->lt == NULL) {
            *current = removed->rt;
            removed->rt = NULL;
        } else if (removed->rt == NULL) {
            *current = removed->lt;
            removed->lt = NULL;
        } else {
            next = &removed->rt;
            while ((*next)->lt != NULL)
                next = &(*next)->lt;
            *current = *next;
            *next = (*next)->rt;
            (*current)->lt = removed->lt, (*current)->rt = removed->rt;
            removed->lt = NULL, removed->rt = NULL;
        }
        delete removed;
        --n;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "BinTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, BinNode<K,T> *node) {
        if (node == NULL) {
            ss << "()";
            return;
        }
        ss << "(" << node->key << ":" << node->item << " ";
        to_string(ss, node->lt);
        to_string(ss, node->rt);
        ss << ")";
    }
};

void test_tree(Tree<char,int> &tree);

#endif