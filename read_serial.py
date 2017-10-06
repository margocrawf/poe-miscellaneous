from serial import Serial, SerialException
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import math

X_ANGLE_MIN = 30 
X_ANGLE_MAX = 75
Z_ANGLE_MIN = 54
Z_ANGLE_MAX = 90

dimensionX = X_ANGLE_MAX - X_ANGLE_MIN + 1
dimensionZ = Z_ANGLE_MAX - Z_ANGLE_MIN + 1

cxn = Serial('/dev/ttyACM0', baudrate=9600)

xs = np.zeros((dimensionX*dimensionZ+1, 1))
ys = np.zeros((dimensionX*dimensionZ+1, 1))
zs = np.zeros((dimensionX*dimensionZ+1, 1))
good_xs = np.zeros((dimensionX*dimensionZ+1, 1))
good_ys = np.zeros((dimensionX*dimensionZ+1, 1))
good_zs = np.zeros((dimensionX*dimensionZ+1, 1))
bad_xs = np.zeros((dimensionX*dimensionZ+1, 1))
bad_ys = np.zeros((dimensionX*dimensionZ+1, 1))
bad_zs = np.zeros((dimensionX*dimensionZ+1, 1))

def dist(sensor_val):
   return -0.1213*sensor_val + 81.02 

def convert_to_cartesian(phi, beta, distance):
    #theta = 90 - phi # the angle from the y axis
    #yPosPrime = distance * math.cos(math.radians(theta))
    #xPos = distance * math.sin(math.radians(theta))
    #yPos = math.cos(math.radians(90-beta))*yPosPrime
    #zPos = math.sin(math.radians(90-beta))*yPosPrime
    xPos = distance * math.sin(math.radians(phi)) * math.cos(math.radians(beta))
    yPos = distance * math.sin(math.radians(phi)) * math.sin(math.radians(beta))
    zPos = distance * math.cos(math.radians(phi))
    return xPos, yPos, zPos
    

i = 0

while True:
    # wait for lines to be available
    while cxn.inWaiting() < 1:
        pass
    # read lines from serial output
    result = cxn.readline()
    result = result.decode()
    # check if the line is complete
    if "angle1 = " in result and "angle2 = " in result and "distance" in result.decode():
        # parse the string for the parts we want
        angle1= result.decode().split(" ")[5]
        angle2 = result.decode().split(" ")[8]
        dist = result.decode().split(" ")[2] 
        # convert from strings to the data types we want
        angle1 = int(angle1)
        angle2 = int(angle2)
        dist = float(dist)
        # convert to cartesian 
        x, y, z = convert_to_cartesian(angle1, angle2, dist)
        # add it to the arrays
        xs[i] = x
        ys[i] = y
        zs[i] = z
        # increment
        i += 1
        # if the scan has finished
        if angle2 >= Z_ANGLE_MAX and angle1 >= X_ANGLE_MAX:
            # reset counter
            i = 0
            # stack the numpy arrays into a matrix, save to a csv
            data_input = np.column_stack((xs, ys, zs))
            df = pd.DataFrame(data_input)
            df.to_csv("data.csv")
            # create a plot
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            # add the points
            ax.scatter(xs, ys, zs, c='r')
            # decorate the axes
            ax.set_xlabel("X position")
            ax.set_ylabel("Y position")
            ax.set_zlabel("Z position")
            # show the plot
            plt.show()
        # why are you here
        if angle2 <= Z_ANGLE_MIN and angle1 <= X_ANGLE_MIN:
            # do not pass go, do not collect $200
            i = 0

 
