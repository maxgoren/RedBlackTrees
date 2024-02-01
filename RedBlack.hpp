#ifndef redblack_hpp
#define redblack_hpp
#include <iostream>
#include "RedBlackNode.hpp"
using namespace std;

template <class K, class V>
class RedBlackTree {
    public:
        using node = rbnode<K,V>;
        node* root;
        int maxRotations;
        int lrcount;
        int rrcount;
        int cfcount;
        int treeSize;
        string title;
        bool isRed(node* x) { 
            return (x == nullptr) ? false:(x->color == red); 
        }
        node* colorFlip(node* x) {
            x->color = !x->color;
            x->left->color = !x->left->color;
            x->right->color = !x->right->color;
            cfcount++;
            return x;
        }
        node* rotR(node* x) {
            rrcount++;
            node* y = x->left;
            x->left = y->right;
            y->right = x;
            y->color = x->color;
            x->color = red;
            return y;
        }
        node* rotL(node* x) {
            lrcount++;
            node* y = x->right;
            x->right = y->left;
            y->left = x;
            y->color = x->color;
            x->color = red;
            return y;
        }
        void preorder(node* x) {
            if (x == nullptr) return;
            cout<<x->key<<" ";
            preorder(x->left);
            preorder(x->right);
        }
        virtual node* fixUp(node* x) = 0;
        node* put(node* x, K key, V value) {
            if (x == nullptr) {
                treeSize++;
                return new node(key, value);
            }
            if (key < x->key) x->left = put(x->left, key, value);
            else              x->right = put(x->right, key, value);
            return fixUp(x);
        }
        RedBlackStats printStats() {
            int totRots = lrcount+rrcount;
            double avRots = (double)totRots/(double)treeSize;
            RedBlackStats stats(title, totRots, maxRotations, avRots, lrcount, rrcount,cfcount,treeSize);
            cout<<"Average Rotations/Insert: "<<avRots<<endl;
            cout<<"Max Rotation/Insert: "<<maxRotations<<endl;
            cout<<"Total Rotations: "<<totRots<<endl;
            cout<<"Left Rotations:  "<<lrcount<<endl;
            cout<<"Right Rotations: "<<rrcount<<endl;
            cout<<"Color Flips:     "<<cfcount<<endl;
            return stats;
        }
        RedBlackTree() {
            lrcount = 0;
            rrcount = 0;
            cfcount = 0;
            maxRotations = 0;
            treeSize = 0;
            root = nullptr;
        } 
};

#endif