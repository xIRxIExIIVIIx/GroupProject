#include <stdio.h>
#include "xbox.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


int main() {
  while (pollController()) {

      
      if (GAMEPAD_A)
        printf("A Pressed\n");

      if (GAMEPAD_B)
        printf("B Pressed\n");

      if (GAMEPAD_X)
        printf("X Pressed\n");

      if (GAMEPAD_Y)
        printf("Y Pressed\n");

      if (GAMEPAD_BACK)
        printf("Back Pressed\n");

      if (GAMEPAD_START)
        printf("Start Pressed\n");

      if (GAMEPAD_LB)
        printf("LB Pressed\n");

      if (GAMEPAD_RB)
        printf("RB Pressed\n");

      if (GAMEPAD_LS)
        printf("LS Pressed\n");

      if (GAMEPAD_RS)
        printf("RS Pressed\n");

      printf("LT: %f\nRT: %f\n", GAMEPAD_LT, GAMEPAD_RT);
      printf("LX: %f LY: %f\nRX: %f RY: %f\n", GAMEPAD_LEFT_X, GAMEPAD_LEFT_Y, GAMEPAD_RIGHT_X, GAMEPAD_RIGHT_Y);

      system(CLEAR);
  }

  return 0;
}