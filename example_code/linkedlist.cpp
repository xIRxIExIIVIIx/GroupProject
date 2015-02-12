#include "main.h"

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

  listItem* lI = (listItem*)calloc(1, sizeof(listItem));
  lI->data = e;
  lI->next=(listItem*)(0);

  if (lst->last!=(listItem*)0){
	  lst->last->next=lI;
	  lst->last=lI;
  } else {
	  lst->first=lI;
	  lst->last=lI;
  }
  return &lI->data;

}

void list_forEach(entlist* lst, funcPtrEnt callback){
  listItem* next = lst->first;
  while (next != (listItem*)(0)){
    callback(&next->data);
    next = next->next;
  }
}
