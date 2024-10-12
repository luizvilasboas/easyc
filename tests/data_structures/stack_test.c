#include <check.h>
#include <stdlib.h>

#include "../../includes/data_structures/stack.h"

int sum;

int cmp_int(void *a, void *b) {
    return (*(int *) a) - (*(int *) b);
}

void sum_int(void *data) {
    sum += *(int *) data;
}

START_TEST(test_stack_init) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    ck_assert_ptr_null(stack.top);
    ck_assert_int_eq(stack.element_size, sizeof(int));
    stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_push) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int value = 42;
    stack_push(&stack, &value);

    ck_assert_ptr_nonnull(stack.top);
    ck_assert_int_eq(*(int *)stack.top->data, 42);

    stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_pop) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int value = 42;
    stack_push(&stack, &value);

    int popped_value;
    stack_pop(&stack, &popped_value);
    ck_assert_int_eq(popped_value, 42);

    stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_peek) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int value = 100;
    stack_push(&stack, &value);

    int *peeked_value = (int *)stack_peek(&stack);
    ck_assert_ptr_nonnull(peeked_value);
    ck_assert_int_eq(*peeked_value, 100);

    stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_search) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int values[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        stack_push(&stack, &values[i]);
    }

    int key = 20;
    int *found = (int *)stack_search(&stack, cmp_int, &key);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 20);

    int key_not_found = 100;
    found = (int *)stack_search(&stack, cmp_int, &key_not_found);
    ck_assert_ptr_null(found);

    stack_destroy(&stack);
}
END_TEST

START_TEST(test_stack_foreach) {
    Stack stack;
    stack_init(&stack, sizeof(int));

    int values[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        stack_push(&stack, &values[i]);
    }

    sum = 0;

    stack_foreach(&stack, sum_int);

    ck_assert_int_eq(sum, 100);

    stack_destroy(&stack);
}
END_TEST

Suite *generic_stack_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Generic Stack");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_stack_init);
    tcase_add_test(tc_core, test_stack_push);
    tcase_add_test(tc_core, test_stack_pop);
    tcase_add_test(tc_core, test_stack_peek);
    tcase_add_test(tc_core, test_stack_search);
    tcase_add_test(tc_core, test_stack_foreach);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = generic_stack_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
