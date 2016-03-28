#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_checksum.h"
#include "api_file_checksum_parser.h"
#include "api_vector.h"

int checksum_test() {
  checksum_t checksum;
  checksum_t bhol_checksum;
  checksum_t rolling_checksum;

  char *bhol = "bhol";
  char *hola = "hola";

  checksum_init_with_checksum_applied_to_string(&checksum, hola, strlen(hola));

  checksum_init_with_checksum_applied_to_string(&bhol_checksum, bhol, strlen(bhol));

  checksum_rolling_init(&bhol_checksum, &rolling_checksum, hola);

  printf("checksum %d bhol_checksum %d rolling_checksum %d\n", checksum.checksum_applied_to_string, bhol_checksum.checksum_applied_to_string, rolling_checksum.checksum_applied_to_string);

  return bhol_checksum.checksum_applied_to_string == rolling_checksum.checksum_applied_to_string;
}

int file_checksum_parser_test() {
  file_checksum_parser_t file_checksum_parser;
  checksum_t checksum;
  checksum_t rolling_checksum;

  char *filename = "test_new_remote_file";
  int block_size = 4;
  char buffer[block_size];
  char rolling_buffer[block_size];

  file_checksum_parser_init(&file_checksum_parser, filename, block_size);

  for (size_t index = 0; index < 4; index++) {
    file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, buffer, index);
    printf("checksum string : %.*s \n", block_size, checksum.string);
    printf("checksum value : %d \n", checksum.checksum_applied_to_string);
    file_checksum_parser_rolling_checksum_at_index(&file_checksum_parser, &checksum, &rolling_checksum, rolling_buffer, index);
    printf("rolling_checksum string : %.*s \n", block_size, rolling_checksum.string);
    printf("rolling_checksum value : %d \n", rolling_checksum.checksum_applied_to_string);
  }


  // printf("checksum from test file : %d, harcoded checksum %d\n", checksum.checksum_applied_to_string, test_checksum.checksum_applied_to_string);
  return 0;
}

int vector_test() {
  vector_t vector;

  vector_init(&vector);
  for (size_t i = 1000; i > 0; i--) {
    /* code */
    vector_append(&vector, i);
  }

  int value = vector_get_value_at_index(&vector, 500);

  printf("%d - %d \n", 500 , value);

  unsigned int index = vector_contains_value(&vector, 0x10);

  printf("%d\n", index);

  return 3 == value;

}

int test_set_chars_to_a_file() {
  FILE *fp = fopen("tu_mama","w");

  fseek(fp, 0, SEEK_SET);

  fprintf(fp, "%.*s", 10, "hola como ");

  fclose(fp);
}

int main(int argc, char *argv[]) {
  int check_test = checksum_test();
  int file_checksum_test = file_checksum_parser_test();
  int vec_test = vector_test();

  test_set_chars_to_a_file();

  if (!check_test && !vec_test && !file_checksum_test) {
    puts("all test succeded");
  }
}
