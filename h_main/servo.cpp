#include "servo.hpp"
#include <Servo.h>

ServoMotor::ServoMotor(){

}

ServoMotor::ServoMotor(unsigned int Pin){
  mServ.attach(Pin); 
}

void ServoMotor::ResetServo(){
  mServ.write(0); 
}

void ServoMotor::RotateTo(int Degrees){
  int dir = (Degrees - RotPos) / abs((Degrees - RotPos)); 

  if (dir > 0){
    for (int curr = RotPos; curr < Degrees; curr++){
      mServ.write(curr); 
      delay(20); 
    }
  } else {
    for (int curr = RotPos; curr > Degrees; curr--){
      mServ.write(curr); 
      delay(20); 
    }
  }

  RotPos = Degrees; 
}

int ServoMotor::GetReading(){
  int rawValue = analogRead(A0);
  int voltage = ((rawValue) * (5.0 / 1023.0)) + 0.5;
  Serial.print(rawValue);
  Serial.print(" ");
  Serial.println(voltage);
  return voltage;
}