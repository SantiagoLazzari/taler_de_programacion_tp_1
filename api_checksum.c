#include "api_checksum.h"

#define M 0x10000

unsigned long checksum(unsigned int low, unsigned long high) {
  return low + (high * M);
}

unsigned long lower(char *string, int size) {
  unsigned long lower = 0;

  for (int i = 0 ; i < size ; i++) {
    lower += string[i];
  }

  lower = lower % M;
  return lower;
}

unsigned long higher(char *string, int size) {
  unsigned long higher = 0;

  for (int i = 0 ; i < size ; i++) {
    higher += (size - i) * string[i];
  }

  higher = higher % M;
  return higher;
}

int checksum_rolling_init(checksum_t *self, checksum_t *rolling_checksum, char *string) {
  checksum_init(rolling_checksum, string, self->size);

  unsigned long new_low = (self->low - self->string[0] + string[self->size -1]) % M;
  unsigned long new_high = (self->high - self->size * self->string[0] + new_low) % M;

  rolling_checksum->checksum_applied_to_string = checksum(new_low, new_high);

  return 0;
}

int checksum_init(checksum_t *self, char *string, int size) {
  self->string = string;
  self->size = size;

  self->low = lower(string, size);
  self->high = higher(string, size);

  self->checksum_applied_to_string = checksum(self->low, self->high);

  return 0;
}
