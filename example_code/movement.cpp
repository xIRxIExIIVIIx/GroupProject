#include "main.h"

void entity_DefaultMove(Entity* e) {
  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
}

void entity_IcebergMove(Entity* e) {

  if (e->movement.x == 0){
    e->movement.x = ((float)(rand() % 100 + 1)) / 100;
    if (e->coords.x>(windowWidth / 2))
      e->movement.x = -e->movement.x;
	}

  if (e->movement.y == 0){
    e->movement.y = ((float)(rand() % 100 + 1)) / 100;
    if (e->coords.y>(windowHeight / 2))
      e->movement.y = -e->movement.y;
	}

	entity_DefaultMove(e);
}

void entity_SharkMove(Entity* e) {
  float xDistance;
  float yDistance;
  float diagDistance;

  xDistance = player->coords.x - e->coords.x;
  yDistance = player->coords.y - e->coords.y;
  diagDistance = sqrt((xDistance*xDistance) + (yDistance*yDistance));

  if (abs(xDistance) > abs(yDistance)){
    if (xDistance>0){
      e->movement.x = 1;
    }
    else {
      e->movement.x = -1;
    }
    e->movement.y = yDistance / abs(xDistance);
  }
  else{
    if (yDistance>0){
      e->movement.y = 1;
    }
    else{
      e->movement.y = -1;
    }
    e->movement.x = xDistance / abs(yDistance);
  }

  if (diagDistance<100){
    e->movement.x *= 2;
    e->movement.y *= 2;
    e->invincible = false;
  }
  else{
    e->invincible = true;
  }

  entity_DefaultMove(e);
}

void entity_CthulhuMove(Entity* e){
  float xDistance;
  float yDistance;
  float diagDistance;

  xDistance = player->coords.x - e->coords.x;
  yDistance = player->coords.y - e->coords.y;
  diagDistance = sqrt((xDistance*xDistance) + (yDistance*yDistance));

  if (abs(xDistance) > abs(yDistance)){
    if (xDistance>0){
      e->movement.x = 1;
    }
    else {
      e->movement.x = -1;
    }
    e->movement.y = yDistance / abs(xDistance);
  }
  else{
    if (yDistance>0){
      e->movement.y = 1;
    }
    else{
      e->movement.y = -1;
    }
    e->movement.x = xDistance / abs(yDistance);
  }

  e->movement.x = e->movement.x*0.5;
  e->movement.y = e->movement.y*0.5;

  entity_DefaultMove(e);
}

void entity_BulletMove(Entity* e) {
	if (e->movement.x==0)
		e->movement.x = player->movement.x;
	
	if (e->movement.y==0)
		e->movement.y = player->movement.y;
	
	entity_DefaultMove(e);
}

void entity_PlayerMove(Entity* e){
  e->movement.x = keys['a'] ? -1 : (keys['d'] ? 1 : 0);
  e->movement.y = keys['w'] ? -1 : (keys['s'] ? 1 : 0);

  entity_DefaultMove(e);

}