/*!!!!!!!!!!!!!!!!!!! NOTE: THIS IS THE ONLY PLACE IN THE PROJECT WHERE ENES100.h CAN BE INCLUDED !!!!!!!!!!!!!!!!!!!!!*/
#include <Enes100.h>
#include <math.h>
#include "controller.hpp"
#include "pin_defns.hpp"
#include "motor_ctl.hpp"
#include "helpers.hpp"
#include "types.hpp"
#include "us_ctl.hpp"

#ifndef SIMULATOR
#define SIMULATOR false
#endif

/// Default constructor
PMC::PMC(){
  // Do nothing
}

PMC::PMC(const char* Name, const int MissionType, const int MarkerID, const int RoomNumber, const int Tx_Pin, const int Rx_Pin){
  Init(Name, MissionType, MarkerID, RoomNumber, Tx_Pin, Rx_Pin); 
}

/// Sets up the basic connections (i.e. Wi-Fi, sends test message, etc.)
void PMC::Init(const char* Name, const int MissionType, const int MarkerID, const int RoomNumber, const int Tx_Pin, const int Rx_Pin){
  // Connect to vision system
  Enes100.begin(Name, MissionType, MarkerID, RoomNumber, Tx_Pin, Rx_Pin);
    
  // Tests connection
  Enes100.println("It'll all be over this time tomorrow");
  Enes100.println("Or we'll just be starting");

  Serial.begin(9600); 
  Serial.println("Serial Connected");

  // Setup DC motors
  FR = Motor(DC_Motor, FrontRight, FORWARD_RIGHT_MOTOR_ENABLE, FORWARD_RIGHT_MOTOR_DRIVER_1, FORWARD_RIGHT_MOTOR_DRIVER_2);
  FL = Motor(DC_Motor, FrontLeft, FORWARD_LEFT_MOTOR_ENABLE, FORWARD_LEFT_MOTOR_DRIVER_1, FORWARD_LEFT_MOTOR_DRIVER_2);
  RR = Motor(DC_Motor, RearRight, REAR_RIGHT_MOTOR_ENABLE, REAR_RIGHT_MOTOR_DRIVER_1, REAR_RIGHT_MOTOR_DRIVER_2);
  RL = Motor(DC_Motor, RearLeft, REAR_LEFT_MOTOR_ENABLE, REAR_LEFT_MOTOR_DRIVER_1, REAR_LEFT_MOTOR_DRIVER_2);

  // Setup US Sensors
  ForwardUS = UltraSonicSensor(FORWARD_US_TRIGGER, FORWARD_US_ECHO); 
  RightUS = UltraSonicSensor(RIGHT_US_TRIGGER, RIGHT_US_ECHO); 
  LeftUS = UltraSonicSensor(LEFT_US_TRIGGER, LEFT_US_ECHO);

  // Setup CS Sensor
  // TODO: Port CS Sensor code from Sampurna

  bInitialized = true; 
}

