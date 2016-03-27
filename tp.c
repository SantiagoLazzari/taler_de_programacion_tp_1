#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_socket.h"
#include "api_server.h"
#include "api_client.h"

#define ARGUMENT_PROGRAM_TYPE argv[1]

#define SERVER_PROGRAM_TYPE "server"
#define SERVER_ARGUMENT_PORT argv[2]
#define SERVER_ARGUMENTS_COUNT 3

#define CLIENT_PROGRAM_TYPE "client"
#define CLIENT_ARGUMENT_HOSTNAME argv[2]
#define CLIENT_ARGUMENT_PORT argv[3]
#define CLIENT_ARGUMENT_OLD_LOCAL_FILE argv[4]
#define CLIENT_ARGUMENT_NEW_LOCAL_FILE argv[5]
#define CLIENT_ARGUMENT_NEW_REMOTE_FILE argv[6]
#define CLIENT_ARGUMENT_BLOCK_SIZE argv[7]
#define CLIENT_ARGUMENTS_COUNT 8

#define STRING_1_IS_EQUAL_TO_STRING_2(string1, string2) !strcmp(string1, string2)

int main(int argc, char *argv[]) {
  if (STRING_1_IS_EQUAL_TO_STRING_2(CLIENT_PROGRAM_TYPE, ARGUMENT_PROGRAM_TYPE) && argc == CLIENT_ARGUMENTS_COUNT) {
    client_t client;
    client_init(&client, \
      CLIENT_ARGUMENT_HOSTNAME, \
      CLIENT_ARGUMENT_PORT, \
      CLIENT_ARGUMENT_OLD_LOCAL_FILE, \
      CLIENT_ARGUMENT_NEW_LOCAL_FILE, \
      CLIENT_ARGUMENT_NEW_REMOTE_FILE, \
      CLIENT_ARGUMENT_BLOCK_SIZE);
    client_begin(&client);
  } else if (STRING_1_IS_EQUAL_TO_STRING_2(SERVER_PROGRAM_TYPE, ARGUMENT_PROGRAM_TYPE) && argc == SERVER_ARGUMENTS_COUNT) {
    server_t server;
    server_init(&server, SERVER_ARGUMENT_PORT);
    server_begin(&server);
  } else {
    return 1;
  }
  return 0;
}
