#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_checksum.h"

int checksum_test() {
  checksum_t checksum;
  checksum_t bhol_checksum;
  checksum_t rolling_checksum;

  char *bhol = "bhol";
  char *hola = "hola";

  checksum_init(&checksum, hola, strlen(hola));
  checksum_init(&bhol_checksum, bhol, strlen(bhol));

  checksum_rolling_init(&bhol_checksum, &rolling_checksum, hola);

  printf("checksum %lu bhol_checksum %lu rolling_checksum %lu\n", checksum.checksum_applied_to_string, bhol_checksum.checksum_applied_to_string, rolling_checksum.checksum_applied_to_string);

  return bhol_checksum.checksum_applied_to_string == rolling_checksum.checksum_applied_to_string;
}

int main(int argc, char *argv[]) {
  int check_test = checksum_test();


  if (!check_test) {
    puts("all test succeded");
  }
}
