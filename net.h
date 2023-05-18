#include <sys/un.h>
#include <sys/socket.h>

void net_await(int fd); // blocking poll on a socket

int net_send(int fd, const char* msg);
int net_recv(int fd, char* buff);

int net_init_sock(int fd, struct sockaddr_un* addr);
void net_close_sock(int fd);
