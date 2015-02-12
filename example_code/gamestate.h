#pragma once
#include "gamemode.h"
#include "entity.h"
#include <list>
#include "mouse.h"
#include "linkedlist.h"

typedef struct GameState {
  GAME_MODE gameMode;
  long score;
  long time;
} GameState;

extern std::list<Entity> entities;
extern entlist* entities2;
extern GameState gameState;
extern Entity* player;
extern Mouse mouse;
extern bool keys[255];
extern const int windowWidth;
extern const int windowHeight;
