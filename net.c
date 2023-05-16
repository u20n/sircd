#include "net.h"
#include "config.h"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

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
        sizeof(struct sockaddr_un)
        == -1))
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

int
net_recv(int fd, char* buff) {
  // accept off fd's queue
  int c = accept(fd, NULL, NULL);
  if (c == -1)
    return -1;
  
  // read until EOF or MAX_BUFF_LEN 
  int l = recv(c, buff, MAX_BUFF_LEN, 0);
  buff[l] = '\0'; // finish off str

  return c;
}

void
net_close_sock(int fd) {
  close(fd); 
}
