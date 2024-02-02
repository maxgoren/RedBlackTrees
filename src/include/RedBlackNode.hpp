#ifndef redblacknode_hpp
#define redblacknode_hpp
#include <iostream>
using namespace std;

const bool red = true;
const bool black = false;

template <class K, class V>
struct rbnode {
    K key;
    V value;
    int id;
    bool color;
    int N;
    rbnode* left;
    rbnode* right;
    rbnode(K key_, V value_) {
        key = key_; value = value_;
        color = true;
        left = nullptr; right = nullptr;
        N = 0;
    }
    rbnode() {
        color = true;
    }
};

struct RedBlackStats {
    string type;
    int totalRotations;
    int maxRotations;
    double avgRotations;
    int lrCount;
    int rrCount;
    int cfCount;
    int treeSize;
    RedBlackStats(string t = "RB", int tr = 0, int mx = 0, double ar = 0, 
                    int lr = 0, int rr = 0, int cf = 0, int ts = 0) {
        type = t; totalRotations = tr; maxRotations = mx; avgRotations = ar;
        lrCount = lr; rrCount = rr; cfCount = cf; treeSize = ts;
    }
};

#endif
