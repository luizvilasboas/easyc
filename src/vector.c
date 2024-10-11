#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/vector.h"

static VectorNode *create_vector_node(void *data, size_t element_size) {
    VectorNode *node = (VectorNode *) malloc(sizeof(VectorNode));

    node->data = malloc(element_size);
    memcpy(node->data, data, element_size);
    node->next = NULL;

    return node;
}

void vector_init(Vector *vector, size_t element_size, void (*free_fn)(void *)) {
    vector->head = NULL;
    vector->element_size = element_size;
    vector->free_n = free_fn;
}


void vector_destroy(Vector *vector) {
    VectorNode *current = vector->head;
    VectorNode *next;

    while (current != NULL) {
        next = current->next;

        if (vector->free_n) {
            vector->free_n(current->data);
        }

        free(current->data);
        free(current);

        current = next;
    }

    vector->head = NULL;
}

void vector_insert(Vector *vector, void *data) {
    VectorNode *new_node = create_vector_node(data, vector->element_size);
    new_node->next = vector->head;
    vector->head = new_node;
}

void vector_remove(Vector *vector, int (*cmp_fn)(void *, void *), void *key) {
    VectorNode *current = vector->head;
    VectorNode *previous = NULL;

    while (current != NULL) {
        if (cmp_fn(current->data, key) == 0) {
            if (previous == NULL) {
                vector->head = current->next;
            } else {
                previous->next = current->next;
            }

            if (vector->free_n) {
                vector->free_n(current->data);
            }

            free(current->data);
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }
}

void *vector_search(Vector *vector, int (*cmp_fn)(void *, void *), void *key) {
    VectorNode *current = vector->head;

    while (current != NULL) {
        if (cmp_fn(current->data, key) == 0) {
            return current->data;
        }

        current = current->next;
    }

    return NULL;
}

void vector_foreach(Vector *vector, void (*fn)(void *)) {
    VectorNode *current = vector->head;

    while (current != NULL) {
        fn(current->data);
        current = current->next;
    }
}
