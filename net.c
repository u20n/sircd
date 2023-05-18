#include "net.h"
#include "config.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <errno.h>

int
net_init_sock(
    int fd,
    struct sockaddr_un* addr
    ) {
  // create socket
  fd = socket(AF_UNIX, SOCK_STREAM, 0); 
  if (fd == -1)
    return fd;

  // init socket struct 
  memset(addr, 0, sizeof(struct sockaddr_un));
  addr->sun_family = AF_UNIX;
  strncpy(addr->sun_path, SOCKET_PATH, sizeof(addr->sun_path) - 1);

  // bind socket
  if (bind(
        fd, (struct sockaddr *) addr, 
        sizeof(struct sockaddr_un))
        == -1)
      return -1;
 
  // mark as recv socket
  if (listen(fd, QUEUE_LEN) == -1)
    return -1;
 
  return 0;
}

int
net_send(int cfd, const char* msg) {
  return send(cfd, msg, strlen(msg), 0); 
}

void
net_await(int fd) {
  struct pollfd pfd = {.fd=fd, .events=POLLIN};
  int pass = 0;
  while (!pass) {
    int p = poll(&pfd, 1, -1);
    if (p < 0)
      exit(1);
    if (pfd.revents == (EAGAIN | ENOMEM))
      continue;
    pass = 1;
  }
}

int
net_recv(int fd, char* buff) {   
  // read until EOF or MAX_BUFF_LEN 
  int l = recv(fd, buff, MAX_BUFF_LEN, 0);
  if (l == -1)
    return l;
  
  buff[l] = '\0'; // finish off str
  return 0;
}

void
net_close_sock(int fd) {
  close(fd); 
}
