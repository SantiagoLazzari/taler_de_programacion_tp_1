#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_checksum.h"
#include "api_file_checksum_parser.h"

int checksum_test() {
  checksum_t checksum;
  checksum_t bhol_checksum;
  checksum_t rolling_checksum;

  char *bhol = "xa";
  char *hola = "aa";

  checksum_init(&checksum, hola, strlen(hola));
  checksum_init(&bhol_checksum, bhol, strlen(bhol));

  checksum_rolling_init(&bhol_checksum, &rolling_checksum, hola);

  printf("checksum %d bhol_checksum %d rolling_checksum %d\n", checksum.checksum_applied_to_string, bhol_checksum.checksum_applied_to_string, rolling_checksum.checksum_applied_to_string);

  return bhol_checksum.checksum_applied_to_string == rolling_checksum.checksum_applied_to_string;
}

int file_checksum_parser_test() {
  file_checksum_parser_t file_checksum_parser;
  checksum_t checksum;
  checksum_t test_checksum;

  char *filename = "test_file.txt";
  int block_size = 4;
  char buffer[block_size];

  file_checksum_parser_init(&file_checksum_parser, filename, block_size);
  file_checksum_parser_checksum_at_index(&file_checksum_parser, &checksum, buffer, 0);

  // int checksum_init(checksum_t *self, char *string, int size);
  checksum_init(&test_checksum, "test", block_size);

  printf("%.*s \n", block_size, checksum.string);


  printf("checksum from test file : %d, harcoded checksum %d\n", checksum.checksum_applied_to_string, test_checksum.checksum_applied_to_string);
  return checksum.checksum_applied_to_string == test_checksum.checksum_applied_to_string;
}

int main(int argc, char *argv[]) {
  int check_test = checksum_test();
  int file_checksum_test = file_checksum_parser_test();

  if (!check_test && !file_checksum_test) {
    puts("all test succeded");
  }
}
