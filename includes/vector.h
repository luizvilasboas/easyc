#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>

typedef struct VectorNode {
    void *data;
    struct VectorNode *next;
} VectorNode;

typedef struct Vector {
    VectorNode *head;
    size_t element_size;
    void (*free_n)(void *);
} Vector;

void vector_init(Vector *vector, size_t element_size, void (*free_fn)(void *));
void vector_destroy(Vector *vector);
void vector_insert(Vector *vector, void *data);
void vector_remove(Vector *vector, int (*cmp_fn)(void *, void *), void *key);
void *vector_search(Vector *vector, int (*cmp_fn)(void *, void *), void *key);
void vector_foreach(Vector *vector, void (*fn)(void *));

#endif // VECTOR_H_
