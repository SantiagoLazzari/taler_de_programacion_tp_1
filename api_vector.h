#ifndef API_VECTOR_H
#define API_VECTOR_H

#define VECTOR_INITIAL_CAPACITY 100

// Define a vector type
typedef struct vector {
  int size;      // slots used so far
  int capacity;  // total available slots
  int *data;     // array of integers we're storing
} vector_t;

void vector_init(vector_t *self);

void vector_append(vector_t *self, int value);

int vector_get_value_at_index(vector_t *self, int index);

void vector_set(vector_t *self, int index, int value);

void vector_double_capacity_if_full(vector_t *self);

unsigned int vector_contains_value(vector_t *self, int value);

void vector_destroy(vector_t *self);

#endif
