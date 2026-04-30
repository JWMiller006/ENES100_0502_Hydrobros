#pragma once
#define USE_OLD_SOURCE false
#include "pin_defns.hpp"
#include <Arduino.h>

enum class Color {
  NotInit,
  White, 
  Black, 
  Red, 
  Green, 
  Blue, 
  Yellow, 
  Gray, // AKA: Dim White
  Default,
};

struct ColorCountStruct {
  Color color;
  unsigned short count;
  ColorCountStruct(Color col, unsigned short cnt){
    color = col; 
    count = cnt; 
  }
};

extern ColorCountStruct gColorCount[9];

String operator*(Color); 
Color max_count(Color[50]); 

enum CS_Calibration : unsigned short {
  Uncalibrated = 0, 
  WhitePoint = 1 << 0, 
  BlackPoint = 2 << 0, 
};

struct vec3 {
  vec3(); 
  vec3(unsigned long r, unsigned long g, unsigned long b); 
  unsigned long r = 0, g = 0, b = 0; 
};

class ColorSensor {
public:
  ColorSensor(unsigned short S0 = CS_S0, unsigned short S1 = CS_S1, unsigned short S2 = CS_S2, unsigned short S3 = CS_S3, unsigned short OutPin = CS_OUT); 

  // Choose to calibrate either using white or black
  void Calibrate(CS_Calibration CalibrationColor);
  
  Color GetColor(); 

  vec3 GetRaw(); 

  bool FullyCalibrated(); 

private: 
  unsigned short Calibrated = CS_Calibration::Uncalibrated; 
  unsigned short mS0 = CS_S0;
  unsigned short mS1 = CS_S1;
  unsigned short mS2 = CS_S2;
  unsigned short mS3 = CS_S3;
  unsigned short mOut = CS_OUT; 

  vec3 BlackPoint{}, WhitePoint{};

  int normalize(unsigned long val, unsigned long blackVal, unsigned long whiteVal);

  unsigned long readDuration(bool levelS2, bool levelS3);

  vec3 readRaw();

  vec3 ReadNorm();

};
/// Old source code (ported from CS test)
#if USE_OLD_SOURCE
/*
 * GY-31 TCS3200 Color Sensor - Serial Output Only
 * Instructions: 
 * 1. Open Serial Monitor (9600 baud).
 * 2. Hold a white object in front of sensor and send 'w'.
 * 3. Hold a black object in front of sensor and send 'k'.
 */

unsigned long whiteR = 0, whiteG = 0, whiteB = 0;
unsigned long blackR = 0, blackG = 0, blackB = 0;
bool hasWhite = false, hasBlack = false;

// Helper functions for math
int max3(int a, int b, int c) { return max(a, max(b, c)); }
int min3(int a, int b, int c) { return min(a, min(b, c)); }

// -------------------------
// Sensor reading
// -------------------------

unsigned long readDuration(bool levelS2, bool levelS3) {
  digitalWrite(s2, levelS2);
  digitalWrite(s3, levelS3);
  delay(50); // Small delay for sensor to stabilize

  unsigned long d = pulseIn(outPin, LOW, 100000);
  if (d == 0) d = 100000; // Timeout handling
  return d;
}

void readRaw(unsigned long &r, unsigned long &g, unsigned long &b) {
  r = readDuration(LOW, LOW);   // RED
  g = readDuration(HIGH, HIGH); // GREEN
  b = readDuration(LOW, HIGH);  // BLUE
}

int normalize(unsigned long val, unsigned long blackVal, unsigned long whiteVal) {
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

// -------------------------
// Color classification
// -------------------------

String detectColor(int R, int G, int B) {
  int mx = max3(R, G, B);
  int mn = min3(R, G, B);
  int spread = mx - mn;
  int sum = R + G + B;

  // Check for neutrals first
  if (R > 150 && G < 220 && B < 200) return "Yellow";
  if (R > 150 && B > 150 && G < 100) return "Purple";
  if (sum < 100) return "Black";
  if (sum > 600 && spread < 40) return "White";
  if (spread < 30) return "Grey";


  // Check for distinct colors
  if (R>240) return "Red";
  if (G>235 && R<230 && B<230) return "Green";
  if (B > R + 40 && B > G + 40) return "Blue";
  
  

  return "Unknown";
}

void setup() {
  Serial.begin(9600);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT);

  // Set frequency scaling to 20% (Common for Arduino)
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  Serial.println("--- TCS3200 Color Detector ---");
  Serial.println("1. Place WHITE object, send 'w'");
  Serial.println("2. Place BLACK object, send 'k'");
}

void loop() {
  // Handle Calibration Input
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'w') {
      readRaw(whiteR, whiteG, whiteB);
      hasWhite = true;
      Serial.println("✓ White Calibrated");
    }
    if (c == 'k') {
      readRaw(blackR, blackG, blackB);
      hasBlack = true;
      Serial.println("✓ Black Calibrated");
    }
  }

  unsigned long rawR, rawG, rawB;
  readRaw(rawR, rawG, rawB);

  if (hasWhite && hasBlack) {
    int R = normalize(rawR, blackR, whiteR);
    int G = normalize(rawG, blackG, whiteG);
    int B = normalize(rawB, blackB, whiteB);

    String colorName = detectColor(R, G, B);

    Serial.print("R:"); Serial.print(R);
    Serial.print(" G:"); Serial.print(G);
    Serial.print(" B:"); Serial.print(B);
    Serial.print("  -> DETECTED: ");
    Serial.println(colorName);
  } else {
    // Show raw values until calibrated
    Serial.print("Raw Readings: ");
    Serial.print(rawR); Serial.print(",");
    Serial.print(rawG); Serial.print(",");
    Serial.println(rawB);
    delay(1000);
  }
  delay(200); 
}
#endif 

