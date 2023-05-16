#include "config.h"

struct client {
  int fd;
  char buff[MAX_BUFF_LEN + 1];
};

void* irc_handle(void* client);
