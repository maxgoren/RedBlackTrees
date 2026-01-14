#ifndef rbnode_hpp
#define rbnode_hpp

const bool red = true;
const bool black = false;

template <class K>
struct rbnode {
    K info;
    bool color;
    rbnode* left;
    rbnode* right;
    rbnode(K k = K(), bool c = red, rbnode* ll = nullptr, rbnode* rr = nullptr) : info(k), color(c), left(ll), right(rr) { }
};

template <class K>
class RBIterator {
    private:
        using link = rbnode<K>*;
        link st[255];
        int n;
    public:
        RBIterator(link root) {
            n = 0;
            link x = root;
            while (x != nullptr) {
                st[n++] = x;
                x = x->left;
            }
        }
        bool done() {
            return n == 0;
        }
        K& get() {
            return st[n-1]->info;
        }
        void next() {
            auto x = st[--n];
            x = x->right;
             while (x != nullptr) {
                st[n++] = x;
                x = x->left;
            }
        }
}; 

#endif