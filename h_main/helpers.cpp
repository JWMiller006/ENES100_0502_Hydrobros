#include "helpers.hpp"
#include "types.hpp"
#include "math.h"

float DegToRad(const float deg){
    return DEG_TO_RAD * deg; 
}

float RadToDeg(const float rad){
    return RAD_TO_DEG * rad; 
}

uint8_t IntToShort(const int In){
  const float fIn = (float)(In);
  constexpr float fBMax = 32767.0; 
  constexpr float fBMin = 32768.0; 
  constexpr float fLMax = 255.0;
  constexpr float fLMin = 0.0; 

  return (uint8_t)(((fIn - fBMin) * fBMax)/(fLMax - fLMin)); 
}

uint8_t FloatToShort(const float In){
  if (In > 0)
    return (uint8_t)(In * 255.0);
  else 
    return (uint8_t)(In * -1.0 * 255.0);
}

float distance(const Point &p1, const Point &p2) {
    const float x = p1.x - p2.x;
    const float y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}
