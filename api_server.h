#ifndef API_SERVER_H
#define API_SERVER_H

#include "api_socket.h"

typedef struct server {
  char *port;
  socket_t *socket;

  char *remote_filename;
  char *block_size;

} server_t;

int server_init(server_t *self, char *port);

int server_begin(server_t *self);

#endif
