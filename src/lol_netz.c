#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include "lol_netz.h"

int lol_client(lol_netz ln) {
    char recv_buff[1024];
    memset(recv_buff, '0', sizeof(recv_buff));
    if((ln.sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return -1;
    }
    return 1;
}

lol_netz *lol_netz_new(lol_netz ln) {
    lol_netz *out = malloc(sizeof(lol_netz));
    *out = (lol_netz) {.sockfd = ln.sockfd, .n = ln.n, .serv_addr = ln.serv_addr};
    return out;
}

lol_netz *lol_netz_copy(lol_netz const *ln) {
    lol_netz *out = malloc(sizeof(lol_netz));
    *out = *ln;
    return out;
}

void lol_netz_free(lol_netz *in) { free(in); }
