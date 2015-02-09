#include "main.h"

void entity_DefaultCollide(Entity* e, Entity* with) {
  std::cout << "def collide" << std::endl;
	
};

void entity_IcebergCollide(Entity* e, Entity* with) {
  std::cout << "iceberg collide" << std::endl;		
	if (with->entType==ENT_ICEBERG){
		Entity(ENT_ICEBERG, e->coords, (e->health+with->health));
		e->health=0;
		with->health=0;			
	}		
};

void entity_SharkCollide(Entity* e, Entity* with) {
  std::cout << "shark collide" << std::endl;

};

void entity_CthulhuCollide(Entity* e, Entity* with) {
  std::cout << "cthulhu collide" << std::endl;

};

void entity_BulletCollide(Entity* e, Entity* with) {
  std::cout << "bullet collide" << std::endl;
	if(with->invincible=false){
	e->health=0;
	with->health--;	  
	}
};

void entity_PlayerCollide(Entity* e, Entity* with) {
  std::cout << "player collide (DEAD)" << std::endl;
  switch(gameState.gameMode){
	  case GAME_STANDARD:
		  e->health--;
		  e->coords=Coords(windowWidth/2, windowHeight/2);
		  break;
	  case GAME_SURVIVAL:
		  e->health=0;
		  break;
	  case GAME_TITANIC:
		  e->health+=2;	//health is timer in this mode so increase timer
		  break;
  }
  with->health=0;
	//respawn function. needs to call collision of the with entity
};