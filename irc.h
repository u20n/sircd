#include "config.h"
#include "hasht.h"

struct client {
  int fd;
  char buff[MAX_BUFF_LEN + 1];
 
  char* nick;
  char* name;
};

struct channel {
  char* name;
  struct hasht* online;
};

struct server { 
  struct hasht* channels[IRC_MAX_CHANNELS];
};

void* irc_handshake(void* client);
void irc_handle(struct client* c);

void irc_broadcast(
    struct server* s, 
    const char* channel, // empty str is broadcast to all
    const char* msg);

