#ifndef llrb23_hpp
#define llrb23_hpp
#include "RedBlack.hpp"
#include "RedBlackNode.hpp"

template <class K, class V>
class LLRedBlack23 : public RedBlackTree<K,V> {
    private:
        using node = rbnode<K,V>;
        node* fixUp(node* x) {
            if (this->isRed(x->right) && !this->isRed(x->left)) 
                x = this->rotL(x);
            if (this->isRed(x->left) && this->isRed(x->left->left))
                x = this->rotR(x);
            if (this->isRed(x->left) && this->isRed(x->right)) 
                x = this->colorFlip(x);
            
            return x;
        }
    public:
        LLRedBlack23() {
            this->root = nullptr;
            this->title = "Left Leaning 2-3 Red/Black";
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
};


#endif