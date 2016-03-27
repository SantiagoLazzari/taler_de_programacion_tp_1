#include "api_server.h"

#include "api_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "api_comunication_formatter.h"
#include "api_file_checksum_parser.h"

#define SERVER_HOST "localhost"

int server_init(server_t *self, char *port) {
  self->port = port;

  return 0;
}

int server_receive_remote_filename_size(server_t *self, char *remote_filename_size_buffer) {
  socket_receive(self->socket, remote_filename_size_buffer, REMOTE_FILENAME_SIZE_BUFFER_SIZE * 2);
  printf("%.*s \n",REMOTE_FILENAME_SIZE_BUFFER_SIZE * 2, remote_filename_size_buffer);

  return 0;
}

int server_receive_remote_filename(server_t *self, char *remote_filename_buffer, int remote_filename_size) {
  socket_receive(self->socket, remote_filename_buffer, remote_filename_size);
  printf("%.*s \n",remote_filename_size, remote_filename_buffer);
  self->new_remote_filename = remote_filename_buffer;

  return 0;
}

int server_receive_block_size(server_t *self, char *block_size_buffer) {
  socket_receive(self->socket, block_size_buffer, REMOTE_FILENAME_SIZE_BUFFER_SIZE * 2);
  printf("%.*s \n",REMOTE_FILENAME_SIZE_BUFFER_SIZE * 2, block_size_buffer);
  self->block_size = block_size_buffer;

  return 0;
}

int server_receive_local_checksums(server_t *self) {
  int did_terminate_recive_checksums = 0;

  char checksum_buffer[CHECKSUM_BUFFER_SIZE - END_SEND_CHECKSUM_BUFFER_SIZE];
  char checksum_buffer_flag[END_SEND_CHECKSUM_BUFFER_SIZE];

  while (!did_terminate_recive_checksums) {
    socket_receive(self->socket, checksum_buffer_flag, END_SEND_CHECKSUM_BUFFER_SIZE);

    did_terminate_recive_checksums = is_checksum_flag_terminating_recive_checksums(checksum_buffer_flag);

    if (!did_terminate_recive_checksums) {
      socket_receive(self->socket, checksum_buffer, CHECKSUM_BUFFER_SIZE - END_SEND_CHECKSUM_BUFFER_SIZE);
      printf("%.*s \n",CHECKSUM_BUFFER_SIZE - END_SEND_CHECKSUM_BUFFER_SIZE, checksum_buffer);
      int checksum_number = (int)strtol(checksum_buffer, NULL, 16);

      vector_append(self->vector, checksum_number);
    }
  }

  return 0;
}

int server_compare_checksums_with_new_remote_file(server_t *self) {
  file_checksum_parser_t file_checksum_parser;
  file_checksum_parser_init(&file_checksum_parser, self->new_remote_filename, atoi(self->block_size));
  vector_t diff_characters_acumulation_vector;
  vector_init(&diff_characters_acumulation_vector);

  checksum_t checksum;
  char checksum_buffer[atoi(self->block_size)];
  checksum_t rolling_checksum;
  char rolling_checksum_buffer[atoi(self->block_size)];

  int block_index = 0;
  int file_checksum_parser_reached_end_of_file = 0;

  file_checksum_parser_reached_end_of_file = file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, checksum_buffer, block_index);

  puts("vector description");
  for (int i = 0 ; i < self->vector->size ; i++) {

    printf("%d\n", vector_get_value_at_index(self->vector, i));
  }


  while (!file_checksum_parser_reached_end_of_file) {
    printf("%d\n", checksum.checksum_applied_to_string);
    int index_of_value = vector_contains_value(self->vector, checksum.checksum_applied_to_string);
    printf("%d\n", index_of_value);
    if (index_of_value != -1) {
      if (diff_characters_acumulation_vector.size != 0) {
          char diff_characters_acumulation_buffer[diff_characters_acumulation_vector.size];
          for (int i = 0; i < diff_characters_acumulation_vector.size; i++) {
            diff_characters_acumulation_buffer[i] = vector_get_value_at_index(&diff_characters_acumulation_vector, i);
          }

          char diff_characters_send_buffer[SEND_DIFF_BUFFER_TO_LOCAL_PROTOCOL_SIZE + SEND_DIFF_BUFFER_TO_LOCAL_SIZE_SIZE + diff_characters_acumulation_vector.size];

          prepare_buffer_to_send_diff_to_local(diff_characters_acumulation_buffer, diff_characters_send_buffer, diff_characters_acumulation_vector.size);

          socket_send(self->socket, diff_characters_send_buffer, SEND_DIFF_BUFFER_TO_LOCAL_PROTOCOL_SIZE + SEND_DIFF_BUFFER_TO_LOCAL_SIZE_SIZE + diff_characters_acumulation_vector.size);

      }

      char buffer[SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT_SIZE];

      prepare_buffer_to_send_block_index_to_local(buffer, index_of_value);
      socket_send(self->socket, buffer, SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT_SIZE);


      block_index += atoi(self->block_size);
      file_checksum_parser_reached_end_of_file = file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, checksum_buffer, block_index);
    } else {
      printf("%c\n", checksum.string[0]);
      vector_append(&diff_characters_acumulation_vector,checksum.string[0]);

      //TODO: rolling checksum bug

      file_checksum_parser_reached_end_of_file = file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, checksum_buffer, ++ block_index);

      // checksum_copy_from_checksum(&checksum, &rolling_checksum);
    }
  }

  vector_destroy(&diff_characters_acumulation_vector);
  //tengo que mandar lo que le falta para completar el archivo
  return 0;
}

int server_begin(server_t *self) {
  puts("Begin Server");

  socket_t accept_socket;
  socket_t peerskt;

  self->socket = &peerskt;

  /*Init server checksum pool*/
  vector_t vector;
  vector_init(&vector);
  self->vector = &vector;

  socket_init(&accept_socket, self->port, SERVER_HOST);
  socket_bind(&accept_socket);
  socket_listen(&accept_socket, 1);
  socket_accept(&accept_socket, self->socket);

  char remote_filename_size_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE];

  server_receive_remote_filename_size(self, remote_filename_size_buffer);

  int remote_filename_size = (int)strtol(remote_filename_size_buffer, NULL, 16);
  char remote_filename_buffer[remote_filename_size];

  server_receive_remote_filename(self, remote_filename_buffer, remote_filename_size);

  char block_size_buffer[REMOTE_FILENAME_SIZE_BUFFER_SIZE];

  server_receive_block_size(self, block_size_buffer);

  server_receive_local_checksums(self);

  server_compare_checksums_with_new_remote_file(self);

  socket_destroy(&accept_socket);
  return 0;
}

int server_destroy(server_t *self) {
  socket_destroy(self->socket);

  vector_destroy(self->vector);
}
