#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define MIN -64
#define MAX 64

int* alloc_array(const size_t S);
size_t increase_size(int* old);
void check(int* H);

size_t left(size_t i){
    return 2*i;
}

size_t right(size_t i){
    return 2*i+1;
}

size_t parent(size_t i){
    return floor(i/2);
}

size_t get_root(){
    return 1;
}

unsigned int is_root(size_t i){
    return (i==1);
}

size_t size(int* H){
    return H[0];
}

unsigned int is_valid_node(int* H, size_t i){
    return (H[0]>=i);
}

int get_min(int* H){
    return H[1];
}

void swap(int* H, size_t i, size_t j){
    if(i>size(H) || j>size(H)) printf("error: %lu-%lu\n", i,j);
    int tmp = H[i];
    H[i] = H[j];
    H[j] = tmp;
}

void heapify(int* H, size_t i);
void iter_heapify(int* H);
void rm_min(int* H, size_t i);
void build_heap(int* H);
void decrease_key(int* H, size_t i, int v);
void new_max(int* old, size_t* Max);
void insert(int* H, int v, size_t* Max);
void mediocre_print(int* H);
void print_lvl(int* H, int lvl);
void print(int* H);


 
void heapify(int* H, size_t i){
    size_t m = i;
    for(size_t j=left(i); j<=right(i); ++j){
        if (is_valid_node(H, j) && H[j] < H[m]){
            m = j;
        } 
    }
    if (i!=m) {
        swap(H, i, m);
        heapify(H, m);
    }
}

void rm_min(int* H, size_t i){
    H[1] = H[size(H)];
    H[0] -= 1; 
    heapify(H, get_root());
}

void build_heap(int* H){
    printf("Building Heap...\t");
    size_t S = size(H);
    for(size_t i=parent(S); i>=1; --i){
        heapify(H, i);
    }
    printf("Done!\n");
}

void decrease_key(int* H, size_t i, int v){
    if(H[i]<=v) printf("Error: %d is not smaller then %d!\n", v, H[i]);
    else {
        H[i] = v;
        while(!(is_root(i) || H[parent(i)] <= H[i])){
            swap(H, i, parent(i));
            i = parent(i);
        }
    }
}

int* alloc_array(const size_t S){
    srand (time(NULL));
    printf("Inizializing the array with random integers...\t");
    int* H = (int*)malloc(sizeof(int)*(S+1));
    H[0] = (int)S;
    for(size_t i=1; i<=S; i++){
        H[i] = rand() % (MAX-MIN) + MIN;
    }
    printf("Done!\n");
    return H;
}

size_t increase_size(int* old){
    size_t old_size = old[0];
    size_t new_size = old_size*(1 + 10*log(2)/log(old_size));
    printf("Reallocating the array with the new size = %lu...\t", new_size);
    old = (int*)realloc(old, sizeof(int)*new_size);
    printf("Done!\n");
    return new_size;
}

void new_max(int* old, size_t* Max){
    *Max = increase_size(old);
}

void insert(int* H, int v, size_t* Max){
    printf("Inserting new value: %d...\n", v);
    if(H[0] == *Max) new_max(H, Max);
    H[0] += 1;
    H[H[0]] = INT_MAX;
    decrease_key(H, H[0], v);
    printf("Done!\n");
}

void check(int* H){
    printf("Checking heap propiety...\t");
    unsigned int test=1;
    for(size_t i=2; i<=size(H); ++i){
        if(H[i]<H[parent(i)]){
            test = 0;
            printf("Error! H[%lu]=%d < H[%lu]=%d\n", i, H[i], parent(i), H[parent(i)]);
            break;
        }
    }
    if(test) printf("Ok!\n");
}

/
void iter_heapify(int* H) {
    size_t n = size(H);
    for (size_t i = 2; i <= n; i++) {
        if (H[i] < H[parent(i)]) {
            size_t j = i;
            while (H[j] < H[parent(j)] && j!=1) {
                swap(H, j, parent(j));
                j = parent(j);
            } 
        } 
    } 
}

void mediocre_print(int* H){
    int j = 1;
    for(int i=0; i<=7-j*2; ++i) printf("\t");
    printf("     %d\n", H[1]);
    for(int i=0; i<=7-j*2; ++i) printf("\t");
    for(size_t i=2; i<H[0]; ++i){
        printf("%d\t", H[i]);
        if(i==(2<<j)-1) {
            printf("\n");
            for(int i=0; i<=6-j*2; ++i) printf("\t");
            ++j;
        }
    }
    printf("\n");
}