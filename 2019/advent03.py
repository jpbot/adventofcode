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

INPUT = 'data/advent03_t1.txt'
wires = []

def check_intersection(a,b):
	# check if line segments a and b intersect
	# assume only horizontal and vertical segments (0,90,180,270 degrees)
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
	if(a(4) = b(4)):
		return False)
	return True


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

# debug
print wires

# search for intersections
# maybe: http://www.cs.swan.ac.uk/~cssimon/line_intersection.html
# maybe do something simple because we have all perpendicular segments
i = 0
for a in wires[0]:
	for b in wires[1]:
		if(check_intersection(a,b)):
			print i,a,b,":",a[0], a[1], a[2], a[3], a[4]
			
