#include "helpers.hpp"

float DegToRad(float deg){
    return DEG_TO_RAD * deg; 
}

float RadToDeg(float rad){
    return RAD_TO_DEG * rad; 
}

uint8_t IntToShort(int In){
  float fIn = (float)(In); 
  constexpr float fBMax = 32767.0; 
  constexpr float fBMin = 32768.0; 
  constexpr float fLMax = 255.0;
  constexpr float fLMin = 0.0; 

  return (uint8_t)(((fIn - fBMin) * fBMax)/(fLMax - fLMin)); 
}

uint8_t FloatToShort(float In){
  if (In > 0)
    return (uint8_t)(In * 255.0);
  else 
    return (uint8_t)(In * -1.0 * 255.0);
}
