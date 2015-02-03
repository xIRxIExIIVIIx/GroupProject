#include "main.h"

void entity_DefaultCollide(Entity* e, Entity* with) {
  std::cout << "def collide" << std::endl;

};

void entity_IcebergCollide(Entity* e, Entity* with) {
  std::cout << "iceberg collide" << std::endl;

};

void entity_SharkCollide(Entity* e, Entity* with) {
  std::cout << "shark collide" << std::endl;

};

void entity_CthulhuCollide(Entity* e, Entity* with) {
  std::cout << "cthulhu collide" << std::endl;
  
};

void entity_BulletCollide(Entity* e, Entity* with) {
  std::cout << "bullet collide" << std::endl;

};

void entity_PlayerCollide(Entity* e, Entity* with) {
  std::cout << "player collide" << std::endl;
};