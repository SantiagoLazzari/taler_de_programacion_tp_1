#ifndef API_COMUNICATION_FORMATTER_H
#define API_COMUNICATION_FORMATTER_H

#include "api_checksum.h"
#include <stdbool.h>

/*Comunication constants*/
#define REMOTE_FILENAME_SIZE_BUFFER_SIZE 4
#define BLOCK_SIZE_BUFFER_SIZE 4
#define CHECKSUM_BUFFER_SIZE 10
#define END_SEND_CHECKSUM_BUFFER_SIZE 2
#define SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT_SIZE 10
#define SEND_DIFF_BUFFER_TO_LOCAL_PROTOCOL_SIZE 2
#define SEND_DIFF_BUFFER_TO_LOCAL_SIZE_SIZE 8
#define END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_SIZE 2

int prepare_buffer_to_send_new_filename_and_blocksize(char *new_remote_filename, char *filename_and_blocksize_buffer, char *block_size);
int prepare_buffer_to_send_checksum_to_remote(checksum_t *checksum, char *buffer);
int prepare_buffer_to_end_send_checksum_to_remote(char *buffer);
bool is_checksum_flag_terminating_recive_checksums(char *checksum_flag);

int prepare_buffer_to_send_block_index_to_local(char *buffer, int index);
int prepare_buffer_to_send_diff_to_local(char *diff_buffer, char *buffer, int size);
int prepare_buffer_to_end_send_checksum_and_diff_to_local(char *buffer);

bool is_checksum_flag_terminating_receive_checksums_and_diff(char *checksum_flag);
bool is_checksum_flag_adding_to_new_local_diff(char *checksum_flag);
bool is_checksum_flag_adding_to_new_local_checksum(char *checksum_flag);

#endif
