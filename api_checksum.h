#ifndef API_CHECKSUM_H
#define API_CHECKSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct checksum {
  char *string;
  unsigned int checksum_applied_to_string;
  int size;
  unsigned int high;
  unsigned int low;

} checksum_t;

int checksum_init(checksum_t *self, char *string, int size);
int checksum_rolling_init(checksum_t *self, checksum_t *rolling_checksum, char *string);

#endif
