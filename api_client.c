#include "api_client.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int client_begin(char *hostname, char *port, char *old_local_file, char *new_local_file, char *new_remote_file, char *block_size) {
  puts("Begin Client");

  socket_t socket;

  char *filename = "new_file_with_an_extreme_large_and_motherfucking_anoying_name";

  int filenamelen = strlen(filename);
  char filename_buffer[4 + strlen(filename)];
  sprintf(filename_buffer, "%.04d%s",filenamelen, filename);

  socket_init(&socket, "3001", "localhost");
  socket_connect(&socket);

  socket_send(&socket, filename_buffer, strlen(filename_buffer));

  socket_destroy(&socket);
}
