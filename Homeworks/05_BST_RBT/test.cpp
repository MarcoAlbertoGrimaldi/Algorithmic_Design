#include <iostream>
#include <utility>
#include <iterator>
#include <vector> 
#include <memory>
#include <string>

struct node{
    node* parent;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    int value;

    node(node* n, int v) : parent{n}, value{v}{};
    ~node() = default;
};

int main(){

    std::unique_ptr<node> up_r (new node{nullptr, 0});
    std::cout << "up_r.get() " <<  up_r.get() << std::endl;
    std::cout << "up_r->value " <<  up_r->value << std::endl;
    up_r->left.reset(new node{nullptr, 2});
    std::cout << "up_r->left.get() " <<  up_r->left.get() << std::endl;
    std::cout << "up_r->left->value " << up_r->left->value << std::endl;
    std::cout << "up_r.get()->left->value " << up_r->left->value << std::endl;
    node* sp = up_r.get();
    std::cout << "sp->left->value  " <<  sp->left->value << std::endl;
    node* vp = up_r.release();
    std::cout << "vp " << vp << std::endl;
    std::cout << "vp->value " << vp->value << std::endl;
    std::cout << "up_r.get() " <<  up_r.get() << std::endl;

    std::unique_ptr<node> n_up{vp};
    
    return 0;

}