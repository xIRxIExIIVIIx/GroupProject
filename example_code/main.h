#include <iostream>
#include <stdlib.h>
#include <list>
#include "sprites.h"

typedef struct Coords {
  Coords() : x(0), y(0) { }
  Coords(float x, float y) : x(x), y(y) { }
  float x;
  float y;
} Coords;

typedef enum GAME_STATE_TYPE {
  MAIN_MENU
};

//ENTITY FORWARD DECLARATIONS
struct Entity;
typedef void(*funcPtr)(Entity*);
void entity_DefaultMove(Entity* e);
void entity_IcebergMove(Entity* e);
void entity_SharkMove(Entity* e);
void entity_CthulhuMove(Entity* e);
void entity_BulletMove(Entity* e);
void entity_PlayerMove(Entity* e);

//end fwd declare
extern std::list<Entity> entities;

typedef struct Entity {
  Entity(ENTITY_TYPE t, Coords c) : entType(t), coords(c){
    switch (t) { //used to initialize based on type;
    case ENT_ICEBERG:
      this->collisionRadius = 50;
      this->move = &entity_IcebergMove;
      break;

    case ENT_SHARK:
      this->collisionRadius = 50;
      this->move = &entity_SharkMove;
      break;

    case ENT_BULLET:
      this->collisionRadius = 50;
      this->move = &entity_BulletMove;
      break;

    case ENT_CTHULHU:
      this->collisionRadius = 50;
      this->move = &entity_CthulhuMove;
      break;

    case ENT_PLAYER:
      this->collisionRadius = 50;
      this->move = &entity_PlayerMove;
      break;

    default:
      this->collisionRadius = 50;
      this->move = &entity_DefaultMove;  //default movement function (used for players?)
      break;
    }

    entities.push_back(*this);
  }
  ENTITY_TYPE entType;
  Coords coords;
  Coords movement;
  float collisionRadius;
  int health;
  bool invincible;
  funcPtr move;
} Entity;

typedef struct Mouse {
  Coords coords;
  bool btn1;
  bool btn2;
} Mouse;


extern Entity* player;
extern Mouse mouse;
extern bool keys[255];
extern const int windowWidth;
extern const int windowHeight;
/*
 * Callable functions below here!
 * 
 */
void drawEntity(Entity e);
void entity_assignPlayer(Entity* e);
float entity_GetDistance(Entity* e1, Entity* e2);
bool entity_CheckCollision(Entity* e1, Entity* e2);

void printText(float x, float y, std::string str, int r, int g, int b);
void printText(float x, float y, std::string str);