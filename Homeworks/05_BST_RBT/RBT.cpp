#include <iostream>
#include <utility>
#include <iterator>
#include <vector>
#include <memory>
#include <string>


struct node
{
    node *parent = nullptr;
    node *left = nullptr;
    node *right = nullptr;
    int key;
    char colour = 'r';

    node() = default;
    //node(node* p, char c) : parent{p}, colour{c} {};
    node(int k) : key{k} {};
    node(node *n, int k) : parent{n}, key{k} {};
    ~node() = default;
};

struct RBT
{
    node *root = nullptr;

    RBT() = default;
    RBT(node* p) : root{p}{};
    ~RBT() = default;

    bool is_right_child(node *n)
    {
        return (n->parent->right == n);
    }

    node *sibling(node *n)
    {
        if (is_right_child(n))
            return n->parent->left;
        return n->parent->right;
    }

    node *uncle(node *n)
    {
        return sibling(n->parent);
    }

    char childhood_side(node *n)
    {
        if (is_right_child(n))
            return 'r';
        return 'l';
    }

    char reverse_side(char s)
    {
        if (s == 'l')
            return 'r';
        return 'l';
    }

    node *get_child(node *p, char s)
    {
        if (s == 'l')
            return p->left;
        return p->right;
    }

    void set_child(node *pn, char s, node *cn)
    {
        if (s == 'l')
            pn->left = cn;
        else
            pn->right = cn;
    }

    node *granparent(node *n)
    {
        return n->parent->parent;
    }

    void in_order_walk_aux(node *n)
    {
        if (n != nullptr)
        {
            in_order_walk_aux(n->left);
            std::cout << n->key << " - " << n->colour << "\t";
            in_order_walk_aux(n->right);
        }
    }

    void in_order_walk()
    {
        in_order_walk_aux(root);
    }

    node *min_sub_tree(node *n)
    {
        while (n->left != nullptr)
            n = n->left;
        return n;
    }

    node *max_sub_tree(node *n)
    {
        while (n->right != nullptr)
            n = n->right;
        return n;
    }

    node *search_subtree(node *n, int v)
    {
        if (n == nullptr)
            return n;
        if (n->key <= v)
        {
            if (v <= n->key)
                return n;
            return search_subtree(n->right, v);
        }
        return search_subtree(n->left, v);
    }

    node *successor(node *n)
    {
        if (n->left != nullptr)
            return min_sub_tree(n->left);
        node *p = n->parent;
        while (p != nullptr && is_right_child(n))
        {
            n = p;
            p = n->parent;
        }
        return p;
    }

/*     void insert_leafs(node* z){
        z->left = new node{z, 'b'};
        z->right = new node{z, 'b'};
    } */

    void insert_bst(node *z)
    {   
        std::cout << "Inserting new node...\t";
        node *x = root;
        node *y = x;
        while (x != nullptr)
        {
            y = x;
            z->key <= x->key ? x = x->left : x = x->right;
        }
        z->parent = y;
        if (y == nullptr)
        {
            root = z;
            //insert_leafs(z);
        }
        else if (z->key <= y->key)
        {
            y->left = z;
            //insert_leafs(z);
        }
        else
        {
            y->right = z;
            //insert_leafs(z);
        }
        std::cout << "Done!\n";
    }

    void transplant(node *x, node *y)
    {
        if (x->parent == nullptr)
            root = y;
        else
        {
            char x_side = childhood_side(x);
            set_child(x->parent, x_side, y);
        }
        if (y != nullptr)
            y->parent = x->parent;
    }

    node *remove_bst(node *z)
    {
        if (z->left == nullptr)
        {
            transplant(z, z->right);
            return z;
        }
        if (z->right = nullptr)
        {
            transplant(z, z->left);
            return z;
        }
        node *next = min_sub_tree(z->right);
        z->key = next->key;
        return remove_bst(next);
    }

    void rotate(node *x, char s)
    {
        char r_side = reverse_side(s);
        node *y = get_child(x, r_side);
        transplant(x, y);
        node *b = get_child(y, s);
        if(b==nullptr){
            if(s == 'l') y->left = x;
            else y->right = x;
            x->parent = y;
        } else {
            transplant(b, x);
            set_child(x, r_side, b);
            b->parent = x;
        }
    }

    void insert_rbt(node *z)
    {
        insert_bst(z);
        z->colour = 'r';
        fix_insert_rbt(z);
    }

    node *fix_insert_rbt_1(node *z)
    {
        uncle(z)->colour = 'b';
        z->parent->colour = 'b';
        granparent(z)->colour = 'r';
        return granparent(z);
    }

    node *fix_insert_rbt_2(node *z)
    {
        node *p = z->parent;
        char z_side = childhood_side(z);
        rotate(p, reverse_side(z_side));
        return p;
    }

    void fix_insert_rbt_3(node *z)
    {
        node *g = granparent(z);
        z->parent->colour = 'b';
        g->colour = 'r';
        rotate(g, childhood_side(z));
    }

    void fix_insert_rbt(node *z)
    {
        while (z->parent != nullptr && (granparent(z) != nullptr || z->parent->colour == 'r'))
        {
            if (uncle(z)->colour == 'r')
                z = fix_insert_rbt_1(z);
            else
            {
                if (childhood_side(z) != childhood_side(z->parent))
                    z = fix_insert_rbt_2(z);
                fix_insert_rbt_3(z);
            }
        }
        root->colour = 'b';
    }

    node *remove_rbt(node *z)
    {
        node *y = remove_bst(z);
        if (y->colour = 'b')
        {
            node *x;
            if (y->left == nullptr)
            {
                x = y->right;
            }
            else
            {
                x = y->left;
            }
            fix_remove_rbt(x);
        }
        return y;
    }

    void fix_remove_rbt_1(node *x)
    {
        sibling(x)->colour = 'b';
        x->parent->colour = 'r';
        rotate(x, childhood_side(x));
    }

    node *fix_remove_rbt_2(node *x)
    {
        sibling(x)->colour = 'r';
        return x->parent;
    }

    void fix_remove_rbt_3(node *x)
    {
        char x_side = childhood_side(x);
        char r_side = reverse_side(x_side);
        node *w = get_child(x->parent, r_side);
        get_child(w, x_side)->colour = 'b';
        w->colour = 'r';
        rotate(w, r_side);
    }

    void fix_remove_rbt_4(node *x)
    {
        char x_side = childhood_side(x);
        char r_side = reverse_side(x_side);
        node *w = get_child(x->parent, r_side);
        get_child(w, r_side)->colour = 'b';
        w->colour = x->parent->colour;
        x->parent->colour = 'b';
        rotate(x->parent, x_side);
    }

    void fix_remove_rbt(node *x)
    {
        while (x != root && x->colour != 'r')
        {
            node *w = sibling(x);
            if (w->colour == 'r')
                x = fix_insert_rbt_1(x);
            else
            {
                char x_side = childhood_side(x);
                char r_side = reverse_side(x_side);
                if (get_child(w, r_side)->colour == 'r')
                {
                    fix_remove_rbt_4(x);
                    return;
                }
                else
                {
                    if (get_child(w, x_side)->colour == 'r')
                        fix_remove_rbt_3(x);
                    else
                        fix_remove_rbt_2(x);
                }
            }
        }
    }
};

int main()
{
    std::cout.setf(std::ios::unitbuf);
    RBT Tree{nullptr};
    node* A[8];
    for (size_t i = 0; i < 7; ++i)
    {
        A[i] = new node{rand() % 64};
        Tree.insert_rbt(A[i]);
        Tree.in_order_walk();
    }
    Tree.in_order_walk();
    return 0;
}