void PMC::RunMission(const MissionType Mission){
  Enes100.println("Mission Type: ");
  Enes100.println(Mission);  
  // Enes100.println(GetUSReading(Forward)); 
  // Enes100.println(GetUSReading(Left)); 
  // Enes100.println(GetUSReading(Right));


  // Add code here to go through the parts of the mission (i.e. locate mission objective, measure data points, etc.)
  if (Mission == FullMission){
    Enes100.println("Full Mission Start"); 
    mStartPosition = GetPosition();
    mArrangement = 0;
    Point target_position;

    // Assuming that we are within acceptable x-coordinate range (normal starting range)
    if (mStartPosition.y > 1.0f) {
      target_position = gPoints[PA];
      mArrangement |= Inverse;
      TurnTo(DegToRad(-90.0f));

      // Get initial reading
      if (const float obstacle_one = GetUSReading(Left); obstacle_one < 1.5f) {
        mArrangement |= A;
      } else {
        mArrangement |= D;
      } 

      // Go to the next position to get a reading
      GoToPosition(gPoints[PE]);

      // Get US Reading on left side
      if (const float obstacle_two = GetUSReading(Left); obstacle_two < 1.5f) {
        mArrangement |= B;
      } else {
        mArrangement |= E;
      }
    } else {
      target_position = gPoints[PB];
      TurnTo(DegToRad(90.0f));

      // Get initial reading
      if (const float obstacle_one = GetUSReading(Right); obstacle_one < 1.5f) {
        mArrangement |= C;
      } else {
        mArrangement |= F;
      }

      Enes100.println("In Proper spot"); 

      // Go to the next position to get a reading
      GoToPosition(gPoints[PE]);

      Stop(); 

      delay(2500); 

      // Get US Reading on right side
      if (const float obstacle_two = GetUSReading(Right); obstacle_two < 1.5f) {
        mArrangement |= B;
      } else {
        mArrangement |= E;
      }

      GoToPosition(gPoints[PD]); 

      Stop(); 
    }

    // Update current position
    auto current_position = GetPosition();

    // line up the x-coordinate
    GoToPosition({target_position.x, current_position.y});

    // Update current position again
    current_position = GetPosition();

    // line up the y-coordinate
    GoToPosition({current_position.x, target_position.y}, Forward, 5.0f);

    // From here, complete logic for completing the mission task. While it is doing that,
    //    we can also be choosing a path to complete the navigation part of the mission
    Enes100.println("TODO: Add mission specific tasking");

    // Now that we have completed the task, we can follow the path to the end of the arena
    mPath = SelectPath(mArrangement);
    Enes100.println("Selected Path:");
    for (unsigned short i = 0; i < mPath.num_points; i++){
      Enes100.println("X");
      Enes100.println(mPath.points[i].x);
      Enes100.println("Y");
      Enes100.println(mPath.points[i].y);
    }

    delay(100000); 

    FollowPath(mPath, Forward, 0.05f);

    MarkCompleteMission();

  } else if (Mission == DriveForward){

    Drive(1.0f, Forward);
    delay(100000); 
  } else if (Mission == DetectObstacles){
    // Drive forward until we see an obstacle within 20 cm
    Drive(0.75f, Forward);
    delay(1000);
    TurnTo(DegToRad(90.0f));
    // WaitUntilSee(20.0f);
    Stop();
    Enes100.println("Obstacle detected! Stopping movement.");
  } else if (Mission == Debug){
    // Add code here to test out different functions and movements
    Enes100.println("Running Debugging mission"); 
    TurnTo(DegToRad(90.0f));
    delay(1000);
    TurnTo(DegToRad(0.0f));
    delay(1000);
    delay(100); 
  } else
  {
    Enes100.println("Error: Invalid Mission Type!");
  }
}

void PMC::MarkCompleteMission() {
  Enes100.println("Mission Complete!");
  const Point current_position = GetPosition();
  const float current_theta = GetTheta();

  Enes100.println("Final Theta:");
  Enes100.println(current_theta);
  Enes100.println("Current Position:");
  Enes100.println("X");
  Enes100.println(current_position.x);
  Enes100.println("Y");
  Enes100.println(current_position.y);
}

void PMC::Stop(){
  SetMotorSpeed(FrontRight | FrontLeft | RearRight | RearLeft, 0.0); 
}

void PMC::ReleaseWheels(const bool free, const unsigned int Wheels){
  SetMotorSpeed(Wheels, 0.0); 

  if (Wheels & FrontRight){
    FR.FreeWheels(free);
  }

  if (Wheels & FrontLeft){
    FL.FreeWheels(free);
  }

  if (Wheels & RearRight){
    RR.FreeWheels(free);
  }

  if (Wheels & RearLeft){
    RL.FreeWheels(free);
  }
}

void PMC::SetMotorSpeed(const unsigned int Motors, const float Speed){

  if (Motors & FrontRight){
    FR.SetSpeed(Speed); 
  }

  if (Motors & FrontLeft){
    FL.SetSpeed(Speed); 
  }

  if (Motors & RearRight){
    RR.SetSpeed(Speed); 
  }

  if (Motors & RearLeft){
    RL.SetSpeed(Speed); 
  }
}

