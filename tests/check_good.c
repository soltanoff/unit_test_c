#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "src/good.h"


#define BUF_SIZE 2U
#define SMALL_LIST_SIZE 5U
#define BIG_LIST_SIZE 50000U


list_t *test_small_list;
list_t *test_big_list;


int8_t make_list(list_t **head, const uint32_t size) {
    list_t *prev = *head;
    for (uint32_t i = 0; i < size; i++) {
        list_t *temp = malloc(sizeof(list_t));
        if (temp) {
            temp->next = NULL;
            temp->data = i;
            if (prev) {
                prev->next = temp;
                prev = temp;
            } else {
                *head = temp;
                prev = *head;
            }
        } else return -1;
    }
    return 1;
}

void free_list(list_t **head) {
    while (*head) {
        list_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

void setup(void) {
    make_list(&test_small_list, SMALL_LIST_SIZE);
    make_list(&test_big_list, BIG_LIST_SIZE);
}

void teardown(void) {
    free_list(&test_small_list);
    free_list(&test_big_list);
}

START_TEST(test_small_list_count)
    {
        ck_assert_int_eq(count_list_items(test_small_list), SMALL_LIST_SIZE);
    }
END_TEST

START_TEST(test_big_list_count)
    {
        ck_assert_int_eq(count_list_items(test_big_list), BIG_LIST_SIZE);
    }
END_TEST

START_TEST(test_empty_list_count)
    {
        list_t *temp_list = NULL;
        ck_assert_int_eq(count_list_items(temp_list), 0);
    }
END_TEST

START_TEST(test_item_data)
    {
        char buf[BUF_SIZE];

        ck_assert_int_eq(item_data(test_big_list, buf), 1);
        ck_assert_int_eq(strcmp(buf, "0"), 0);

        ck_assert_int_eq(item_data(test_small_list->next, buf), 1);
        ck_assert_int_eq(strcmp(buf, "1"), 0);
    }
END_TEST

START_TEST(test_remove_next_from_list_middle)
    {
        const uint32_t temp_list_size = 3;
        list_t *temp_list = NULL;
        if (!make_list(&temp_list, temp_list_size))
            ck_abort_msg("Can't create a list, please try again...");

        // temp_list = [0, 1, 2]
        remove_next_from_list(temp_list);  // [0, 1, 2] -> [0, 2]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next->data, 2);
        ck_assert_int_eq(temp_list->next->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 2);
        free_list(&temp_list);
    }
END_TEST

START_TEST(test_remove_next_from_list_last)
    {
        const uint32_t temp_list_size = 2;
        list_t *temp_list = NULL;
        if (!make_list(&temp_list, temp_list_size))
            ck_abort_msg("Can't create a list, please try again...");

        // temp_list = [0, 1]
        remove_next_from_list(temp_list->next);  // [0, 1] -> [0, 1]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next->data, 1);
        ck_assert_int_eq(temp_list->next->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 2);

        remove_next_from_list(temp_list);  // [0, 2] -> [0]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 1);
    }
END_TEST

START_TEST(test_remove_next_from_list_of_sizes_one)
    {
        const uint32_t temp_list_size = 1;
        list_t *temp_list = NULL;
        if (!make_list(&temp_list, temp_list_size))
            ck_abort_msg("Can't create a list, please try again...");

        // temp_list = [0]
        remove_next_from_list(temp_list);  // [0] -> [0]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 1);
        free_list(&temp_list);
    }
END_TEST

START_TEST(test_insert_next_from_list_after_head)
    {
        const uint32_t temp_list_size = 3;
        list_t *temp_list = NULL;
        if (!make_list(&temp_list, temp_list_size))
            ck_abort_msg("Can't create a list, please try again...");

        // temp_list = [0, 1, 2]
        insert_next_to_list(temp_list, -1);  // [0, 1, 2] -> [0, -1, 1, 2]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next->data, -1);
        ck_assert_int_eq(temp_list->next->next->data, 1);
        ck_assert_int_eq(temp_list->next->next->next->data, 2);
        ck_assert_int_eq(temp_list->next->next->next->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 4);
        free_list(&temp_list);
    }
END_TEST

START_TEST(test_insert_next_from_list_after_last)
    {
        const uint32_t temp_list_size = 2;
        list_t *temp_list = NULL;
        if (!make_list(&temp_list, temp_list_size))
            ck_abort_msg("Can't create a list, please try again...");

        // temp_list = [0, 1]
        insert_next_to_list(temp_list->next, 500);  // [0, 1] -> [0, 1, 500]
        ck_assert_int_eq(temp_list->data, 0);
        ck_assert_int_eq(temp_list->next->data, 1);
        ck_assert_int_eq(temp_list->next->next->data, 500);
        ck_assert_int_eq(temp_list->next->next->next == NULL, 1);
        ck_assert_int_eq(count_list_items(temp_list), 3);
        free_list(&temp_list);
    }
END_TEST

START_TEST(test_methods_with_empty_pointer)
    {
        list_t *temp_list = NULL;
        char buf[BUF_SIZE];

        ck_assert_int_eq(count_list_items(temp_list), 0);
        ck_assert_int_eq(insert_next_to_list(temp_list, 666), -1);
        ck_assert_int_eq(remove_next_from_list(temp_list), -1);
        ck_assert_int_eq(item_data(temp_list, buf), -1);
    }
END_TEST


Suite *list_suite(void) {
    Suite *s;
    TCase *tc_list_count;
    TCase *tc_item_data;
    TCase *tc_rm;
    TCase *tc_insert;
    TCase *tc_empty;

    s = suite_create("list");

    /* `List count` test case */
    tc_list_count = tcase_create("`List count`");

    tcase_add_checked_fixture(tc_list_count, setup, teardown);
    tcase_add_test(tc_list_count, test_small_list_count);
    tcase_add_test(tc_list_count, test_big_list_count);
    tcase_add_test(tc_list_count, test_empty_list_count);
    suite_add_tcase(s, tc_list_count);

    /* `Item data` test case */
    tc_item_data = tcase_create("`Item data`");

    tcase_add_checked_fixture(tc_item_data, setup, teardown);
    tcase_add_test(tc_item_data, test_item_data);
    suite_add_tcase(s, tc_item_data);

    /* `Remove next from list` test case */
    tc_rm = tcase_create("`Remove next from list`");
    tcase_add_test(tc_rm, test_remove_next_from_list_middle);
    tcase_add_test(tc_rm, test_remove_next_from_list_last);
    tcase_add_test(tc_rm, test_remove_next_from_list_of_sizes_one);
    suite_add_tcase(s, tc_rm);

    /* `Insert next from list` test case */
    tc_insert = tcase_create("`Insert next from list`");
    tcase_add_test(tc_insert, test_insert_next_from_list_after_head);
    tcase_add_test(tc_insert, test_insert_next_from_list_after_last);
    suite_add_tcase(s, tc_insert);

    /* `Methods with empty pointer` test case */
    tc_empty = tcase_create("`Methods with empty pointer`");
    tcase_add_test(tc_empty, test_methods_with_empty_pointer);
    suite_add_tcase(s, tc_empty);

    return s;
}

int main(void) {
    uint32_t number_failed;
    Suite *s;
    SRunner *sr;

    s = list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
