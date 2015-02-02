#include "main.h"
#include "xbox.h"

// This is called when the mouse is clicked.
void OnMouseClick(int button, int state, int x, int y)
{
  /*
  if (button == GLUT_LEFT_BUTTON) {
  if (state == GLUT_DOWN) {
  std::cout << "mouse cursor is at " << x << " " << y << std::endl;
  g_lmb = true;
  g_lmb_pos_x = x;
  } else { // GLUT_UP
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
void Keyboard(unsigned char Key, int x, int y)
{
  /*
  if (Key == 'a') {
  g_rectangle_pos_x -= 2.0f;
  }
  if (Key == 'd') {
  g_rectangle_pos_x += 2.0f;
  }
  if (Key == 'w') {
  g_rectangle_pos_y -= 2.0f;
  }
  if (Key == 's') {
  g_rectangle_pos_y += 2.0f;
  }

  if (Key == 'p') {
  std::cout << "print something on the screen..." << std::endl;
  }
  */
}

void XInput()
{
  // List of gamepad inputs can be found in xbox.h
  player->movement.x = GAMEPAD_LEFT_X * 5;
  player->movement.y = GAMEPAD_LEFT_Y * 5;
}