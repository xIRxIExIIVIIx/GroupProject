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

  list_forEach(entities2, [](Entity* e){
    e->move(e);

    list_forEach(entities2, [](Entity* e2){

    });
  });

  /*
	listItem* item = entities2->first;	//need extern to work to be uncommented <-------
	while (item != 0){
		//std::cout << item->data.entType << std::endl;

		item->data.move(&(item->data)); 
		//std::cout << item->data.entType;
		//std::cout << item->data.entType;
		item=item->next;
	}
  */
	//need to repeat code for the last item added

  //example: moves entities based on their move functions (in movement.cpp)
  //for (std::list<Entity>::iterator ent = entities.begin(); ent != entities.end(); ++ent) {
  //  //ent->move(&(*ent));
  //  for (std::list<Entity>::iterator ent2 = ent; ent2 != entities.end(); ++ent2) //for every other element.
  //    if (ent != ent2) // dont collide with self
  //      if (entity_CheckCollision(&(*ent), &(*ent2))) // if they are touching
  //        if (ent2->entType == ENT_BULLET)  // is ent2 a bullet?
  //          ent2->collide(&(*ent2), &(*ent));  // trigger collision on the bullet or the object hitting the player.
  //        else
  //          ent->collide(&(*ent), &(*ent2)); // trigger collision normally.
  //}

  funcPtr update_Game[] = { &update_GameMainMenu, &update_GameStandard };
  update_Game[gameState.gameMode]();
}