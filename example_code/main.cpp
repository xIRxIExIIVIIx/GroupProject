#include "main.h"
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#include <vector>

//Screen dimension constants
const int windowWidth = 1024;
const int windowHeight = 768;

using namespace std;

// Image data, used for loading textures in OpenGL
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

std::list<Entity> entities; // Linked list of all entities (todo: replace with R*-tree from libspatialindex [?])

// engine constants.
int targetFramerate = 60;

const char* Instructions = " a - move left\n d - move right\n";

// import modules
#include "update.h"
#include "draw.h"
#include "input.h"
#include "xbox.h"

// global externs defined in main.h

Mouse mouse; // mouse input data
bool keys[255];
GameState gameState;
Entity* player; // Player pointer (currently set to first item added to entities)

// OpenGL stuff:
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

void drawEntity(Entity e) {
  glColor4f(1.0,1.0,1.0,0.9); // set background color
  glBindTexture(GL_TEXTURE_2D, g_images[e.entType].img_data); // choose which one before draw
  glBegin(GL_QUADS); // begin quad
  // draw four corners of image:
    glTexCoord2f(0.0, 0.0); glVertex2f(e.coords.x, e.coords.y); 
    glTexCoord2f(0.0, 1.0); glVertex2f(e.coords.x, e.coords.y + g_images[e.entType].img_height);
    glTexCoord2f(1.0, 1.0); glVertex2f(e.coords.x + g_images[e.entType].img_height, e.coords.y + g_images[e.entType].img_height);
    glTexCoord2f(1.0, 0.0); glVertex2f(e.coords.x + g_images[e.entType].img_height, e.coords.y);
  glEnd();  // complete draw
}

// This function is called to initialise opengl
bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load splash image
  gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
  if (gHelloWorld == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    success = false;
  }

  return success;
}

void close()
{
  //Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  //Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}
/*
 * Prints text to screen with color.
 * note: only usable in draw.cpp and main.cpp under draw calls.
 */
void printText(float x, float y, string str, int r, int g, int b)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glColor3f(r / 255.0f, g / 255.0f, b / 255.0f); // Green

  glRasterPos2f(x, y);
  int i = 0;
  for (auto c: str) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    i++;
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

/*
* Prints text to screen.
* note: only usable in draw.cpp and main.cpp under draw calls.
*/
void printText(float x, float y, string str)
{
  printText(x, y, str, 0, 0, 0);
}

// Assign an entity as a player
void entity_assignPlayer(Entity* e) {
  player = e;
  player->move = &entity_PlayerMove;
  e->entType = ENT_PLAYER;
}

float entity_GetDistance(Entity* e1, Entity* e2) {
  float dx = e2->coords.x - e1->coords.x;
  float dy = e2->coords.y - e1->coords.y;
  return sqrtf((dx * dx) + (dy * dy));
}

bool entity_CheckCollision(Entity* e1, Entity* e2) {
  return entity_GetDistance(e1, e2) <= (e1->collisionRadius + e2->collisionRadius);
}

// This is the main display callback function.
// It sets up an orthographic projection and calls Draw2D().
void Draw()
{
  // Clear the background
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // glShadeModel(GL_SMOOTH);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT); // not really needed?

  // for transparency
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set the orthographic viewing transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,windowWidth,windowHeight,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  funcPtr drawModes[] = {&DrawMenu, &DrawGame};
  drawModes[gameState.gameMode]();

  // Bring the back buffer to the front and vice-versa
  glutSwapBuffers();
}

// 	This function is called when the window is resized.
void Resize(int w, int h)
{
  // Allow drawing in full region of the screen
  glViewport(0,0,w,h);
}

void gameLogic(int i)  //game logic goes here. No drawing stuff in this. Only movement / collision checking.
{
  // main game update function (see update.cpp)
  Update(i);
  //can add more function calls here if needed, would be better to call them from Update(i) though.

  //leave this alone, redraws game. Must come last.
  glutPostRedisplay(); //draw updated data
  glutTimerFunc(targetFramerate, gameLogic, 0); //callback for next update
}

// for XInput, refreshes controller data when game is idle.
void PollJoystick()
{
  if (pollController() != 1) {
    //no controller
  }
}

// controller input detected.
void Joystick(unsigned int btmsk, int x, int y, int z)
{
  XInput();
}

void Init()
{
  gameState = {GAME_STANDARD, 0, 0};

  Entity(ENT_PLAYER, Coords(400, 400));
  entity_assignPlayer(&entities.front());

  Entity(ENT_ICEBERG, Coords(500, 500));
  Entity(ENT_SHARK, Coords(200, 200));
  Entity(ENT_CTHULHU, Coords(700, 200));
}

int main(int argc, char* args[])
{
  //Start up SDL and create window
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    //Load media
    if (!loadMedia())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      //Apply the image
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      //Update the surface
      SDL_UpdateWindowSurface(gWindow);
      //Wait two seconds
      SDL_Delay(2000);
    }
  }

  //Free resources and close SDL
  close();

  return 0;
}
  /*
  printf(Instructions);

  glutInit(&argc,argv);
  //	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("2D_example_screen");

  glutTimerFunc(targetFramerate, gameLogic, 0); // Game logic here!
  glutDisplayFunc(Draw);
  glutReshapeFunc(Resize);
  glutMouseFunc(OnMouseClick);
  glutPassiveMotionFunc(MouseMotion);
  glutMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  glutJoystickFunc(Joystick, targetFramerate);
  glutIdleFunc(PollJoystick);
  ilInit();
  OGLInit();

  Init();

  glutMainLoop();
  */

/*
glColor4f(0.5,0.5,0.5,0.8);
glPointSize(8);
glBegin(GL_POINTS);
glVertex2f(g_lmb_pos_x,240.0f);
glEnd();

glColor4f(0.2,0.8,0.2,0.5);
glPointSize(16);
glBegin(GL_POINTS);
glVertex2f(480.0f,240.0f);
glEnd();

glColor4f(0.0,0.0,0.0,1.0);
glLineWidth(2.0);
glPushMatrix();
glTranslatef(g_rectangle_pos_x, g_rectangle_pos_y, 0.0f);
// there's also glRotatef() if needed
glBegin(GL_LINE_LOOP);
glVertex2f(100.0f, 200.0f);
glVertex2f(200.0f, 200.0f);
glVertex2f(200.0f, 150.0f);
glVertex2f(100.0f, 150.0f);
glEnd();
glPopMatrix();

glColor4f(0.0,0.0,1.0,1.0);
glLineWidth(4.0);
glBegin(GL_LINES);
glVertex2f(150.0f,300.0f);
glVertex2f(150.0f,400.0f);
glEnd();

glColor4f(1.0,0.0,0.0,0.5);
glBegin(GL_TRIANGLES);
glVertex2f(300.0f,300.0f);
glVertex2f(400.0f,300.0f);
glVertex2f(400.0f,350.0f);
glEnd();
*/