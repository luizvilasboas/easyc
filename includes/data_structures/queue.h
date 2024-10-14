#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    size_t element_size;
} Queue;

void queue_init(Queue *queue, size_t element_size);
void queue_destroy(Queue *queue);
void queue_enqueue(Queue *queue, void *element);
void queue_dequeue(Queue *queue, void *element);
void *queue_search(Queue *queue, int (*cmp_fn)(void *, void *), void *key);
void queue_foreach(Queue *queue, void (*fn)(void *));
size_t queue_size(Queue *queue);
int queue_is_empty(Queue *queue);
void *queue_peek(Queue *queue);
void queue_clear(Queue *queue);
void queue_reverse(Queue *queue);

#endif // QUEUE_H_
