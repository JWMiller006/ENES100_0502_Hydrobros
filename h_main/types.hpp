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
  Drive         = 1 << 4,
  Center        = 1 << 5,
  Turn          = 1 << 6,
  Strafe        = 1 << 7,
  CW            = 1 << 8,
  CCW           = 1 << 9,
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
enum Arrangement : unsigned int {
  Unknown       = 0, 
  A             = 1 << 0,   // Or this in if there is an obstacle at pos A
  B             = 1 << 1,   // Or this in if there is an obstacle at pos B
  C             = 1 << 2,   // Or this in if there is an obstacle at pos C
  D             = 1 << 3,   // Or this in if there is an obstacle at pos D
  E             = 1 << 4,   // Or this in if there is an obstacle at pos E
  F             = 1 << 5,   // Or this in if there is an obstacle at pos F
  Inverse       = 1 << 7    // Or this in if we started from the top
};

enum MissionType : unsigned int {
  Mission_None = 0,
  FullMission = 1,
  DriveForward = 2,
  DetectObstacles = 3,
  Debug = 4, 
  CalibrateMotors = 5, 
  CalibrateUS = 6,
  CalibrateServo = 7, 
};

/// 2D point on the arena
struct Point {
  Point()
  {
    x = 0.0f; y = 0.0f;
  }

  Point(const float x, const float y) {
    this->x = x;
    this->y = y;
  }

  float x, y;
};

/**************************************/
/*********** Position Chart ***********/
/*                                 |   *
*   B    O1    L1     O4         L | F *
*   C                              |   *
*                                  |   *
*   E    O2    L2     O5     G     -   *
*                                  |   *
*   D                              |   *
*   A    O3    L3     O6           |   *
*                                  |   */
/**************************************/

static Point gPoints[] = {
  {0.22f, 0.45f},     // A
  {0.22f, 1.59f},     // B
  {0.20f, 1.28f},     // C 1.046
  {0.22f, 0.75f},     // D
  {0.22f, 1.00f},     // E
  {3.95f, 1.57f},     // F
  {3.13f, 1.00f},     // G
  {3.43f, 1.60f},     // L
  {1.21f, 1.59f},     // O1
  {1.25f, 1.00f},     // O2
  {1.25f, 0.43f},     // O3
  {2.17f, 1.60f},     // O4
  {2.21f, 0.95f},     // O5
  {2.20f, 0.40f},     // O6
  {1.70f, 1.60f},     // L1
  {1.70f, 1.00f},     // L2
  {1.70f, 0.40f},     // L3
};

enum Position : unsigned short {
  PA = 0,
  PB = 1,
  PC = 2,
  PD = 3,
  PE = 4,
  PF = 5,
  PG = 6,
  PL = 7,
  PO1 = 8,
  PO2 = 9,
  PO3 = 10,
  PO4 = 11,
  PO5 = 12,
  PO6 = 13,
  L1 = 14,
  L2 = 15,
  L3 = 16
};

constexpr float kOffsetX = 0.00f, kOffsetY = -0.24f; 





