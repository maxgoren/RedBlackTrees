#ifndef redblack_hpp
#define redblack_hpp
#include <iostream>
#include <stack>
#include <limits>
using namespace std;

using RBColor = bool;

const static RBColor black = false;
const static RBColor red = true;

template <class Item>
struct RBNode {
    Item key;
    RBColor color;
    RBNode* left;
    RBNode* right;
    RBNode(Item item, RBColor col, RBNode* l, RBNode* r) : key(item), color(col), left(l), right(r) { }
};

template <class Item>
class RBIterator {
    private:
        using link = RBNode<Item>*;
        stack<link> st;
        link sentinel;
    public:
        RBIterator(link root, link nilsent) {
            sentinel = nilsent;
            link x = root;
            while (x != sentinel) {
                st.push(x);
                x = x->left;
            }
        }
        bool done() {
            return st.empty();
        }
        Item& get() {
            return st.top()->key;
        }
        void next() {
            link curr = st.top(); st.pop();
            curr = curr->right;
            while (curr != sentinel) {
                st.push(curr);
                curr = curr->left;
            }
        }
};

template <class Item>
class RedBlack {
    private:
        using node = RBNode<Item>;
        using link = node*;
        link head, z;
        bool isRed(link h) {
            return h->color == red;
        }
        bool isBlack(link h) {
            return !isRed(h);
        }
        link rotateLeft(link h) {
            link x = h->right; h->right = x->left; x->left = h;
            x->color = h->color;
            h->color = red;
            return x;
        }
        link rotateRight(link h) {
            link x = h->left; h->left = x->right; x->right = h;
            x->color = h->color;
            h->color = red;
            return x;
        }
        link rotate(Item v, link h) {
            link c, gc;
            c = (v < h->key) ? h->left:h->right;
            if (v < c->key) {
                gc = rotateRight(c);
            } else {
                gc = rotateLeft(c);
            }
            if (v < h->key) h->left = gc; else h->right = gc;
            return gc;
        }
        void split(link gg, link g, link p, link x, Item v) {
            x->color = red;
            x->left->color = black;
            x->right->color = black;
            if (isRed(p)) {
                g->color = red;
                if (v < p->key != v < g->key) p = rotate(v, g);
                x = rotate(v, gg);
                x->color = black;
            }
        }
        link pushRedDown(link par, link grand, Item v) {
            link curr, sib;
            if (v < par->key) {
                curr = par->left;
                sib = par->right;
            } else {
                curr = par->right;
                sib = par->left;
            }
            if (isBlack(curr) && isRed(sib)) {
                par = v < par->key ? rotateLeft(par):rotateRight(par);
            }
            curr = (v < par->key) ? par->left:par->right;
            if (curr != z && isBlack(curr) && isBlack(curr->left) && isBlack(curr->right))
                par = (v < par->key) ? pushLeft(par, v):pushRight(par, v);
            if (v < grand->key) grand->left = par; else grand->right = par;
            return par;
        }
        link colorFlip(link curr) {
            curr->color = !curr->color;
            curr->left->color = !curr->left->color;
            curr->right->color = !curr->right->color;
            return curr;
        }
        link pushRight(link curr, Item v) {
            curr = colorFlip(curr);
            if (curr->left != z) {
                if (isRed(curr->left)) {
                    if (isRed(curr->left->right)) {
                        curr->left = rotateLeft(curr->left);
                        curr = rotateRight(curr);
                        curr = colorFlip(curr);
                    } else if (isRed(curr->left->left)) {
                        curr = rotateRight(curr);
                        curr = colorFlip(curr);
                    }
                }
            }
            return curr;
        }
        link pushLeft(link curr, Item v) {
            curr = colorFlip(curr);
            if (curr->right != z) {
                if (isRed(curr->right)) {
                    if (isRed(curr->right->left)) {
                        curr->right = rotateRight(curr->right);
                        curr = rotateLeft(curr);
                        curr = colorFlip(curr);
                    } else if (isRed(curr->right->right)) {
                        curr = rotateLeft(curr);
                        curr = colorFlip(curr);
                    }
                }
            }
            return curr;
        }
        bool validate(link x, int bb) {
            if (x == z) {
                if (bb != 0) {
                    cout<<"Black Balance: "<<bb<<endl;
                }
                return bb == 0;
            }
            if (isBlack(x)) bb--;
            if (x->left != z && x->left->key > x->key) {
                cout<<"Not BST order."<<endl;
                return false;
            }
            if (x->right != z && x->right->key < x->key) {
                cout<<"Not BST order."<<endl;
                return false;
            }
            if (isRed(x) && isRed(x->left) && x != x->left) {
                cout<<"Red violation"<<endl;
                return false;
            }
            if (isRed(x) && isRed(x->right) && x != x->right) {
                cout<<"Red violation"<<endl;
                return false;                
            }
            return validate(x->left, bb) && validate(x->right, bb);
        }
        void cleanup(link h) {
            if (h != z) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
        link min(link x) {
            if (x == z)
                return x;
            auto it = x;
            while (it->left != z) it = it->left;
            return it;
        }
        link max(link x) {
            if (x == z)
                return x;
            auto it = x;
            while (it->right != z) it = it->right;
            return it;
        }
        link clone(link o, link e) {
            if (o == e)
                return z;
            return new node(o.key, o.color, clone(o->left, e), clone(o->right, e));
        }
    public:
        RedBlack() {
            z = new node(std::numeric_limits<Item>::max(), black, nullptr, nullptr);
            z->left = z; z->right = z;
            head = new node(std::numeric_limits<Item>::min(), black, z, z);
        }
        RedBlack(const RedBlack& rbi) {
            z = new node(std::numeric_limits<Item>::max(), black, nullptr, nullptr);
            z->left = z; z->right = z;
            head = new node(std::numeric_limits<Item>::min(), black, z, z);
            head->right = clone(rbi.head->right, rbi.z);
        }
        ~RedBlack() {
            cleanup(head);
        }
        bool isRedBlack() {
            if (head->right == z)
                return true;
            link t = head->right;
            int bb = 0;
            while (t != z) {
                if (isBlack(t)) bb++;
                t = t->left;
            }
            return validate(head->right, bb);
        }
        void insert(Item data) {
            link gg = head;
            link g = head;
            link p = head;
            link x = head;
            while (x != z) {
                gg = g; g = p; p = x;
                x = (data < x->key) ? x->left:x->right;
                if (isRed(x->left) && isRed(x->right))
                    split(gg, g, p, x, data);
            }
            x = new node(data, red, z, z);
            if (data < p->key) p->left = x; else p->right = x;
            split(gg, g, p, x, data);
            head->right->color = black;
        }
        void erase(Item v) {
            link g = head;
            link p = head; link x = head->right;
            if (isBlack(x->left) && isBlack(x->right))
                x->color = red;
            while (x != z) {
                x = pushRedDown(x, p, v);
                if (v == x->key) { 
                    if (x->right == z) {
                        link t = x;
                        if (x == p->left) p->left = x->left; else p->right = x->left;
                        x = z;
                        delete t;
                    } else {
                        v = min(x->right)->key;
                        x->key = v;
                        p = x;
                        x = x->right;
                    }
                } else {
                    p = x;
                    x = (v < x->key) ? x->left:x->right;
                }
            }
            head->right->color = black;
            z->color = black;
            head->color = black;
        }
        void print() {
            stack<link> st;
            st.push(head->right);
            while (!st.empty()) {
                link curr = st.top(); st.pop();
                if (curr != z) {
                    cout<<curr->key<<" ";
                    st.push(curr->right);
                    st.push(curr->left);
                }
            }
            cout<<endl;
        }
        RBIterator<Item> iterator() {
            return RBIterator<Item>(head->right, z);
        }
        RedBlack& operator=(const RedBlack& rbi) {
            if (this != &rbi) {
                z = new node(std::numeric_limits<Item>::max(), black, nullptr, nullptr);
                z->left = z; z->right = z;
                head = new node(std::numeric_limits<Item>::min(), black, z, z);
                head->right = clone(rbi.head->right, rbi.z);
            }
            return *this;
        }
};

#endif