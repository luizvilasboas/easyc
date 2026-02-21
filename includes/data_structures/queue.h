#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct QueueNode {
  void *data;
  struct QueueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front;
  QueueNode *back;
  size_t element_size;
  size_t size;
} Queue;

void queue_init(Queue *queue, size_t element_size);
void queue_destroy(Queue *queue);
bool queue_push(Queue *queue, void *data);
bool queue_pop(Queue *queue);
void *queue_front(Queue *queue);
void *queue_back(Queue *queue);
int queue_search(Queue *queue, int (*cmp_fn)(void *, void *), void *key);
int queue_size(Queue *queue);

#endif  // QUEUE_H_
