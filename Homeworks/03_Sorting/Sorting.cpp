#include <array>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>

const int N{3};
constexpr size_t S{2 << N};
using a_int = std::array<int, S>;
using a_double = std::array<double, S>;

template <typename T>
void linear_fill(T &A);

template <typename T>
void random_fill_int(T &A, int min = 0, int max = S);

template <typename T>
void random_fill_double(T &A, double min = 0.0, double max = (double)S);

template <typename T>
void insertion_sort(T &A, size_t l = 0, size_t r = S - 1);

template <typename T>
void quick_sort(T &A, size_t l = 0, size_t r = S - 1);

template <typename T>
size_t partition(T &A, size_t l = 0, size_t r = S - 1, size_t p = 0);

template <typename T>
void counting_sort(T &A, int min, int max);

template <typename T>
void radix_sort(T &A, unsigned int d);

template <typename T>
void bucket_sort(T &A);

template <typename T>
void select_sort(T &A);

template <typename T>
size_t select_aux(T &A, size_t i, size_t l = 0, size_t r = S - 1);

template <typename T>
size_t select_pivot(T &A, size_t l = 0, size_t r = S - 1);

template <typename T>
void check(T &A);

template <typename T>
void print(T &A);

int main()
{
    a_int A{};
    constexpr int min = 0;
    constexpr int max = 31;
    std::cout << "Array size = " << A.size() << std::endl;
    srand(time(NULL));

    random_fill_int(A, min, max);
    insertion_sort(A, 0, A.size() - 1);
    check(A);
    //print(A);

    random_fill_int(A, min, max);
    quick_sort(A, 0, A.size() - 1);
    check(A);
    //print(A);

    random_fill_int(A, min, max);
    counting_sort(A, min, max);
    check(A);
    //print(A);

    random_fill_int(A, 2 << 9, 2 << 12);
    radix_sort(A, 4);
    check(A);
    //print(A);

    a_double B{};
    random_fill_double(B, 0.0, 1.0);
    bucket_sort(B);
    check(B);

    random_fill_int(A);
    size_t i = rand() % A.size();
    size_t p = select_aux(A, i);
    std::cout << "If A was sorted the value in position: " << i << " would be: " << A[p] << std::endl;
    insertion_sort(A);
    std::cout << "After sorting A[" << i << "] is: " << A[p] << std::endl;

    a_int C = {16, 2, 45, 12, -5, 1, 13, 11, 7, -1, -14, 18, 12, -8, 22, 0};
    i = rand() % C.size();
    p = select_aux(C, i);
    std::cout << "If C was sorted the value in position: " << i << " would be: " << C[p] << std::endl;
    insertion_sort(C);
    std::cout << "After sorting C[" << i << "] is: " << C[p] << std::endl;
    
    return 0;
}

