#define entIt std::list<Entity>::iterator

void entity_DefaultCollide(entIt e, entIt with);
void entity_IcebergCollide(entIt e, entIt with);
void entity_SharkCollide(entIt e, entIt with);
void entity_CthulhuCollide(entIt e, entIt with);
void entity_BulletCollide(entIt e, entIt with);
void entity_PlayerCollide(entIt e, entIt with);