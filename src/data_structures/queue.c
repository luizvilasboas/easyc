#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../includes/data_structures/queue.h"

void queue_init(Queue *queue, size_t element_size) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->element_size = element_size;
}

void queue_destroy(Queue *queue) {
    QueueNode *current = queue->front;
    while (current != NULL) {
        QueueNode *tmp = current;
        current = current->next;
        free(tmp->data);
        free(tmp);
    }
    queue->front = NULL;
    queue->rear = NULL;
}

void queue_enqueue(Queue *queue, void *element) {
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    assert(new_node != NULL);

    new_node->data = malloc(queue->element_size);
    assert(new_node->data != NULL);

    memcpy(new_node->data, element, queue->element_size);
    new_node->next = NULL;

    if (queue->rear != NULL) {
        queue->rear->next = new_node;
    }

    queue->rear = new_node;

    if (queue->front == NULL) {
        queue->front = new_node;
    }
}

void queue_dequeue(Queue *queue, void *element) {
    assert(queue->front != NULL);

    QueueNode *old_front = queue->front;
    memcpy(element, old_front->data, queue->element_size);

    queue->front = old_front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(old_front->data);
    free(old_front);
}

void *queue_search(Queue *queue, int (*cmp_fn)(void *, void *), void *key) {
    QueueNode *current = queue->front;
    while (current != NULL) {
        if (cmp_fn(current->data, key) == 0) {
            return current->data;
        }

        current = current->next;
    }

    return NULL;
}

void queue_foreach(Queue *queue, void (*fn)(void *)) {
    QueueNode *current = queue->front;
    while (current != NULL) {
        fn(current->data);
        current = current->next;
    }
}

size_t queue_size(Queue *queue) {
    size_t size = 0;
    QueueNode *current = queue->front;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void *queue_peek(Queue *queue) {
    if (queue->front != NULL) {
        return queue->front->data;
    }
    return NULL;
}

void queue_reverse(Queue *queue) {
    QueueNode *prev = NULL, *current = queue->front, *next = NULL;
    queue->rear = queue->front;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    queue->front = prev;
}
