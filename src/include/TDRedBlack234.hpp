#ifndef topdownrb_hpp
#define topdownrb_hpp
#include <limits>
#include "RedBlackNode.hpp"
using namespace std;

template <class K, class V>
class TopDown234 {
    private:
        using node = rbnode<K,V>;
        using link = node*;
        link head, z;
        link x, p, g, gg;
        int count;
        node* rotate(K v, node* y) {
            node* gc, *c = (v < y->key) ? y->left:y->right;
            if (v < c->key) {
                gc = c->left; c->left = gc->right; gc->right = c;
            } else {
                gc = c->right; c->right = gc->left; gc->left = c;
            }
            if (v < y->key) y->left = gc; else y->right = gc;
            return gc;
        }
        void split(K v) {
            x->color = red;
            x->left->color = black;
            x->right->color = black;
            if (p->color == red) {
                g->color = red;
                if (v < g->key != v < p->key) {
                    p = rotate(v, g);
                }
                x = rotate(v, gg);
                x->color = black;
            }
            head->right->color = black;
        }
    public:
        TopDown234() {
            z = new node(K(), V());
            z->left = z; z->right = z;
            z->color = false;
            head = new node(numeric_limits<K>::min(), V());
            head->color = black;
            head->left = z; head->right = z;
            count = 0;
        }
        void insert(K key, V value) {
            x = head;
            p = x; g = x;
            z->key = key;
            while (x != z) {
                gg = g; g = p; p = x;
                x = (key < x->key) ? x->left:x->right;
                if (x->left->color && x->right->color)
                    split(key);
            }
            x = new node(key, value);
            x->left = z; x->right = z; x->color = red;
            if (key < p->key) p->left = x;
            else p->right = x;
            split(key);
            count++;
        }
        link rootNode() {
            return head->right;
        }
        link nil() {
            return z;
        }
};


#endif