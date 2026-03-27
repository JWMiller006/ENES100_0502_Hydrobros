#pragma once

#define PI 3.14159

enum MotorType : unsigned int { 
  M_None          = 0, 
  DC_Motor      = 1, 
  Stepper_Motor = 2, 
  Servo_Motor  = 3, 
};

enum MotorPos : unsigned int {
  MP_None          = 0, 
  FrontRight    = 1 << 0, 
  FrontLeft     = 1 << 1,
  RearRight     = 1 << 2, 
  RearLeft      = 1 << 3,
};

enum MovementDir : unsigned int {
  MD_None          = 0, 
  Forward       = 1 << 0, 
  Right         = 1 << 1, 
  Left          = 1 << 2, 
  Backward      = 1 << 3, 
  Center        = 1 << 5,
  Turn          = 1 << 6,
  Strafe        = 1 << 7,
};

/******************************/
/****** Position Chart ********/
/*                            *
*   I     A     |     D       *
*         B     |     E       *
*         C     |     F       *
*                             */
/******************************/

/// Binary or these together to make the map
enum Arragnement : unsigned int {
  Unknown       = 0, 
  A             = 1 << 0,   // Or this in if thre is an obstacle at pos A
  B             = 1 << 1,   // Or this in if thre is an obstacle at pos B
  C             = 1 << 2,   // Or this in if thre is an obstacle at pos C
  D             = 1 << 3,   // Or this in if thre is an obstacle at pos D
  E             = 1 << 4,   // Or this in if thre is an obstacle at pos E
  F             = 1 << 5,   // Or this in if thre is an obstacle at pos F
  Inverse       = 1 << 7    // Or this in if we started from the top
};

/// 2D point on the arena
struct Point {
  float x, y;
};






