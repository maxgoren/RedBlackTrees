#ifndef redblack23_hpp
#define redblack23_hpp
#include "RedBlackNode.hpp"
#include "RedBlack.hpp"

template <class K, class V>
class RedBlack23 : public RedBlackTree<K,V> {
    private:
        using node = rbnode<K,V>;
        node* makeRedChildrenLean(node* x) {
            if (this->isRed(x->left) && this->isRed(x->left->right))
                x->left = this->rotL(x->left);
            if (this->isRed(x->right) && this->isRed(x->right->left)) 
                x->right = this->rotR(x->right); 
            return x;
        }
        node* makeRedParentSibling(node* x) {
            if (this->isRed(x->left) && this->isRed(x->left->left)) 
                x = this->rotR(x);
            if (this->isRed(x->right) && this->isRed(x->right->right))
                x = this->rotL(x);
            return x;
        }
        node* pushRedUp(node* x) {
             if (this->isRed(x->left) && this->isRed(x->right))
                x = this->colorFlip(x);
            return x;
        }
        node* fixUp(node* x) {
            x = makeRedChildrenLean(x);
            x = makeRedParentSibling(x);
            x = pushRedUp(x);
            return x;
        }
    public:
        RedBlack23() {
            this->root = nullptr;
            this->title = "2-3 Red/Black";
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
