#include "main.h"

void Draw2D()
{
  // Iterating entities byval, cannot change coords. used for drawing only.
  for (auto e : entities)
    drawEntity(e);

  // text printing! 
  printText(mouse.coords.x, mouse.coords.y, "Test");


  // text printing! (with color & variables) 
  std::string test;
  char tst[64];
  int i = 420;
  sprintf_s(tst, sizeof(char) * 64, "Score: %i", i);
  printText(20, windowHeight - 20, tst, 0, 255, 0);
}