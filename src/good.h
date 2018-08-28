#ifndef GOOD_H
#define GOOD_H

#include <stdint.h>


typedef struct list_s {
    struct list_s *next; /* for the last item in a list */
    int32_t data;
} list_t;

uint32_t count_list_items(list_t *const head);

int8_t insert_next_to_list(list_t *item, int32_t data);

int8_t remove_next_from_list(list_t *item);

//char *item_data(const list_t *list);  // not secure for multithreaded programming

int8_t item_data(const list_t *list, char *buf);

#endif /* GOOD_H */
