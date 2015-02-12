#include "main.h"
#include "linkedlist.h"

list* list_Create() {
  list* a = (list*)calloc(1, sizeof(list));
  a->first = (listItem*)(0);
}

bool list_Destroy(list* lst) {
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

bool list_Remove(Entity* e, list* lst) {
  if (!lst) return false;
  listItem* current = lst->first;
  Entity* ent = &current->next->data;

  while (current) {
    if (ent = e) {
      listItem* temp = current->next;
      current->next = temp->next;
      free(temp);
      return true;
    } else {
      current = current->next;
    }
  }
}

bool list_Add(Entity* e, list* lst) {
  if (!lst) return false;
  listItem* current = lst->first;
  Entity* ent = &current->next->data;

  while (current) {
    if (ent = e) {
      listItem* temp = current->next;
      current->next = temp->next;
      free(temp);
      return true;
    } else {
      current = current->next;
    }
  }

}


