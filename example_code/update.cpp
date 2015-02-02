#include "main.h"

/**
 * Function triggered every 30 ms
 * Use for game logic. Drawing from here will not work.
 **/

void Update(int t)
{
  //example: moves entities based on their move functions (in movement.cpp)
  for (std::list<Entity>::iterator ent = entities.begin(); ent != entities.end(); ++ent) {
    ent->move(&(*ent));
  }

}

bool entity_CheckCollision(Entity* e1, Entity* e2) {
  float dx = e2->coords.x - e1->coords.x;
  float dy = e2->coords.y - e1->coords.y;
  return sqrtf((dx * dx) + (dy * dy)) <= (e1->collisionRadius + e2->collisionRadius);
}