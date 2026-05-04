
#ifndef RUNNING
#define RUNNING true
#endif
#ifndef DEBUG
#define DEBUG true
#endif 
#ifndef USE_OFFSET
#define USE_OFFSET false
#endif 
#ifndef USE_START_PIN
#define USE_START_PIN false
#endif 

// #include <Enes100.h>
#include "helpers.hpp"
#include "controller.hpp"
#include "pin_defns.hpp"
#include "types.hpp"

// void WaitUntilSee(float distance){
//     // float dist = Tank.readDistanceSensor(1); 
//     float dist = 0; 
//     while (dist < 0 || dist > distance){
//         // dist = Tank.readDistanceSensor(1); 
//         dist = 0; 
//     }
// }

PMC controller;

void setup()
{

    controller = PMC(TEAM_NAME, TEAM_TYPE, TAG_NUMBER, ROOM_NUMBER, WiFi_TX, WiFi_RX); // TODO: Wire up start button to pin 22 and a ground

    // controller.mServ.RotateTo(0); 

    // controller.mServ.ResetServo();

    // delay(50000); 
    
    // Setup interupts for calibration
    pinMode(BUTTON_RESET_WHITE_POINT, INPUT_PULLUP); 
    pinMode(BUTTON_RESET_BLACK_POINT, INPUT_PULLUP); 
    attachInterrupt(digitalPinToInterrupt(BUTTON_RESET_WHITE_POINT), PMC::CalibrateWhitePoint, CHANGE); // TODO: Wire up buttons to this and a ground
    attachInterrupt(digitalPinToInterrupt(BUTTON_RESET_BLACK_POINT), PMC::CalibrateBlackPoint, CHANGE); // TODO: Wire up buttons to this and a ground

    controller.RunMission(FullMission);

    // controller.RunMission(Debug);

    // controller.RunMission(CalibrateMotors); 

    // controller.RunMission(CalibrateUS); 

    // controller.RunMission(CalibrateServo); 

    // controller.RunMission(TestPathFinding); 
}

void loop() {
    #if USE_START_PIN
    while(digitalRead(RESTART_CODE_PIN) != LOW){
      delay(50);
      __asm__ __volatile__ ("nop");
    }

    delay(1000); 

    controller.RunMission(FullMission); 
    #else
    delay(10000); 
    #endif 
}

