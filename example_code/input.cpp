#include "main.h"
#include "xbox.h"

// This is called when the mouse is clicked.
void OnMouseClick(int button, int state, int x, int y)
{
	if (gameState.gameMode!=GAME_TITANIC)
		Entity(ENT_BULLET, Coords(player->coords.x, player->coords.y), 1);
  /*
  if (button == GLUT_LEFT_BUTTON) {
  if (state == GLUT_DOWN) {
  std::cout << "mouse cursor is at " << x << " " << y << std::endl;
  g_lmb = true;
  g_lmb_pos_x = x;
  } else { // GLUT_UPw
  g_lmb = false;
  }
  }
  */
}

// This is called when the mouse is moved.
void MouseMotion(int x, int y)
{
  mouse.coords.x = x;
  mouse.coords.y = windowHeight - y;

  //glutPostRedisplay();
}



// This is called when keyboard presses are detected.
void KeyboardUp(unsigned char Key, int x, int y)
{
  keys[Key] = false;
}

void Keyboard(unsigned char Key, int x, int y)
{
  keys[Key] = true;
}

void XInput()
{
  // List of gamepad inputs can be found in xbox.h
  //player->movement.x = GAMEPAD_LEFT_X * 5;
  //player->movement.y = GAMEPAD_LEFT_Y * 5;
}