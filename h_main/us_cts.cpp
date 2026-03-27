#include "us_ctl.hpp"
#include <Arduino.h>

UltraSonicSensor::UltraSonicSensor(){
  // Do nothing
}

UltraSonicSensor::UltraSonicSensor(const uint8_t Trigger, const uint8_t Echo){
  TriggerPin = Trigger; 
  EchoPin = Echo; 

  pinMode(TriggerPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 

  bInitialized = true; 
}

float UltraSonicSensor::GetDistance(){
  if (!bInitialized) return -1.0;
   
  digitalWrite(TriggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TriggerPin, LOW); 

  constexpr float convert = 0.0343 / 2; 
  long duration = pulseIn(EchoPin, HIGH);
  return ((float)(duration) * convert); // returns the distance in cm
}
