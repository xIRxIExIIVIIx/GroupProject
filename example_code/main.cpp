#include "main.h"
#include <GL/glut.h>
#include "IL/il.h"
#pragma comment(lib,"DevIL.lib")

#include <vector>

using namespace std;

// Image data, used for loading textures in OpenGL
typedef struct Image {
  ILuint img_width;
  ILuint img_height;
  GLuint img_data; // Int id for image data.
} Image;

entlist* entities2;
std::list<Entity> entities; // Linked list of all entities (todo: replace with R*-tree from libspatialindex [?])

// engine constants.
const int windowWidth = 1024; 
const int windowHeight = 768;
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

//list_Add(player, entities2);

// OpenGL stuff:
ILuint *g_img_name; // unsure, but needed.
Image *g_images;  // pointer to image data.

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
void OGLInit()
{
  int count = 0; // for each image in sprits list (see sprites.h & sprites.cpp)
  targetFramerate = 1000 / targetFramerate;  // set target framerate to ms/frame rather than FPS
  while (imgstr[count]) count++; // enumerate sprites

  glClearColor (1.0, 1.0, 1.0, 0.0); //set background color (white)

  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_LIGHT0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	g_img_name = new ILuint[count];
	g_images = new Image[count];

  // for each image in the sprites list:
  for (int i = 0; i < count; i++) {
    ilGenImages(count, &g_img_name[i]); // initialize image data
    ilBindImage(g_img_name[i]); // bind name to data

    // Use DevIL to load image from file:
    if (!ilLoadImage((const wchar_t *) imgstr[i])) {
      std::cout << "image file not loaded" << std::endl;
      exit(1);
    }

    // set image params:
    g_images[i].img_width = ilGetInteger(IL_IMAGE_WIDTH);
    g_images[i].img_height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILenum img_format = ilGetInteger(IL_IMAGE_FORMAT);
    ILenum img_type = ilGetInteger(IL_IMAGE_TYPE);
    // store image data:
    ILubyte *img_data = ilGetData();

    // generate OpenGL textures from image data & bind:
    glGenTextures(count, &g_images[i].img_data);
    glBindTexture(GL_TEXTURE_2D, g_images[i].img_data);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, g_images[i].img_width, g_images[i].img_height, 0, img_format, img_type, img_data);

    // ilDeleteImages(1, &g_img_name); // unsure what this does? Clears images from cache? if so, not needed.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  // also unsure, doesn't seem needed.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }

  // Enable drawing:
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
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
//void entity_assignPlayer(Entity* e) {
//  player = e;
//  player->move = &entity_PlayerMove;
//  e->entType = ENT_PLAYER;
//}

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
<<<<<<< HEAD
  gameState.gameMode = GAME_STANDARD;
  //entlist* entities2;
  entities2 = list_Create();

  player = list_Add(Entity(ENT_PLAYER, Coords(400, 400), 3) , entities2);

  list_Add(Entity(ENT_ICEBERG, Coords(500, 500), 2),entities2);
  list_Add(Entity(ENT_SHARK, Coords(200, 200), 1),entities2);
  list_Add(Entity(ENT_CTHULHU, Coords(700, 200), 100),entities2);
=======
  gameState = {GAME_STANDARD, 0, 0};

  Entity(ENT_PLAYER, Coords(400, 400), 3);
  entity_assignPlayer(&entities.front());

  Entity(ENT_ICEBERG, Coords(500, 500), 2);
  Entity(ENT_SHARK, Coords(200, 200), 1);
  Entity(ENT_CTHULHU, Coords(700, 200), 100);
>>>>>>> parent of 9ee74c4... totally broken again.
}

int main(int argc,char **argv)
{
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
  return 0;
}

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