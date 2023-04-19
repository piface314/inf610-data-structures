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

    void insert(K &k, T &it, BNode<K,T,M> *nx) {
        size_t i;
        for (i = n; i > 0 && k < this->key[i-1]; --i)
            key[i] = key[i-1], item[i] = item[i-1], next[i+1] = next[i];
        key[i] = k, item[i] = it, next[i+1] = nx;
        ++n;
    }
    void insert_at(K &k, T &it, BNode<K,T,M> *nx, size_t i) {
        // this method assumes when i == 0, nx goes before the key
        for (size_t j = n; j > i; --j)
            key[j] = key[j-1], item[j] = item[j-1], next[j+1] = next[j];
        if (i == 0) {
            next[1] = next[0];
            key[0] = k, item[0] = it, next[0] = nx;
        } else
            key[i] = k, item[i] = it, next[i+1] = nx;
        ++n;
    }

    void remove(size_t i) {
        // this method assumes the node is a leaf
        --n;
        for (; i < n; ++i) {
            key[i] = key[i+1];
            item[i] = item[i+1];
        }
    }

    void merge(size_t i) {
        bool lt = (i < this->n); // 1 => smaller is at left, 0 => smaller is at right
        int sign = (lt<<1)-1;
        size_t ref_i = i - !lt;
        BNode<K,T,M> *smaller = this->next[i];
        BNode<K,T,M> *larger = this->next[i+sign];
        // check how many keys from the larger node can be passed to the smaller one
        size_t available = (larger->n - M + 1) / 2;
        if (available) {
            // if available, first parent key from the current node is passed to the smaller
            smaller->insert_at(this->key[ref_i], this->item[ref_i],
                               larger->next[larger->n - lt*larger->n], lt*smaller->n);
            larger->next[larger->n - lt*larger->n] = NULL;
            // then (available-1) keys from the larger are passed to the smaller
            size_t j, k;
            for (j = 0; j < available - 1; ++j) {
                // sm@left: k = j, sm@right: k = larger->n - 1 - j
                k = !lt*(larger->n - 1) + sign*j;
                smaller->insert_at(larger->key[k], larger->item[k], larger->next[k+lt], smaller->n);
                larger->next[k+lt] = NULL;
            }
            // then one key from the larger is the new parent key
            // sm@left: k = available - 1, sm@right: k = larger->n - available
            k = !lt*(larger->n - 1) + sign*j;
            this->key[ref_i] = larger->key[k];
            this->item[ref_i] = larger->item[k];

            // then the larger is adjusted
            larger->adjust(lt ? 0 : larger->n, available);
        } else {
            // left and right children nodes must be merged
            BNode<K,T,M> *left, *right;
            if (lt)
                left = smaller, right = larger;
            else
                left = larger, right = smaller;
            // parent key is passed to the left node
            left->insert_at(this->key[ref_i], this->item[ref_i], right->next[0], left->n);
            right->next[0] = NULL;
            // keys from right node are passed to the left node
            for (size_t j = 0; i < right->n; ++j) {
                left->insert_at(right->key[j], right->item[j], right->next[j+1], left->n);
                right->next[j+1] = NULL;
            }
            this->adjust(ref_i, 1);
            delete right;
        }
    }

    void adjust(size_t i, size_t delta) {
        n -= delta;
        if (i < n) {
            for (size_t j = i; j < n; ++j)
                key[j] = key[j+delta],
                item[j] = item[j+delta],
                next[j] = next[j+delta];
            next[n] = next[n+delta];   
        }
        for (size_t j = 1; j <= delta; ++j)
            next[n + j] = NULL;
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

    void remove(K& key, BNode<K,T,M> *node) {
        // Key not found
        if (node == NULL)
            return;
        // Search for key
        size_t i;
        for (i = 0; i < node->n && key >= node->key[i]; ++i)
            ;
        if (key == node->key[i-1]) {
            --n;
            // Key found
            if (node->next[0] == NULL)
                return node->remove(i-1); // Node is a leaf
            // Node is internal, swap removed for successor
            std::pair<K,T> *lt = leftmost(node->next[i]);
            node->key[i-1] = lt->first;
            node->item[i-1] = lt->second;
            delete lt;
            // if child has less than M elements, merge
            if (node->next[i]->n < M)
                node->merge(i);
            return;
        }
        // Key not found
        remove(key, node->next[i]);
        // if child has less than M elements, merge
        if (node->next[i]->n < M)
            node->merge(i);
    }

    std::pair<K,T> *leftmost(BNode<K,T,M> *node) {
        if (node == NULL)
            return NULL;
        if (node->next[0] == NULL) {
            std::pair<K,T> *lt = new std::pair<K,T>(node->key[0],node->item[0]);
            node->remove(0);
            return lt;
        }
        std::pair<K,T> *lt = leftmost(node->next[0]);
        if (node->next[0]->n < M)
            node->merge(0);
        return lt;
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
        remove(key, root);
        if (root->n == 0) {
            BNode<K,T,M> *removed = root;
            root = root->next[0];
            removed->next[0] = NULL;
            delete removed;
        }
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "BTree";
        to_string(ss, root);
        return ss.str();
    }

    void to_string(std::stringstream& ss, BNode<K,T,M> *node) {
        if (node == NULL) {
            ss << "()";
            return;
        }
        ss << "(";
        for (size_t i = 0; i < node->n; ++i)
            ss << node->key[i] << ":" << node->item[i] << " ";
        for (size_t i = 0; i <= node->n; ++i)
            if (node->next[i] != NULL)
                to_string(ss, node->next[i]);
        ss << ")";
    }
};


#endif