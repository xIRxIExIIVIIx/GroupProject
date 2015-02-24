#include "main.h"
#include "xbox.h"
void entity_DefaultMove(Entity* e) {
  e->coords.x += e->movement.x;
  e->coords.y += e->movement.y;
  if (e->coords.x <-50 || e->coords.x >windowWidth+50 || e->coords.y<-50 || e->coords.y>windowHeight+50)
	  if (e->entType==ENT_PLAYER){
		e->health--;
		e->coords.x=windowWidth/2;				//border calculation
		e->coords.y=windowHeight/2;
	  }
	  else
		e->health=0;				
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

  if (fabsf(xDistance) > fabsf(yDistance)){
    e->movement.x = xDistance > 0 ? 1 : -1;
    e->movement.y = yDistance / fabsf(xDistance);
  } else {
    e->movement.y = yDistance > 0 ? 1 : -1;
    e->movement.x = xDistance / fabsf(yDistance);
  }

  if (diagDistance<300){
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

  if (fabsf(xDistance) > fabsf(yDistance)){
    e->movement.x = xDistance > 0 ? 1 : -1;
    e->movement.y = yDistance / fabsf(xDistance);
  } else {
    e->movement.y = yDistance > 0 ? 1 : -1;
    e->movement.x = xDistance / fabsf(yDistance);
  }

  e->movement.x = e->movement.x * (3.5f - 3 * (e->health / 100.0f));
  e->movement.y = e->movement.y * (3.5f - 3 * (e->health / 100.0f));

  entity_DefaultMove(e);
}

void entity_BulletMove(Entity* e) {
	
	if (e->movement.x==0 && e->movement.y==0){
		//std::cout <<"player coords: "<<player->coords.x << '\t' << player->coords.y << std::endl;
		float xDistance;
		float yDistance;
		float diagDistance;

		if (pollController() == 0) {
			xDistance = mouse.coords.x - player->coords.x;
			yDistance = (windowHeight - mouse.coords.y) - player->coords.y;
		} else {
			xDistance = GAMEPAD_RIGHT_X;
			yDistance = GAMEPAD_RIGHT_Y;
		}
		//std::cout <<"mouse coords: "<<mouse.coords.x << '\t' << mouse.coords.y << std::endl;
		diagDistance = sqrt((xDistance*xDistance) + (yDistance*yDistance));

		if (fabsf(xDistance) > fabsf(yDistance)){
			e->movement.x = xDistance > 0 ? 1 : -1;
			e->movement.y = yDistance / fabsf(xDistance);

		} else {
			e->movement.y = yDistance > 0 ? 1 : -1;
			e->movement.x = xDistance / fabsf(yDistance);
		}
		e->movement.x*=10;
		e->movement.y*=10;
	}
	entity_DefaultMove(e);
}

void entity_PlayerMove(Entity* e){

  float rx = GAMEPAD_LEFT_X, ry = GAMEPAD_LEFT_Y;
  e->movement.x = (rx == 0 ? (keys['a'] ? -1 : (keys['d'] ? 1 : 0)) : rx) * playerMoveSpeedModifier;	//if a, left. if d, right. else 0
  e->movement.y = (ry == 0 ? (keys['w'] ? -1 : (keys['s'] ? 1 : 0)) : ry) * playerMoveSpeedModifier;	//if w, up. if s, down. else 0;
  
  entity_DefaultMove(e);
}