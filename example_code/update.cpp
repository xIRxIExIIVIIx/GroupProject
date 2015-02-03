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
    for (std::list<Entity>::iterator ent2 = ent; ent2 != entities.end(); ++ent2) 
      if (ent != ent2) 
        if (entity_CheckCollision(&(*ent), &(*ent2))) 
          if (&(*ent) == player || ent2->entType == ENT_BULLET)
            ent2->collide(&(*ent2), &(*ent));
          else
            ent->collide(&(*ent), &(*ent2));
  }

}
