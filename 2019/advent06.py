# Advent of Code 2019
# Day 6
# 05-Dec-2019
#
# https://adventofcode.com/2019/day/6
#
# Checking orbit maps, where each object orbits exactly one other object.
# see instructions for more detail
#
#

import csv

INPUT = 'data/advent06.txt'
orbitmap = {}


# recursively count objects that orbit each other
def get_orbits(map, obj):
	if(obj in map):
		return get_orbits(map, map[obj]) + 1
	else:
		return 0

# recursively build a map l with number of orbits away from an object obj from map map
# leave 4th parameter (c) blank or 0 unless you know why you would change it
def mk_orbit_dict(l, map, obj, c = 0):
	if(obj in map):
		l[map[obj]] = c
		# print("C: {:5}  obj: {}   orbits: {}".format(c,obj,map[obj]))
		return mk_orbit_dict(l, map, map[obj], c + 1)
	else:
		return c


# find the first intersection between two maps from mk_orbit_dict
def find_orbit_intersection(a, b):
	xfers = 0
	for (obj, orbits) in a.items():
		for (obj2, orbits2) in b.items():
			if(obj == obj2):
				if(xfers == 0 or xfers > (orbits + orbits2)):
					xfers = orbits + orbits2
					# debug
					# print("XFER FOUND: a: ({}, {})  b: (){}, {})  xfers: {})"
					#      .format(obj, orbits, obj2, orbits2, xfers))
				#else:
					# print("xfer found: a: ({}, {})  b: (){}, {})  xfers: {})"
					#       .format(obj, orbits, obj2, orbits2, orbits + orbits2))
	return xfers


# load data file into a dictionary
with open(INPUT, 'r') as input:
	csv_read = csv.reader(input, delimiter = ')')
	for row in csv_read:
		orbitmap[row[1]] = row[0]
		
# PART 1 - SUM of all orbits
a = 0
for (obj, orbits) in orbitmap.items():
	a = a + get_orbits(orbitmap, obj)

print("Total orbits in map from file {}: {}".format(INPUT, a))

# PART 2 - COUNT orbit jumps between
#              a. the object YOU are orbiting and
#              b. the object SAN is orbiting
a = {}
b = {}
mk_orbit_dict(a, orbitmap, 'YOU')
mk_orbit_dict(b, orbitmap, 'SAN')

orbit_xfers = find_orbit_intersection(a, b)

print("Minimum orbit XFERS between YOU and SAN: {}".format(orbit_xfers))
