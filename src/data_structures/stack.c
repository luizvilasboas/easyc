#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../includes/data_structures/stack.h"

void stack_init(Stack *stack, size_t element_size) {
    stack->top = NULL;
    stack->element_size = element_size;
}

void stack_destroy(Stack *stack) {
    while (stack->top != NULL) {
        StackNode *node = stack->top;
        stack->top = node->next;

        free(node->data);
        free(node);
    }
}

void stack_push(Stack *stack, void *element) {
    StackNode *new_node = (StackNode *) malloc(sizeof(StackNode));
    assert(new_node != NULL);

    new_node->data = malloc(stack->element_size);
    assert(new_node->data != NULL);
    memcpy(new_node->data, element, stack->element_size);

    new_node->next = stack->top;
    stack->top = new_node;
}

void stack_pop(Stack *stack, void *element) {
    assert(stack->top != NULL);

    StackNode *top_node = stack->top;
    memcpy(element, top_node->data, stack->element_size);

    stack->top = top_node->next;
    free(top_node->data);
    free(top_node);
}

void *stack_peek(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }

    return stack->top->data;
}

void *stack_search(Stack *stack, int (*cmp_fn)(void *, void *), void *key) {
    StackNode *current = stack->top;

    while (current != NULL) {
        if (cmp_fn(current->data, key) == 0) {
            return current->data;
        }

        current = current->next;
    }

    return NULL;
}

void stack_foreach(Stack *stack, void (*fn)(void *)) {
    StackNode *current = stack->top;

    while (current != NULL) {
        fn(current->data);
        current = current->next;
    }
}

size_t stack_size(Stack *stack) {
    StackNode *current = stack->top;
    size_t count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void stack_reverse(Stack *stack) {
    StackNode *prev = NULL;
    StackNode *current = stack->top;
    StackNode *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    stack->top = prev;
}
