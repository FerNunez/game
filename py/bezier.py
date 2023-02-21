from math import * 
import numpy as np
import matplotlib.pyplot as plt
from Vector2D import Vector2D

class Bezier():

	def __init__(self, num_way_points: int, p0: Vector2D, p1: Vector2D, p2: Vector2D, p3: Vector2D):
		self.t = np.linspace(start=0,stop=1,num=num_way_points)
		
		self.p0 = p0
		self.p1 = p1
		self.p2 = p2
		self.p3 = p3
		
		self.bezier_points = [] 
		self.bezier_tangent = [] 
		self.bezier_normal = [] 

		self.calculateBezierPoints()
		
		self.selected_point_idx = None
		self.min_dist = 0.05


	def calculateBezierPoints(self):
		t = self.t

		# Curve
		u = 1 - t
		uu = u*u
		uuu = uu * u
		tt = t*t
		ttt = tt * t

		p = uuu * self.p0
		p = p + 3 * uu * t * self.p1
		p = p + 3 * u * tt * self.p2
		p = p + ttt * self.p3

		# [x,y]= (1–t)^3*P0 + 3*(1–t)^2*t*P1 + 3*(1–t)*t^2*P2 + t^3*P3
		self.bezier_points = p

		# derivative
		p_dot = (-3*tt+6*t-3) * self.p0
		p_dot = p_dot + (9*tt-12*t+3) * self.p1
		p_dot = p_dot + (-9*tt+6*t) * self.p2
		p_dot = p_dot + (3*tt) * self.p3

		self.bezier_tangent = p_dot

		self.bezier_normal = [Vector2D(-vec.y, vec.x) for vec in p_dot]

	def onClick(self, event):
		point_list = [self.p0, self.p1, self.p2, self.p3]
		mouse_pos = Vector2D(event.xdata, event.ydata)

		dist_list = [mouse_pos.distance_to(x) for x in point_list ]
		min_distance = min(dist_list)
		idx = dist_list.index(min_distance)
		
		if min_distance <= self.min_dist: 
			self.selected_point_idx = idx
		else:
			self.selected_point_idx = None

	def onRelease(self, event):
	    if self.selected_point_idx is not None:
	    	mouse_pos = Vector2D(event.xdata, event.ydata)
	    	if self.selected_point_idx == 0:
	    		self.p0 = mouse_pos
	    	elif self.selected_point_idx == 1:
	    		self.p1 = mouse_pos	    		 
	    	elif self.selected_point_idx == 2:
	    		self.p2 = mouse_pos
	    	elif self.selected_point_idx == 3:
	    		self.p3 = mouse_pos

    		plt.clf()
    		self.update()

	def update(self):
		plt.clf()
		self.calculateBezierPoints()
		self.display()    	

	def display(self):

		fig, ax = plt.subplots()
		plt.plot(self.p0.x, self.p0.y, 'o', color='black')
		plt.plot(self.p1.x, self.p1.y, 'o', color='red')
		plt.plot(self.p2.x, self.p2.y, 'o', color='green')
		plt.plot(self.p3.x, self.p3.y, 'o', color='blue')

		for i in range(0, len(self.bezier_points)):
			point = self.bezier_points[i]
			normal = self.bezier_normal[i]
			plt.plot(point.x, point.y, '.', color='black')
			plt.quiver(point.x, point.y, normal.x, normal.y)
		fig.canvas.mpl_connect('button_press_event', self.onClick)
		fig.canvas.mpl_connect('button_release_event', self.onRelease)
		plt.xlim([-2, 2])
		plt.ylim([-2, 2])
		plt.show()

if __name__ == '__main__':

	num_way_points = 50
	b = Bezier(num_way_points, Vector2D(-1, -1), Vector2D(-1, 1), Vector2D(1, 1), Vector2D(1, -1))

	b.display()
