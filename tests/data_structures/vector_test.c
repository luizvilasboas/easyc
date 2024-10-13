#include <check.h>
#include <stdlib.h>

#include "../../includes/data_structures/vector.h"

int sum;

int cmp_int(void *a, void *b) {
    return (*(int *) a) - (*(int *) b);
}

void sum_int(void *data) {
    sum += *(int *) data;
}

START_TEST(test_vector_init) {
    Vector vector;
    vector_init(&vector, sizeof(int));
    ck_assert_ptr_null(vector.head);
    ck_assert_int_eq(vector.element_size, sizeof(int));
    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_insert) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int value = 42;
    vector_insert(&vector, &value);
    ck_assert_ptr_nonnull(vector.head);
    ck_assert_int_eq(*(int *)vector.head->data, 42);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_remove) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int values[] = {5, 10, 15};
    for (int i = 0; i < 3; i++) {
        vector_insert(&vector, &values[i]);
    }

    int key = 10;
    vector_remove(&vector, cmp_int, &key);

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
    vector_init(&vector, sizeof(int));

    int values[] = {5, 10, 15};
    for (int i = 0; i < 3; i++) {
        vector_insert(&vector, &values[i]);
    }

    int key = 10;
    void *found = vector_search(&vector, cmp_int, &key);

    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*(int *)found, 10);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_foreach) {
    Vector vector;

    vector_init(&vector, sizeof(int));

    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        vector_insert(&vector, &values[i]);
    }

    sum = 0;
    vector_foreach(&vector, sum_int);

    ck_assert_int_eq(sum, 15);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_insert_at) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 1, data2 = 2, data3 = 3;

    vector_insert(&vector, &data1);
    vector_insert_at(&vector, 1, &data3);
    vector_insert_at(&vector, 1, &data2);

    int *found1 = (int *)vector_search(&vector, cmp_int, &data1);
    int *found2 = (int *)vector_search(&vector, cmp_int, &data2);
    int *found3 = (int *)vector_search(&vector, cmp_int, &data3);

    ck_assert_ptr_nonnull(found1);
    ck_assert_ptr_nonnull(found2);
    ck_assert_ptr_nonnull(found3);
    ck_assert_int_eq(*found1, 1);
    ck_assert_int_eq(*found2, 2);
    ck_assert_int_eq(*found3, 3);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_remove_at) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 1, data2 = 2, data3 = 3;

    vector_insert(&vector, &data1);
    vector_insert(&vector, &data2);
    vector_insert(&vector, &data3);

    vector_remove_at(&vector, 1);

    int *found1 = (int *)vector_search(&vector, cmp_int, &data1);
    int *found2 = (int *)vector_search(&vector, cmp_int, &data2);
    int *found3 = (int *)vector_search(&vector, cmp_int, &data3);

    ck_assert_ptr_nonnull(found1);
    ck_assert_ptr_null(found2);
    ck_assert_ptr_nonnull(found3);

    ck_assert_int_eq(*found1, 1);
    ck_assert_int_eq(*found3, 3);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_find) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 1, data2 = 2, data3 = 3;

    vector_insert(&vector, &data1);
    vector_insert(&vector, &data2);
    vector_insert(&vector, &data3);

    int index1 = vector_find(&vector, cmp_int, &data1);
    int index2 = vector_find(&vector, cmp_int, &data2);
    int index3 = vector_find(&vector, cmp_int, &data3);

    ck_assert_int_eq(index1, 2);
    ck_assert_int_eq(index2, 1);
    ck_assert_int_eq(index3, 0);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_reverse) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 1, data2 = 2, data3 = 3;

    vector_insert(&vector, &data1);
    vector_insert(&vector, &data2);
    vector_insert(&vector, &data3);

    vector_reverse(&vector);

    int *found1 = (int *)vector_search(&vector, cmp_int, &data1);
    int *found2 = (int *)vector_search(&vector, cmp_int, &data2);
    int *found3 = (int *)vector_search(&vector, cmp_int, &data3);

    ck_assert_ptr_nonnull(found1);
    ck_assert_ptr_nonnull(found2);
    ck_assert_ptr_nonnull(found3);

    ck_assert_int_eq(*found1, 1);
    ck_assert_int_eq(*found2, 2);
    ck_assert_int_eq(*found3, 3);

    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_sort) {
    Vector vector;
    vector_init(&vector, sizeof(int));

    int data1 = 3, data2 = 1, data3 = 2;

    vector_insert(&vector, &data1);
    vector_insert(&vector, &data2);
    vector_insert(&vector, &data3);

    vector_sort(&vector, cmp_int);

    int *found1 = (int *)vector_search(&vector, cmp_int, &data1);
    int *found2 = (int *)vector_search(&vector, cmp_int, &data2);
    int *found3 = (int *)vector_search(&vector, cmp_int, &data3);

    ck_assert_ptr_nonnull(found1);
    ck_assert_ptr_nonnull(found2);
    ck_assert_ptr_nonnull(found3);

    ck_assert_int_eq(*found1, 3);
    ck_assert_int_eq(*found2, 1);
    ck_assert_int_eq(*found3, 2);

    vector_destroy(&vector);
}
END_TEST

Suite *generic_list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Generic Vector");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vector_init);
    tcase_add_test(tc_core, test_vector_insert);
    tcase_add_test(tc_core, test_vector_remove);
    tcase_add_test(tc_core, test_vector_search);
    tcase_add_test(tc_core, test_vector_foreach);
    tcase_add_test(tc_core, test_vector_insert_at);
    tcase_add_test(tc_core, test_vector_remove_at);
    tcase_add_test(tc_core, test_vector_find);
    tcase_add_test(tc_core, test_vector_reverse);
    tcase_add_test(tc_core, test_vector_sort);
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
