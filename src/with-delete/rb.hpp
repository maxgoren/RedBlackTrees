#ifndef rb_hpp
#define rb_hpp
#include "rbnode.hpp"
#include <iostream>
using namespace std;

/*
*   2-3-4 Red/Black Tree
*   Bottom up insertion, Top-down deletion
*
*
*/

template <class K>
class RedBlackTree {
    private:
        using node = rbnode<K>;
        using link = node*;
        link root;
        int count;
        bool isRed(link h) {
            return h == nullptr ? false:(h->color == red);
        }
        bool isBlack(link h) {
            return !isRed(h);
        }
        link putR(link h, K data) {
            if (h == nullptr) {
                count++;
                return new node(data, red, nullptr, nullptr);
            }
            if (data < h->info) {
                h->left = putR(h->left, data);
            } else {
                h->right = putR(h->right, data);
            }
            return balance(h);
        }
        link eraseR(link h, K key) {
            if (h == nullptr)
                return h;
            h = pushRedDown(h, key);
            if (key < h->info) {
                h->left = eraseR(h->left, key);
            } else if (key > h->info) {
                h->right = eraseR(h->right, key);
            } else {
                if (h->right == nullptr) {
                    link t = h;
                    h = h->left;
                    delete t;
                    count--;
                } else {
                    link tmp = min(h->right);
                    h->info = tmp->info;
                    h->right = eraseR(h->right, h->info);
                }
            }
            return h ? balance(h):h;
        }
        link getR(link h, K key) {
            if (h == nullptr)
                return nullptr;
            if (key == h->info)
                return h;
            if (key < h->info) return getR(h->left, key);
            else return getR(h->right, key);
        }
        link min(link from)  {
            if (from == nullptr)
                return from;
            link x = from;
            while (x->left != nullptr) x = x->left;
            return x;
        }
        link max(link from) {
            if (from == nullptr)
                return from;
            link x = from;
            while (x->right != nullptr) x = x->right;
            return x;
        }
        link rotL(link h) {
            link x = h->right; h->right = x->left; x->left = h;
            x->color = h->color;
            h->color = red;
            return x;
        }
        link rotR(link h) {
            link x = h->left; h->left = x->right; x->right = h;
            x->color = h->color;
            h->color = red;
            return x;
        }
        link colorFlip(link h) {
            h->color = !h->color;
            if (h->left)
                h->left->color = !h->left->color;
            if (h->right)
                h->right->color = !h->right->color;
            return h;
        }
        link balance(link h) {
            if (isRed(h->left) && isRed(h->right)) {
                h = colorFlip(h);
            }
            if (isRed(h->right)) {
                if (isRed(h->right->left)) {
                    h->right = rotR(h->right);
                    h = rotL(h);
                } else if (isRed(h->right->right)) {
                    h = rotL(h);
                }
            } else if (isRed(h->left)) { 
                if (isRed(h->left->right)) {
                    h->left = rotL(h->left);
                    h = rotR(h);
                } else if (isRed(h->left->left)) {
                    h = rotR(h);
                }
            }
            //this is the only case that should ever hit bottom-up
            if (isRed(h->left) && isRed(h->right) && (isRed(h->right->right) || isRed(h->left->left))) {
                h = colorFlip(h);
                cout<<"Oi den."<<endl;
            }
            return h;
        }
        link pushRedDown(link p, K key) {
            link x, s;
            bool wentLeft = key < p->info;
            if (wentLeft) {
                x = p->left;
                s = p->right;
            } else {
                x = p->right;
                s = p->left;
            }
            if (isBlack(x) && isRed(s)) {
                p = wentLeft ? rotL(p):rotR(p);
            }
            x = key < p->info ? p->left:p->right;
            if (x && isBlack(x) && isBlack(x->left) && isBlack(x->right)) {
                p = wentLeft ? pushLeft(p):pushRight(p);
            }
            return p;
        }
        link pushRight(link h) {
            h = colorFlip(h);
            if (h->left) {
                if (isRed(h->left) && isRed(h->left->right)) {
                    h->left = rotL(h->left);
                    h = rotR(h);
                    h = colorFlip(h);
                } else if (isRed(h->left) && isRed(h->left->left)) {
                    h = rotR(h);
                    h = colorFlip(h);
                }
            }
            return h;
        }
        link pushLeft(link h) {
            h = colorFlip(h);
            if (h->right) {
                if (isRed(h->right) && isRed(h->right->left)) {
                    h->right = rotR(h->right);
                    h = rotL(h);
                    h = colorFlip(h);
                } else if (isRed(h->right) && isRed(h->right->right)) {
                    h = rotL(h);
                    h = colorFlip(h);
                }
            }
            return h;
        }
        void cleanup(link h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
        link clone(link h) {
            if (h == nullptr)
                return nullptr;
            return new rbnode<K>(h->info, h->color, clone(h->left), clone(h->right));
        }
    public:
        RedBlackTree() {
            root = nullptr;
            count = 0;
        }
        RedBlackTree(const RedBlackTree& rb) {
            root = nullptr;
            root = clone(rb.root);
            count = rb.count;
        }
        ~RedBlackTree() {
            cleanup(root);
        }
        bool empty() const {
            return root == nullptr;
        }
        int size() const {
            return count;
        }
        void insert(K data) {
            root = putR(root, data);
            root->color = black;
        }
        void erase(K data) {
            if (empty()) 
                return;
            if (isBlack(root->left) && isBlack(root->right)) {
                root->color = red;
            }
            root = eraseR(root, data);
            if (root != nullptr) root->color = black;
        }
        K get(K data) {
            link x = getR(root, data);
            return x == nullptr ? K(-1):x->info;
        }
        bool contains(K key) {
            return getR(root, key) != nullptr;
        }
        K min() {
            link x = min(root);
            return x == nullptr ? K(-1):x->info;
        }
        K max() {
            link x = max(root);
            return x == nullptr ? K(-1):x->info;
        }
        K pred(K data) {
            link x = getR(root, data);
            if (x == nullptr)
                return K(-1);
            link t = max(x->left);
            return t == nullptr ? K(-1):t->info;
        }
        K succ(K data) {
            link x = getR(root, data);
            if (x == nullptr)
                return K(-1);
            link t = min(x->right);
            return t == nullptr ? K(-1):t->info;
        }
        link getroot() {
            return root;
        }
        RBIterator<K> iter() {
            return RBIterator<K>(root);
        }
        RedBlackTree& operator=(const RedBlackTree& rb) {
            if (this != &rb) {
                root = nullptr;
                root = clone(rb.root);
                count = rb.count;
            }
            return *this;
        }
};

#endif