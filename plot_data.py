import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import math
# get the data from the file as a matrix
df = pd.read_csv("data.csv")
mat = df.as_matrix()
# split it by column
_, xs, ys, zs = np.hsplit(mat, 4)
# make matrices to add the points to
good_xs = []
good_ys = []
good_zs = []
bad_xs = []
bad_ys = []
bad_zs = []
# sort the points into good (in range) and bad (not in range)
for i in range(len(xs)):
    if ys[i] >= 20 and ys[i] <= 50 and zs[i] < 40:
        good_xs.append(xs[i])
        good_ys.append(ys[i])
        good_zs.append(zs[i])
    else:
        bad_xs.append(xs[i])
        bad_ys.append(ys[i])
        bad_zs.append(zs[i])
# make the figure 
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# plot the data
ax.scatter(bad_xs, bad_ys, bad_zs, c='w')
ax.scatter(good_xs, good_ys, good_zs, c='b')
# decorate the axes
ax.set_xlabel("X position")
ax.set_ylabel("Y position")
ax.set_zlabel("Z position")
# show the plot
plt.show()

