#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>

typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    size_t element_size;
} Stack;

void stack_init(Stack *stack, size_t element_size);
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, void *element);
void stack_pop(Stack *stack, void *element);
void *stack_peek(Stack *stack);
void *stack_search(Stack *stack, int (*cmp_fn)(void *, void *), void *key);
void stack_foreach(Stack *stack, void (*fn)(void *));

#endif // STACK_H_
