#include <check.h>
#include <stdlib.h>

#include "../includes/vector.h"

int sum;

int compare_int(void *a, void *b) {
    return (*(int *) a) - (*(int *) b);
}

void free_int(void *data) {
    free(data);
}

void sum_int(void *data) {
    sum += *(int *) data;
}

START_TEST(test_vector_init) {
    Vector vector;
    vector_init(&vector, sizeof(int), NULL);
    ck_assert_ptr_null(vector.head);
    ck_assert_int_eq(vector.element_size, sizeof(int));
    ck_assert_ptr_null(vector.free_n);
    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_insert) {
    Vector vector;
    vector_init(&vector, sizeof(int), NULL);

    int value = 42;
    vector_insert(&vector, &value);
    ck_assert_ptr_nonnull(vector.head);
    ck_assert_int_eq(*(int *)vector.head->data, 42);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_remove) {
    Vector vector;
    vector_init(&vector, sizeof(int), NULL);

    int values[] = {5, 10, 15};
    for (int i = 0; i < 3; i++) {
        vector_insert(&vector, &values[i]);
    }

    int key = 10;
    vector_remove(&vector, compare_int, &key);

    VectorNode *current = vector.head;
    while (current != NULL) {
        ck_assert_int_ne(*(int *)current->data, 10);
        current = current->next;
    }

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_search) {
    Vector vector;
    vector_init(&vector, sizeof(int), NULL);

    int values[] = {5, 10, 15};
    for (int i = 0; i < 3; i++) {
        vector_insert(&vector, &values[i]);
    }

    int key = 10;
    void *found = vector_search(&vector, compare_int, &key);

    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*(int *)found, 10);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_foreach) {
    Vector vector;

    vector_init(&vector, sizeof(int), NULL);

    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        vector_insert(&vector, &values[i]);
    }

    sum = 0;
    vector_foreach(&vector, sum_int);

    ck_assert_int_eq(sum, 15);

    vector_destroy(&vector);
}

Suite *generic_list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Vector List");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vector_init);
    tcase_add_test(tc_core, test_vector_insert);
    tcase_add_test(tc_core, test_vector_remove);
    tcase_add_test(tc_core, test_vector_search);
    tcase_add_test(tc_core, test_vector_foreach);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = generic_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
