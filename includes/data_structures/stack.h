#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    size_t element_size;
    size_t size;
} Stack;

void stack_init(Stack *stack, size_t element_size);
void stack_destroy(Stack *stack);
bool stack_push(Stack *stack, void *data);
bool stack_pop(Stack *stack);
void *stack_top(Stack *stack);
int stack_search(Stack *stack, int (*cmp_fn)(void *, void *), void *key);
int stack_size(Stack *stack);

#endif // STACK_H_
