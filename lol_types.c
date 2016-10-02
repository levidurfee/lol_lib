#include <stdlib.h>
#include <stdio.h>
#include "lol_types.h"
/* lol_arg type functions */
lol_arg *lol_arg_new(size_t max, size_t cur, int tid, size_t bit) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = (lol_arg) {.max = max, .cur = cur, .tid = tid, .bit = bit};
    return out;
}

lol_arg *lol_arg_copy(lol_arg const *in) {
    lol_arg *out = malloc(sizeof(lol_arg));
    *out = *in;
    return out;
}

void lol_arg_free(lol_arg *in) { free(in); }
