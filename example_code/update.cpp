#include "main.h"

/**
 * Function triggered every 30 ms
 * Use for game logic. Drawing from here will not work.
 **/

void Update(int t)
{
  //example: moves entities based on their move functions (in movement.cpp)
  for (std::list<Entity>::iterator ent = entities.begin(); ent != entities.end(); ++ent) {
    ent->move(&(*ent));
    for (std::list<Entity>::iterator ent2 = ent; ent2 != entities.end(); ++ent2) //for every other element.
      if (ent != ent2) // dont repeat
        if (entity_CheckCollision(&(*ent), &(*ent2))) // if they are touching
          if (&(*ent) == player || ent2->entType == ENT_BULLET)  // is ent the player? or is ent2 a bullet?
            ent2->collide(&(*ent2), &(*ent));  // trigger collision on the bullet or the object hitting the player.
          else
            ent->collide(&(*ent), &(*ent2)); // trigger collision normally.
  }

}
