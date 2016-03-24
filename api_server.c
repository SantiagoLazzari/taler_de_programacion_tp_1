#include "api_server.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int server_begin(char *port) {
  puts("Begin Server");

  socket_t accept_socket;
  socket_t peerskt;

  char filenamelen_buffer[4];

  socket_init(&accept_socket, "3001", "localhost");
  socket_bind(&accept_socket);
  socket_listen(&accept_socket, 1);

  socket_accept(&accept_socket, &peerskt);

  socket_receive(&peerskt, filenamelen_buffer, 4);

  printf("%.*s \n",4, filenamelen_buffer);

  int filenamelen = atoi(filenamelen_buffer);
  char filename_buffer[filenamelen];

  socket_receive(&peerskt, filename_buffer, filenamelen);

  printf("%.*s \n",filenamelen, filename_buffer );

  socket_destroy(&accept_socket);
  socket_destroy(&peerskt);
  return 0;
}
