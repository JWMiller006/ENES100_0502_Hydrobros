// #include <Enes100.h>
#include "helpers.hpp"
#include "controller.hpp"


void Stop(){
    SetLRMotors(0, 0); 
}

void Drive(int speed, float direction){
    // TurnTo(direction); 
    SetLRMotors(speed, speed); 
}

void SetLRMotors(int left, int right){
    // Tank.setLeftMotorPWM(left); 
    // Tank.setRightMotorPWM(right); 
}

void TurnRelative(float rel_direction){
    // float target = rel_direction + Enes100.getTheta();
    float target = 0.0;
    while (target > PI){
        target-=PI;
    }
    // TurnTo(target); 
}

void WaitUntilSee(float distance){
    // float dist = Tank.readDistanceSensor(1); 
    float dist = 0; 
    while (dist < 0 || dist > distance){
        // dist = Tank.readDistanceSensor(1); 
        dist = 0; 
    }
}

void setup() {
    // Enes100.begin("Simulator", FIRE, 3, 1116, 8, 9);
    // Tank.begin();
    
    // Enes100.println("Starting driving");
    // Tank.setLeftMotorPWM(255);
    // Tank.setRightMotorPWM(255);
    
    Drive(255, DegToRad(90)); 
    
    WaitUntilSee(0.4f); 
    
    Stop(); 
    
    Drive(255, 0.0f); 
    
    WaitUntilSee(0.4f); 
    
    Stop(); 
    
    Drive(255, DegToRad(-90)); 
    
    WaitUntilSee(0.9f); 
    
    Stop(); 
    
    Drive(255, 0.0f); 
    
    WaitUntilSee(0.9f);  
    
    Stop(); 
    
    Drive(255, DegToRad(90)); 
    
    WaitUntilSee(0.5f); 
    
    Stop(); 
    
    Drive(255, 0.0f); 
    
    WaitUntilSee(0.25f); 
    
    Stop(); 
    
    // Enes100.println("Finished Driving"); 
}

void loop() {
    delay(10000); 
    
}

