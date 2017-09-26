//Arduino code for 3D scanner
//Ben Lilly and Adam Selker, PoE 2017
//
//By setting azimuthLower and azimuthUpper, you choose how far
// left and right the sensor pans while scannning.
//By setting elevationLower and elevationUpper, you choose how 
// high and low the sensor tilts while scanning. elevationLower
// and elevationUpper both have to be even or zero.
//azimuthLower and azimuthUpper must have a difference that's a
// multiple of azimuthStep
//elevationLower and elevationUpper must have a difference that's
// a multiple of elevationStep


#include "Servo.h" //Works better than bare PWM, not sure why
#include <SharpIR.h> //To read the IR sensor

const int azimuthCenter=60; //Deg - straight forward
const int azimuthSweep=25; //Center to edge of range
const int azimuthStep=1; //"pixel" size, degrees

const int azimuthLower=azimuthCenter-azimuthSweep; //Lower extent
const int azimuthUpper=azimuthCenter+azimuthSweep;


const int elevationCenter=70; //Same but for vertical
const int elevationSweep=30;
const int elevationStep=1;

const int elevationLower=elevationCenter-elevationSweep;
const int elevationUpper=elevationCenter+elevationSweep;

int distance;
int azimuthDegreesOffCenter;
int elevationDegreesOffCenter;

SharpIR sharp(A0, 20150);
Servo pan;
Servo tilt;


void setup() {

  Serial.begin(9600); //For comms with laptop
  pan.attach(9); //Horizontal servo pin
  tilt.attach(10); //Vertical pin

}

void loop() {

  while(Serial.read()!='1'){} //Wait for Python to be ready
  
  for (int azimuth=azimuthLower; azimuth<=azimuthUpper; \
    azimuth=azimuth+azimuthStep) { //Loop through horizontal positions

    pan.write(azimuth); //Move the azimuth, prepare for a vertical stripe
    delay(400); //Wait for the servo to get where it's going

    for (int elevation=elevationLower; elevation<=elevationUpper; \
      elevation=elevation+elevationStep) { //Loop through vertical positions
      tilt.write(elevation); //Move the servo
      delay(50); //Wait for the servo to get in position

      distance=sharp.distance(); //Read from the distance sensor
      if(distance > 150) distance = 151; //Clamp values
      else if (distance < 20) distance = 20;

      azimuthDegreesOffCenter=azimuth-azimuthCenter; 
      elevationDegreesOffCenter=elevation-elevationCenter;
        //Transmit values relative to center

      Serial.println(String(azimuthDegreesOffCenter) + "," + \
        String(elevationDegreesOffCenter) + "," + \
        String(distance)); //Actually send the data
    }
  }

  Serial.println("-1,-1,-1"); //Tell Python we're done
}  
