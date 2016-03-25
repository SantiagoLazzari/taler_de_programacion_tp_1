#include "api_client.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_socket.h"
#include "api_file_checksum_parser.h"
#include "api_comunication_formatter.h"

#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 4
#define BLOCK_SIZE_BUFFER_SIZE 4
#define FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT "%.08x%s%.08x"

int client_begin(char *hostname, char *port, char *old_local_filename, char *new_local_filename, char *new_remote_filename, char *block_size) {
  puts("Begin Client");

  socket_t socket;

  /*Send new remote name with protocol*/
  char filename_and_blocksize_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE + strlen(new_remote_filename) + BLOCK_SIZE_BUFFER_SIZE];
  prepare_buffer_to_send_new_filename_and_blocksize(new_remote_filename, filename_and_blocksize_buffer, block_size);

  socket_init(&socket, port, hostname);
  socket_connect(&socket);

  socket_send(&socket, filename_and_blocksize_buffer, strlen(filename_and_blocksize_buffer));

  /*send all checksums with protocol*/

  file_checksum_parser_t file_checksum_parser;
  checksum_t checksum;
  char checksum_buffer[atoi(block_size)];
  char checksum_send_buffer[CHECKSUM_BUFFER_SIZE];

  file_checksum_parser_init(&file_checksum_parser, old_local_filename, atoi(block_size));
  file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, checksum_buffer, 0);

  prepare_buffer_to_send_checksum_to_remote(&checksum, checksum_send_buffer);

  socket_send(&socket, checksum_send_buffer, CHECKSUM_BUFFER_SIZE);


  socket_destroy(&socket);

  return 0;
}
