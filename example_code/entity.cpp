#include "entity.h"
#include <math.h>

float entity_GetDistance(Entity* e1, Entity* e2) {
  float dx = e2->coords.x - e1->coords.x;
  float dy = e2->coords.y - e1->coords.y;
  return sqrtf((dx * dx) + (dy * dy));
}

bool entity_CheckCollision(Entity* e1, Entity* e2) {
  return entity_GetDistance(e1, e2) <= (e1->collisionRadius + e2->collisionRadius);
}