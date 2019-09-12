#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 

void M(size_t *p, size_t *m, size_t *s, size_t n);
void M_Aux (size_t *p, size_t *m, size_t *s, size_t i, size_t j, size_t n);
void print(size_t *m, size_t *s, size_t n);

double get_execution_time(const struct timespec b_time, const struct timespec e_time){
  return (e_time.tv_sec-b_time.tv_sec) + (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int main(){


    size_t* m{new size_t[2<<22]};
    size_t* s{new size_t[2<<20]};

    for(int e=2; e<12; ++e){
        size_t n = 2<<e;
        std::cout << "N = " << n << std::endl;
        srand (time(NULL));
        size_t p[n+1];
        //std::cout << "p = ";
        for(size_t x=0; x<=n; ++x){
            p[x] =  rand() % 1024 + 1;
            //std::cout << p[x] << " ";
        }
        std::cout << std::endl;

        struct timespec b_time, e_time;

        clock_gettime(CLOCK_REALTIME, &b_time);
        M(p, m, s, n);  
        clock_gettime(CLOCK_REALTIME, &e_time);

        std::cout << "Wall time: " << get_execution_time(b_time, e_time) << std::endl;
        std::cout << std::endl;
    }

    delete[] m;
    delete[] s;

    return 0;
}


void M(size_t *p, size_t *m, size_t *s, size_t n){

    for (size_t i=0; i < n; ++i){
        m[i*(n+1)] = 0;
    }

    for (size_t l = 1; l < n; ++l){
        for (size_t i = 0; i < (n - l); ++i){
            size_t j = i + l;
	        M_Aux(p, m, s, i, j, n);
	    }
    }
}


void M_Aux (size_t *p, size_t *m, size_t *s, size_t i, size_t j, size_t n){

    m[i*n + j] = SIZE_MAX;

    for (size_t k = i; k < j; ++k){
        size_t tmp = m[i*n+k] + m[(k+1)*n+j] + p[i]*p[k+1]*p[j+1];
	    if ( tmp < m[i*n+j]){
            m[i*n+j] = tmp;
	        s[i*n+j] = k;
	    }
    }
}

void print(size_t *m, size_t *s, size_t n){

    std::cout << "M =" << std::endl;

    for(size_t i=0; i<n; ++i){
        for(size_t j=0; j<n; ++j){
            std::cout << m[i*n+j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "S =" << std::endl;

    for(size_t i=0; i<n-1; ++i){
        for(size_t j=0; j<n-1; ++j){
            std::cout << s[i*n+j] << "\t";
        }
        std::cout << std::endl;
    } 
}