void PMC::GoToPosition(const Point& p, float ThetaBound, unsigned int US_Override, float DistOverride){
  Point current_position = GetPosition();
  float target_theta = atan2(p.y - current_position.y, p.x - current_position.x);

  if (target_theta > 0.1f) {
    TurnTo(target_theta, Center | Turn);
  }

  Drive(GLOBAL_DRIVE_SPEED, Forward);
  float prev_distance = distance(current_position, p);
  float curr_distance = distance(current_position, p);
  while (curr_distance > 0.1f){
    current_position = GetPosition();

    if (ThetaBound > 0.1f){
      if (const float curr_theta = GetTheta(); curr_theta - target_theta > ThetaBound || curr_theta - target_theta < -1.0f * ThetaBound) {
        Stop();
        target_theta = atan2(p.y - current_position.y, p.x - current_position.x);
        TurnTo(target_theta, Center | Turn);
        Drive(GLOBAL_DRIVE_SPEED, Forward);
      }
    }

    if (prev_distance - 0.25f < curr_distance) {
      if (const float temp_theta = atan2(p.y - current_position.y, p.x - current_position.x); temp_theta > 0.01f) {
        Stop();
        TurnTo(temp_theta, Center | Turn);
        Drive(GLOBAL_DRIVE_SPEED, Forward);
      }
    }

    prev_distance = curr_distance;
    curr_distance = distance(current_position, p);
    Drive(GLOBAL_DRIVE_SPEED, Forward); 
    delay(1);
    Stop(); 

    if (US_Override != MD_None){
      if (const float dist = GetUSReading(US_Override); dist < DistOverride && dist > 0.0f){
        Stop();
        Enes100.println("Obstacle detected! Stopping movement.");
        return;
      }
    }
  }

  Stop();
}

/// Get the direction that we need to turn in order to get to the specified theta
int GetDirTheta(const float target_theta, const float range = 0.025f){
    int dir;
    if (const float theta = Enes100.getTheta(); target_theta - theta > range){
        dir = 1; 
    } else if (target_theta - theta < -1.0 * range) {
        dir = -1; 
    } else {
        dir = 0; 
    }
    
    return dir; 
}

void PMC::TurnTo(float direction, unsigned int axis){
  while (direction > PI){
      direction -= PI; 
  }
  
  while (direction < -1 * PI){
      direction += PI; 
  }

  Enes100.println("Direction: "); 
  Enes100.println(direction); 
  Enes100.println("Axis: "); 
  Enes100.println((float)axis);
  
  if (axis & Center){
    Enes100.println("Turning about center");
    TurnAboutCenter(direction);
  } else if (axis & (Turn) && !(axis & Strafe)){
    Enes100.println("Turning about strafe");
    TurnAboutCorner(direction, axis); 
  } else if (axis & Strafe && !(axis & Turn)){
    Enes100.println("Error: Trying to strafe in the turn function");
  }
}

void PMC::TurnAboutCenter(const float Theta){
  int dir = GetDirTheta(Theta);

  // Turn at the given rate (between 0 and 1)
  constexpr float turn_speed = TURN_SPEED; 

  while (dir != 0){
    SetMotorSpeed(FrontRight | RearRight, (float)dir * turn_speed);
    SetMotorSpeed(FrontLeft | RearLeft, -1.0f * (float)dir * turn_speed);

    delay(5); 
    Stop(); 

    dir = GetDirTheta(Theta);
  }

  Stop(); 
  Enes100.println("Arrived at angle"); 
}

