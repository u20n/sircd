#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "config.h"
#include "net.h"
#include "irc.h"

void ax(void) {
  printf("Closing...\n");
  pthread_exit(NULL);
}

int main (void) { 
  int fd;
  struct sockaddr_un addr;
  if (net_init_sock(fd, &addr) == -1) {
    printf("could not initialise socket\n");
    exit(1);
  }

  pthread_t tid;
    
  atexit(ax);
  
  while (1) {
    char buff[MAX_BUFF_LEN + 1];
    int c = net_recv(fd, buff);
    if (c == -1) {
      printf("Could not accept client\n");
      continue;
    }
    struct client info = {.fd=c};
    info.fd = c;
    strncpy(info.buff, buff, sizeof buff);
 
    pthread_create(&tid, NULL, irc_handle, (void*)&info); 
  }

  net_close_sock(fd); 
  exit(0);
}