// vector.c

#include <stdio.h>
#include <stdlib.h>
#include "api_vector.h"

void vector_init(vector_t *self) {
  // initialize size and capacity
  self->size = 0;
  self->capacity = VECTOR_INITIAL_CAPACITY;

  // allocate memory for self->data
  self->data = malloc(sizeof(int) * self->capacity);
}

void vector_append(vector_t *self, int value) {
  // make sure there's room to expand into
  vector_double_capacity_if_full(self);

  // append the value and increment self->size
  self->data[self->size++] = value;
}

int vector_get_value_at_index(vector_t *self, int index) {
  if (index >= self->size || index < 0) {
    printf("Index %d out of bounds for self of size %d\n", index, self->size);
    exit(1);
  }
  return self->data[index];
}

void vector_set(vector_t *self, int index, int value) {
  // zero fill the vector up to the desired index
  while (index >= self->size) {
    vector_append(self, 0);
  }

  // set the value at the desired index
  self->data[index] = value;
}

void vector_double_capacity_if_full(vector_t *self) {
  if (self->size >= self->capacity) {
    // double self->capacity and resize the allocated memory accordingly
    self->capacity *= 2;
    self->data = realloc(self->data, sizeof(int) * self->capacity);
  }
}

unsigned int vector_contains_value(vector_t *self, int value) {
  for (unsigned int i = 0; i < self->size; i++) {
    if(self->data[i] == value) {
      return i;
    }
  }

  return -1;
}

int vector_clean(vector_t *self) {
  vector_destroy(self);

  vector_init(self);

  return 0;
}

void vector_destroy(vector_t *self) {
  free(self->data);
}
