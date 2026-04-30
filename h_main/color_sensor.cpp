#include "color_sensor.hpp"
#include <Arduino.h>

vec3::vec3(){
  r = g = b = 0; 
}

vec3::vec3(const unsigned long R, const unsigned long G, const unsigned long B){
 r = R; 
 g = G; 
 b = B; 
}

String operator*(Color inColor){
  switch (inColor){
    case Color::Black:
      return "Black";
    case Color::Blue:
      return "Blue";
    case Color::Default:
      return "Default"; 
    case Color::Gray: 
      return "Gray"; 
    case Color::Green: 
      return "Green";
    case Color::NotInit: 
      return "Not Initialized";
    case Color::Red: 
      return "Red"; 
    case Color::White: 
      return "White"; 
    case Color::Yellow: 
      return "Yellow"; 
    default: 
      return "Not Mapped Yet"; 
  }
}

ColorSensor::ColorSensor(unsigned short S0, unsigned short S1, unsigned short S2, unsigned short S3, unsigned short OutPin){
  mS0 = S0; 
  mS1 = S1; 
  mS2 = S2; 
  mS3 = S3; 
  mOut = OutPin; 

  Calibrated = CS_Calibration::Uncalibrated; 

  // Set the pin modes
  pinMode(mS0, OUTPUT);
  pinMode(mS1, OUTPUT);
  pinMode(mS2, OUTPUT);
  pinMode(mS3, OUTPUT);
  pinMode(mOut, INPUT);

  // Set frequency
  digitalWrite(mS0, HIGH);
  digitalWrite(mS1, LOW);

  Color color = Color::Black;

  Serial.print("Testing Color to string: ");
  Serial.println(*color);
}

void ColorSensor::Calibrate(CS_Calibration CalibrationColor){
  if ((unsigned short)CalibrationColor & (unsigned short)CS_Calibration::WhitePoint){
    WhitePoint = readRaw(); 
  } else if ((unsigned short)CalibrationColor & (unsigned short)CS_Calibration::BlackPoint){
    BlackPoint = readRaw(); 
  }

  Calibrated |= (unsigned short)CalibrationColor; 
}


// Helper functions for math
int max3(int a, int b, int c) { return max(a, max(b, c)); }
int min3(int a, int b, int c) { return min(a, min(b, c)); }

Color ColorSensor::GetColor(){
  if (FullyCalibrated()){
    const vec3 NormValues = ReadNorm(); 
    const unsigned int R = NormValues.r, G = NormValues.g, B = NormValues.b; 

    int mx = max3(R, G, B);
    int mn = min3(R, G, B);
    int spread = mx - mn;
    int sum = R + G + B;

    // Check for neutrals first
    if (R > 150 && G < 220 && B < 200) return Color::Yellow;
    if (sum < 100) return Color::Black;
    if (sum > 600 && spread < 40) return Color::White;
    if (spread < 30) return Color::Gray;


    // Check for distinct colors
    if (R>240) return Color::Red;
    if (G>235 && R<230 && B<230) return Color::Green;
    if (B > R + 40 && B > G + 40) return Color::Blue;

    return Color::Default;
  } else {
    return Color::NotInit;
  }
}

bool ColorSensor::FullyCalibrated(){
  if ((Calibrated & (CS_Calibration::BlackPoint | CS_Calibration::WhitePoint)) == (CS_Calibration::BlackPoint | CS_Calibration::WhitePoint)) 
    return true;
  return false; 
}

unsigned long ColorSensor::readDuration(bool levelS2, bool levelS3) {
  digitalWrite(mS2, levelS2);
  digitalWrite(mS3, levelS3);
  delay(50); // Small delay for sensor to stabilize

  unsigned long d = pulseIn(mOut, LOW, 100000L);
  if (d == 0) d = 100000L; // Timeout handling
  return d;
}

vec3 ColorSensor::readRaw() {
  const unsigned long r = readDuration(LOW, LOW);   // RED
  const unsigned long g = readDuration(HIGH, HIGH); // GREEN
  const unsigned long b = readDuration(LOW, HIGH);  // BLUE
  return {r, g, b}; 
}

int ColorSensor::normalize(unsigned long val, unsigned long blackVal, unsigned long whiteVal) {
  if (whiteVal == blackVal) return 0;
  long x = (long)val;
  long b = (long)blackVal;
  long w = (long)whiteVal;

  // Constrain and map values to 0-255
  if (x < w) x = w;
  if (x > b) x = b;

  long result = (b - x) * 255L / (b - w);
  return (int)constrain(result, 0, 255);
}

vec3 ColorSensor::ReadNorm(){
  const vec3 raw = readRaw();
  return {normalize(raw.r, BlackPoint.r, WhitePoint.r), normalize(raw.g, BlackPoint.g, WhitePoint.g), normalize(raw.b, BlackPoint.b, WhitePoint.b)}; 
}












