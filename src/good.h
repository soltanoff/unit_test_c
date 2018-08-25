#ifndef GOOD_H
#define GOOD_H

typedef struct list_s {
    struct list_s *next; /* for the last item in a list */
    int data;
} list_t;

int count_list_items(list_t *const head);

int insert_next_to_list(list_t *item, int data);

void remove_next_from_list(list_t *item);

//char *item_data(const list_t *list);  // not secure for multithreaded programming
char *item_data(const list_t *list, char *buf);

#endif /* GOOD_H */
