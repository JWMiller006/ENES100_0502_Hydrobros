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

    delay(5000);

    // RL FL FR RR

    // controller.FR.SetSpeed(1.0f);

    // delay(1500); 

    // controller.Stop();

    // controller.FL.SetSpeed(1.0f);

    // delay(1500); 

    // controller.Stop();

    // controller.RR.SetSpeed(1.0f); 

    // delay(1500); 

    // controller.Stop(); 

    // controller.RL.SetSpeed(1.0f); 

    // delay(1500); 

    // controller.Stop(); 

    controller.RunMission(FullMission);

    // controller.RunMission(Debug);

    // controller.RunMission(CalibrateMotors); 
}

void loop() {
    delay(10000); 
    
}

