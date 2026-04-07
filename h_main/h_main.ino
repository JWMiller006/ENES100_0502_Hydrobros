// #include <Enes100.h>
#include "helpers.hpp"
#include "controller.hpp"
#include "pin_defns.hpp"

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
    controller = PMC("Hydrobros", TEAM_TYPE, TAG_NUMBER, ROOM_NUMBER, WiFi_TX, WiFi_RX);

    while (true)
    {
        controller.Drive(0.5f, Right);
    delay(2500);
    controller.Drive(0.5f, Left);
    delay(2500);
    controller.Drive(0.5f, Forward | Right);
    delay(2500);
    controller.Drive(0.5f, Forward | Left);
    delay(2500);
    controller.Drive(0.5f, Forward | Right);
    delay(2500);
    controller.Drive(0.5f, Backward | Left);
    delay(2500);
    controller.Drive(0.5f, Backward | Left);
}

    // while (true)
    // {
        // Serial.print("Theta: ");
        // Serial.println(controller.GetTheta());
    // }

    // Enes100.begin("Simulator", FIRE, 3, 1116, 8, 9);
    // Tank.begin();
    
    // Enes100.println("Starting driving");
    // Tank.setLeftMotorPWM(255);
    // Tank.setRightMotorPWM(255);
    
    // Drive(255, DegToRad(90)); 
    
    // WaitUntilSee(0.4f); 
    
    // Stop(); 
    
    // Drive(255, 0.0f); 
    
    // WaitUntilSee(0.4f); 
    
    // Stop(); 
    
    // Drive(255, DegToRad(-90)); 
    
    // WaitUntilSee(0.9f); 
    
    // Stop(); 
    
    // Drive(255, 0.0f); 
    
    // WaitUntilSee(0.9f);  
    
    // Stop(); 
    
    // Drive(255, DegToRad(90)); 
    
    // WaitUntilSee(0.5f); 
    
    // Stop(); 
    
    // Drive(255, 0.0f); 
    
    // WaitUntilSee(0.25f); 
    
    // Stop(); 
    
    // Enes100.println("Finished Driving"); 
}

void loop() {
    delay(10000); 
    
}

