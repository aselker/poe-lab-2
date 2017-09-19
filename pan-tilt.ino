//By setting azimuthLower and azimuthUpper, you choose how far left and right the sensor pans while scannning.
//By setting elevationLower and elevationUpper, you choose how high and low the sensor tilts while scanning. elevationLower and elevationUpper both have to be even or zero.

 #include "Servo.h"

Servo pan;
Servo tilt;

int azimuthLower = 0;
int azimuthUpper = 180;

int elevationLower = 0;
int elevationUpper = 180;

int voltage

void setup() {

  pan.attach(10);
  tilt.attach(9);
}

void loop() {
  for (int elevation=elevationLower; elevation=elevationUpper; elevation=elevation+2) {
    tilt.write(elevation);
    delay(53);
    for (int azimuth=azimuthLower; azimuth=azimuthUpper; azimuth++) {
      pan.write(azimuth);
      delay(53);
      println(String(azimuth) "," String(elevation) "," String(analogRead(A0))) 
    }
    tilt.write(elevation+1);
    delay(53);
    for (int (azimuth=azimuthUpper; azimuth=azimuthLower; azimuth--) {
      pan.write(azimuth);
      delay(53);
      println(String(azimuth) "," String(elevation) "," String(analogRead(A0))) 
    }
  }

