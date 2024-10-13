#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/data_structures/vector.h"

static VectorNode *create_vector_node(void *data, size_t element_size) {
    VectorNode *node = (VectorNode *) malloc(sizeof(VectorNode));

    node->data = malloc(element_size);
    memcpy(node->data, data, element_size);
    node->next = NULL;

    return node;
}

void vector_init(Vector *vector, size_t element_size) {
    vector->head = NULL;
    vector->element_size = element_size;
    vector->size = 0;
}


void vector_destroy(Vector *vector) {
    VectorNode *current = vector->head;
    VectorNode *next;

    while (current != NULL) {
        next = current->next;

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
    vector->size++;
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

            free(current->data);
            free(current);
            vector->size--;
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

void vector_insert_at(Vector *vector, size_t index, void *data) {
    if (index > vector->size) return;

    VectorNode *new_node = create_vector_node(data, vector->element_size);

    if (index == 0) {
        new_node->next = vector->head;
        vector->head = new_node;
    } else {
        VectorNode *current = vector->head;
        for (size_t i = 0; i < index - 1 && current != NULL; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    vector->size++;
}

void vector_remove_at(Vector *vector, size_t index) {
    if (index >= vector->size) return;

    VectorNode *current = vector->head;
    VectorNode *previous = NULL;

    if (index == 0) {
        vector->head = current->next;
    } else {
        for (size_t i = 0; i < index; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

    free(current->data);
    free(current);
    vector->size--;
}

int vector_find(Vector *vector, int (*cmp_fn)(void *, void *), void *key) {
    VectorNode *current = vector->head;
    size_t index = 0;
    while (current != NULL) {
        if (cmp_fn(current->data, key) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void vector_reverse(Vector *vector) {
    VectorNode *prev = NULL;
    VectorNode *current = vector->head;
    VectorNode *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    vector->head = prev;
}

void vector_sort(Vector *vector, int (*cmp_fn)(void *, void *)) {
    if (vector->size < 2) return;

    for (VectorNode *i = vector->head; i != NULL; i = i->next) {
        for (VectorNode *j = i->next; j != NULL; j = j->next) {
            if (cmp_fn(i->data, j->data) > 0) {
                void *temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
