#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 17  CONWAY CUBES
#
#           A: 3D CONWAY LIFE, how many cells after 6 cycles
#              given a 2D plane as a starting state
#
#           B: 4D CONWAY LIFE, how many cells after 6 cycles
#              given a 2D plane as a starting state
# ===============================================================
from collections import namedtuple

INPUTFILE = "day17.input"
debug = False

def count_active_cubes_4d(cube):
    count = 0
    for w in cube:
        for z in cube[w]:
            for y in cube[w][z]:
                for x in y:
                    if x:
                        count += 1
    return count

def count_active_neighbors_4d(c, w, z, y, x):
    count = 0
    for tw in [w - 1, w, w + 1]:
        if tw < min(c.keys()) or tw > max(c.keys()):
            continue
        for tz in [z - 1, z, z + 1]:
            if tz < min(c[w].keys()) or tz > max(c[w].keys()):
                continue
            for ty in [y - 1, y, y + 1]:
                if ty < 0 or ty == len(c[0][0]):
                    continue
                for tx in [x - 1, x, x + 1]:
                    if tx < 0 or tx == len(c[0][0][0]):
                        continue
                    if tx == x and ty == y and tz == z and tw == w:
                        continue
                    if c[tw][tz][ty][tx]:
                        count = count + 1
    return count

def run_model_4d(c):
    new_cube = {}
    # add new cubes to consider
    # add x and y dims
    empty_row = [False] * (len(c[0][0]) + 2)
    for w in c.keys():
        for z in c[w].keys():
            for y in c[w][z]:
                y.append(False)
                y.insert(0, False)
            c[w][z].insert(0,empty_row)
            c[w][z].append(empty_row)
        
    # add new empty z's
    for w in c.keys():
        for z in [min(c[w].keys()) - 1, max(c[w].keys()) + 1]:
            c[w][z] = []
            for i in range(len(c[0][0])):
                c[w][z].append(c[0][0][0])

    # add new empty w's
    for w in [min(c.keys()) - 1, max(c.keys()) + 1]:
        new_z = {}
        for z in c[0].keys():
            new_y = []
            for x in range(len(empty_row)):
                new_y.append(empty_row)
            new_z[z] = new_y
        c[w] = new_z

    # do the model
    for w in get_ordered_keys_list(c):
        new_z = {}
        for z in get_ordered_keys_list(c[w]):
            new_y = []
            for y in range(len(c[w][z])):
                new_x = []
                for x in range(len(c[w][z][y])):
                    a = count_active_neighbors_4d(c, w, z, y, x)
                    if c[w][z][y][x]:
                        if a > 1 and a < 4:
                            new_x.append(True)
                        else:
                            new_x.append(False)
                    elif a == 3:
                        new_x.append(True)
                    else:
                        new_x.append(False)
                new_y.append(new_x)
            new_z[z] = new_y
        new_cube[w] = new_z
    
    return new_cube

def get_ordered_keys_list(c):
    ordered_list = list(c.keys())
    ordered_list.sort()
    return ordered_list

def count_active_cubes(cube):
    count = 0
    for z in cube:
        for y in cube[z]:
            for x in y:
                if x:
                    count += 1
    return count

def print_4d(c):
    for w in get_ordered_keys_list(c):
        print("  W={}".format(w))
        print_cube(c[w])

def print_cube(c):
    for z in get_ordered_keys_list(c):
        print("  Z={}".format(z))
        for i, y in enumerate(c[z]):
            print("{:5} ".format(i), end='')
            for x in y:
                if(x):
                    print("#", end='')
                else:
                    print(".", end='')
            print()

def count_active_neighbors(c, z, y, x):
    count = 0
    for tz in [z - 1, z, z + 1]:
        if tz < min(c.keys()) or tz > max(c.keys()):
            continue
        for ty in [y - 1, y, y + 1]:
            if ty < 0 or ty == len(c[0]):
                continue
            for tx in [x - 1, x, x + 1]:
                if tx < 0 or tx == len(c[0][0]):
                    continue
                if tx == x and ty == y and tz == z:
                    continue
                # print_cube(c)
                # print(tz,ty,tx)
                if c[tz][ty][tx]:
                    count = count + 1
    return count

def run_model(c):
    new_cube = {}
    # add new cubes to consider
    # add x and y dims
    empty_row = [False] * (len(c[0][0]) + 2)
    for z in c.keys():
        for y in c[z]:
            y.append(False)
            y.insert(0, False)
        c[z].insert(0,empty_row)
        c[z].append(empty_row)
    
    # add new empty z's
    for z in [min(c.keys()) - 1, max(c.keys()) + 1]:
        c[z] = []
        for i in range(len(c[0])):
            c[z].append(c[0][0])

    # do the model
    for z in get_ordered_keys_list(c):
        new_y = []
        for y in range(len(c[z])):
            new_x = []
            for x in range(len(c[z][y])):
                a = count_active_neighbors(c, z, y, x)
                if c[z][y][x]:
                    if a > 1 and a < 4:
                        new_x.append(True)
                    else:
                        new_x.append(False)
                elif a == 3:
                    new_x.append(True)
                else:
                    new_x.append(False)

            new_y.append(new_x)
        new_cube[z] = new_y
    
    return new_cube
    
def main():
    global debug
    cube = {}
    cube_4d = {}

    input = open(INPUTFILE, 'r')

    # READ INITIAL STATE
    y = []
    for row in input:
        x = []
        row = row.rstrip()
        for c in row:
            if c == '#':
                x.append(True)
            else:
                x.append(False)
        y.append(x)
    cube[0] = y

    input.close()
    
    # build 4D cube, for part B
    y = []
    for c in cube[0]:
        y.append(c[:])
    cube_4d[0] = {0: y[:]}


    # access individual cube as:
    # cube[z][y][x]
    
    ##
    ## PART A
    ## 
    ## Run 6 cycles, count active cells
    for i in range(6):
        cube = run_model(cube)

    
    c = count_active_cubes(cube)
    print("PART A: Active cubes (3D): {}".format(c))
    
    ##
    ## PART B
    ## 
    ## Run 6 cycles, count active cells, now in 4D
    for i in range(6):
        cube_4d = run_model_4d(cube_4d)

    c = count_active_cubes_4d(cube_4d)
    print("PART B: Active cubes (4D): {}".format(c))

if __name__ == "__main__":
    main()