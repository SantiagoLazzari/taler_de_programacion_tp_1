#include "api_comunication_formatter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT "%.08x%s%.08x"
#define SEND_CHECKSUM_TO_REMOTE_FORMAT "01%.08x"

int prepare_buffer_to_send_new_filename_and_blocksize(char *new_remote_filename, char *filename_and_blocksize_buffer, char *block_size) {
  int new_remote_file_size = strlen(new_remote_filename);
  sprintf(filename_and_blocksize_buffer, FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT,new_remote_file_size, new_remote_filename, atoi(block_size));

  return 0;
}

int prepare_buffer_to_send_checksum_to_remote(checksum_t *checksum, char *buffer) {
    sprintf(buffer, SEND_CHECKSUM_TO_REMOTE_FORMAT, checksum->checksum_applied_to_string);

    return 0;
}
