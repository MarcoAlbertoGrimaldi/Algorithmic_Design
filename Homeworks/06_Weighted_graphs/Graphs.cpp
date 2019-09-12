#include <iostream>
#include <utility>
#include <iterator>
#include <vector>
#include <memory>
#include <string>
#include <math.h>

struct node
{
    char colour = 'w';
    unsigned int dist = INT16_MAX;
    node* prec = nullptr;

    node();
    ~node() = default;
};

struct Dense_Graphs
{
    unsigned int size;
    bool *adj_m;
    double density;
    unsigned int *dist_m;
    node* nodes;

    Dense_Graphs(unsigned int s) : size{s}
    {
        this->adj_m = new bool[s * s]{};
        this->dist_m = new unsigned int[s * s]{};
        this->density = log(2*s) / s;
        this->nodes = new node[s]{};
    };

    ~Dense_Graphs() = default;

    void rng_fill()
    {
        std::cout << "Random filling adj_m. matrix...\t"; 
        for (size_t i = 0; i < size * size; ++i)
        {
            if ((rand() % 100) <= (density * 100)) adj_m[i] = 1;
            if ((i % (size + 1)) == 0) dist_m[i] = 0;
            else dist_m[i] = INT16_MAX;
        }
        std::cout << "Done!\n";
    }
};

void print_adj_m(Dense_Graphs *dg)
{
    unsigned int s = dg->size;
    for (unsigned int i = 0; i < s; i++)
    {
        for (unsigned int j = 0; j < s; j++)
        {
            std::cout << dg->adj_m[i * s + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_dist(Dense_Graphs *dg)
{
    unsigned int s = dg->size;
    for (unsigned int i = 0; i < s; i++)
    {
        for (unsigned int j = 0; j < s; j++)
        {
            std::cout << dg->dist_m[i * s + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



int main()
{
    Dense_Graphs dg{8};
    dg.rng_fill();
    print_adj_m(&dg);
    print_dist(&dg);

    return 0;
}
