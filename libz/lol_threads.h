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
#include <time.h>
#include <stdint.h>
#include "lol_colors.h"
#include "lol_misc.h"

#ifndef LOL_NUM_THREADS
#define LOL_NUM_THREADS 5
#endif

#ifndef LOL_THREADZ
#define LOL_THREADZ

typedef struct lol_threadz {
    void *(*start_routine) (void *);
    int join_threads;
    int loops;
    int output;
} lol_threadz_s;


int lol_threads(lol_threadz_s lts) {
    //int LOL_NUM_THREADS = sysconf(_SC_NPROCESSORS_ONLN);
    int rc, cnt, loops, progress, tph;
    time_t start_t, end_t;
    double diff_t, total_time, time_left;
    time(&start_t);
    cnt = 0;
    uint64_t i;
    pthread_t threads[LOL_NUM_THREADS];
    loops = lts.loops / LOL_NUM_THREADS;
    while(loops > cnt) {
        
        for(i = 0;i<LOL_NUM_THREADS;i++) {
            if(lts.output == 1) {
                //printf("In main: creating thread %ld\n", i);
            }
            rc = pthread_create(&threads[i], NULL, lts.start_routine, (void *)i); 
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }
        if(lts.join_threads == 1) {
            for(i=0;i<LOL_NUM_THREADS;i++) {
                pthread_join(threads[i], NULL);
                //i++;
            }
        }
        cnt++;
        progress = (cnt * 100) / loops;
        if(lts.output == 1) {
            lol_clear();
            lol_gotoxy(0,0);
            printf(LOL_BLUE "[" LOL_GREEN "Percent done:"
            LOL_RESET "\t%i" LOL_BLUE "]"
            LOL_GREEN "[%i / %i]\n", 
                progress, 
                cnt * LOL_NUM_THREADS, 
                loops * LOL_NUM_THREADS);
            time(&end_t);
            diff_t = difftime(end_t, start_t) / 60 / 60;
            tph = (cnt * LOL_NUM_THREADS) / diff_t; // get threads per hour
            total_time = (double)lts.loops / (double)tph;
            time_left = total_time - diff_t;
            lol_pb_f("Total time", total_time);
            lol_pb_f("Running time", diff_t);
            lol_pb_f("Time left", time_left);
            
            lol_pb_i("Threads/hr", tph);
        }
    }
    pthread_exit(NULL);
    return 1;
}
#endif
