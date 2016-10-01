#include <stdio.h>
#include <pthread.h>

#ifndef _LOL_THREADZ
#define _LOL_THREADZ

typedef void *lfptr(void *arg);

typedef struct {
    int max;            // max amount of loops?
    int cur;            // current iteration
    char *data;         // data for the function pointer
    int tid;            // thread id
} lol_arg;

typedef struct {
    int debug;          // display debugging output
    int num_threads;    // number of threads to use
    int join_threads;   // join threads? normally yes/1
    lfptr *lfptr;       // function pointer
    lol_arg *la;        // arguments for function ptr
} lol_threadz;

lol_arg *lol_arg_new(int max, int cur, char *data, int tid);
lol_arg *lol_arg_copy(lol_arg const *in);
void lol_arg_free(lol_arg *in);

lol_threadz *lol_threadz_new(
                int debug, 
                int num_threads, 
                int join_threads,
                lfptr *lfptr,
                lol_arg *la);
lol_threadz *lol_threadz_copy(lol_threadz const *in);
void lol_threadz_free(lol_threadz *in);
                
int lol_threadz_create(lol_threadz *lt);

#endif
