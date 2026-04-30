#pragma once

#include <Servo.h>
#include <Arduino.h>

class ServoMotor {
public: 
  ServoMotor(); 
  ServoMotor(unsigned int Pin); 
  
  Servo mServ{}; 
  int RotPos = 0; 

  void RotateTo(int Degrees);

  void ResetServo(); 

  int GetReading(); 
};

// const int analogPin = A0;
// Servo myservo;  // create Servo object to control a servo
// myservo.attach(SERVO_PIN);
// int pos = 0; 
// void rotateServo(){
//     for (pos = 0; pos <=90; pos++) {
//         myservo.write(pos);
//         delay(20);
//     }
// }
// void resetServo(){
//     myservo.write(0);
// }
// int readVoltage(){
//     int rawValue = analogRead(analogPin);
//     int voltage = ((rawValue) * (5.0 / 1023.0)) + 0.5;
//     Serial.print(rawValue);
//     Serial.print(" ");
//     Serial.println(voltage);
//     delay(2000); 
//     return voltage;
// }