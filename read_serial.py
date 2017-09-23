from serial import Serial, SerialException
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math

ANGLE_MIN = 30
ANGLE_MAX = 100

cxn = Serial('/dev/ttyACM0', baudrate=9600)

xs = np.zeros((19*19, 1))
ys = np.zeros((19*19, 1))
zs = np.zeros((19*19, 1))

y = 2 # offset in inches, fake data

def convert_to_cartesian(phi, beta, distance):
    theta = 90 - phi
    z = y / math.cos(math.radians(theta))
    print(z)
    x = z*math.sin(math.radians(theta))
    t = distance - x
    l = t*math.sin(math.radians(phi))
    yPos = z + l
    xPos = t * math.cos(math.radians(phi))
    return xPos, yPos, 0

i = 0
while True:
    while cxn.inWaiting() < 1:
        pass
    result = cxn.readline()
    #print(result)
    if "angle1 = " in result.decode() and "distance" in result.decode():
        angle1= result.decode().split(" ")[5]
        angle1 = int(angle1)
        angle2 = result.decode().split(" ")[8]
        angle2 = int(angle2)
        dist = result.decode().split(" ")[2] 
        dist = float(dist)
        #print(angle1, angle2, dist)
        
        x, y, z = convert_to_cartesian(angle1, angle2, dist)
        xs[i] = x
        ys[i] = y
        zs[i] = z
        i += 1
        print(angle1, angle2, dist, x, y, z)

        #X[angle2//10, angle1//10] = dist
        if angle2 >= ANGLE_MAX and angle1 >= ANGLE_MAX:
            #plt.contourf(X)
            #plt.show()
            i = 0
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.scatter(xs, ys, zs)
            plt.show()

        if angle2 <= ANGLE_MIN and angle1 <= ANGLE_MIN:
            i = 0

 
