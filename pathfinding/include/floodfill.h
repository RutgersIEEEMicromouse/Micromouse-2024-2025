#pragma once
#include <stdint.h>

typedef struct
{
  union
  {
    struct
    {
      uint8_t N : 1;
      uint8_t S : 1;
      uint8_t E : 1;
      uint8_t W : 1;
      uint8_t visited : 1;
    };
    uint8_t raw;
  }; // Union named as `u`

  int16_t weight; // Will use -1 to indicate uninitialized
} cell;

typedef struct
{
  uint8_t x;
  uint8_t y;
} point;





void initialize_maze(point dest, bool reset);
void floodfill();
void movebot();