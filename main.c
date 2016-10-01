#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "lol_types.h"
#include "lol_primez.h"

int thread_test(lol_arg *arg);
void show_progress(int cur, int max, clock_t start);

int main() {
    clock_t start;
    start = clock();
    /* thread args */
    lol_arg *la = lol_arg_new(1000, 1, "Hello", 5);
    int nthreads, tid;
    #pragma omp parallel for private(nthreads, tid)
    for(int i=0;i<la->max;i++) {
        thread_test(la);
        show_progress(la->cur, la->max, start);
    }
    lol_arg_free(la);           // free the malloc
    
    return 1;
}

/* @todo the time is skewed / wrong */
void show_progress(int cur, int max, clock_t start) {
    clock_t t;
    t = clock() - start;
    double time_taken = ((double)t)/CLOCKS_PER_SEC/60/60;
    double per_hour = (double)cur / time_taken;
    double total_time = (double)max / per_hour;
    double time_remaining = total_time - time_taken;
    printf("Time elapsed:       %f\n", time_taken);
    printf("Per hour:           %f\n", per_hour);
    printf("Total time needed:  %f\n", total_time);
    printf("Time remaining:     %f\n", time_remaining);
}

int thread_test(lol_arg *arg) {
    // libcrypto has lots of memory leaks
    // make test = 1 if debugging. otherwise
    // you'll see a lot of extra info
    int test = 0;
    if(test == 0) {
        int tid;
        tid = omp_get_thread_num();
        size_t p_size = 128;
        char prime[p_size];
        srand(time(NULL)); // feed the machine
        l_prime(p_size, prime, 0);
        
        // get time started and how many have been generated to get
        // the threads per hour and estimated time left. maybe make
        // a progress bar.
        printf("thread: %i\nprime: %s\n\n", tid, prime);
        arg->cur++;
        
        FILE *fp;
        fp = fopen("output.pri", "a");
        fprintf(fp, "%s\n", prime);
        fclose(fp);
    } else {
        printf("Debugging\n");
    }
    return 1;
}
