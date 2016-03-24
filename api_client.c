#include "api_client.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 4
#define BLOCK_SIZE_BUFFER_SIZE 4

int client_begin(char *hostname, char *port, char *old_local_filename, char *new_local_filename, char *new_remote_filename, char *block_size) {
  puts("Begin Client");

  socket_t socket;

  int new_remote_file_size = strlen(new_remote_filename);
  char filename_and_blocksize_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE + strlen(new_remote_filename) + BLOCK_SIZE_BUFFER_SIZE];
  sprintf(filename_and_blocksize_buffer, "%.04d%s%.04d",new_remote_file_size, new_remote_filename, atoi(block_size));

  socket_init(&socket, port, hostname);
  socket_connect(&socket);

  socket_send(&socket, filename_and_blocksize_buffer, strlen(filename_and_blocksize_buffer));

  socket_destroy(&socket);
}
