#include "main.h"
#include <string>

// Draw Method for GAME_STANDARD (and other game types at the moment)
void DrawGame()
{
  // Iterating entities byval, cannot change coords. used for drawing only.
  for (auto e : entities)
	  drawEntity(e);

  // text printing! 

  printText(windowWidth-100, windowHeight-30, "Score: " + std::to_string(gameState.score),255,0,0);
  printText(windowWidth-220, windowHeight-30, "Health: " + std::to_string(player->health),255,0,0);
  if(player->invincible==true){
	printText(windowWidth-320, windowHeight-30, "invincible",255,0,0);
  }
  

  // text printing! (with color & variables) 
  char tst[64];
  int i = 420;
  sprintf_s(tst, sizeof(char) * 64, "x:%f y:%f", mouse.coords.x, mouse.coords.y);
  printText(20, windowHeight - 20, tst, 0, 255, 0);
}

// Draw Method for menus
void DrawMenu()
{
  // text printing! 
  printText(mouse.coords.x, mouse.coords.y, "MENU MENU MENU");


  // text printing! (with color & variables) 
  std::string test;
  char tst[64];
  int i = 420;
  sprintf_s(tst, sizeof(char) * 64, "x:%f y:%f", mouse.coords.x, mouse.coords.y);
  printText(20, windowHeight - 20, tst, 0, 255, 0);
}