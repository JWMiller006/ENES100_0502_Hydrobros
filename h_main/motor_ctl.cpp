#include "motor_ctl.hpp"
#include "helpers.hpp"
#include <Arduino.h>

Motor::Motor(){

}

/// Setup motor of given type 
Motor::Motor(const MotorType TypeOfMotor, MotorPos Pos, const uint8_t EnablePin, const uint8_t DirPin1, const uint8_t DirPin2){
  // set the type of the pin and store the pin numbers 
  pinMode(EnablePin, OUTPUT); 
  mEnablePin = EnablePin;

  if (TypeOfMotor == DC_Motor || TypeOfMotor == Servo_Motor){
    pinMode(DirPin1, OUTPUT); 
    pinMode(DirPin2, OUTPUT); 

    mOutOnePin = DirPin1; 
    mOutTwoPin = DirPin2; 
  }

  MotorKind = TypeOfMotor; 
  bInitialized = true; 
}

/// Run specified motor at specified speed
void Motor::SetSpeed(const float Speed){
  if (MotorKind == DC_Motor) {
    if (Speed > 0) { // aka go forward
      digitalWrite(mOutOnePin, LOW); 
      digitalWrite(mOutTwoPin, HIGH); 
    } else {
      digitalWrite(mOutOnePin, HIGH); 
      digitalWrite(mOutTwoPin, LOW); 
    }

    const uint8_t NormSpeed = FloatToShort(Speed);
    digitalWrite(mEnablePin, NormSpeed); 
  }
  
}

Motor::~Motor(){
  if (bInitialized){
    FreeWheels(); 
  }
}

/// Activate motor pin
void Motor::EnableMotor(bool Enable){
  FreeWheels(false);
}

/// Allow the motor to move freely
void Motor::FreeWheels(bool Free){
  if (bInitialized && MotorKind == DC_Motor){
    if (Free) {
      digitalWrite(mEnablePin, LOW);
    } else {
      digitalWrite(mEnablePin, HIGH); 
    } 
  }
} 











