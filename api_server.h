#ifndef API_SERVER_H
#define API_SERVER_H

#include "api_socket.h"
#include "api_vector.h"

typedef struct server {
  char *port;
  socket_t *socket;
  vector_t *vector;

  char *new_remote_filename;
  char *block_size;

} server_t;

int server_init(server_t *self, char *port, vector_t *vector);

int server_begin(server_t *self);

int server_destroy(server_t *self);

#endif
