#include <stdio.h>
#include "lol_primez.h"
#include "lol_threadz.h"

void *thread_test(void *arg);

int main() {
    /* thread stuff */
    lol_threadz lt;             // thread arguments
    lt.debug = 0;               // debugging on / off
    lt.num_threads = 2;         // number of threads - maybe pass as main arg
    lt.join_threads = 1;        // don't know when this would be 0
    lt.lfptr = &thread_test;    // function pointer for threads to call
    
    lol_arg la;                 // arguments for function pointer
    la.max = 10;                // example int max
    la.cur = 1;                 // example int min
    la.data = "Hello";          // example char array
    
    lt.la = &la;                // add fptr args to threadz args
    int i;                      // simple int for looping
    for(i=0;i<100;i++) {
        lol_threadz_create(lt); // create the threads and wait
    }
    pthread_exit(NULL);         // end the threads
    
    /* prime stuff */
    /*
    size_t p_size = 256;
    //char entropy[ent];
    int i;
    char prime[p_size];
    srand(time(NULL)); // feed the machine
    for(i=0;i<2;i++) {
        if(l_rand_entropy(ent, entropy)) {
            printf("Entropy: %s\n", entropy);
        }
    }
    for(i=0;i<5;i++) {
        l_prime(p_size, prime, 0);
        printf("%s\n\n", prime);
    }
    */
    return 1;
}

void *thread_test(void *arg) {
    lol_arg *la = malloc(sizeof(lol_arg));
    if(la == NULL) {
        printf("Error: couldn't allocate lol_arg memory\n");
    }
    memcpy(la, arg, sizeof(lol_arg));
    printf("%lu thread_test: %s %i\n", la->tid, la->data, la->cur);
    free(la);
    pthread_exit(NULL);
}
