#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "lol_threadz.h"

lol_arg *lol_arg_new(int max, int cur, char *data, int tid) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = (lol_arg) {.max = max, .cur = cur, .data = data, .tid = tid};
    return out;
}

lol_arg *lol_arg_copy(lol_arg const *in) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = *in;
    return out;
}

void lol_arg_free(lol_arg *in) { free(in); }

lol_threadz *lol_threadz_new(
        int debug, 
        int num_threads, 
        int join_threads,
        lfptr *lfptr,
        lol_arg *la) {
    lol_threadz *out = malloc(sizeof(lol_threadz));
    *out = (lol_threadz) {
        .debug = debug, .num_threads = num_threads, 
        .join_threads = join_threads, .lfptr = lfptr, .la = la
    };
    return out;
}

void lol_threadz_free(lol_threadz *in) { free(in); }

int lol_threadz_create(lol_threadz *lt) {
    int er;
    long i;
    void *status;
    pthread_t tid[lt->num_threads];
    for(i=0;i<lt->num_threads;i++) {
        // demonstrating ability to change value after it's passed
        lt->la->cur = 4; // this is an example that needs to be removed
        lt->la->tid = i;
        er = pthread_create(&tid[i], NULL, lt->lfptr, (void*)lt->la);
        if(er != 0) {
            printf("Error creating thread\n");
            return -1;
        } else {
            if(lt->debug == 1) {
                printf("Thread created\n");
            }
        }
    }
    for(i=0;i<lt->num_threads;i++) {
        er = pthread_join(tid[i], &status);
        if(lt->debug == 1) {
            printf("Thread joined\n");
        }
    }
    if(lt->debug == 1) {
        printf("lol_threadz: program completed. Exiting.\n");
    }
    return 1;
}