void PMC::TurnAboutCorner(const float Theta, unsigned int Axis){
  int dir = GetDirTheta(Theta); 
  Enes100.println("Warning: This function is built with logic to rotate about the center, but is trying to rotate about an off center axis! Please watch carefully when it gets closer to the range");

  // Turn at the given rate (between 0 and 1)
  constexpr float turn_speed = 0.015; 
  constexpr float range = 0.1; // radians for error

  // Data for motor selection and direction 
  unsigned int motors_used = 0; 
  bool axis_is_corner = true; 
  float dir_modifier = 1.0; 

  if (Axis & (Forward | Right)){
    motors_used |= FrontLeft | RearLeft; 
    dir_modifier = -1.0; 
  } else if (Axis & (Forward | Left)){
    motors_used |= FrontRight | RearRight; 
    dir_modifier = -1.0; 
  } else if (Axis & (Backward | Right)){
    motors_used |= FrontLeft | RearLeft; 
  } else if (Axis & (Backward | Left)){
    motors_used |= FrontRight | RearRight;
  } else if (Axis & (Backward)){
    motors_used |= FrontRight | FrontLeft; 
    axis_is_corner = false;
  } else if (Axis & Forward) {
    motors_used |= RearRight | RearLeft; 
    axis_is_corner = false; 
    dir_modifier = -1.0; 
  }

  // No motors got selected, so now we need to return because we will never get to the desired rotation
  if (!motors_used){
    Enes100.println("Error: Trying to turn about an off axis without specifying an axis!");
    return; 
  }

  // rotate in the corner
  if (axis_is_corner){
    while (dir != 0){
      SetMotorSpeed(motors_used, dir_modifier * dir * turn_speed); 
      dir = GetDirTheta(Theta, range); 
    }
  } else { // rotate about either the front center or back center
    // Pick out the motor that we want based on the direction we are rotating
    const unsigned int RightMotor = motors_used & (FrontRight | RearRight); 
    const unsigned int LeftMotor = motors_used & (FrontLeft | RearLeft); 

    // set the motor speeds based on the direction and axis
    while (dir != 0){
      SetMotorSpeed(RightMotor, dir_modifier * dir * turn_speed);
      SetMotorSpeed(LeftMotor, -1.0 * dir_modifier * dir * turn_speed); 
      dir = GetDirTheta(Theta, range); 
    }
  }

  Stop(); 
}

void PMC::Drive(float Speed, const unsigned int Axis){
  unsigned int forward_motors = 0, reverse_motors = 0, off_motors = 0;

  if ((Axis & (Forward | Right)) == (Forward | Right)){
    forward_motors |= FrontLeft | RearRight | FrontRight | RearLeft;
  } else if ((Axis & (Forward | Left)) == (Forward | Left)){
    forward_motors |= FrontRight | RearLeft;
    off_motors |= FrontLeft | RearRight;
  } else if ((Axis & (Backward | Right)) == (Backward | Right)){
    reverse_motors |= FrontRight | RearLeft;
    off_motors |= FrontLeft | RearRight;
  } else if ((Axis & (Backward | Left)) == (Backward | Left)){
    reverse_motors |= FrontLeft | RearRight;
    off_motors |= FrontLeft | RearRight;
  } else if (Axis & Forward){
    forward_motors |= FrontRight | FrontLeft | RearRight | RearLeft;
  } else if (Axis & Backward){
    reverse_motors |= FrontRight | FrontLeft | RearRight | RearLeft;
  } else if (Axis & Right){
    reverse_motors |= FrontRight | RearLeft; 
    forward_motors |= FrontLeft | RearRight;
  } else if (Axis & Left){
    reverse_motors |= FrontLeft | RearRight; 
    forward_motors |= FrontRight | RearLeft;
  }

  SetMotorSpeed(forward_motors, Speed);
  SetMotorSpeed(reverse_motors, -1.0f * Speed);
  SetMotorSpeed(off_motors, 0.0f);
}

void PMC::WaitUntilSee(float Distance, unsigned int Direction)
{
  float read_dist = GetUSReading(Direction);
  while (Distance > read_dist)
  {
    read_dist = GetUSReading(Direction);
  }
}

void PMC::FollowPath(Path &path, unsigned int US_Override, float DistOverride) {
  while (!path.empty()) {
    const Point next_point = path.GetNextPoint();
    GoToPosition(next_point, 0.05f, US_Override, DistOverride);
  }
}

float PMC::GetUSReading(const unsigned int Direction){
  if (Direction & Forward){
    return ForwardUS.GetDistance();
  } else if (Direction & Right){
    return RightUS.GetDistance();
  } else if (Direction & Left){
    return LeftUS.GetDistance(); 
  } else {
    return -1.0f; 
  }
}

float PMC::GetTheta(){
  const float t = Enes100.getTheta();
  // Enes100.println(t);
  return t; 
}

Point PMC::GetPosition()
{
  return {GetX(), GetY()};
}

float PMC::GetX()
{
  return Enes100.getX();
}

float PMC::GetY()
{
  return Enes100.getY();
}








