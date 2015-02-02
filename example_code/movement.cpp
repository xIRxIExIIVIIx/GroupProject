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
  if (e->movement.x == 0){
    if (e->coords.x<(windowWidth / 2)){
      e->movement.x = (rand() % 100 + 1) / 100;
    }
    else{
      e->movement.x = -(rand() % 100 + 1) / 100;
    }
  }

  if (e->movement.y == 0){
    if (e->coords.y<(windowHeight / 2)){
      e->movement.y = (rand() % 100 + 1) / 100;
    }
    else{
      e->movement.y = -(rand() % 100 + 1) / 100;
    }
  }

  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
}

void entity_SharkMove(Entity* e) {

  int xDistance;
  int yDistance;
  int diagDistance;

  xDistance = e->coords.x - player->coords.x;
  yDistance = e->coords.y - player->coords.y;
  diagDistance = sqrt((xDistance*xDistance) + (yDistance*yDistance));

  if (xDistance > yDistance){
    e->movement.x = 1;
    e->movement.y = yDistance / xDistance;
  }
  else{
    e->movement.y = 1;
    e->movement.x = xDistance / yDistance;
  }

  if (diagDistance<100){
    e->movement.x *= 2;
    e->movement.y *= 2;
    e->invincible = false;
  }
  else{
    e->invincible = true;
  }

  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
}