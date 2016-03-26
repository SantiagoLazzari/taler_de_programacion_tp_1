#ifndef API_CLIENT_H
#define API_CLIENT_H

#include "api_socket.h"

typedef struct client {
  char *hostname;
  char *port;
  char *old_local_filename;
  char *new_local_filename;
  char *new_remote_filename;
  char *block_size;

  socket_t *socket;
} client_t;

int client_init(client_t *self, char *hostname, char *port, char *old_local_filename, char *new_local_filename, char *new_remote_filename, char *block_size);
int client_begin(client_t *self);

#endif
