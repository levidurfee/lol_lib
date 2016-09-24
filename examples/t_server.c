#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "../libz/lol_inetz.h"
#include "../libz/lol_misc.h"

int show_me(int sock, int pid) {
   int n;
   char buffer[256];
   long long ms;
      
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) {
        error("ERROR reading from socket");
   }
   ms = lol_get_ms_time();
   printf("[fptr] Here is the message: %s [pid]: %d [time]:%llu\n", buffer, pid, ms);
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