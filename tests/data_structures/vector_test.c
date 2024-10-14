#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/data_structures/vector.h"

typedef struct {
    Vector vector;
} VectorFixture;

int cmp_fn(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

void vector_setup(VectorFixture *fixture) {
    vector_init(&fixture->vector, sizeof(int));
}

void vector_teardown(VectorFixture *fixture) {
    vector_destroy(&fixture->vector);
}

START_TEST(test_vector_init) {
    Vector vector;
    vector_init(&vector, sizeof(int));
    ck_assert_int_eq(vector.size, 0);
    ck_assert_ptr_eq(vector.head, NULL);
    vector_destroy(&vector);
}
END_TEST

START_TEST(test_vector_insert) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value1 = 10;
    int value2 = 20;

    ck_assert(vector_insert(&fixture.vector, &value1));
    ck_assert_int_eq(fixture.vector.size, 1);
    ck_assert_ptr_ne(fixture.vector.head, NULL);
    ck_assert_int_eq(*(int *)fixture.vector.head->data, 10);

    ck_assert(vector_insert(&fixture.vector, &value2));
    ck_assert_int_eq(fixture.vector.size, 2);
    ck_assert_int_eq(*(int *)fixture.vector.head->data, 20);

    vector_teardown(&fixture);
}
END_TEST

START_TEST(test_vector_remove) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value1 = 10;
    int value2 = 20;
    vector_insert(&fixture.vector, &value1);
    vector_insert(&fixture.vector, &value2);

    ck_assert(vector_remove(&fixture.vector, 0));
    ck_assert_int_eq(fixture.vector.size, 1);
    ck_assert_int_eq(*(int *)fixture.vector.head->data, 10);

    ck_assert(vector_remove(&fixture.vector, 0));
    ck_assert_int_eq(fixture.vector.size, 0);
    ck_assert_ptr_eq(fixture.vector.head, NULL);

    vector_teardown(&fixture);
}
END_TEST

START_TEST(test_vector_update) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value1 = 10;
    int value2 = 20;
    int new_value = 30;

    vector_insert(&fixture.vector, &value1);
    vector_insert(&fixture.vector, &value2);

    ck_assert(vector_update(&fixture.vector, 0, &new_value));
    ck_assert_int_eq(*(int *)fixture.vector.head->data, 30);

    vector_teardown(&fixture);
}
END_TEST

START_TEST(test_vector_get) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value1 = 10;
    int value2 = 20;

    vector_insert(&fixture.vector, &value1);
    vector_insert(&fixture.vector, &value2);

    int *result = (int *)vector_get(&fixture.vector, 1);
    ck_assert_int_eq(*result, 10);

    result = (int *)vector_get(&fixture.vector, 0);
    ck_assert_int_eq(*result, 20);

    vector_teardown(&fixture);
}
END_TEST

START_TEST(test_vector_search) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value1 = 10;
    int value2 = 20;

    vector_insert(&fixture.vector, &value1);
    vector_insert(&fixture.vector, &value2);

    int pos = vector_search(&fixture.vector, cmp_fn, &value1);
    ck_assert_int_eq(pos, 1);

    pos = vector_search(&fixture.vector, cmp_fn, &value2);
    ck_assert_int_eq(pos, 0);

    pos = vector_search(&fixture.vector, cmp_fn, NULL);
    ck_assert_int_eq(pos, -1);

    vector_teardown(&fixture);
}
END_TEST

START_TEST(test_vector_destroy) {
    VectorFixture fixture;
    vector_setup(&fixture);

    int value = 10;
    vector_insert(&fixture.vector, &value);
    vector_destroy(&fixture.vector);

    ck_assert_ptr_eq(fixture.vector.head, NULL);
}
END_TEST

Suite *vector_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Vector");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vector_init);
    tcase_add_test(tc_core, test_vector_insert);
    tcase_add_test(tc_core, test_vector_remove);
    tcase_add_test(tc_core, test_vector_update);
    tcase_add_test(tc_core, test_vector_get);
    tcase_add_test(tc_core, test_vector_search);
    tcase_add_test(tc_core, test_vector_destroy);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = vector_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
