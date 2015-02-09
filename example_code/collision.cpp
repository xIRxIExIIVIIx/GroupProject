#include "main.h"

void entity_DefaultCollide(entIt e, entIt with) {
  std::cout << "def collide" << std::endl;

};

void entity_IcebergCollide(entIt e, entIt with) {
  std::cout << "iceberg collide" << std::endl;

};

void entity_SharkCollide(entIt e, entIt with) {
  std::cout << "shark collide" << std::endl;
};

void entity_CthulhuCollide(entIt e, entIt with) {
  std::cout << "cthulhu collide" << std::endl;
  
};

void entity_BulletCollide(entIt e, entIt with) {
  std::cout << "bullet collide" << std::endl;
  switch (gameState.gameMode) {
  case GAME_STANDARD:
    // logic for bullet collision in normal (classic) games.
    break;
    // add extra cases here for each game mode.
  }

};

void entity_PlayerCollide(entIt e, entIt with) {
  std::cout << "player collide (DEAD)" << std::endl;
  e = entities.erase(with);

};