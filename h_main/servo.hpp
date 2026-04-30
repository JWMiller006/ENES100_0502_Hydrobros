#pragma once

/*
 *  Note that this current version includes a major update to prevent
 *    the jitter by detaching when not in use (though will stay attached)
 *    if the user wants to by calling Enable() before any other connection
 */

#include <Servo.h>
#include <Arduino.h>

class ServoMotor {
public: 
  ServoMotor(); 
  ServoMotor(unsigned int Pin); 

  void RotateTo(int Degrees);

  void ResetServo(); 

  /// Gets the voltage reading, but if the parameter is 
  ///   greater than 0, it will sample over the course of
  ///   that number of data points over the course of 
  ///   10 times the number of data points in milliseconds
  short GetReading(unsigned int NumDataPoints = 0); 

  void Enable();

  void Disable(); 

private:
  bool bEnabled = false; 
  int RotPos = 0; 
  unsigned int mPin; 
  
  Servo mServ{}; 
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