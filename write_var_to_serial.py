import sys
from serial import Serial, SerialException

try:
    cxn = Serial('/dev/ttyACM0', baudrate=9600)
except SerialException:
    print("Serial connection not found. Is the arduino connected?")
    sys.exit()

while True:
    string_input = input("Enter a variable and value: ")

    cxn.write(string_input.encode())
