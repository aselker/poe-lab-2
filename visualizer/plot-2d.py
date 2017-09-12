#!/bin/python3.6
import serial
import matplotlib.pyplot as plt
from time import sleep

def main():
  

  rs = [] #Read as plural of r -- "r's"

  with serial.Serial("/dev/ttyACM0") as ser:
    ser.write('1'.encode()) #Tell the scanner to start
    #sleep(1) #Time to get in position -- necessary?
    while True:
      words = ser.readline().split(b",")
      words = list(map((lambda x: x.decode().replace("\r","").replace("\n","")), words))
      #assert len(words) == 3
      print("Words:" + str(words))
      t1 = int(words[0]) #"theta sub 1"
      t2 = int(words[1])
      r  = int(words[2]) #radius

      if t1 == t2 == r == -1:
        break
      else:
        rs.append((t1, t2, r))

  xmax = max(map((lambda x: x[0]), rs))
  ymax = max(map((lambda x: x[1]), rs))
  grid = list(( list(0 for i in range(ymax + 1)) for i in range(xmax + 1) ))

  for i in rs:
    print("Adding point " + str(i))
    grid[i[0]][i[1]] = i[2]

  print(grid)

  plt.imshow(grid);
  plt.show();


if __name__ == "__main__":
  main()
