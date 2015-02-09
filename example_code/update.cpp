#include "main.h"

/**
 * Function triggered every 30 ms
 * Use for game logic. Drawing from here will not work.
 **/

void update_GameMainMenu()
{
  // update code for specific game mode 
  // i.e. spawning, triggered every 16ms
}

void update_GameStandard()
{
  // update code for specific game mode 
  // i.e. spawning, triggered every 16ms
}

void Update(int t)
{
  //example: moves entities based on their move functions (in movement.cpp)
  entIt ent = entities.begin();
  entIt ent2 = entities.begin();
  while (ent != entities.end()) {
    ent->move(&(*ent));

    while (ent2 != entities.end()) {
      if (ent != ent2) // dont collide with self
        if (entity_CheckCollision(&(*ent), &(*ent2))) // if they are touching
          if (ent2->entType == ENT_BULLET)  // is ent2 a bullet?
            ent2->collide(ent2, ent);  // trigger collision on the bullet or the object hitting the player.
          else
            ent->collide(ent, ent2); // trigger collision normally.
      if (ent2 != entities.end())
        ++ent2;
    }
    if (ent != entities.end())
      ++ent;
  }

  funcPtr update_Game[] = { &update_GameMainMenu, &update_GameStandard };
  update_Game[gameState.gameMode]();
}