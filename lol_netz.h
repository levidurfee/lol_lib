#ifndef LOL_NETZ_H
#define LOL_NETZ_H
typedef struct {
    struct sockaddr_in myaddr;      // defined in netinet/in.h
} lol_netz;

lol_netz *lol_netz_new(lol_netz ln);
lol_netz *lol_netz_copy(lol_netz const *ln);
void lol_netz_free(lol_netz *in);
#endif
