#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

typedef unsigned short Sock_port_t;

typedef struct Sock_error_t {
  int error;
  int h_error;
} *Sock_error_t;

int Sock_init(void);
int Sock_open(Sock_port_t port, Sock_error_t perr);
int Sock_listen(int fd, char *cname, int buflen, Sock_error_t perr);
int Sock_connect(Sock_port_t port, char *sname, Sock_error_t perr);
int Sock_close(int fd, Sock_error_t perr);
ssize_t Sock_read(int fd, void *buf, size_t nbytes, Sock_error_t perr);
ssize_t Sock_write(int fd, void *buf, size_t nbytes, Sock_error_t perr);
