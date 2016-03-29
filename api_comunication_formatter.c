#include "api_comunication_formatter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT "%.08x%s%.08x"
#define SEND_CHECKSUM_TO_REMOTE_FORMAT "01%.08x"
#define END_SEND_CHECKSUM_TO_REMOTE_FORMAT "02"
#define SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT "04%.08x"
#define SEND_DIFF_BUFFER_TO_LOCAL_FORMAT "03%.08x%.*s"
#define END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_FORMAT "05"

int prepare_buffer_to_send_new_filename_and_blocksize\
(char *new_remote_filename, char *filename_and_blocksize_buffer,\
  char *block_size) {
  int new_remote_file_size = strlen(new_remote_filename);

  snprintf(filename_and_blocksize_buffer, 8 + new_remote_file_size + 8 + 1\
    , FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT,\
    new_remote_file_size, new_remote_filename, atoi(block_size));
/*
  sprintf(filename_and_blocksize_buffer, FILENAME_AND_BLOCKSIZE_BUFFER_FORMAT,\
    new_remote_file_size, new_remote_filename, atoi(block_size));
*/
  return 0;
}

int prepare_buffer_to_send_checksum_to_remote\
(checksum_t *checksum, char *buffer) {
  snprintf(buffer, 2 + 8 + 1, SEND_CHECKSUM_TO_REMOTE_FORMAT,\
    checksum->checksum_applied_to_string);

/*
    sprintf(buffer, SEND_CHECKSUM_TO_REMOTE_FORMAT,\
      checksum->checksum_applied_to_string);
*/


    return 0;
}

int prepare_buffer_to_end_send_checksum_to_remote(char *buffer)  {
  snprintf(buffer, 2 + 1, END_SEND_CHECKSUM_TO_REMOTE_FORMAT);
/*
  sprintf(buffer, END_SEND_CHECKSUM_TO_REMOTE_FORMAT);
*/
  return 0;
}

bool is_checksum_flag_terminating_recive_checksums(char *checksum_flag) {
  char *terminate_flag = END_SEND_CHECKSUM_TO_REMOTE_FORMAT;

  for (int index = 0 ; index < END_SEND_CHECKSUM_BUFFER_SIZE ; index ++) {
    if (checksum_flag[index] != terminate_flag[index]) {
      return false;
    }
  }

  return true;
}

int prepare_buffer_to_send_block_index_to_local(char *buffer, int index) {
  snprintf(buffer, 2 + 8 + 1, SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT, index);
  // sprintf(buffer, SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT, index);

  return 0;
}

int prepare_buffer_to_send_diff_to_local\
(char *diff_buffer, char *buffer, int size) {
  snprintf(buffer, 2 + 8 + size + 1,\
    SEND_DIFF_BUFFER_TO_LOCAL_FORMAT, size, size, diff_buffer);
  // sprintf(buffer, SEND_DIFF_BUFFER_TO_LOCAL_FORMAT, size, size, diff_buffer);

  return 0;
}

int prepare_buffer_to_end_send_checksum_and_diff_to_local(char *buffer) {
  snprintf(buffer, 2 + 1, END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_FORMAT);
//  sprintf(buffer, END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_FORMAT);

  return 0;
}

bool is_checksum_flag_terminating_receive_checksums_and_diff\
(char *checksum_flag) {
  char *terminate_flag = END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_FORMAT;

  for (int index = 0 ; index < END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_SIZE ;\
     index ++) {
    if (checksum_flag[index] != terminate_flag[index]) {
      return false;
    }
  }

  return true;
}

bool is_checksum_flag_adding_to_new_local_diff(char *checksum_flag) {
  char *add_diff_flag = SEND_DIFF_BUFFER_TO_LOCAL_FORMAT;

  for (int index = 0 ; index < END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_SIZE ;\
     index ++) {
    if (checksum_flag[index] != add_diff_flag[index]) {
      return false;
    }
  }

  return true;
}

bool is_checksum_flag_adding_to_new_local_checksum(char *checksum_flag) {
  char *add_checksum_flag = SEND_CHECKSUM_INDEX_TO_LOCAL_FORMAT;

  for (int index = 0 ; index < END_SEND_CHECKSUM_AND_DIFF_TO_LOCAL_SIZE ;\
     index ++) {
    if (checksum_flag[index] != add_checksum_flag[index]) {
      return false;
    }
  }

  return true;
}
