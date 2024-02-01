#ifndef redblack234_hpp
#define redblack234_hpp
#include "RedBlackNode.hpp"
#include "RedBlack.hpp"

template <class K, class V>
class RedBlack234 : public RedBlackTree<K,V> {
    private:
        using node = rbnode<K,V>;
        node* handleLeft(node* x) {
            if (this->isRed(x->left->left)) {
                x = this->rotR(x);                
            } else if (this->isRed(x->left->right)) {
                x->left = this->rotL(x->left);
                x = this->rotR(x);            
            }
            return x;
        }
        node* handleRight(node* x) {
            if (this->isRed(x->right->right)) {
                x = this->rotL(x);
            } else if (this->isRed(x->right->left)) {
                x->right = this->rotR(x->right);
                x = this->rotL(x);
            }
            return x;
        }
        node* fixUp(node* x) {
            if (this->isRed(x->left) && this->isRed(x->right))
                x = this->colorFlip(x);
            if (this->isRed(x->left))
                x = handleLeft(x);
            if (this->isRed(x->right))
                x = handleRight(x);
            return x;
        }
        node* min(node* x) {
            node* y = x;
            while (y->left) y = y->left;
            return y;
        }
        node* eraseMin(node* y) {
            if (y->left == nullptr)
                return y->right;
            y->left = eraseMin(y->left);
            return y;
        }
        node* erase(node* x, K key) {
            if (x == nullptr)
                return nullptr;
            if (key == x->key) {
                node* t = x;
                if (x->left == nullptr)
                    return x->right;
                if (x->right == nullptr)
                    return x->left;
                x = min(t->right);
                x->left = eraseMin(x->left);
                x->right = t->right;
                delete t;
            }
            if (key < x->key) {
                x->left = erase(x->left, key);
            } else if (key > x->key) {
                x->right = erase(x->right, key);
            }
            return x;
        }
    public:
        RedBlack234() {
            this->root = nullptr;
            this->title = "2-3-4 Red/Black";
        }
        void insert(K key, V value) {
            int prerc = this->lrcount + this->rrcount;
            this->root = this->put(this->root, key, value);
            this->root->color = black;
            int postrc = this->lrcount + this->rrcount;
            int rotc = postrc - prerc;
            if (this->maxRotations < rotc)
                this->maxRotations = rotc;
        }
        void erase(K key) {
            this->root = erase(this->root, key);
            this->root->color = black;
        }
        RedBlackStats stats() {
            return this->printStats();
        }
        node* getRoot() {
            return this->root;
        }
        int size() {
            return this->treeSize;
        }
};

#endif