template <typename T>
void print(T &A)
{
    std::cout << "Array: ";
    for (auto &x : A)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void random_fill_int(T &A, int min, int max)
{
    std::cout << "Ramdom filling the array...\t";
    for (auto &x : A)
    {
        x = rand() % (max - min) + min;
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void random_fill_double(T &A, double min, double max)
{
    std::cout << "Ramdom filling the array...\t";
    for (auto &x : A)
    {
        x = double(rand()) / RAND_MAX * (max - min) + min;
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void linear_fill(T &A)
{
    std::cout << "Lineary filling the array...\t";
    for (size_t i = 0; i < S; ++i)
    {
        A[i] = i;
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void inv_linear_fill(T &A)
{
    std::cout << "Inverse lineary filling the array...\t";
    for (size_t i = 0; i < S; ++i)
    {
        A[i] = S - i - 1;
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void insertion_sort(T &A, size_t l, size_t r)
{
    std::cout << "Insertion sorting the array...\t";
    size_t j{};
    for (size_t i = l + 1; i <= r; ++i)
    {
        j = i;
        while (j > l && A[j] < A[j - 1])
        {
            std::swap(A[j], A[j - 1]);
            j--;
        }
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
size_t partition(T &A, size_t l, size_t r, size_t p)
{
    if(l==r) return l;
    std::swap(A[p], A[l]);
    p = l;
    l++;
    while (l <= r)
    {
        if (A[l] > A[p])
        {
            std::swap(A[l], A[r]);
            r--;
        }
        else
        {
            l++;
        }
    }
    std::swap(A[p], A[r]);
    return r;
}

template <typename T>
void quick_sort(T &A, size_t l, size_t r)
{
    if ((r - l + 1) == A.size())
        std::cout << "Quick sorting the array...\t";
    if (l < r)
    {
        size_t p = partition(A, l, r, l);
        if (p > l)
            quick_sort(A, l, p - 1);
        if (p < r)
            quick_sort(A, p + 1, r);
    }
    if ((r - l + 1) == A.size())
        std::cout << "Done!" << std::endl;
}

template <typename T>
void counting_sort(T &A, const int min, const int max)
{
    std::cout << "Counting sorting the array...\t";
    int range = max - min;
    std::array<int, 32> C{0};
    T B{0};
    for (int i = 0; i < A.size(); ++i)
    {
        C[A[i] - min]++;
    }
    for (int j = 1; j <= range; ++j)
    {
        C[j] += C[j - 1];
    }
    for (int i = A.size() - 1; i >= 0; --i)
    {
        B[C[A[i] - min]] = A[i];
        C[A[i] - min]--;
    }
    B[C[A[0] - min]] = A[0];
    for (int i = 0; i < A.size(); ++i)
    {
        A[i] = B[i];
    }
    std::cout << "Done!" << std::endl;
}

/* void radix_sort(a_int& A, size_t d){
    std::cout << "Radix sorting the array..." << std::endl;
    for(size_t i=0; i<d; ++i){
        std::array<std::pair<int,size_t>,S> p;
        for(size_t i=0; i<A.size()-1; ++i){
            p[i] = { A[i] / (int)pow(10,d) % 10, i };
        }
        //sort(p);
        a_int tmp{};
        for(size_t i=0; i<A.size(); ++i){
            tmp[i] = A[p[i].second];
        }
        A = tmp;
    }
    std::cout << "Done!" << std::endl;

} */

template <typename T>
void radix_sort(T &A, unsigned int d)
{
    std::cout << "Radix sorting the array...\t";
    unsigned int m, p, tmp;
    size_t idx, count;
    std::list<int> pocket[10];
    for (unsigned int i = 0; i < d; ++i)
    {
        m = (int)pow(10, i + 1);
        p = (int)pow(10, i);
        for (size_t j = 0; j < S; ++j)
        {
            tmp = A[j] % m;
            idx = tmp / p;
            pocket[idx].push_back(A[j]);
        }
        count = 0;
        for (unsigned int j = 0; j < 10; ++j)
        {
            while (!pocket[j].empty())
            {
                A[count] = *(pocket[j].begin());
                pocket[j].erase(pocket[j].begin());
                count++;
            }
        }
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void bucket_sort(T &A)
{
    std::cout << "Buket sorting the array...\t";
    std::list<double> bucket[A.size()];
    size_t idx{}, count{};
    for (size_t i = 0; i < A.size(); ++i)
    {
        idx = floor(A[i] * A.size());
        bucket[idx].push_back(A[i]);
    }
    count = 0;
    for (unsigned int j = 0; j < A.size(); ++j)
    {
        bucket[j].sort();
        while (!bucket[j].empty())
        {
            A[count] = *(bucket[j].begin());
            bucket[j].erase(bucket[j].begin());
            count++;
        }
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
size_t select_pivot(T &A, size_t l, size_t r)
{
    T B{A};
    size_t range{r - l + 1};
    if (range <= 5)
    {
        quick_sort(B, l, r);
        return B[(r + l) / 2];
    }

    for (size_t i = 0; i <= range; i += 5)
    {
        if (i > range - 5)
        {
            if (range % 5 == 1)
                B[l + i / 5] = B[l + i];
            else
            {
                quick_sort(B, l+i, l+i+range%5-1);
                B[l + i / 5] = B[(l + i + l + i + range % 5 - 1) / 2];
            }
        }
        else
        {
            quick_sort(B, l + i, l + i + 4);
            B[l + i / 5] = B[l + i + 2];
        }
    }

    range = (range - 1) / 5;
    return select_pivot(B, l, l+range);
}

template <typename T>
size_t select_aux(T &A, size_t i, size_t l, size_t r)
{
    if(l==r) return l;
    size_t p = select_pivot(A, l, r);
    size_t k = partition(A, l, r, p);
    if (i == k)
    {
        return k;
    }
    if (i < k)
    {
        if(k==l) return k;
        return select_aux(A, i, l, k - 1);
    }
    if (i > k)
        if(k==r) return k;
    {
        return select_aux(A, i, k + 1, r);
    }
}

template <typename T>
void select_sort(T &A)
{
    std::cout << "Select sorting the array...\t";
    T tmp{A};
    for (size_t i = 0; i < A.size(); ++i)
    {
        std::cout << i;
        tmp[i] = A[select_aux(A, i)];
    }
    A = tmp;
    std::cout << "Done!" << std::endl;
}

template <typename T>
void check(T &A)
{
    bool test{1};
    for (size_t i = 0; i < A.size() - 1; ++i)
    {
        if (A[i] > A[i + 1])
        {
            test = 0;
            break;
        }
    }
    (test != 0) ? (std::cout << "Test passed!" << std::endl) : (std::cout << "Test failed!" << std::endl);
}
