#ifndef LOL_NETZ_H
#define LOL_NETZ_H
typedef struct {
    char myaddr;
} lol_netz;

lol_netz *lol_netz_new(lol_netz ln);
lol_netz *lol_netz_copy(lol_netz const *ln);
void lol_netz_free(lol_netz *in);
#endif
