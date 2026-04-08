// #include <Enes100.h>
#include "helpers.hpp"
#include "controller.hpp"
#include "pin_defns.hpp"
#include "types.hpp"

#ifndef RUNNING
#define RUNNING true
#endif

void WaitUntilSee(float distance){
    // float dist = Tank.readDistanceSensor(1); 
    float dist = 0; 
    while (dist < 0 || dist > distance){
        // dist = Tank.readDistanceSensor(1); 
        dist = 0; 
    }
}

PMC controller;

void setup()
{
    controller = PMC(TEAM_NAME, TEAM_TYPE, TAG_NUMBER, ROOM_NUMBER, WiFi_TX, WiFi_RX);

    controller.RunMission(FullMission);
}

void loop() {
    delay(10000); 
    
}

