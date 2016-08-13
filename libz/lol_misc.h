/*
 *  _            _   _       _ 
 * | | _____   _(_) | | ___ | |
 * | |/ _ \ \ / / | | |/ _ \| |
 * | |  __/\ V /| |_| | (_) | |
 * |_|\___| \_/ |_(_)_|\___/|_|
 *
 * misc helper library
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LOL_HELPER
#define LOL_HELPER

void lol_init_rand(void) {
    srand(time(NULL));
}

/* single random number */
int lol_s_rand(int max) {
    int i_rand;
    
    i_rand = rand() % max + 1;
    return i_rand;
}

/* array of random numbers */
int lol_m_rand(int max, int num, int i_rand[num]) {
    int i;
    for(i=0;i<num;i++) {
        i_rand[i] = rand() % max + 1;
    }
    return 0;
}
#endif