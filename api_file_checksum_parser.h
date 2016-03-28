#ifndef API_FILE_CHECKSUM_PARSER_H
#define API_FILE_CHECKSUM_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "api_checksum.h"

#define FILE_CHECKSUM_PARSER_REACHED_END_OF_FILE 1;

typedef struct file_checksum_parser {
  char *filename;
  int block_size;
  FILE *fp;

} file_checksum_parser_t;

int file_checksum_parser_init(file_checksum_parser_t *self, char *filename,int block_size, char *mode);
int file_checksum_parser_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, char *buffer, unsigned int index);
int file_checksum_parser_rolling_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, checksum_t *rolling_checksum, char *buffer, unsigned int index);
int file_checksum_parser_get_buffer_from_block_index(file_checksum_parser_t *self, char *buffer, int index);
int file_checksum_parser_set_buffer_at_index(file_checksum_parser_t *self, char *buffer, int buffer_size, int index);
int file_checksum_parser_destroy(file_checksum_parser_t *self);

#endif
