#pragma once

struct Entity;
typedef void(*funcPtrEnt)(Entity*);
typedef void(*funcPtrEnt2)(Entity*, Entity*);
typedef void(*funcPtr)(void);

#include "coords.h"
#include "sprites.h"
#include "movement.h"
#include "collision.h"

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

    //entities.push_back(*this);
    //list_Add(this, entities2);
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

float entity_GetDistance(Entity* e1, Entity* e2);
bool entity_CheckCollision(Entity* e1, Entity* e2);