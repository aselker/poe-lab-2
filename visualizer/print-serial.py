#!/bin/python3.6
import serial


def main():
  
  ser = serial.Serial("/dev/pts/7");

  while True:
    print(ser.readline())


if __name__ == "__main__":
  main()
