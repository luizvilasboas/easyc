#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/hashmap.h"

int sum;

unsigned long hash_int(void *key) {
    return *(int *)key;
}

int cmp_ints(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

void sum_int(void *key, void *value) {
    sum += *(int *) value + *(int *) key;
}

START_TEST(test_hashmap_insert_search) {
    HashMap map;
    hashmap_init(&map, 10, sizeof(int), sizeof(int), hash_int, cmp_ints);

    int key = 10, value = 100;
    hashmap_insert(&map, &key, &value);

    int *found = (int *)hashmap_search(&map, &key);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 100);

    int non_existent_key = 20;
    found = (int *)hashmap_search(&map, &non_existent_key);
    ck_assert_ptr_null(found);

    hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_foreach) {
    HashMap map;
    hashmap_init(&map, 10, sizeof(int), sizeof(int), hash_int, cmp_ints);

    int keys[] = {10, 20, 30};
    int values[] = {100, 200, 300};
    for (int i = 0; i < 3; i++) {
        hashmap_insert(&map, &keys[i], &values[i]);
    }

    sum = 0;
    hashmap_foreach(&map, sum_int);

    ck_assert_int_eq(sum, 660);

    hashmap_destroy(&map);
}
END_TEST

START_TEST(test_hashmap_remove) {
    HashMap map;
    hashmap_init(&map, 10, sizeof(int), sizeof(int), hash_int, cmp_ints);

    int key1 = 10, value1 = 100;
    int key2 = 20, value2 = 200;
    hashmap_insert(&map, &key1, &value1);
    hashmap_insert(&map, &key2, &value2);

    int *found = (int *)hashmap_search(&map, &key1);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 100);

    found = (int *)hashmap_search(&map, &key2);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 200);

    hashmap_remove(&map, &key1);
    found = (int *)hashmap_search(&map, &key1);
    ck_assert_ptr_null(found);

    found = (int *)hashmap_search(&map, &key2);
    ck_assert_ptr_nonnull(found);
    ck_assert_int_eq(*found, 200);

    hashmap_destroy(&map);
}
END_TEST


Suite *generic_hashmap_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("HashMap");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_hashmap_insert_search);
    tcase_add_test(tc_core, test_hashmap_foreach);
    tcase_add_test(tc_core, test_hashmap_remove);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = generic_hashmap_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
