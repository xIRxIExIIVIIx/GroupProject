#include "main.h"
#include "Tables.h"

 int playerInvuln=0;
 long timer = 0;
/**
 * Function triggered every 30 ms
 * Use for game logic. Drawing from here will not work.
 **/

void update_GameMainMenu()
{
  // update code for specific game mode 
  // i.e. spawning, triggered every 16ms
}
int  j =0;
void update_GameStandard()
{
  int x;				//current random spawning. could be changed later based on what we want.
  int y;
 
  long num;
  if(timer % 420 ==0) // every 8 secs
  {
	  int i=0;
	  
	  for (i =0; i<=j; i++)
	  {
		   x = rand();
		   y = rand();
		  
		   if (x>y){
				Entity(ENT_SHARK, Coords(rand() % windowWidth, 0), 1);
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, windowHeight), 1);
				Entity(ENT_SHARK, Coords(0, rand() % windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(windowWidth, rand() % windowHeight), 1);
		   }
		   else{
			    Entity(ENT_SHARK, Coords(windowWidth, rand() % windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(0, rand() % windowHeight), 1);
				Entity(ENT_SHARK, Coords(rand() % windowWidth, windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, 0), 1);
			}
	  }
	
	  j++;
	 
  }
  if (timer % 3150 ==0)
	{
		
		Entity(ENT_CTHULHU, Coords(rand() % windowWidth, 0), 100);
		Entity(ENT_UPGRADE, Coords(rand() % windowWidth, rand() % windowHeight), 1);
	}
  if (timer % 1575 ==0)
  {
		//Entity(ENT_SHIELD, Coords(rand() % windowWidth, rand() % windowHeight), 1);  //power ups spwaing
  }
}

void update_GameTitanic(){
int x;				//current random spawning. could be changed later based on what we want.
  int y;
 
  long num;
  if(timer % 158 ==0) // every 3 secs
  {
	  
	 // int i=0;
	 // j=1;
	 // for (i =0; i<=j; i++)
	 // {
		   x = rand();
		   y = rand();
		   j++;
		   if (x>y){
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(windowWidth, rand() % windowHeight), 1);
		   }
		   else{
				Entity(ENT_ICEBERG, Coords(0, rand() % windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, 0), 1);
			}
	 // }
	
	  
	 
  }
  if (timer % 1575 ==0)
  {
	  //power ups spwaning
  }

  int loss = 75 - j;
  if (loss<40)
	  loss=40;
  if (timer %  loss == 0){
	player->health--;
  }
}

void update_GameSurvival(){
  int x;				//current random spawning. could be changed later based on what we want.
  int y;
 
  long num;
  if(timer % 420 ==0) // every 8 secs
  {
	  int i=0;
	  
	  for (i =0; i<=j; i++)
	  {
		   x = rand();
		   y = rand();
		  
		   if (x>y){
				Entity(ENT_SHARK, Coords(rand() % windowWidth, 0), 1);
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, windowHeight), 1);
				Entity(ENT_SHARK, Coords(0, rand() % windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(windowWidth, rand() % windowHeight), 1);
		   }
		   else{
			    Entity(ENT_SHARK, Coords(windowWidth, rand() % windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(0, rand() % windowHeight), 1);
				Entity(ENT_SHARK, Coords(rand() % windowWidth, windowHeight), 1);
				Entity(ENT_ICEBERG, Coords(rand() % windowWidth, 0), 1);
			}
	  }
	
	  j++;
	 
  }
  if (timer % 3150 ==0)
	{
		
		Entity(ENT_CTHULHU, Coords(rand() % windowWidth, 0), 100);
	}
  if (timer % 1575 ==0)
  {
	  //power ups spwaning
  }
  if (timer % 53==0){
	gameState.score++;
  }
}

void Update(int t)
{
	timer++;
  std::list<Entity>::iterator ent = entities.begin();
  while (ent != entities.end()){
	  if (ent->health <= 0) {
		ent = entities.erase(ent);
	  }
	  else {
		ent->move(&(*ent));
		for (std::list<Entity>::iterator ent2 = ent; ent2 != entities.end(); ++ent2){ //for every other element.
			if (ent != ent2)														  // dont collide with self
				if (entity_CheckCollision(&(*ent), &(*ent2)))						  // if they are touching
					if (ent2->entType == ENT_BULLET)								  // is ent2 a bullet?
						ent2->collide(&(*ent2), &(*ent));							  // trigger collision on the bullet or the object hitting the player.
					else
						ent->collide(&(*ent), &(*ent2));							  // trigger collision normally.
		}
		ent++;
	  }
  }

  //removes any entities which need removing
  if (keys[27])
  	  player->health=0;
  if (player->health==0){
	  updateScores();
	  exit(0);
	  
	//leaderboard here
	//go to main menu
	  //gameState.gameMode==GAME_MAIN_MENU;
	//exit game
  }

  funcPtr update_Game[] = { &update_GameMainMenu, &update_GameStandard, &update_GameTitanic, &update_GameSurvival};
  update_Game[gameState.gameMode]();

  if (playerInvuln >0){
	  playerInvuln--;			//handles player being invulnrable
  }
  else
	  player->invincible=false;
}