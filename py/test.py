from math import * 
from matplotlib import pyplot as plt
plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True

PI = 3.1416

rotation = 131.483 * PI/180.0
width = 64 
height = 16  
vec_x=[width/2, -width/2, -width/2, width/2]
vec_y=[height/2, height/2, -height/2, -height/2,]

#Transform
vec_x_correc=[ a*cos(rotation) - b*sin(rotation) for a,b in zip(vec_x, vec_y)]
vec_y_correc=[ a*sin(rotation) + b*cos(rotation) for a,b in zip(vec_x, vec_y)]

print(vec_x_correc)
print(vec_y_correc)

plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.grid()
# plt.plot(vec_x, vec_y, marker="o", markersize=10, markerfacecolor="green")
plt.plot(vec_x_correc, vec_y_correc, marker="o", markersize=10, markerfacecolor="red")
ax = plt.gca()
ax.set_aspect('equal', adjustable='box')
plt.show()