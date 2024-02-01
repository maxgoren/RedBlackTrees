#ifndef validaterb_hpp
#define validaterb_hpp
#include <iostream>
#include "RedBlackNode.hpp"
using namespace std;

template <class K, class V>
class ValidateRB {
    private:
        using node = rbnode<K,V>;
        bool isRed(node* x) { return (x == nullptr) ? false:(x->color == true); }
        bool is23(node* x) {
            if (x == nullptr)
                return true;
            if (isRed(x->left) && isRed(x->right))
                return false;
            if (isRed(x->left) && (isRed(x->left->left) || isRed(x->left->right)))
                return false;
            if (isRed(x->right) && (isRed(x->right->right) || isRed(x->right->left)))
                return false;
            return is23(x->left) && is23(x->right);
        }
        bool is234(node* x) {
            if (x == nullptr)
                return true;
            if (isRed(x->left) && (isRed(x->left->left) || isRed(x->left->right)))
                return false;
            if (isRed(x->right) && (isRed(x->right->right) || isRed(x->right->left)))
                return false;
            return is234(x->left) && is234(x->right);
        }
        bool isBal(node* x, int bb) {
            if (x == nullptr)
                return bb == 0;
            if (!isRed(x)) bb--;
            return isBal(x->left, bb) && isBal(x->right, bb);
        }
        bool isBST(node* x) {
            if (x == nullptr)
                return true;
            if (x->left && x->key < x->left->key)
                return false;
            if (x->right && x->right->key < x->key)
                return false;
            return isBST(x->left) && isBST(x->right);
        }
        bool blackBalance(node* root) {
            int bb = 0;
            node* x = root;
            while (x != nullptr) {
                if (!isRed(x)) bb++;
                x = x->left;
            }
            return isBal(root, bb);
        }
    public:
        ValidateRB() {

        }
        void validate23(node* root) {
            bool black_balanced = blackBalance(root);
            bool is_23_tree = is23(root);
            bool is_bst_tree = isBST(root);
            if (is_bst_tree) cout<<"+ Tree is BST"<<endl;
            else             cout<<"- INVALID BST"<<endl;
            if (is_23_tree) cout<<"+ Tree is 2-3 tree"<<endl;
            else cout<<"- INVALID 2-3 TREE"<<endl;
            if (black_balanced) cout<<"+ Tree is black balanced"<<endl;
            else cout<<"- INVALID BLACK BALANCE."<<endl;
        }
        void validate234(node* root) {
            bool black_balanced = blackBalance(root);
            bool is_234_tree = is234(root);
            bool is_bst_tree = isBST(root);
            if (is_bst_tree) cout<<"+ Tree is BST"<<endl;
            else             cout<<"- INVALID BST"<<endl;
            if (is_234_tree) cout<<"+ Tree is 2-3-4 tree"<<endl;
            else cout<<"- INVALID 2-3-4 TREE"<<endl;
            if (black_balanced) cout<<"+ Tree is black balanced"<<endl;
            else cout<<"- INVALID BLACK BALANCE."<<endl;
        }
};

#endif