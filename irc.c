#include <string.h>
#include <stdio.h>

#include "irc.h"
#include "net.h"

void* irc_handshake(void* client) {
  struct client* c = (struct client*) client;

  if (IRC_PASS) { 
    if (c->buff != "PASS " IRC_PASS) { // incorrect pass
      net_close_sock(c->fd);
    } else {
      net_recv(c->fd, c->buff);
    }
  }

  irc_handle(c);
}

void
split(char* str, char* delim, char** arr) {
  int i = 0;
  char* t;
  while ((t = strtok(str, delim))) {
    arr[i] = t;
    i++;
  }
}

void
irc_handle(struct client* c) {
  while (1) { 
    char* msg[32]; // TODO this is arbitrary
    split(c->buff, " ", msg); // this has the bonus effect of clearing c->buff
    
    // TODO switch based on hash
    net_recv(c->fd, c->buff);
  }
  net_close_sock(c->fd);
}

void
irc_broadcast(
    struct server* s, 
    const char* channel, // empty str is broadcast to all
    const char* msg
    ) {
  // etc
}
