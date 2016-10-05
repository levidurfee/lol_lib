#include <stdlib.h>
#include <netinet/in.h>
#include "lol_netz.h"

lol_netz *lol_netz_new(lol_netz ln) {
    lol_netz *out = malloc(sizeof(lol_netz));
    *out = (lol_netz) {.myaddr = ln.myaddr};
    return out;
}

lol_netz *lol_netz_copy(lol_netz const *ln) {
    lol_netz *out = malloc(sizeof(lol_netz));
    *out = *ln;
    return out;
}

void lol_netz_free(lol_netz *in) { free(in); }
