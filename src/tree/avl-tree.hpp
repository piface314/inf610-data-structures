#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "tree.hpp"
#include <sstream>

template <typename K, typename T>
class AVLTreeNode {
public:
    K key;
    T item;
    size_t height;
    AVLTreeNode<K,T> *lt, *rt;
    AVLTreeNode(K key, T item) : key(key), item(item), height(0), lt(NULL), rt(NULL) { }
    ~AVLTreeNode() {
        if (lt != NULL) delete lt;
        if (rt != NULL) delete rt;    
    }
};

template <typename K, typename T>
class AVLTree : public Tree<K,T> {
private:
    size_t n;
    AVLTreeNode<K,T> *root;
    long long height(AVLTreeNode<K,T> *node) {
        return node == NULL ? -1 : (long long)node->height;
    }
    void update_height(AVLTreeNode<K,T> *node) {
        node->height = (size_t)(1 + std::max(height(node->lt), height(node->rt)));
    }

    AVLTreeNode<K,T> *rotate_ll(AVLTreeNode<K,T> *node) {
        AVLTreeNode<K,T> *rotated = node->lt;
        node->lt = rotated->rt;
        rotated->rt = node;
        update_height(node);
        update_height(rotated);
        return rotated;
    }
    
    AVLTreeNode<K,T> *rotate_lr(AVLTreeNode<K,T> *node) {
        AVLTreeNode<K,T> *rotated = node->lt->rt;
        node->lt->rt = rotated->lt;
        rotated->lt = node->lt;
        node->lt = rotated->rt;
        rotated->rt = node;
        update_height(node);
        update_height(rotated->lt);
        update_height(rotated);
        return rotated;
    }

    AVLTreeNode<K,T> *rotate_rr(AVLTreeNode<K,T> *node) {
        AVLTreeNode<K,T> *rotated = node->rt;
        node->rt = rotated->lt;
        rotated->lt = node;
        update_height(node);
        update_height(rotated);
        return rotated;
    }

    AVLTreeNode<K,T> *rotate_rl(AVLTreeNode<K,T> *node) {
        AVLTreeNode<K,T> *rotated = node->rt->lt;
        node->rt->lt = rotated->rt;
        rotated->rt = node->rt;
        node->rt = rotated->lt;
        rotated->lt = node;
        update_height(node);
        update_height(rotated->rt);
        update_height(rotated);
        return rotated;
    }

    AVLTreeNode<K,T> *insert(K& key, T& item, AVLTreeNode<K,T> *node) {
        if (node == NULL)
            return new AVLTreeNode<K,T>(key, item);
        if (key < node->key)
            node->lt = insert(key, item, node->lt);
        else
            node->rt = insert(key, item, node->rt);
        long long height_l = height(node->lt);
        long long height_r = height(node->rt);
        long long delta = height_l - height_r;
        if (std::abs(delta) <= 1) {
            node->height = 1 + std::max(height_l, height_r);
            return node;
        }
        if (delta > 0) {
            if (height(node->lt->lt) > height(node->lt->rt))
                return rotate_ll(node);
            else
                return rotate_lr(node);
        } else {
            if (height(node->rt->lt) > height(node->rt->rt))
                return rotate_rl(node);
            else
                return rotate_rr(node);
        }
    }

public:
    AVLTree() : n(0), root(NULL) { }
    ~AVLTree() { delete root; }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    T *search(K key) {
        AVLTreeNode<K,T> *current = root;
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
        root = insert(key, item, root);
        ++n;
    }

    void remove(K key) {
        AVLTreeNode<K,T> **current = &root, **next = NULL, *removed = NULL;
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
        ss << "AVLTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, AVLTreeNode<K,T> *node) {
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