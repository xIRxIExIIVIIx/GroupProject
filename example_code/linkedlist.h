
typedef struct listItem {
  listItem* next;
  Entity data;
} listItem;

typedef struct list {
  listItem* first;
  listItem* last;
};

list* list_Create();
bool list_Destroy(list* lst);
bool list_Remove(Entity* e, list* lst);
bool list_Add(Entity* e, list* lst);