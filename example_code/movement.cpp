#include "main.h"
/*
 * Player:
 * player->coords...
 * player->movement etc...
 *
 * Entity:
 * e-> ...
 */
void entity_DefaultMove(Entity* e) {
  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
}

void entity_IcebergMove(Entity* e) {
  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
  std::cout << "x: " << player->coords.x << " y: " << player->coords.y << std::endl;
}

void entity_SharkMove(Entity* e) {
  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
}