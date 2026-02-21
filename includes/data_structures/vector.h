#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct VectorNode {
  void *data;
  struct VectorNode *next;
} VectorNode;

typedef struct Vector {
  VectorNode *head;
  size_t element_size;
  size_t size;
} Vector;

void vector_init(Vector *vector, size_t element_size);
void vector_destroy(Vector *vector);
bool vector_insert(Vector *vector, void *data);
bool vector_remove(Vector *vector, size_t index);
bool vector_update(Vector *vector, size_t index, void *new_data);
void *vector_get(Vector *vector, size_t index);
int vector_search(Vector *vector, int (*cmp_fn)(void *, void *), void *key);
int vector_size(Vector *vector);
bool vector_sort(Vector *vector, int (*cmp_fn)(void *, void *));

#endif  // VECTOR_H_
