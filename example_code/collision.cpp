#include "main.h"
#include "update.h"

void entity_DefaultCollide(Entity* e, Entity* with) {
  //std::cout << "def collide" << std::endl;
};

void entity_IcebergCollide(Entity* e, Entity* with) {
  //std::cout << "iceberg collide" << std::endl;		
	if (with->entType==ENT_ICEBERG){
		e->health += with->health;
		e->maxHealth += with->maxHealth;
		e->collisionRadius = 16 + e->maxHealth * 2.5;
		with->health = 0;			
	}		
};

void entity_SharkCollide(Entity* e, Entity* with) {
  //std::cout << "shark collide" << std::endl;

};

void entity_CthulhuCollide(Entity* e, Entity* with) {
  //std::cout << "cthulhu collide" << std::endl;

};

void entity_BulletCollide(Entity* e, Entity* with) {
  //std::cout << "bullet collide" << std::endl;
	if(with->entType!=ENT_BULLET && with->entType!=ENT_PLAYER)
		if(with->invincible==false){
			e->health=0;
			with->health--;	  
			if (with->health<=0 && gameState.gameMode==GAME_STANDARD)
				switch (with->entType){
				case(ENT_ICEBERG):
					gameState.score+=with->maxHealth;
					break;
				case(ENT_SHARK):
					gameState.score+=2;
					break;
				case(ENT_CTHULHU):
					gameState.score+=300;
					break;
				}
		}
};

void entity_PlayerCollide(Entity* e, Entity* with) {
  //std::cout << "player collide (DEAD)" << std::endl;
  switch(gameState.gameMode){
	  case GAME_STANDARD:
		  if (e->invincible != true){
			  e->health--;
			  e->coords=Coords(windowWidth/2, windowHeight/2);
			  e->invincible=true;
			  playerInvuln = 100;
		  }
		  break;
	  case GAME_SURVIVAL:
		  e->health=0;
		  break;
	  case GAME_TITANIC:
		  e->health+=2;	//health is timer in this mode so increase timer
		  gameState.score+=2;
		  break;
  }
  with->health=0;
	//respawn function. needs to call collision of the with entity
};