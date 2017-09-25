//By setting azimuthLower and azimuthUpper, you choose how far left and right the sensor pans while scannning.
//By setting elevationLower and elevationUpper, you choose how high and low the sensor tilts while scanning. elevationLower and elevationUpper both have to be even or zero.
//azimuthLower and azimuthUpper must have a difference that's a multiple of azimuthStep
//elevationLower and elevationUpper must have a difference that's a multiple of elevationStep


 #include "Servo.h"

 #include <SharpIR.h>

Servo pan;
Servo tilt;

//int azimuthLower = 0;
//int azimuthUpper = 180;
//int azimuthStep = 20;

int azimuthCenter=90;
int azimuthSweep=45;
int azimuthStep=5;
int azimuthLower=azimuthCenter-azimuthSweep;
int azimuthUpper=azimuthCenter+azimuthSweep;

//int elevationLower = 45;
//int elevationUpper = 180-45;
//int elevationStep = 20;

int elevationCenter=90;
int elevationSweep=45;
int elevationStep=5;
int elevationLower=elevationCenter-elevationSweep;
int elevationUpper=elevationCenter+elevationSweep;

int distance;
int azimuthDegreesOffCenter;
int elevationDegreesOffCenter;

SharpIR sharp(A0, 20150);

void setup() {

  Serial.begin(9600);
  pan.attach(10);
  tilt.attach(9);
}

void loop() {

  //while(Serial.read()!='1'){} //Wait for a prompt from Python
  
  for (int azimuth=azimuthLower; azimuth<=azimuthUpper; azimuth=azimuth+azimuthStep) {
    tilt.write(azimuth);
    delay(200);
    for (int elevation=elevationLower; elevation<=elevationUpper; elevation=elevation+elevationStep) {
      pan.write(elevation);
      delay(50);
      distance=sharp.distance();
      if(distance>150){
        distance=150;
      }
      azimuthDegreesOffCenter=azimuth-azimuthCenter;
      elevationDegreesOffCenter=elevation-elevationCenter;
      //Serial.println(String(azimuth) + "," + String(elevation) + "," + String(sharp.distance())); 
      Serial.println(String(azimuthDegreesOffCenter) + "," + String(elevationDegreesOffCenter) + "," + String(distance));
    }
    azimuth=azimuth+azimuthStep;
    //tilt.write(azimuth+azimuthStep);
    tilt.write(azimuth);
    delay(200);
    if(azimuth<azimuthUpper){ //Skips last downward tilt if azimuthUpper has already been reached
      for (int elevation=elevationUpper; elevation>=elevationLower; elevation=elevation-elevationStep) {
        pan.write(elevation);
        delay(50);
        distance=sharp.distance();
        if(distance>150){
          distance=150;
        }
        azimuthDegreesOffCenter=azimuth-azimuthCenter;
        elevationDegreesOffCenter=elevation-elevationCenter;
        //Serial.println(String(azimuth+azimuthStep) + "," + String(elevation) + "," + String(sharp.distance()));
        Serial.println(String(azimuthDegreesOffCenter) + "," + String(elevationDegreesOffCenter) + "," + String(distance));
      }  
    }
  }
  Serial.println("-1,-1,-1"); //Done!
  delay(750); 
}  
