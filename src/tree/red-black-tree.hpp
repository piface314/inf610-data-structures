#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "tree.hpp"
#include "../colors.h"
#include <sstream>

enum class RBColor { BLACK, RED };

template <typename K, typename T>
class RedBlackNode {
public:
    K key;
    T item;
    RBColor color;
    RedBlackNode<K,T> *next[2];
    RedBlackNode(K key, T item) : key(key), item(item), color(RBColor::RED) {
        this->next[0] = this->next[1] = NULL;
    }
    ~RedBlackNode() {
        if (next[0] != NULL) delete next[0];
        if (next[1] != NULL) delete next[1];
    }
};

template <typename K, typename T>
class RedBlackTree : public Tree<K,T> {
private:
    size_t n;
    RedBlackNode<K,T> *root;
    RBColor color(RedBlackNode<K,T> *node) {
        return node == NULL ? RBColor::BLACK : node->color;
    }

    RedBlackNode<K,T> *rotation(RedBlackNode<K,T> *node, bool dir) {
        RedBlackNode<K,T> *pivot = node->next[1-dir];
        node->next[1-dir] = pivot->next[dir];
        pivot->next[dir] = node;
        return pivot;
    }

    RedBlackNode<K,T> *double_rotation(RedBlackNode<K,T> *node, bool dir) {
        RedBlackNode<K,T> *pivot = node->next[1-dir]->next[dir];
        node->next[1-dir]->next[dir] = pivot->next[1-dir];
        pivot->next[1-dir] = node->next[1-dir];
        node->next[1-dir] = pivot->next[dir];
        pivot->next[dir] = node;
        return pivot;
    }

    RedBlackNode<K,T> *insert(K& key, T& item, RedBlackNode<K,T> *node, bool &end) {
        if (node == NULL)
            return new RedBlackNode<K,T>(key, item);
        bool dir = key >= node->key;
        node->next[dir] = insert(key, item, node->next[dir], end);
        if (end)
            return node;
        if (color(node->next[dir]) == RBColor::BLACK)
            // Case 2: new node parent is black
            end = true;
        else if (color(node->next[1-dir]) == RBColor::RED) {
            // Case 3: other child is red
            node->next[0]->color = node->next[1]->color = RBColor::BLACK;
            node->color = RBColor::RED;
        } else if (color(node->next[dir]->next[1-dir]) == RBColor::RED) {
            // Case 4: unbalanced node is "inner"
            node = double_rotation(node, 1-dir);
            node->next[1-dir]->color = RBColor::RED;
            node->color = RBColor::BLACK;
        } else if (color(node->next[dir]->next[dir]) == RBColor::RED) {
            // Case 5: unbalanced node is "outer"
            node = rotation(node, 1-dir);
            node->next[1-dir]->color = RBColor::RED;
            node->color = RBColor::BLACK;
        }
        return node;
    }

    RedBlackNode<K,T> *leftmost(RedBlackNode<K,T> *node, RedBlackNode<K,T> *&lt) {
        if (node->next[0] == NULL) {
            lt = node;
            return node->next[1];
        }
        node->next[0] = leftmost(node->next[0], lt);
        return node;
    }

    RedBlackNode<K,T> *remove(K& key, RedBlackNode<K,T> *node) {
        // TODO: implement balance in removal
        if (node == NULL)
            return node;
        if (key < node->key)
            node->next[0] = remove(key, node->next[0]);
        else if (key > node->key)
            node->next[1] = remove(key, node->next[1]);
        else {
            RedBlackNode<K,T> *removed = node;
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
        return node;
    }

public:
    RedBlackTree() : n(0), root(NULL) { }
    ~RedBlackTree() {
        if (root != NULL)
            delete root;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    T *search(K key) {
        RedBlackNode<K,T> *current = root;
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
        bool end = false;
        root = insert(key, item, root, end);
        root->color = RBColor::BLACK;
        ++n;
    }

    void remove(K key) {
        root = remove(key, root);
        if (root != NULL)
            root->color = RBColor::BLACK;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "RedBlackTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, RedBlackNode<K,T> *node) {
        if (node == NULL) {
            ss << CL_BG_BLACK CL_FG_WHITE "()" CL_RESET;
            return;
        }
        std::string cl = color(node) == RBColor::BLACK ? CL_BG_BLACK : CL_BG_RED;
        ss << cl << CL_FG_WHITE "(" << node->key << ":" << node->item << " ";
        to_string(ss, node->next[0]);
        to_string(ss, node->next[1]);
        ss << cl << CL_FG_WHITE ")" << CL_RESET;
    }
};

void test_tree(Tree<char,int> &tree);

#endif