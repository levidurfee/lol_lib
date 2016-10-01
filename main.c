#include <stdio.h>
#include <omp.h>
#include "lol_types.h"
#include "lol_primez.h"

int thread_test(lol_arg *arg);

int main() {
    /* thread args */
    lol_arg *la = lol_arg_new(1000, 1, "Hello", 5);
    int nthreads, tid;
    #pragma omp parallel for private(nthreads, tid)
    for(int i=0;i<la->max;i++) {
        thread_test(la);
    }
    lol_arg_free(la);           // free the malloc
    
    return 1;
}

int thread_test(lol_arg *arg) {
    // libcrypto has lots of memory leaks
    // make test = 1 if debugging. otherwise
    // you'll see a lot of extra info
    int test = 0;
    if(test == 0) {
        int tid;
        tid = omp_get_thread_num();
        size_t p_size = 4096;
        char prime[p_size];
        srand(time(NULL)); // feed the machine
        l_prime(p_size, prime, 0);
        printf("thread: %i status: %i out of %i\nprime: %s\n\n", tid, arg->cur, arg->max, prime);
        arg->cur++;
    } else {
        printf("Debugging\n");
    }
    return 1;
}
