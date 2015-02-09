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

typedef enum GAME_MODE {
  GAME_MAIN_MENU,
  GAME_STANDARD,
  GAME_TITANIC,
  GAME_SURVIVAL
};

//ENTITY FORWARD DECLARATIONS
struct Entity;
typedef void(*funcPtrEnt)(Entity*);
typedef void(*funcPtrEnt2)(Entity*, Entity*);
typedef void(*funcPtr)(void);

#include "movement.h"
#include "collision.h"

//end fwd declare
extern std::list<Entity> entities;

typedef struct Entity {
  Entity(ENTITY_TYPE t, Coords c, int h) : entType(t), coords(c), health(h){
    this->invincible = false;
    switch (t) { //used to initialize based on type;
    case ENT_ICEBERG:
      this->collisionRadius = 20;
      this->move = &entity_IcebergMove;
      this->collide = &entity_IcebergCollide;
      break;

    case ENT_SHARK:
      this->collisionRadius = 20;
      this->move = &entity_SharkMove;
      this->collide = &entity_SharkCollide;
      break;

    case ENT_BULLET:
      this->collisionRadius = 20;
      this->move = &entity_BulletMove;
      this->collide = &entity_BulletCollide;
      break;

    case ENT_CTHULHU:
      this->collisionRadius = 20;
      this->move = &entity_CthulhuMove;
      this->collide = &entity_CthulhuCollide;
      break;

    case ENT_PLAYER:
      this->collisionRadius = 20;
      this->move = &entity_PlayerMove;
      this->collide = &entity_PlayerCollide;
      break;

    default:
      this->collisionRadius = 20;
      this->move = &entity_DefaultMove;  //default movement function (used for players?)
      this->collide = &entity_DefaultCollide;
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
  funcPtrEnt move;
  funcPtrEnt2 collide;
} Entity;

#include "linkedlist.h"

typedef struct Mouse {
  Coords coords;
  bool btn1;
  bool btn2;
} Mouse;

typedef struct GameState {
  GAME_MODE gameMode;
  long score;
  long time;
} GameState;

extern GameState gameState;
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