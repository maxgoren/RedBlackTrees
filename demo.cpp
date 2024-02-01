#include <iostream>
#include "RedBlack23.hpp"
#include "RedBlack234.hpp"
#include "LLRedBlack23.hpp"
#include "ValidateRedBlack.hpp"
using namespace std;

int main() {
    RedBlack23<int,int> rb23;
    RedBlack234<int,int> rb234;
    LLRedBlack23<int,int> llrb23;
    ValidateRB<int,int> validate;
    for (int i = 0; i < 100; i++) {
        int p = rand() % (1337 - 1) + 1;
        rb23.insert(p, i);
        rb234.insert(p, i);
        llrb23.insert(p, i);
    }
    cout<<"2-3-4 Red/Black: \n";
    validate.validate234(rb234.getRoot());
    rb234.stats();
    cout<<"------------\n\n2-3 Red/Black: \n";
    validate.validate23(rb23.getRoot());
    rb23.stats();
    cout<<"------------\n\nLeft Leaning 2-3 Red/Black: \n";
    validate.validate23(llrb23.getRoot());
    llrb23.stats();

    return 0;
}
