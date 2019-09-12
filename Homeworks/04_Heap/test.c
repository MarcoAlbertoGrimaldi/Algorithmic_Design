#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
    size_t N=32;
    int* i=(int*)malloc(sizeof(int)*N);
    i[0]=N;
    printf("%d\n", i[0]);
    printf("%d\n", i[N]);
    printf("%d\n", i[N+1]);
    printf("%d\n", i[N+2]);

    N = (int)N*1.4;
    i = realloc(i, N);

    i[0]=N;
    printf("%d\n", i[0]);
    printf("%d\n", i[N]);
    printf("%d\n", i[N+1]);
    printf("%d\n", i[N+2]);

    printf("%d   ", (int)56>>4);
    printf("%d", 2<<1);
    
    free(i);
}