#ifndef LOL_NETZ_H
#define LOL_NETZ_H
#include <netinet/in.h>
#include <sys/socket.h>
typedef struct {
    int sockfd;
    int n;
    struct sockaddr_in serv_addr;
} lol_netz;

int lol_client(lol_netz ln);

lol_netz *lol_netz_new(lol_netz ln);
lol_netz *lol_netz_copy(lol_netz const *ln);
void lol_netz_free(lol_netz *in);
#endif
