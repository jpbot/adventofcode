#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 12  FERRY LOGO
#
#           A: Manhattan distance between start and end points
#           B: 
# ===============================================================
INPUTFILE = "day12.input"


def main():
    input = open(INPUTFILE, 'r')
    pos = [0, 0]
    waypoint = [10, 1]
    direction = 90

    # PART A
    # read values
    for line in input:
        line = line.rstrip()
        cmd = line[0]
        val = int(line.rstrip()[1:])
        x = 0
        y = 0

        if(cmd == "F"):
            if(direction == 0):
                cmd = "N"
            elif(direction == 90):
                cmd = "E"
            elif(direction == 180):
                cmd = "S"
            elif(direction == 270):
                cmd = "W"
            else:
                print("DIRECTION {} not recognized.".format(direction))
                exit(1)

        if(cmd == "S"):
            y = val * -1
        if(cmd == "N"):
            y = val
        if(cmd == "E"):
            x = val
        if(cmd == "W"):
            x = val * -1

        if(cmd == "R"):
            direction = (direction + val) % 360
        if(cmd == "L"):
            direction -= val
            if(direction < 0):
                direction += 360
        
        pos = [pos[0] + x, pos[1] + y]

    print("PART A: Manhattan distance: {} ({})".format(abs(pos[0])+abs(pos[1]), pos))

    # PART B
    input.seek(0)
    pos = [0, 0]
    # read values
    for line in input:
        line = line.rstrip()
        cmd = line[0]
        val = int(line.rstrip()[1:])
        x = 0
        y = 0

        if(cmd == "F"):
            for i in range(val):
                pos = [pos[0] + waypoint[0], pos[1] + waypoint[1]]

        if(cmd == "S"):
            waypoint = [waypoint[0], waypoint[1] - val]
        if(cmd == "N"):
            waypoint = [waypoint[0], waypoint[1] + val]
        if(cmd == "E"):
            waypoint = [waypoint[0] + val, waypoint[1]]
        if(cmd == "W"):
            waypoint = [waypoint[0] - val, waypoint[1]]

        # should be some geometry here, but we cheat because
        # directions are modulo 90 (E/W/N/S 90/270/0/180)
        if(cmd == "R"):
            direction = val
        if(cmd == "L"):
            direction = 360 - val
        if(cmd == "R" or cmd == "L"):
            # rotate the waypoint around the ship
            if(direction == 90):
                waypoint = [waypoint[1], -waypoint[0]]
            elif(direction == 270):
                waypoint = [-waypoint[1], waypoint[0]]
            elif(direction == 180):
                waypoint = [-waypoint[0], -waypoint[1]]
        
        waypoint = [waypoint[0] + x, waypoint[1] + y]
        # print(cmd, val, " : waypoint:", waypoint)
        # print(cmd, val, " :      pos:", pos)

    print("PART B: Manhattan distance: {} ({})".format(abs(pos[0])+abs(pos[1]), pos))

    # print("PART B: sum of memory: {}".format(total_b))
        
    


if __name__ == "__main__":
    main()