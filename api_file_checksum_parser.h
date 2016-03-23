#ifndef API_FILE_CHECKSUM_PARSER_H
#define API_FILE_CHECKSUM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "api_checksum.h"

typedef struct file_checksum_parser {
  char *filename;
  int block_size;
} file_checksum_parser_t;

int file_checksum_parser_init(file_checksum_parser_t *self, char *filename,int block_size);

int file_checksum_parser_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, char *buffer, unsigned long index);

#endif
