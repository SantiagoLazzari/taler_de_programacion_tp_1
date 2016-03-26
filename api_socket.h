#ifndef API_SOCKET_H
#define API_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct socket {
  int skt;
  char *port;
  char *host;
  struct addrinfo *addrinfo;
} socket_t ;

int socket_init(socket_t *self, char *port, char *host);
int socket_destroy(socket_t *self);

int socket_send(socket_t *self, char *buf, int size);
int socket_receive(socket_t *self, char *buf, int size);

int socket_listen(socket_t *self, int listen_queue_size);
int socket_accept(socket_t *self, socket_t *peerskt);

int socket_bind(socket_t *self);
int socket_connect(socket_t *self);

int socket_shutdown(socket_t *self);
int socket_close(socket_t *self);

#endif
