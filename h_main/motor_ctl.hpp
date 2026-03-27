#pragma once
#include "types.hpp"
#include <Arduino.h>

class Motor {
  public: 
    /// Setup blank motor
    Motor(); 

    /// Setup motor of given type 
    Motor(MotorType TypeOfMotor, MotorPos Pos, uint8_t EnablePin, uint8_t DirPin1 = -1, uint8_t DirPin2 = -1); 

    virtual ~Motor(); 

    /// Activate motor pin
    void EnableMotor(bool Enable = true); 

    /// Run specified motor at specified speed (between -1 and 1)
    void SetSpeed(float Speed);

    /// Allow the motor to be free
    void FreeWheels(bool Free = true); 

  private: 
    /// If this current instance is initalized or not yet
    bool bInitialized = false; 

    /// Whether the motor is enabled or not at this moment
    bool bEnabled = false; 

    /// The type of motor this class represents
    MotorType MotorKind = 0; 

    /// Out Enable pin
    uint8_t mEnablePin = 0; 
    /// Out 1 pin
    uint8_t mOutOnePin = 0; 
    /// Out 2 pin
    uint8_t mOutTwoPin = 0; 


};