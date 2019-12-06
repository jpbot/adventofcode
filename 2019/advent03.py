# Manhattan distance: https://en.wikipedia.org/wiki/Taxicab_geometry

# --- Day 3: Crossed Wires ---
# 
# The gravity assist was successful, and you're well on your way to the
# Venus refuelling station. During the rush back on Earth, the fuel
# management system wasn't completely installed, so that's next on the
# priority list.
# 
# Opening the front panel reveals a jumble of wires. Specifically, two
# wires are connected to a central port and extend outward on a grid. You
# trace the path each wire takes as it leaves the central port, one wire
# per line of text (your puzzle input).
# 
# The wires twist and turn, but the two wires occasionally cross paths. To
# fix the circuit, you need to find the intersection point closest to the
# central port. Because the wires are on a grid, use the Manhattan
# distance for this measurement. While the wires do technically cross
# right at the central port where they both start, this point does not
# count, nor does a wire count as crossing with itself.
# 
# For example, if the first wire's path is R8,U5,L5,D3, then starting from
# the central port (o), it goes right 8, up 5, left 5, and finally down 3:
# 
# ...........
# ...........
# ...........
# ....+----+.
# ....|....|.
# ....|....|.
# ....|....|.
# .........|.
# .o-------+.
# ...........
# Then, if the second wire's path is U7,R6,D4,L4, it goes up 7, right 6,
# down 4, and left 4:
# 
# ...........
# .+-----+...
# .|.....|...
# .|..+--X-+.
# .|..|..|.|.
# .|.-X--+.|.
# .|..|....|.
# .|.......|.
# .o-------+.
# ...........
# These wires cross at two locations (marked X), but the lower-left one is
# closer to the central port: its distance is 3 + 3 = 6.
# 
# Here are a few more examples:
# 
# R75,D30,R83,U83,L12,D49,R71,U7,L72
# U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
# R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
# U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
# 
# What is the Manhattan distance from the central port to the closest
# intersection?

import os
import csv
import math

#          1
#          |
#          |
#   -1  ---0---  1
#          |
#          |
#          -1

DOWN = 'D'
UP = 'U'
LEFT = 'L'
RIGHT = 'R'
LR = 0
UD = 1

INPUT = 'data/advent03_t3.txt'
wires = []

def get_intersection(a, b):
	# check if line segments a and b intersect
	# assume only horizontal and vertical segments (0,90,180,270 degrees)
	#
	# returns point of intersection, or none if segments do not intersect
	#
	# ...........
	# .+-----+...
	# .|.....|...             b               a
	# .|..+--X-+.   6,5  (6,3)-(6,7)*1 & (3,5)-(8,5)*0
	# .|..|..|.|.
	# .|.-X--+.|.   3,3  (2,3)-(6,3)*0 & (3,2)-(3,5)*1
	# .|..|....|.
	# .|.......|.                    * direction
	# .o-------+.
	# ...........
	#
	# maybe: http://www.cs.swan.ac.uk/~cssimon/line_intersection.html
	# maybe do something simple because we have all perpendicular segments

	if(a[4] == 1 and b[4] == 0):
		if(a[0] > b[0] and a[2] < b[2] and a[1] < b[1] and a[3] > b[3]):
			return (a[0],b[1])
	if(a[4] == 0 and b[4] == 1):
		if(a[0] < b[0] and a[2] > b[2] and a[1] > b[1] and a[3] < b[3]):
			return (b[0],a[1])

def is_segment_point(segment, point):
	# similar to get_intersection, lazy implementation only works
	# with single axis segments	
	x = point[0]
	y = point[1]
	if(segment[0] == segment[2] == x and segment[1] < y < segment[3]):
		return segment[3] - y	
	if(segment[1] == segment[3] == y and segment[0] < x < segment[2]):
		return segment[2] - x	
	return False
	
	
def segment_length(segment):
	# return math.sqrt((segment[3]-segment[1]) ** 2 + (segment[2]-segment[0]) ** 2)
	# do less work since segments always follow a single axis
	return (segment[3]-segment[1]) + (segment[2]-segment[0])

	
def manhattan(point):
	return abs(point[0]) + abs(point[1])
	

def path_distance(wire, point):
	d = 0
	for segment in wire:
		a = is_segment_point(segment, point)
		if(a):
			# d = d + segment_distance_point(segment, point)
			return d + a
		else:
			d = d + segment_length(segment)
		print("{}: {} :: {}".format(d,segment, point))
	

def part_a():
	d = 0
	i = (0, 0)
	for a in wires[0]:
		for b in wires[1]:
			intersect = get_intersection(a,b)
			if(intersect):
				if(d == 0 or d > manhattan(intersect)):
					d = manhattan(intersect)
					i = intersect

	if(d):
		print("Closest intersection of wires to origin is {}".format(i))
		print("Manhattan Distance: {}".format(d))			


def part_b():
	d = 0
	i = (0, 0)
	for a in wires[0]:
		for b in wires[1]:
			intersect = get_intersection(a,b)
			if(intersect):
				apath = path_distance(wires[0],intersect)
				bpath = path_distance(wires[1],intersect)
				print("intersection: {}".format(intersect))
				print("      wire a: {}".format(apath))
				print("      wire b: {}".format(bpath))
				print("        path: {}".format(apath + bpath))
				print
				if(d == 0 or d > manhattan(intersect)):
					d = manhattan(intersect)
					i = intersect

	if(d):
		print("Closest intersection of wires to origin is {}".format(i))
		print("Manhattan Distance: {}".format(d))		
		

# build a list of wires, each wire a list of segments of the path
with open(INPUT, 'r') as input:
	csv_reader = csv.reader(input)
	for row in csv_reader:
		x1 = 0
		y1 = 0
		x2 = 0
		y2 = 0
		wire = []
		wires.append(wire)
		for move in row:
			d = move[0]
			if(d == DOWN):
				x1 = x2
				y1 = y2
				y2 = y1 - int(move[1:])
				dir = UD
			elif(d == UP):			
				x1 = x2
				y1 = y2
				y2 = y1 + int(move[1:])
				dir = UD
			elif(d == LEFT):
				y1 = y2
				x1 = x2
				x2 = x1 - int(move[1:])
				dir = LR
			elif(d == RIGHT):
				y1 = y2
				x1 = x2
				x2 = x1 + int(move[1:])
				dir = LR
			else:
				print("Bad move in file: {}".format(INPUT))
				break
			# min and max only works because points of segments share a common axis
			wire.append((min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2),dir))

# search for intersections
# part_a()	# intersection closest to origin point
part_b()	# intersection shortest path
