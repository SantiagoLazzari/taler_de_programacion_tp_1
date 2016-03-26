#include "api_server.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_HOST "localhost"
#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 0x8
#define BLOCK_SIZE_BUFFER_SIZE 0x8

int server_init(server_t *self, char *port) {
  self->port = port;

  return 0;
}

int server_receive_remote_filename_size(server_t *self, char *remote_filename_size_buffer) {
  socket_receive(self->socket, remote_filename_size_buffer, REMOTE_FILENAME_SIZE_BUFFER_SIZE);
  printf("%.*s \n",REMOTE_FILENAME_SIZE_BUFFER_SIZE, remote_filename_size_buffer);

  return 0;
}

int server_receive_remote_filename(server_t *self, char *remote_filename_buffer, int remote_filename_size) {
  socket_receive(self->socket, remote_filename_buffer, remote_filename_size);
  printf("%.*s \n",remote_filename_size, remote_filename_buffer);
  self->remote_filename = remote_filename_buffer;

  return 0;
}

int server_receive_block_size(server_t *self, char *block_size_buffer) {
  socket_receive(self->socket, block_size_buffer, BLOCK_SIZE_BUFFER_SIZE);
  printf("%.*s \n",BLOCK_SIZE_BUFFER_SIZE, block_size_buffer);
  self->block_size = block_size_buffer;

  return 0;
}

int server_begin(server_t *self) {
  puts("Begin Server");

  socket_t accept_socket;
  socket_t peerskt;

  self->socket = &peerskt;

  socket_init(&accept_socket, self->port, SERVER_HOST);
  socket_bind(&accept_socket);
  socket_listen(&accept_socket, 1);
  socket_accept(&accept_socket, self->socket);

  char remote_filename_size_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE];

  server_receive_remote_filename_size(self, remote_filename_size_buffer);

  int remote_filename_size = (int)strtol(remote_filename_size_buffer, NULL, 16);
  char remote_filename_buffer[remote_filename_size];

  server_receive_remote_filename(self, remote_filename_buffer, remote_filename_size);

  char block_size_buffer[BLOCK_SIZE_BUFFER_SIZE];

  server_receive_block_size(self, block_size_buffer);



  socket_destroy(&accept_socket);
  socket_destroy(self->socket);
  return 0;
}
