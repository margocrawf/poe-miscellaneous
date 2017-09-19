import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

f = open("sensorvals_infrared.txt", "r")
vals = f.readlines()

total = 0.0
count = 0
dists = []
averages = []

for line in vals:
    if "in" in line:
        if count: 
            print(total/count)
            averages.append(total/count)
        dist = line.split(" ")[0]
        print(dist + ": ")
        dists.append(dist)
        total = 0.0
        count = 0
    elif "sensor" in line:
        val = line.split(" ")[2]
        total += float(val)
        count += 1

print(total/count)
averages.append(total/count)

plt.scatter(averages, dists)

print(dists)
print(averages)

regr = linear_model.LinearRegression()

dists = np.array(dists).reshape((1, -1))

regr.fit(averages, dists)

predicted_dists = regr.predict(averages)

plt.plot(averages, predicted_dists, color="blue", linewidth=3)
plt.show()
