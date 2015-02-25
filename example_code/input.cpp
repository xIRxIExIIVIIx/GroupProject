#include "main.h"
#include "xbox.h"

long xinputTimer = 0;
int bulletDmg = 1;
// This is called when the mouse is clicked.
void OnMouseClick(int button, int state, int x, int y)
{
	if (gameState.gameMode!=GAME_TITANIC)
		Entity(ENT_BULLET, Coords(player->coords.x, player->coords.y), 1 * bulletDmg);
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
	float rx = GAMEPAD_RIGHT_X, ry = GAMEPAD_RIGHT_Y;

	xinputTimer++;
	if (!(xinputTimer % 5))
		if (fabsf(rx) > 0.5 || fabsf(ry) > 0.5) 
			OnMouseClick(0, 0, 0, 0);
}