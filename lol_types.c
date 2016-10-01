#include <stdlib.h>
#include <stdio.h>
#include "lol_types.h"
/* lol_arg type functions */
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
