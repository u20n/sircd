#include "config.h"

#include <sys/un.h>

int net_init_sock(int fd, struct sockaddr_un* addr);
int net_send(int fd, const char* msg);
int net_recv(int fd, char* buff);
void net_close_sock(int fd);
