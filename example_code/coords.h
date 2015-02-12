#pragma once

typedef struct Coords {
  Coords() : x(0), y(0) { }
  Coords(float x, float y) : x(x), y(y) { }
  float x;
  float y;
} Coords;
