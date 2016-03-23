/*
si se ejecuta el programa en modo servidor
./tp  ​
1) server (explicitamente palabra "server")  ​
2) port (el numero de puerto)

si se ejecuta el programa en modo cliente
./tp
1) client (explicitamente palabra "client")  ​
2) hostname (el nombre del host al que se quiere conectar el cliente)
3) port (el puerto al que se quiere conectar el cliente)
4) old_local_file (nombre del archivo que se desea actualizar)
5) new_local_file (nombre del archivo que deberia representar el archivo actualizado)
6) new_remote_file (nombre del archivo que esta actualizado)
7) block_size (el tamano del checksum que se desa utilizar)
*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_socket.h"

#define ARGUMENT_PROGRAM_TYPE argv[1]
#define ARGUMENT_PORT argv[2]

#define SOCKET_MODE_SERVER "server"
#define SOCKET_MODE_CLIENT "client"

#define PROGRAM_MODE_SERVER_ARGUMENTS_COUNT 3
#define STRING_1_IS_EQUAL_TO_STRING_2(string1, string2) !strcmp(string1, string2)

#define PROGRAM_MODE_CLIENT_ARGUMENTS_COUNT 3

#define LARGO_FILE 20
#define POS_NOMBRE_ARCHIVO 1
#define ARCHIVO_NO_ENCONTRADO 1
#define SALIDA_NORMAL 0

void mainWithClientMode() {
  puts("CLIENT MODE");

  socket_t socket;

  char request[20];

  snprintf(request, 20, "Client Sending Data\n");

  socket_init(&socket, "3001", "localhost");
  socket_connect(&socket);

  socket_send(&socket, request, 20);

  // socket_destroy(&socket);
}

void mainWithServerMode() {
  puts("SERVER MODE");

  socket_t accept_socket;
  socket_t peerskt;

  char message_receive[4];

  socket_init(&accept_socket, "3001", "localhost");
  socket_bind(&accept_socket);
  socket_listen(&accept_socket, 1);

  socket_accept(&accept_socket, &peerskt);
  socket_receive(&peerskt, message_receive, strlen(message_receive));

  printf("%s\n", message_receive);

  socket_destroy(&accept_socket);
  socket_destroy(&peerskt);
}

int main(int argc, char *argv[]) {
  char *programMode = argv[1];

  if (STRING_1_IS_EQUAL_TO_STRING_2(programMode, SOCKET_MODE_CLIENT) && argc != PROGRAM_MODE_CLIENT_ARGUMENTS_COUNT) {
    mainWithClientMode();
  } else if (STRING_1_IS_EQUAL_TO_STRING_2(programMode, SOCKET_MODE_SERVER) && argc != PROGRAM_MODE_SERVER_ARGUMENTS_COUNT) {
    mainWithServerMode();
  } else {
    return 1;
  }
  return 0;
}
