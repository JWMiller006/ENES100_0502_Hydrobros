#pragma once 
#include "types.hpp"
#include <Arduino.h>

class UltraSonicSensor{
  public: 
    UltraSonicSensor(); 
    UltraSonicSensor(uint8_t Trigger, uint8_t Echo);

    float GetDistance(); 

  private: 
    uint8_t TriggerPin = 0; 
    uint8_t EchoPin = 0; 

    bool bInitialized = false; 
};