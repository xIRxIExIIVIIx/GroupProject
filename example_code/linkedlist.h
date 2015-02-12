
typedef struct listItem {
  listItem* next;
  Entity data;
} listItem;

typedef struct entlist {
  listItem* first;
  listItem* last;
} entlist;

typedef void(*funcPtrEnt)(Entity*);

entlist* list_Create();
bool list_Destroy(entlist* lst);
bool list_Remove(Entity* e, entlist* lst);
Entity* list_Add(Entity e, entlist* lst);
void list_forEach(entlist* lst, funcPtrEnt callback);
void list_forEach(entlist* lst, Entity* ent2, funcPtrEnt2 callback);