#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_socket.h"
#include "api_client.h"
#include "api_server.h"


/**Server arguments*/
#define SERVER_ARGUMENT_PORT argv[2]
#define SERVER_ARGUMENTS_COUNT 2

/*Client arguments*/
#define CLIENT_ARGUMENT_HOSTNAME argv[2]
#define CLIENT_ARGUMENT_PORT argv[3]
#define CLIENT_ARGUMENT_OLD_LOCAL_FILE argv[4]
#define CLIENT_ARGUMENT_NEW_LOCAL_FILE argv[5]
#define CLIENT_ARGUMENT_NEW_REMOTE_FILE argv[6]
#define CLIENT_ARGUMENT_BLOCK_SIZE argv[7]
#define CLIENT_ARGUMENTS_COUNT 8

/*Program mode argument*/
#define ARGUMENT_PROGRAM_TYPE argv[1]
#define SOCKET_MODE_SERVER "server"
#define SOCKET_MODE_CLIENT "client"

/*String comparisson*/
#define STRING_1_IS_EQUAL_TO_STRING_2(string1, string2) !strcmp(string1, string2)

int main(int argc, char *argv[]) {
  char *programMode = argv[1];

  if (STRING_1_IS_EQUAL_TO_STRING_2(programMode, SOCKET_MODE_CLIENT) && argc != CLIENT_ARGUMENTS_COUNT) {
    client_begin(CLIENT_ARGUMENT_HOSTNAME, CLIENT_ARGUMENT_PORT, CLIENT_ARGUMENT_OLD_LOCAL_FILE, CLIENT_ARGUMENT_NEW_LOCAL_FILE, CLIENT_ARGUMENT_NEW_REMOTE_FILE, CLIENT_ARGUMENT_BLOCK_SIZE);
  } else if (STRING_1_IS_EQUAL_TO_STRING_2(programMode, SOCKET_MODE_SERVER) && argc != SERVER_ARGUMENTS_COUNT) {
    server_begin(SERVER_ARGUMENT_PORT);
  } else {
    return 1;
  }
  return 0;
}
