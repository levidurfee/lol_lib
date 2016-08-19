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
int lol_rand_entropy(int num, char e[num]) {
    int i, rn, len = 0;
    char tmp[num];
    for(i=0;i<num;i++) {
        rn = lol_rand_s(32, 128); // keep it within ascii chars
        sprintf(tmp, "%c", rn);
        len += sprintf(e+len, tmp);
    }
    
    /*
    FILE *fp;
    fp = fopen("entropy.txt", "a");
    fwrite(e, 1, num, fp);
    fclose(fp);
    */
    //printf("%s\n", e);
    
    return 0;
}
void lol_gotoxy(int x, int y) {
    printf("%c[%d;%df",0x1B,y,x);
}
#endif