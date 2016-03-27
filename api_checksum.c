#include "api_checksum.h"

#define M 0x10000

unsigned int checksum(unsigned int low, unsigned int high) {
  return low + (high * M);
}

unsigned int lower(char *string, int size) {
  unsigned int lower = 0;

  for (int i = 0 ; i < size ; i++) {
    lower += string[i];
  }

  lower = lower % M;
  return lower;
}

unsigned int higher(char *string, int size) {
  unsigned int higher = 0;

  for (int i = 0 ; i < size ; i++) {
    higher += (size - i) * string[i];
  }

  higher = higher % M;
  return higher;
}

int checksum_rolling_init(checksum_t *self, checksum_t *rolling_checksum, char *string) {
  checksum_init(rolling_checksum, string, self->size);

  unsigned int new_low = (self->low - self->string[0] + string[self->size -1]) % M;
  unsigned int new_high = (self->high - self->size * self->string[0] + new_low) % M;

  rolling_checksum->low = new_low;
  rolling_checksum->high = new_high;

  rolling_checksum->checksum_applied_to_string = checksum(new_low, new_high);

  return 0;
}

int checksum_calculate_checksum(checksum_t *self) {
  self->low = lower(self->string, self->size);
  self->high = higher(self->string, self->size);

  self->checksum_applied_to_string = checksum(self->low, self->high);

  return 0;
}

int checksum_init(checksum_t *self, char *string, int size) {
  self->string = string;
  self->size = size;

  return 0;
}

int checksum_init_with_checksum_applied_to_string(checksum_t *self, char *string, int size) {
  checksum_init(self, string, size);
  checksum_calculate_checksum(self);

  return 0;
}

int checksum_copy_from_checksum(checksum_t *self, checksum_t *other_checksum) {
  self->string = other_checksum->string;
  self->checksum_applied_to_string = other_checksum->checksum_applied_to_string;
  self->size = other_checksum->size;
  self->high = other_checksum->high;
  self->low = other_checksum->low;

  return 0;
}
