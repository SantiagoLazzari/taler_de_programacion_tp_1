#ifndef API_CHECKSUM_H
#define API_CHECKSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct checksum {
  char *string;
  unsigned long checksum_applied_to_string;
  int size;
  unsigned long high;
  unsigned long low;

} checksum_t;

int checksum_init(checksum_t *chechsum, char *string, int size);
int checksum_rolling_init(checksum_t *self, checksum_t *rolling_checksum, char *string);

#endif
