#!/bin/python3.6
# Simple 3D scanner, laptop half
# Receives x pos, y pos, and distance from Arduino
# Displays result as matplotlib heatmap
# Benjamin Lilly and Adam Selker, PoE 2017

import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from time import sleep
from math import sin, cos, pi

sensorOffset = 24 #mm, horizontal

def main():
  
  rs = [] #Read as plural of r -- "r's"

  with serial.Serial("/dev/ttyACM0") as ser:
    sleep(2) #Wait for Arduino to boot
    ser.write('1'.encode()) #Tell the scanner to start
    while True:
      words = ser.readline().split(b",") #Split comma-separated values
      words = list(map((lambda x: x.decode().replace("\r","").replace("\n","")), words)) #Remove newlines and carriage returns
      #assert len(words) == 3
      print("Words: " + str(words))
      t1 = int(words[0]) #"theta sub 1"
      t2 = int(words[1])
      r  = int(words[2]) #radius (distance read from IR sensor)

      if t1 == t2 == r == -1: #-1 is used to indicate end of scan
        break
      else:
        rs.append((t1, t2, r)) #List of pixels

  xs = ys = zs = []
  
  for (t1, t2, r) in rs: #Transform points from offset radial to Cartesian
    t1 = t1 * 2*pi / 360 #Degrees to radians
    t2 = t2 * 2*pi / 360 #Note that because of scope, this won't change `rs`

    x = r * cos(t1) * cos(t2) #Positions without adjust for sensor offset
    y = r * sin(t1) * cos(t2)
    z = r * sin(t2);

    x += sensorOffset * sin(t1) #Sensor offset
    y -= sensorOffset * cos(t1)

    xs.append(x)
    ys.append(y)
    zs.append(z)

    print("X: " + str(x) + " Y: " + str(y) + " Z: " + str(z))

  
  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  #ax.scatter(xs, ys, zs, s=1, c='b', depthshade=False)
  ax.scatter(xs, ys, 0, s=1, c='b', depthshade=False)
  ax.set_xlabel('X')
  ax.set_ylabel('Y')
  ax.set_zlabel('Z')
  plt.show()


if __name__ == "__main__":
  main()
