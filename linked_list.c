#include "linked_list.h"

#include <stdlib.h>

// typedef struct list_node
// {
//   struct list_node * next;
//   size_t value;
// }list_node_t;

// typedef struct linked_list 
// {
//   list_node_t *head;
//   list_node_t *tail;
// }linked_list_t;

struct list_node *new_node(size_t value) 
{ 
  struct list_node *node = malloc(sizeof(struct list_node));
  if(!node)
  {
    return NULL;
  } 
  node->value = value;
  node->next  = NULL;
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);
  if(!node){return;}
  node->next = list->head;
  list -> head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);
  if(!node){return;}
  if(list->head == NULL) 
  {
    list->head = node;
  }
  else
  {
    struct list_node *current_node = list -> head;
    while (current_node ->next  != NULL)
    {
      current_node = current_node -> next;
    }
    current_node -> next = node;
    free(node);
  }
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if (list-> head == NULL) {return 0;} 
  struct list_node *temp = list->head;
  size_t value = temp->value;
  list->head = temp->next;
  free(temp);
  return value;
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  if (list ->head == NULL){return 0;}
  struct list_node *current_node = list->head;
  struct  list_node *node_track = NULL;
  while(current_node -> next != NULL)
  {
    node_track = current_node;
    current_node = current_node -> next;
  }
  size_t value = current_node -> value;

  if (node_track == NULL)
  {
    list-> head = NULL;
  }
  else 
  {
    node_track -> next = NULL;
  }
  free(current_node);
  return value;
}

void free_list(struct linked_list list) 
{
  struct list_node *current_node = list.head;
  while(current_node != NULL)
  {
    struct list_node *next = current_node->next;
    free(current_node);
    current_node = next;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
