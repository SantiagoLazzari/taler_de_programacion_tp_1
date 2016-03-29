#include "api_file_checksum_parser.h"

int file_checksum_parser_init(file_checksum_parser_t *self,\
   char *filename,int block_size, char *mode) {
  self->filename = filename;
  self->block_size = block_size;

  self->fp = fopen(self->filename,mode);

  return 0;
}

int file_checksum_parser_checksum_at_index(file_checksum_parser_t *self,\
  checksum_t *checksum, char *buffer, unsigned int index) {
  fseek(self->fp, index, SEEK_SET);

  char character;

  for (int index = 0 ; index < self->block_size ; index++) {
    character = fgetc(self->fp);
    if (feof(self->fp))
      return FILE_CHECKSUM_PARSER_REACHED_END_OF_FILE;
    buffer[index] = character;
  }

  checksum_init_with_checksum_applied_to_string(checksum,\
    buffer, self->block_size);

  return 0;
}

int file_checksum_parser_rolling_checksum_at_index\
(file_checksum_parser_t *self, checksum_t *checksum,\
  checksum_t *rolling_checksum, char *buffer, unsigned int index) {
  fseek(self->fp, index + 1, SEEK_SET);

  char character;

  for (int index = 0 ; index < self->block_size ; index++) {
    character = fgetc(self->fp);
    if (feof(self->fp))
      return FILE_CHECKSUM_PARSER_REACHED_END_OF_FILE;
    buffer[index] = character;
  }

  checksum_rolling_init(checksum, rolling_checksum, buffer);

  return 0;
}

int file_checksum_parser_get_buffer_from_block_index\
(file_checksum_parser_t *self, char *buffer, int index) {
  fseek(self->fp, index * self->block_size, SEEK_SET);

  char character;

  for (int i = 0 ; i < self->block_size ; i++) {
    character = fgetc(self->fp);

    buffer[i] = character;
  }
  
  return 0;
}

int file_checksum_parser_set_buffer_at_index\
(file_checksum_parser_t *self, char *buffer, int buffer_size, int index) {
  fseek(self->fp, index, SEEK_SET);

  printf("agregue %.*s en el inddex %d\n", buffer_size, buffer, index);

  fprintf(self->fp, "%.*s", buffer_size, buffer);
  return 0;
}

int file_checksum_parser_destroy(file_checksum_parser_t *self) {
  fclose(self->fp);
  return 0;
}
