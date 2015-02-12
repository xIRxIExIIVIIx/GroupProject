
#include <stdlib.h>
#include "linkedlist.h"

entlist* list_Create() {
  entlist* a = (entlist*)calloc(1, sizeof(entlist));
  a->first = (listItem*)(0);
  a->last=(listItem*)(0);
  return a;
}

bool list_Destroy(entlist* lst) {
  if (!lst) return false;
  listItem* current = lst->first;

  while (current) {
    listItem* temp = current;
    current = current->next;
    free(temp);
  }

  free(lst->first);
  free(lst);
  return true;
}

bool list_Remove(Entity* e, entlist* lst) {
  if (!lst) return false;
  listItem* current = lst->first;
  Entity* ent = &current->next->data;

  while (current) {
    if (ent = e) {
      listItem* temp = current->next;
      current->next = temp->next;
      free(temp);
      return true;
    } 
	else {
      current = current->next;
    }
  }
}

Entity* list_Add(Entity e, entlist* lst) {
  if (!lst) return (Entity*)(0);

  listItem* lstItem = (listItem*)calloc(1, sizeof(listItem));
  lstItem->data = e;
  lstItem->next = (listItem*)(0);

  if (lst->last != (listItem*)0){
    lst->last->next = lstItem;
    lst->last = lstItem;
  } else {
    lst->first = lstItem;
    lst->last = lstItem;
  }
  return &lstItem->data;
}


