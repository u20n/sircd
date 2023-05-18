#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "config.h"
#include "net.h"
#include "irc.h"

void ax(void) {
  printf("Closing...\n");
  pthread_exit(NULL);
  unlink(SOCKET_PATH);
}

int main (void) { 
  atexit(ax);
  
  int fd;
  struct sockaddr_un addr;
  if (net_init_sock(fd, &addr) == -1) {
    printf("could not initialise socket\n");
    exit(1);
  }

  pthread_t tid;

  while (1) {
    char buff[MAX_BUFF_LEN + 1];
    
    net_await(fd); // await new connections
    int c = accept(fd, NULL, NULL);  // accept 
    
    if (c == -1) {
      printf("Could not accept client\n");
      continue;
    }
    struct client info = {.fd=c};
    strncpy(info.buff, buff, sizeof buff);
 
    pthread_create(&tid, NULL, irc_handshake, (void*)&info); 
  }

  net_close_sock(fd); 
  exit(0);
}
