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
  }

}
