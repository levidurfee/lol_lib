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
#include <string.h>
#include <sys/time.h>
#include "lol_colors.h"

#ifndef LOL_HELPER
#define LOL_HELPER

#define lol_clear() printf("\033[H\033[J")

/* simple int swap */
void lol_int_swap(int *a, int *b) {
    int s;
    s = *a;
    *a = *b;
    *b = s;
}

/* this needs to be ran before any other _rand functions */
void lol_init_rand(void) {
    srand(time(NULL));
}

/* single random number */
int lol_rand_s(int min, int max) {
    int i_rand = ( rand() % (max - min) ) + min;
    return i_rand;
}

/* array of random numbers */
int lol_rand_m(int min, int max, int num, int i_rand[num]) {
    int i;
    for(i=0;i<num;i++) {
        i_rand[i] = lol_rand_s(min, max);
    }
    return 0;
}

/* create a string of random entropy */
int lol_rand_entropy(int num, char *e) {
    int i, rn, len = 0;

    char *buf = malloc(num * sizeof(char));
    if(!buf) {
        printf("Bad\n");
        return -1;
    }
    
    for(i=0;i<num;i++) {
        rn = lol_rand_s(32, 128); // keep it within ascii chars
        sprintf(buf, "%c", rn);
        len += sprintf(e+len, buf);
    }
    free(buf);
    buf = NULL;
    
    return 0;
}
void lol_gotoxy(int x, int y) {
    printf("%c[%d;%df",0x1B,y,x);
}

void lol_pb_i(char *message, int i) {
    printf(LOL_BLUE "[" 
    LOL_GREEN "%s:" LOL_RESET "\t%i" LOL_BLUE "]" LOL_RESET "\n", message, i);
}
void lol_pb_f(char *message, float i) {
    printf(LOL_BLUE "[" 
    LOL_GREEN "%s:" LOL_RESET "\t%f" LOL_BLUE "]" LOL_RESET "\n", message, i);
}

long long lol_get_ms_time(void) {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}
#endif