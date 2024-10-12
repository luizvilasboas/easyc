#include <stdio.h>
#include <check.h>
#include <stdlib.h>

#include "../../includes/data_structures/queue.h"

int sum;

int cmp_int(void *a, void *b) {
    return (*(int *)a) - (*(int *)b);
}

void sum_int(void *data) {
    sum += *(int *) data;
}

START_TEST(test_queue_init) {
    Queue queue;
    queue_init(&queue, sizeof(int));

    ck_assert_ptr_null(queue.front);
    ck_assert_ptr_null(queue.rear);
    ck_assert_int_eq(queue.element_size, sizeof(int));
    queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_enqueue) {
    Queue queue;
    queue_init(&queue, sizeof(int));

    int value = 42;
    queue_enqueue(&queue, &value);

    ck_assert_ptr_nonnull(queue.front);
    ck_assert_ptr_nonnull(queue.rear);
    ck_assert_int_eq(*(int *)queue.front->data, 42);
    ck_assert_int_eq(*(int *)queue.rear->data, 42);

    queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_dequeue) {
    Queue queue;
    queue_init(&queue, sizeof(int));

    int values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        queue_enqueue(&queue, &values[i]);
    }

    int dequeued_value;
    queue_dequeue(&queue, &dequeued_value);
    ck_assert_int_eq(dequeued_value, 1);

    queue_dequeue(&queue, &dequeued_value);
    ck_assert_int_eq(dequeued_value, 2);

    queue_dequeue(&queue, &dequeued_value);
    ck_assert_int_eq(dequeued_value, 3);

    queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_search) {
    Queue queue;
    queue_init(&queue, sizeof(int));

    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        queue_enqueue(&queue, &values[i]);
    }

    int target = 20;
    int *found = (int *)queue_search(&queue, cmp_int, &target);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 20);

    int not_found_value = 100;
    found = (int *)queue_search(&queue, cmp_int, &not_found_value);
    ck_assert_ptr_null(found);

    queue_destroy(&queue);
}
END_TEST

START_TEST(test_queue_foreach) {
    Queue queue;
    queue_init(&queue, sizeof(int));

    int values[] = {5, 15, 25};
    for (int i = 0; i < 3; i++) {
        queue_enqueue(&queue, &values[i]);
    }

    sum = 0;
    queue_foreach(&queue, sum_int);

    ck_assert_int_eq(sum, 45);

    queue_destroy(&queue);
}
END_TEST

Suite *generic_queue_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Generic Queue");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_queue_init);
    tcase_add_test(tc_core, test_queue_enqueue);
    tcase_add_test(tc_core, test_queue_dequeue);
    tcase_add_test(tc_core, test_queue_search);
    tcase_add_test(tc_core, test_queue_foreach);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = generic_queue_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
