
typedef struct listItem {
  listItem* next;
  Entity data;
} listItem;

typedef struct entlist {
  listItem* first;
  listItem* last;
} entlist;

entlist* list_Create();
bool list_Destroy(entlist* lst);
bool list_Remove(Entity* e, entlist* lst);
bool list_Add(Entity* e, entlist* lst);
