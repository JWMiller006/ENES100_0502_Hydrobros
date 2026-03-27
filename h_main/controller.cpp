/*!!!!!!!!!!!!!!!!!!! NOTE: THIS IS THE ONLY PLACE IN THE PROJECT WHERE ENES100.h CAN BE INCLUDED !!!!!!!!!!!!!!!!!!!!!*/
#include <Enes100.h>      
#include "controller.hpp"
#include "pin_defns.hpp"
#include "motor_ctl.hpp"
#include "helpers.hpp"
#include "types.hpp"

/// Defualt contructor
PMC::PMC(){
  // Do nothing
}

PMC::PMC(const char* Name, const int MissionType, const int MarkerID, const int RoomNumber, const int Tx_Pin, const int Rx_Pin){
  Init(Name, MissionType, MarkerID, RoomNumber, Tx_Pin, Rx_Pin); 
}

/// Sets up the basic connections (i.e. WiFi, sends test message, etc.)
void PMC::Init(const char* Name, const int MissionType, const int MarkerID, const int RoomNumber, const int Tx_Pin, const int Rx_Pin){
  // Connect to vision system
  Enes100.begin(Name, MissionType, MarkerID, RoomNumber, Tx_Pin, Rx_Pin);
    
  // Tests connection
  Enes100.println("It'll all be over this time tomorrow");
  Enes100.println("Or we'll just be starting");

  // Setup motors
  FR = Motor(DC_Motor, MotorPos::FrontRight, FORWARD_RIGHT_MOTOR_ENABLE, FORWARD_RIGHT_MOTOR_DRIVER_1, FORWARD_RIGHT_MOTOR_DRIVER_2); 
  FL = Motor(DC_Motor, MotorPos::FrontLeft, FORWARD_LEFT_MOTOR_ENABLE, FORWARD_LEFT_MOTOR_DRIVER_1, FORWARD_LEFT_MOTOR_DRIVER_2);
  RR = Motor(DC_Motor, MotorPos::RearRight, REAR_RIGHT_MOTOR_ENABLE, REAR_RIGHT_MOTOR_DRIVER_1, REAR_RIGHT_MOTOR_DRIVER_2); 
  RL = Motor(DC_Motor, MotorPos::RearLeft, REAR_LEFT_MOTOR_ENABLE, REAR_LEFT_MOTOR_DRIVER_1, REAR_LEFT_MOTOR_DRIVER_2);


  bInitialized = true; 
}

void PMC::RunMission(){
  // Add code here to go through the parts of the mission (i.e. locate mission objective, measure data points, etc.)
}

void PMC::Stop(){
  SetMotorSpeed(FrontRight | FrontLeft | RearRight | RearLeft, 0.0); 
}

void PMC::SetMotorSpeed(unsigned int Motors, float Speed){
  if (Motors & FrontRight){
    FR.SetSpeed(Speed); 
  }

  if (Motors & FrontLeft){
    FR.SetSpeed(Speed); 
  }

  if (Motors & RearRight){
    RR.SetSpeed(Speed); 
  }

  if (Motors & RearLeft){
    RL.SetSpeed(Speed); 
  }
}

void PMC::GoToPosition(Point p){

}