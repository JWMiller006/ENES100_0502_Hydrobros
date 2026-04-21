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

    delay(2500);

    if (Serial.available() > 0){
        String command;

        while (true){
            command = Serial.readStringUntil('\n');

            if (command == "run"){
                break; 
            } else if (command == "fr"){
                Serial.println("Front Right");
                controller.FR.SetSpeed(1.0f); 
            } else if (command == "fl"){
                Serial.println("Front Left");
                controller.FL.SetSpeed(1.0f);
            } else if (command == "rr"){
                Serial.println("Rear Right");
                controller.RR.SetSpeed(1.0f);
            } else if (command == "rl"){
                Serial.println("Rear Left"); 
                controller.RL.SetSpeed(1.0f); 
            } else if (command == "stop"){
                controller.Stop();
                Serial.println("Stop"); 
            }
        }

    }

    delay(2500); 

    controller.FL.SetSpeed(1.0f); 

    delay(2500); 

    controller.Stop();

    controller.FR.SetSpeed(1.0f); 

    delay(2500); 

    controller.Stop(); 

    controller.RL.SetSpeed(1.0f); 

    delay(2500); 

    controller.Stop(); 

    controller.RR.SetSpeed(1.0f); 

    delay(2500); 

    controller.Stop(); 

    controller.RunMission(FullMission);
}

void loop() {
    delay(10000); 
    
}

