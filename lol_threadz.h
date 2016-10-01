#include <stdio.h>
#include <pthread.h>

#ifndef _LOL_THREADZ
#define _LOL_THREADZ

typedef void *lfptr(void *arg);

typedef struct {
    int max;            // max amount of loops?
    int cur;            // current iteration
    char *data;         // data for the function pointer
} lol_arg;

typedef struct {
    int debug;          // display debugging output
    int num_threads;    // number of threads to use
    int join_threads;   // join threads? normally yes/1
    lfptr *lfptr;       // function pointer
    lol_arg *la;        // arguments for function ptr
} lol_threadz;

int lol_threadz_create(lol_threadz lt);

int lol_threadz_create(lol_threadz lt) {
    int er;
    long i;
    void *status;
    pthread_t tid[lt.num_threads];
    for(i=0;i<lt.num_threads;i++) {
        // demonstrating ability to change value after it's passed
        lt.la->cur = 2; // this is an example that needs to be removed
        er = pthread_create(&tid[i], NULL, lt.lfptr, (void*)lt.la);
        if(er != 0) {
            printf("Error creating thread\n");
            return -1;
        } else {
            if(lt.debug == 1) {
                printf("Thread created\n");
            }
        }
    }
    for(i=0;i<lt.num_threads;i++) {
        er = pthread_join(tid[i], &status);
        if(lt.debug == 1) {
            printf("Thread joined\n");
        }
    }
    if(lt.debug == 1) {
        printf("lol_threadz: program completed. Exiting.\n");
    }
    return 1;
}
#endif
