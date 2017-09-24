from serial import Serial, SerialException
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math

X_ANGLE_MIN = 30 
X_ANGLE_MAX = 75
Z_ANGLE_MIN = 60
Z_ANGLE_MAX = 90

cxn = Serial('/dev/ttyACM0', baudrate=9600)

xs = np.zeros((19*19, 1))
ys = np.zeros((19*19, 1))
zs = np.zeros((19*19, 1))
good_xs = np.zeros((19*19, 1))
good_ys = np.zeros((19*19, 1))
good_zs = np.zeros((19*19, 1))

y = 2 # offset in inches, fake data

def convert_to_cartesian(beta, phi, distance):
    theta = 90 - phi # the angle from the y axis
    #z = y / math.cos(math.radians(theta))
    #x = z*math.sin(math.radians(theta))
    #t = distance - x
    #l = t*math.sin(math.radians(phi))
    #yPosPrime = z + l
    #xPos = t * math.cos(math.radians(phi))
    yPosPrime = distance * math.cos(math.radians(phi))
    xPos = distance * math.sin(math.radians(phi))
    yPos = math.cos(math.radians(90-beta))*yPosPrime
    zPos = math.sin(math.radians(90-beta))*yPosPrime
    return xPos, yPos, zPos

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
        if y >= 25 and y <= 45:
            good_xs[i] = x
            good_ys[i] = y
            good_zs[i] = z
        else:
            xs[i] = x
            ys[i] = y
            zs[i] = z
        i += 1
        print(angle1, angle2, dist, x, y, z)

        #X[angle2//10, angle1//10] = dist
        if angle2 >= Z_ANGLE_MAX and angle1 >= X_ANGLE_MAX:
            #plt.contourf(X)
            #plt.show()
            i = 0
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.scatter(good_xs, good_ys, good_zs, c='b')
            ax.scatter(xs, ys, zs, c='r')
            ax.set_xlabel("X position")
            ax.set_ylabel("Y position")
            ax.set_zlabel("Z position")
            plt.show()

        if angle2 <= Z_ANGLE_MIN and angle1 <= X_ANGLE_MIN:
            i = 0

 
