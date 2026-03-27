#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <Arduino.h>

#define DEG_TO_RAD 0.017453292519943295
#define RAD_TO_DEG 57.29577951308232

float DegToRad(float deg);
float RadToDeg(float rad);

uint8_t IntToShort(int In); 
uint8_t FloatToShort(float In); 

#endif // HELPERS_HPP