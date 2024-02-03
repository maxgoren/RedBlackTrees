#ifndef topdown2345_hpp
#define topdown2345_hpp
#include "RedBlackNode.hpp"
template <class K, class V>
class TopDown2345 {
    private:
        using node = rbnode<K,V>;
        using link = node*;
        link head, z;
        link curr, parent, grand;
        int count;
        node* left(node* t) {
            return t->left;
        }
        node* right(node* t) {
            return t->right;
        }
        bool color(node* t) {
            return t->color;
        }
        K key(node* t) {
            return t->key;
        }
        bool isnil(node* x) {
            return x == z;
        }
        node* rotate(K v, node* y) {
            node* gchild, *child = (v < key(y)) ? left(y):right(y);
            if (v < key(child)) {
                gchild = child->left; child->left = gchild->right; gchild->right = child;
            } else {
                gchild = child->right; child->right = gchild->left; gchild->left = child;
            }
            if (v < key(y)) y->left = gchild; else y->right = gchild;
            return gchild;
        }
        void balance(K v) {
            if (color(curr) == black) {
                curr->color = red;
                curr->left->color = black;
                curr->right->color = black;
            } else {
                curr->color = black;
                parent->color = red;
            }
            if (color(curr) == black || (color(parent) == red && (v < key(grand) != v < key(parent)))) {
                parent = rotate(v, grand);
            }
            head->right->color = black;
        }
    public:
        TopDown2345() {
            z = new node(numeric_limits<K>::max(), numeric_limits<V>::max(), black, nullptr, nullptr);
            z->left = z; z->right = z;
            head = new node(numeric_limits<K>::min(), numeric_limits<V>::min(), black, z, z);
            count = 0;
        }
        void insert(K k, V value) {
            curr = head;
            parent = curr; 
            grand = parent;
            while (!isnil(curr)) {
                grand = parent; parent = curr;
                curr = (k < key(curr)) ? left(curr):right(curr);
                if ((color(curr->left) && color(curr->right)) || (color(curr) && color(curr->left)) || (color(curr) && color(curr->right)))
                    balance(k);
            }
            curr = new node(k, value, black, z, z);
            if (k < key(parent)) parent->left = curr;
            else parent->right = curr;
            balance(k);
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