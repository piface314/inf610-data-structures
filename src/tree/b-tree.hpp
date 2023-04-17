#ifndef B_TREE_H
#define B_TREE_H

#include "tree.hpp"
#include <sstream>

template <typename K, typename T, size_t M>
class BNode {
public:
    size_t n;
    K key[2*M];
    T item[2*M];
    BNode<K,T,M> *next[2*M+1];
    BNode() : n(0) {
        for (size_t i = 0; i <= 2*M; ++i)
            next[i] = NULL;
    }
    BNode(K &key, T &item, BNode<K,T,M> *lt, BNode<K,T,M> *rt) : n(1) {
        this->key[0] = key;
        this->item[0] = item;
        this->next[0] = lt;
        this->next[1] = rt;
        for (size_t i = 2; i <= 2*M; ++i)
            this->next[i] = NULL;
    }
    ~BNode() {
        for (size_t i = 0; i <= 2*M; ++i) {
            if (next[i] == NULL)
                break;
            delete next[i];
        }
    }
    bool full() { return n == 2*M; }

    void insert(K &key, T &item, BNode<K,T,M> *next) {
        size_t i;
        for (i = n; i > 0 && key < this->key[i-1]; --i) {
            this->key[i] = this->key[i-1];
            this->item[i] = this->item[i-1];
            this->next[i+1] = this->next[i];
        }
        this->key[i] = key;
        this->item[i] = item;
        this->next[i+1] = next;
        ++n;
    }
};

template <typename K, typename T, size_t M>
class BTree : public Tree<K,T> {
private:
    size_t n;
    BNode<K,T,M> *root;

    BNode<K,T,M> *insert(K& key, T& item, BNode<K,T,M> *node) {
        // Find insertion point
        if (node == NULL)
            return NULL;
        size_t i;
        for (i = 0; i < node->n && key >= node->key[i]; ++i)
            ;
        BNode<K,T,M> *next = insert(key, item, node->next[i]);
        
        // If must not insert in this node and no new node was created, stop
        if (next != NULL && next == node->next[i])
            return node;
        
        // If current node has space, insert in this node
        if (!node->full()) {
            node->insert(key, item, next);
            return node;
        }
        // Node overflow
        BNode<K,T,M> *created = new BNode<K,T,M>();
        if (i <= M) {
            // inserted item resides in current node
            --node->n;
            created->insert(node->key[2*M-1], node->item[2*M-1], node->next[2*M]);
            node->insert(key, item, next);
            node->next[2*M] = NULL;
        } else
            // inserted item resides in created node
            created->insert(key, item, next);
        for (size_t i = M+1; i < 2*M; ++i) {
            created->insert(node->key[i], node->item[i], node->next[i+1]);
            node->next[i+1] = NULL;
        }
        node->n = M;
        key = node->key[M];
        item = node->item[M];
        created->next[0] = node->next[M+1];
        node->next[M+1] = NULL;
        return created;
    }

    BNode<K,T,M> *remove(K& key, BNode<K,T,M> *node) {
        return node;
    }
public:
    BTree() : n(0), root(NULL) { }
    ~BTree() {
        if (root != NULL)
            delete root;
    }
    size_t size() { return n; }
    bool empty() { return n == 0; }

    T *search(K key) {
        BNode<K,T,M> *node = root;
        while (node != NULL) {
            size_t i;
            for (i = 0; i < node->n && key >= node->key[i]; ++i)
                ;
            if (i-1 < n && key == node->key[i-1])
                return &node->item[i-1];
            node = node->next[i];
        }
        return NULL;
    }

    void insert(K key, T item) {
        BNode<K,T,M> *next = insert(key, item, root);
        if (next == NULL || next != root)
            root = new BNode<K,T,M>(key, item, root, next);
        ++n;
    }

    void remove(K key) {
        root = remove(key, root);
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "BTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, BNode<K,T,M> *node) {
        if (node == NULL)
            return;
        ss << "(";
        for (size_t i = 0; i < node->n; ++i)
            ss << node->key[i] << ":" << node->item[i] << " ";
        for (size_t i = 0; i <= node->n; ++i)
            to_string(ss, node->next[i]);
        ss << ")";
    }
};


#endif