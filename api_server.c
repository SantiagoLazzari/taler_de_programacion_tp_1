#include "api_server.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_HOST "localhost"
#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 0x8
#define BLOCK_SIZE_BUFFER_SIZE 0x8


int server_begin(char *port) {
  puts("Begin Server");

  socket_t accept_socket;
  socket_t peerskt;

  char remote_filename_size_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE];

  socket_init(&accept_socket, port, SERVER_HOST);
  socket_bind(&accept_socket);
  socket_listen(&accept_socket, 1);
  socket_accept(&accept_socket, &peerskt);

  socket_receive(&peerskt, remote_filename_size_buffer, REMOTE_FILENAME_SIZE_BUFFER_SIZE);
  printf("%.*s \n",REMOTE_FILENAME_SIZE_BUFFER_SIZE, remote_filename_size_buffer);

  int remote_filename_size = (int)strtol(remote_filename_size_buffer, NULL, 16);
  char remote_filename_buffer[remote_filename_size];

  socket_receive(&peerskt, remote_filename_buffer, remote_filename_size);
  printf("%.*s \n",remote_filename_size, remote_filename_buffer );

  char blocksize_buffer[BLOCK_SIZE_BUFFER_SIZE];

  socket_receive(&peerskt, blocksize_buffer, BLOCK_SIZE_BUFFER_SIZE);
  printf("%.*s \n",BLOCK_SIZE_BUFFER_SIZE, blocksize_buffer);

  

  socket_destroy(&accept_socket);
  socket_destroy(&peerskt);
  return 0;
}
