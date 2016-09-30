#include <stdio.h>
#include <pthread.h>

#ifndef _LOL_THREADZ
#define _LOL_THREADZ

typedef void *lfptr(void *arg);

typedef struct {
    int debug;          // display debugging output
    int num_threads;    // number of threads to use
    int join_threads;   // join threads? normally yes/1
    lfptr *lfptr;       // function pointer
} lol_threadz;

int lol_threadz_create(lol_threadz lt);

int lol_threadz_create(lol_threadz lt) {
    int er, i;
    pthread_t tid[lt.num_threads];
    for(i=0;i<lt.num_threads;i++) {
        er = pthread_create(&tid[i], NULL, lt.lfptr, NULL);
        if(er != 0) {
            printf("Error creating thread\n");
            return -1;
        } else {
            printf("Thread created\n");
        }
    }
    return 1;
}
#endif
