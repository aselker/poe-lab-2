#!/bin/python3.6
# Simple 3D scanner, laptop half
# Receives x pos, y pos, and distance from Arduino
# Displays result as matplotlib heatmap
# Benjamin Lilly and Adam Selker, PoE 2017

import serial
import matplotlib.pyplot as plt
from time import sleep

def main():
  
  rs = [] #Read as plural of r -- "r's"

  with serial.Serial("/dev/ttyACM0") as ser:
    sleep(2) #Wait for Arduino to boot
    ser.write('1'.encode()) #Tell the scanner to start
    while True:
      words = ser.readline().split(b",") #Split comma-separated values
      words = list(map((lambda x: x.decode().replace("\r","").replace("\n","")), words)) #Remove newlines and carriage returns
      #assert len(words) == 3
      print("Words:" + str(words))
      t1 = int(words[0]) #"theta sub 1"
      t2 = int(words[1])
      r  = int(words[2]) #radius (distance read from IR sensor)

      if t1 == t2 == r == -1: #-1 is used to indicate end of scan
        break
      else:
        rs.append((t1, t2, r)) #List of pixels

  xmax = max(map((lambda x: x[0]), rs)) #Find the necessary dimensions of the grid which arranges the pixels for display
  ymax = max(map((lambda x: x[1]), rs))
  grid = list(( list(0 for i in range(ymax + 1)) for i in range(xmax + 1) )) #List of lists of zeros

  for i in rs:
    print("Adding point " + str(i))
    grid[i[0]][i[1]] = i[2] #Move a point from the list of pixels to the grid

  plt.imshow(grid); #Actually plot the points
  plt.show();


if __name__ == "__main__":
  main()
