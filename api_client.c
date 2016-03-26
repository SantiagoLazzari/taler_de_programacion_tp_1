#include "api_client.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_file_checksum_parser.h"
#include "api_comunication_formatter.h"

#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 4
#define BLOCK_SIZE_BUFFER_SIZE 4

int client_init(client_t *self, char *hostname, char *port, char *old_local_filename, char *new_local_filename, char *new_remote_filename, char *block_size) {
  self->hostname = hostname;
  self->port = port;
  self->old_local_filename = old_local_filename;
  self->new_local_filename = new_local_filename;
  self->new_remote_filename = new_remote_filename;
  self->block_size = block_size;

  return 0;
}

int client_send_filename_and_block_size(client_t *self) {
  char filename_and_blocksize_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE + strlen(self->new_remote_filename) + BLOCK_SIZE_BUFFER_SIZE];
  prepare_buffer_to_send_new_filename_and_blocksize(self->new_remote_filename, filename_and_blocksize_buffer, self->block_size);
  socket_send(self->socket, filename_and_blocksize_buffer, strlen(filename_and_blocksize_buffer));

  return 0;
}

int client_send_checksums(client_t *self) {
  file_checksum_parser_t file_checksum_parser;
  checksum_t checksum;
  char checksum_buffer[atoi(self->block_size)];
  char checksum_send_buffer[CHECKSUM_BUFFER_SIZE];

  file_checksum_parser_init(&file_checksum_parser, self->old_local_filename, atoi(self->block_size));
  int block_index = 0;
  int file_checksum_parser_reached_end_of_file = 0;

  while (!file_checksum_parser_reached_end_of_file) {
    file_checksum_parser_reached_end_of_file = file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, checksum_buffer, block_index);

    if (!file_checksum_parser_reached_end_of_file) {
      prepare_buffer_to_send_checksum_to_remote(&checksum, checksum_send_buffer);
      socket_send(self->socket, checksum_send_buffer, CHECKSUM_BUFFER_SIZE);
    }

    block_index += atoi(self->block_size);
  }

  char end_send_checksum_buffer[END_SEND_CHECKSUM_BUFFER_SIZE];

  prepare_buffer_to_end_send_checksum_to_remote(end_send_checksum_buffer);
  socket_send(self->socket, end_send_checksum_buffer, END_SEND_CHECKSUM_BUFFER_SIZE);
  return 0;
}


int client_begin(client_t *self) {
  puts("Begin Client");
  socket_t socket;
  self->socket = &socket;
  socket_init(self->socket, self->port, self->hostname);
  socket_connect(self->socket);

  /*Send new remote name with protocol*/
  client_send_filename_and_block_size(self);

  /*send all checksums with protocol*/
  client_send_checksums(self);



  socket_destroy(self->socket);

  return 0;
}
