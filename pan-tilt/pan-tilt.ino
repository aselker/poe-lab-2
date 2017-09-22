//By setting azimuthLower and azimuthUpper, you choose how far left and right the sensor pans while scannning.
//By setting elevationLower and elevationUpper, you choose how high and low the sensor tilts while scanning. elevationLower and elevationUpper both have to be even or zero.
//azimuthLower and azimuthUpper must have a difference that's a multiple of azimuthStep
//elevationLower and elevationUpper must have a difference that's a multiple of elevationStep


 #include "Servo.h"

 #include <SharpIR.h>

Servo pan;
Servo tilt;

int azimuthLower = 0;
int azimuthUpper = 180;
int azimuthStep = 5;

int elevationLower = 45;
int elevationUpper = 180-45;
int elevationStep=5;

int distance;

SharpIR sharp(A0, 20150);

void setup() {

  Serial.begin(9600);
  pan.attach(10);
  tilt.attach(9);

  while(Serial.read()!='1'){
  }
  
}


void loop() {
  for (int azimuth=azimuthLower; azimuth<=azimuthUpper; azimuth=azimuth+2*azimuthStep) {
    tilt.write(azimuth);
    delay(200);
    for (int elevation=elevationLower; elevation<=elevationUpper; elevation=elevation+elevationStep) {
      pan.write(elevation);
      delay(50);
      Serial.println(String(azimuth) + "," + String(elevation) + "," + String(sharp.distance())); 
    }
    tilt.write(azimuth+azimuthStep);
    delay(200);
    for (int elevation=elevationUpper; elevation>=elevationLower; elevation=elevation-elevationStep) {
      pan.write(elevation);
      delay(50);
      distance=sharp.distance();
      Serial.println(String(azimuth+azimuthStep) + "," + String(elevation) + "," + String(sharp.distance()));
    }
  }
delay(750); 
}  
