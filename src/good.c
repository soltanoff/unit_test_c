#include <stdlib.h>
#include <stdio.h>
#include "good.h"

/* Counts the number of items in a list.
*/
uint32_t count_list_items(list_t *const head) {
    uint32_t count = 0;
    list_t *temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* Inserts a new list item after the one specified as the argument.
*/
int8_t insert_next_to_list(list_t *item, int32_t data) {
    if (item) {
        list_t *temp = malloc(sizeof(list_t));
        if (temp) {
            temp->data = data;
            temp->next = item->next ? item->next : NULL;
            item->next = temp;
            return 1;
        }
    }
    return -1;
}

/* Removes an item following the one specified as the argument.*/
int8_t remove_next_from_list(list_t *item) {
    if (item && item->next) {
        list_t *temp = item->next->next;
        free(item->next);
        item->next = NULL;
        item->next = temp;
        return 1;
    }
    return -1;
}
/* Returns item data as text.
*/
// not secure for multithreaded programming
//char *item_data(const list_t *list) {
//    static char buf[12];
//    sprintf(buf, "%d", list->data);
//    return buf;
//}

int8_t item_data(const list_t *list, char *buf) {
    if (list) {
        sprintf(buf, "%d", list->data);
        return 1;
    }
    return -1;
}
