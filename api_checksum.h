#ifndef API_CHECKSUM_H
#define API_CHECKSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

typedef struct checksum {
  char *a_string;
  unsigned int checksum_applied_to_string;
  int size;
  unsigned int high;
  unsigned int low;
} checksum_t;

int checksum_init(checksum_t *self, char *a_string, int size);

int checksum_calculate_checksum(checksum_t *self);

int checksum_rolling_init(checksum_t *self, checksum_t *rolling_checksum,\
   char *a_string);

int checksum_init_with_checksum_applied_to_string(checksum_t *self,\
   char *a_string, int size);

int checksum_copy_from_checksum(checksum_t *self, checksum_t *other_checksum);

#endif
