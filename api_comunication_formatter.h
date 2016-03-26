#ifndef API_COMUNICATION_FORMATTER_H
#define API_COMUNICATION_FORMATTER_H

#include "api_checksum.h"

/*Comunication constants*/
#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 4
#define BLOCK_SIZE_BUFFER_SIZE 4
#define CHECKSUM_BUFFER_SIZE 10
#define END_SEND_CHECKSUM_BUFFER_SIZE 2

int prepare_buffer_to_send_new_filename_and_blocksize(char *new_remote_filename, char *filename_and_blocksize_buffer, char *block_size);
int prepare_buffer_to_send_checksum_to_remote(checksum_t *checksum, char *buffer);
int prepare_buffer_to_end_send_checksum_to_remote(char *buffer);

#endif
