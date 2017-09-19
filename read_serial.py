from serial import Serial, SerialException
import numpy as np
import matplotlib.pyplot as plt

cxn = Serial('/dev/ttyACM0', baudrate=9600)

x = y = np.zeros((181))
X, Y = np.meshgrid(x, y)

while True:
    while cxn.inWaiting() < 1:
        pass
    result = cxn.readline()
    if "angle = " in result.decode() and "distance" in result.decode():
        angle = result.decode().split(" ")[6]
        angle = int(angle)
        dist = result.decode().split(" ")[3] 
        dist = float(dist)
        print(angle, dist)
        for i in range(180):
            X[i, angle] = dist
        if angle == 180:
            plt.contourf(X)
            plt.show()
