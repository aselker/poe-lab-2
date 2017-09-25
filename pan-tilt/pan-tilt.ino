//By setting azimuthLower and azimuthUpper, you choose how far left and right the sensor pans while scannning.
//By setting elevationLower and elevationUpper, you choose how high and low the sensor tilts while scanning. elevationLower and elevationUpper both have to be even or zero.
//azimuthLower and azimuthUpper must have a difference that's a multiple of azimuthStep
//elevationLower and elevationUpper must have a difference that's a multiple of elevationStep


 #include "Servo.h"

 #include <SharpIR.h>

Servo pan;
Servo tilt;

int azimuthCenter=60;
int azimuthSweep=25;
int azimuthStep=1;
int azimuthLower=azimuthCenter-azimuthSweep;
int azimuthUpper=azimuthCenter+azimuthSweep;


int elevationCenter=70;
int elevationSweep=30;
int elevationStep=1;
int elevationLower=elevationCenter-elevationSweep;
int elevationUpper=elevationCenter+elevationSweep;

int distance;
int azimuthDegreesOffCenter;
int elevationDegreesOffCenter;

SharpIR sharp(A0, 20150);

void setup() {

  Serial.begin(9600);
  pan.attach(9);
  tilt.attach(10);
}

void loop() {

  while(Serial.read()!='1'){} //Wait for a prompt from Python
  
  for (int azimuth=azimuthLower; azimuth<=azimuthUpper; azimuth=azimuth+azimuthStep) {
    pan.write(azimuth);
    delay(400); //Wait for the servo to get where it's going
    for (int elevation=elevationLower; elevation<=elevationUpper; elevation=elevation+elevationStep) {
      tilt.write(elevation);
      delay(50);
      distance=sharp.distance();
      if(distance > 150) distance = 151;
      else if (distance < 20) distance = 20;
      azimuthDegreesOffCenter=azimuth-azimuthCenter;
      elevationDegreesOffCenter=elevation-elevationCenter;
      //Serial.println(String(azimuth) + "," + String(elevation) + "," + String(sharp.distance())); 
      Serial.println(String(azimuthDegreesOffCenter) + "," + String(elevationDegreesOffCenter) + "," + String(distance));
    }
    /*azimuth=azimuth+azimuthStep;
    //tilt.write(azimuth+azimuthStep);
    pan.write(azimuth);
    delay(200);
    if(azimuth<azimuthUpper){ //Skips last downward tilt if azimuthUpper has already been reached
      for (int elevation=elevationUpper; elevation>=elevationLower; elevation=elevation-elevationStep) {
        tilt.write(elevation);
        delay(50);
        distance=sharp.distance();
        if(distance > 150) distance = 151;
        else if (distance < 20) distance = 20;
        azimuthDegreesOffCenter=azimuth-azimuthCenter;
        elevationDegreesOffCenter=elevation-elevationCenter;
        //Serial.println(String(azimuth+azimuthStep) + "," + String(elevation) + "," + String(sharp.distance()));
        Serial.println(String(azimuthDegreesOffCenter) + "," + String(elevationDegreesOffCenter) + "," + String(distance));
      }  
    }*/
  }
  Serial.println("-1,-1,-1"); //Done!
  delay(750); 
}  
