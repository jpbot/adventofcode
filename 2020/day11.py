#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 11  WAITING SEATING
#
#           A: 
#           B: 
# ===============================================================
INPUTFILE = "day11.input"
debug = False

def adjacency_mode_1(m, x, y):
    max_y = len(m) -1
    if y > max_y:
        return -1

    max_x = len(m[y]) -1
    if x > max_x:
        return -1
    
    seats = 0
    if y >= 0 and y <= max_y and x + 1 >= 0 and x < max_x and m[y][x+1] == '#':
        seats += 1
    if y >= 0 and y <= max_y and x - 1 < max_x and x > 0 and m[y][x-1] == '#':
        seats += 1
    if y + 1 >= 0 and y < max_y and x <= max_x and x >= 0 and m[y+1][x] == '#':
        seats += 1
    if y > 0 and y - 1 <= max_y and x <= max_x and x >= 0 and m[y-1][x] == '#':
        seats += 1
    if y + 1 >= 0 and y < max_y and x < max_x and x + 1 >= 0 and m[y+1][x+1] == '#':
        seats += 1
    if y > 0 and y - 1 <= max_y and x < max_x and x + 1 >= 0 and m[y-1][x+1] == '#':
        seats += 1
    if y + 1 >= 0 and y < max_y and x - 1 < max_x and x > 0 and m[y+1][x-1] == '#':
        seats += 1
    if y > 0 and y - 1 <= max_y and x - 1 < max_x and x > 0 and m[y-1][x-1] == '#':
        seats += 1
    return seats

def adjacency_mode_2(m, x, y):
    max_y = len(m) -1
    if y > max_y:
        return -1

    max_x = len(m[y]) -1
    if x > max_x:
        return -1
    
    seats = 0
    if y >= 0 and y <= max_y and x + 1 >= 0:
        wx = x
        while wx < max_x:
            if m[y][wx+1] == '#':
                seats += 1
                break
            if m[y][wx+1] == 'L':
                break
            wx += 1
    if y >= 0 and y <= max_y and x - 1 < max_x:
        wx = x
        while wx > 0:
            if m[y][wx-1] == '#':
                seats += 1
                break
            if m[y][wx-1] == 'L':
                break
            wx -= 1
    if y + 1 >= 0 and x <= max_x and x >= 0:
        wy = y
        while wy < max_y:
            if m[wy+1][x] == '#':
                seats += 1
                break
            if m[wy+1][x] == 'L':
                break
            wy += 1
    if y - 1 <= max_y and x <= max_x and x >= 0:
        wy = y
        while wy > 0:
            if m[wy-1][x] == '#':
                seats += 1
                break
            if m[wy-1][x] == 'L':
                break
            wy -= 1
    if y + 1 >= 0 and x + 1 >= 0:
        wx = x
        wy = y
        while wy < max_y and wx < max_x:
            if m[wy+1][wx+1] == '#':
                seats += 1
                break
            if m[wy+1][wx+1] == 'L':
                break
            wy += 1
            wx += 1
    if y - 1 <= max_y and x + 1 >= 0:
        wx = x
        wy = y
        while wy > 0 and wx < max_x:
            if m[wy-1][wx+1] == '#':
                seats += 1
                break
            if m[wy-1][wx+1] == 'L':
                break
            wy -= 1
            wx += 1
    if y + 1 >= 0 and x - 1 < max_x:
        wx = x
        wy = y
        while wy < max_y and wx > 0:
            if m[wy+1][wx-1] == '#':
                seats += 1
                break
            if m[wy+1][wx-1] == 'L':
                break
            wy += 1
            wx -= 1
    if y - 1 <= max_y and x - 1 < max_x:
        wx = x
        wy = y
        while wy > 0 and wx > 0:
            if m[wy-1][wx-1] == '#':
                seats += 1
                break
            if m[wy-1][wx-1] == 'L':
                break
            wy -= 1
            wx -= 1
    return seats

def adjacent_filled_seats(m, x, y, mode):
    if x < 0 or y < 0:
        return -1
    

    if mode == 1:
        return adjacency_mode_1(m, x, y)
    if mode == 2:
        return adjacency_mode_2(m, x, y)

    print("Model Mode Error")
    return -1

def run_model(m, mode = 1):
    map = []
    c = 0

    for y, row in enumerate(m):
        newrow = ''
        for x, seat in enumerate(row):
            adjacent_fill = adjacent_filled_seats(m, x, y, mode)
            if seat == 'L' and adjacent_fill == 0:
                newrow += '#'
                c += 1
            elif seat == '#' and ((mode == 1 and adjacent_fill > 3) or (mode == 2 and adjacent_fill > 4)):
                newrow += 'L'
                c += 1
            else:
                newrow += seat
        map.append(newrow)
    
    return c, map[:]

def print_map(m):
    for y, row in enumerate(m):
        print(y, row, sep='::')

def count_seats(m):
    seats = 0
    for row in m:
        for seat in row:
            if seat == "#":
                seats += 1
    return seats

def main():
    global debug
    map = []

    input = open(INPUTFILE, 'r')
    rlen = -1
    for i, row in enumerate(input):
        row = row.rstrip()
        if rlen == -1:
            rlen = len(row)
        if not rlen == len(row):
            print("Skipping row {}, length ({}) does not match first row length ({})".format(i, len(row), rlen))
        map.append(row.rstrip())
    input.close()

    print("PART A:")
    i = 0
    changes = 1
    m = map[:]
    while(changes > 0):
        i += 1
        changes, m = run_model(m)
        if(debug):
            print_map(m)
            print("rounds:", i, "\nchanges:", changes)
            print()

    print("  iterations of model to reach steady state:", i)
    print("  seats occupied at steady state:", count_seats(m))
    print()
    
    # PART B
    print("PART B:")
    i = 0
    changes = 1
    m = map[:]
    while(changes > 0):
        i += 1
        changes, m = run_model(m, mode = 2)
        if(debug):
            print_map(m)
            print("rounds:", i, "\nchanges:", changes)
            print()

    print("  iterations of model to reach steady state:", i)
    print("  seats occupied at steady state:", count_seats(m))
    print()

        
    


if __name__ == "__main__":
    main()