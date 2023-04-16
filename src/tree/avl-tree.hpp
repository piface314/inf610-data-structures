#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "tree.hpp"
#include <sstream>

template <typename K, typename T>
class AVLNode {
public:
    K key;
    T item;
    size_t height;
    AVLNode<K,T> *next[2];
    AVLNode(K key, T item) : key(key), item(item), height(0) {
        this->next[0] = this->next[1] = NULL;
    }
    ~AVLNode() {
        if (next[0] != NULL) delete next[0];
        if (next[1] != NULL) delete next[1];
    }
};

template <typename K, typename T>
class AVLTree : public Tree<K,T> {
private:
    size_t n;
    AVLNode<K,T> *root;
    long long height(AVLNode<K,T> *node) {
        return node == NULL ? -1 : (long long)node->height;
    }
    void update_height(AVLNode<K,T> *node) {
        node->height = (size_t)(1 + std::max(height(node->next[0]), height(node->next[1])));
    }

    AVLNode<K,T> *rotation(AVLNode<K,T> *node, bool dir) {
        AVLNode<K,T> *pivot = node->next[1-dir];
        node->next[1-dir] = pivot->next[dir];
        pivot->next[dir] = node;
        update_height(node);
        update_height(pivot);
        return pivot;
    }

    AVLNode<K,T> *double_rotation(AVLNode<K,T> *node, bool dir) {
        AVLNode<K,T> *pivot = node->next[1-dir]->next[dir];
        node->next[1-dir]->next[dir] = pivot->next[1-dir];
        pivot->next[1-dir] = node->next[1-dir];
        node->next[1-dir] = pivot->next[dir];
        pivot->next[dir] = node;
        update_height(node);
        update_height(pivot->next[1-dir]);
        update_height(pivot);
        return pivot;
    }

    AVLNode<K,T> *balance(AVLNode<K,T> *node) {
        if (node == NULL)
            return node;
        long long height_l = height(node->next[0]);
        long long height_r = height(node->next[1]);
        long long delta = height_l - height_r;
        if (std::abs(delta) <= 1) {
            node->height = 1 + std::max(height_l, height_r);
            return node;
        }
        if (delta > 0) {
            if (height(node->next[0]->next[0]) > height(node->next[0]->next[1]))
                return rotation(node, 1);
            else
                return double_rotation(node, 1);
        } else {
            if (height(node->next[1]->next[0]) > height(node->next[1]->next[1]))
                return double_rotation(node, 0);
            else
                return rotation(node, 0);
        }
    }

    AVLNode<K,T> *insert(K& key, T& item, AVLNode<K,T> *node) {
        if (node == NULL)
            return new AVLNode<K,T>(key, item);
        if (key < node->key)
            node->next[0] = insert(key, item, node->next[0]);
        else
            node->next[1] = insert(key, item, node->next[1]);
        return balance(node);
    }

    AVLNode<K,T> *leftmost(AVLNode<K,T> *node, AVLNode<K,T> *&lt) {
        if (node->next[0] == NULL) {
            lt = node;
            return node->next[1];
        }
        node->next[0] = leftmost(node->next[0], lt);
        return balance(node);
    }

    AVLNode<K,T> *remove(K& key, AVLNode<K,T> *node) {
        if (node == NULL)
            return node;
        if (key < node->key)
            node->next[0] = remove(key, node->next[0]);
        else if (key > node->key)
            node->next[1] = remove(key, node->next[1]);
        else {
            AVLNode<K,T> *removed = node;
            if (removed->next[0] == NULL)
                node = removed->next[1];
            else if (removed->next[1] == NULL)
                node = removed->next[0];
            else {
                removed->next[1] = leftmost(removed->next[1], node);
                node->next[0] = removed->next[0];
                node->next[1] = removed->next[1];
            }
            removed->next[0] = NULL;
            removed->next[1] = NULL;
            delete removed;
            --n;
        }
        return balance(node);
    }

public:
    AVLTree() : n(0), root(NULL) { }
    ~AVLTree() { delete root; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    T *search(K key) {
        AVLNode<K,T> *current = root;
        while (current != NULL)
            if (key < current->key)
                current = current->next[0];
            else if (key > current->key)
                current = current->next[1];
            else
                return &current->item;
        return NULL;
    }

    void insert(K key, T item) {
        root = insert(key, item, root);
        ++n;
    }

    void remove(K key) {
        root = remove(key, root);
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "AVLTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, AVLNode<K,T> *node) {
        if (node == NULL) {
            ss << "()";
            return;
        }
        ss << "(" << node->key << ":" << node->item << " ";
        to_string(ss, node->next[0]);
        to_string(ss, node->next[1]);
        ss << ")";
    }
};

void test_tree(Tree<char,int> &tree);

#endif