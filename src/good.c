#include <stdlib.h>
#include <stdio.h>
#include "good.h"

/* Counts the number of items in a list.
*/
int count_list_items(list_t *const head) {
    u_int32_t count = 0;
    list_t *temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* Inserts a new list item after the one specified as the argument.
*/
int insert_next_to_list(list_t *item, int data) {
    list_t *temp = malloc(sizeof(list_t));
    if (temp) {
        temp->data = data;
        temp->next = item->next ? item->next : NULL;
        item->next = temp;
        return 1;
    }
    return 0;
}

/* Removes an item following the one specified as the argument.*/
void remove_next_from_list(list_t *item) {
    if (item->next) {
        list_t *temp = item->next->next;
        free(item->next);
        item->next = temp;
    }
}
/* Returns item data as text.
*/
// not secure for multithreaded programming
//char *item_data(const list_t *list) {
//    static char buf[12];
//    sprintf(buf, "%d", list->data);
//    return buf;
//}

char *item_data(const list_t *list, char *buf) {
    sprintf(buf, "%d", list->data);
    return buf;
}
