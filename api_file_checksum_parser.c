#include "api_file_checksum_parser.h"

int file_checksum_parser_init(file_checksum_parser_t *self, char *filename,int block_size) {
  self->filename = filename;
  self->block_size = block_size;

  return 0;
}

int file_checksum_parser_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, char *buffer, unsigned int index) {
  FILE *fp = fopen(self->filename,"r");

  fseek(fp, index, SEEK_SET);

  char character;

  for (int index = 0 ; index < self->block_size ; index++) {
    character = fgetc(fp);
    if(feof(fp))
      return FILE_CHECKSUM_PARSER_REACHED_END_OF_FILE;
    buffer[index] = character;
  }

  checksum_init_with_checksum_applied_to_string(checksum, buffer, self->block_size);

  fclose(fp);
  return 0;
}

int file_checksum_parser_rolling_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, checksum_t *rolling_checksum, char *buffer, unsigned int index) {
  FILE *fp = fopen(self->filename,"r");

  fseek(fp, index + 1, SEEK_SET);

  char character;

  for (int index = 0 ; index < self->block_size ; index++) {
    character = fgetc(fp);
    if(feof(fp))
      return FILE_CHECKSUM_PARSER_REACHED_END_OF_FILE;
    buffer[index] = character;
  }

  checksum_rolling_init(checksum, rolling_checksum, buffer);

  fclose(fp);
  return 0;

}
