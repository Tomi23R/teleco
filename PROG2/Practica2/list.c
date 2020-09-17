
#include "list.h"
#include <stdlib.h>
#include <assert.h>

list * new_list() {
  list *l = (list *) malloc(sizeof(list));
  
  /* Nodo cabecera: todo a null */
  l->data = NULL;
  l->next = NULL; 
  
  return l;
}

void destroy_list(list *l) {
  list_node *node = l->next;
  
  while ( node != NULL ) {
    list_node *next = node->next;
    free(node);
    node = next;
  }

  free(l);
}

list_node * new_node(void *data) 
{
  list_node *node = (list_node *) malloc(sizeof(list_node));
  node->data = data;
  return node;
}

list_node * list_insert(list_node *node, void *data) 
{
  list_node *new_node_ = new_node(data);
  new_node_->next = node->next;
  
  node->next = new_node_;
  
  return new_node_;
}

void * list_get_data(list_node *node) 
{
  assert(node != NULL);
  return node->data;
}

int list_size(list *l) 
{
  list *node = l->next;
  int i = 0;
  while ( node != NULL ) {
    i++;
    node = node->next;
  }
  return i;
}

list_node * list_first(list *list) 
{
  return list->next;
}

list_node * list_node_next(list *node) 
{
  return node->next;
}


