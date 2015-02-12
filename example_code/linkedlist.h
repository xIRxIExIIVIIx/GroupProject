
typedef struct listItem {
  listItem* next;
  Entity data;
} listItem;

typedef struct list {
  listItem* first;
  listItem* last;
};

<<<<<<< HEAD
typedef void(*funcPtrEnt)(Entity*);

entlist* list_Create();
bool list_Destroy(entlist* lst);
bool list_Remove(Entity* e, entlist* lst);
Entity* list_Add(Entity e, entlist* lst);
void list_forEach(entlist* lst, funcPtrEnt callback);
=======
list* list_Create();
bool list_Destroy(list* lst);
bool list_Remove(Entity* e, list* lst);
bool list_Add(Entity* e, list* lst);
>>>>>>> parent of 9ee74c4... totally broken again.
