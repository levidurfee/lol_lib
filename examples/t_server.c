#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "../libz/lol_inetz.h"

int show_me(int sock) {
   int n;
   char buffer[256];
      
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) {
        error("ERROR reading from socket");
   }
   printf("[fptr] Here is the message: %s\n",buffer);
   n = write(sock,"[fptr] I got your message", 18);
   if (n < 0) {
        error("ERROR writing to socket");
   }
   return 1;
}

int main(int argc, char *argv[]) {
    fptrOp f;
    f = show_me;
    lol_server(9191, f);
    return 0;
}