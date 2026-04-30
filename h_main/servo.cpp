#include "servo.hpp"
#include <Arduino.h>
#include <Servo.h>
#include "pin_defns.hpp"
#ifndef DEBUG
#define DEBUG true
#endif 

// Macro that gets the raw voltage of the voltage pin in float form
#define GetRawVoltage() ((float)(analogRead(VOLTAGE_PIN) * (5.0f / 1023.0f)))

// Macro that gets the short value for the voltage that is rounded 
#define GetRoundedVoltage() ((short)((float)(analogRead(VOLTAGE_PIN) * (5.0f / 1023.0f)) + 0.5f))

ServoMotor::ServoMotor(){

}

ServoMotor::ServoMotor(unsigned int Pin){
  mPin = Pin;
  bEnabled = false; 
  pinMode(mPin, OUTPUT);
}

void ServoMotor::ResetServo(){
  const bool bWasEnabled = bEnabled; 
  if (!bWasEnabled){
    Enable(); 
  }

  mServ.write(0); 

  if (!bWasEnabled){
    Disable(); 
  }
}

void ServoMotor::RotateTo(int Degrees){
  const bool bWasEnabled = bEnabled; 
  if (!bWasEnabled){
    Enable(); 
  }

  int dir = (Degrees - RotPos) / abs((Degrees - RotPos)); 

  if (dir > 0){
    for (int curr = RotPos; curr < Degrees; curr++){
      mServ.write(curr); 
      delay(20); 
    }
  } else {
    for (int curr = RotPos; curr > Degrees; curr--){
      mServ.write(curr); 
      delay(20); 
    }
  }

  RotPos = Degrees; 

  if (!bWasEnabled){
    Disable(); 
  }
}

short GetReadingHelper(){
  short voltage = GetRoundedVoltage();
  #if DEBUG
  Serial.print(GetRawVoltage());
  Serial.print(" ");
  Serial.println(voltage);
  #endif 
  return voltage;
}

short ServoMotor::GetReading(unsigned int NumDataPoints){
  if (NumDataPoints == 0){
    return GetReadingHelper();
  }

  float currAverage = GetRawVoltage(); // Start the average 

  for (unsigned int i = 1; i < NumDataPoints; i++){
    delay(10); 
    currAverage += GetRawVoltage(); 
    currAverage /= 2.0f; 
    #if DEBUG
    Serial.print("Current Average: ");
    Serial.print(currAverage); 
    Serial.println(" V"); 
    #endif
  }

  #if DEBUG
  Serial.print("Average found to be: ");
  Serial.print(currAverage); 
  Serial.println(" V"); 
  #endif

  return (short)(currAverage + 0.5f); 
}

void ServoMotor::Enable(){
  if (!bEnabled){
    mServ.attach(mPin);
    bEnabled = true; 
  }
}

void ServoMotor::Disable(){
  if (bEnabled){
    mServ.detach();
    bEnabled = false; 
  }
}












