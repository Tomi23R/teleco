
#ifndef _LIST_H
#define _LIST_H

#include "const.h"

typedef struct _list_node *plist_node;

typedef struct _list_node {
  void * data;
  plist_node next;
} list_node;

typedef list_node list;

list * new_list();
void destroy_list(list *l);

list_node * list_insert(list_node *node, void *data);

void * list_get_data(list_node *node);

list_node * list_first(list *list);
list_node * list_node_next(list_node *node);

int  list_size(list *l);
BOOL list_is_empty(list *l);

#endif

