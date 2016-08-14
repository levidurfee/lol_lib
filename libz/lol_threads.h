/*
 *  _            _   _       _ 
 * | | _____   _(_) | | ___ | |
 * | |/ _ \ \ / / | | |/ _ \| |
 * | |  __/\ V /| |_| | (_) | |
 * |_|\___| \_/ |_(_)_|\___/|_|
 *
 * thread helper library
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#ifndef LOL_NUM_THREADS
#define LOL_NUM_THREADS 2
#endif

#ifndef LOL_THREADZ

typedef struct lol_threadz {
    void *(*start_routine) (void *);
    int join_threads;
    int loops;
    int output;
} lol_threadz_s;

#define LOL_THREADZ
int lol_threads(
        void *(*start_routine) (void *), 
        int join_threads,
        int loops,
        int output) {
    //int LOL_NUM_THREADS = sysconf(_SC_NPROCESSORS_ONLN);
    int rc, cnt;
    cnt = 0;
    long i;
    pthread_t threads[LOL_NUM_THREADS];
    while(loops >= cnt) {
        for(i=0;i<LOL_NUM_THREADS;i++) {
            if(output == 1) {
                printf("In main: creating thread %ld\n", i);
            }
            rc = pthread_create(&threads[i], NULL, start_routine, (void *)i); 
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }
        if(join_threads == 1) {
            for(i=0;i<LOL_NUM_THREADS;i++) {
                pthread_join(threads[i], NULL);
                i++;
            }
        }
        cnt++;
    }
    pthread_exit(NULL);
    return 1;
}
#endif