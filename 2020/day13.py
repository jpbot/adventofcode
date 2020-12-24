#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 13  Shuttle Search: find the shuttle bus you wait the
#           shortest time for. Buses depart at timestamp 0 and
#           every <busid> timestamps.
# 
#           A: busid * time to wait
#
#           B: 
# ===============================================================
INPUTFILE = "day13.input"

# INPUTFILE = "day13.sample"
# test_partb = 1068788 + 10

# INPUTFILE = "day13.sample2"
# test_partb = 3417 + 3

def main():
    input = open(INPUTFILE, 'r')
    earliest_departure = int(input.readline().rstrip())

    bus_idx = {}
    bus = []
    bus_c = 0
    for b in input.readline().rstrip().split(","):
        if(not b == "x"):
            bus.append(int(b))
            bus_idx[int(b)] = bus_c
        bus_c += 1

    print(bus)

    # PART A

    # Check for bus with perfect timing
    bus_best = -1
    bus_time = earliest_departure
    for b in bus:
        if(earliest_departure % b == 0):
            bus_best = b
            bus_time = earliest_departure

    if(bus_best == -1):
        # Looking for the next best bus
        for b in bus:
            trip_count = int(earliest_departure / b) + 1
            if(bus_time <= earliest_departure or bus_time > trip_count * b):            
                bus_best = b
                bus_time = trip_count * b
    
    wait_time = bus_time - earliest_departure
    
    print("Estimated earliest departure:", earliest_departure)
    print("PART A: The earliest departing viable bus is # {} at timestamp {}".format(bus_best, bus_time))
    print("        Wait time will be: {} product of wait and bus_id {}".format(wait_time, wait_time * bus_best))
    
    # #     
    # # PART B
    # #
    max_bus = max(bus)
    ts_max_bus = max_bus
    accellerate = {}
    step = max_bus

    print()
    print("MAX BUS:", max_bus)

    while(True):
        found = True
        for b in bus:
            if(b == max_bus):
                continue
            if((ts_max_bus-bus_idx[max_bus]+bus_idx[b]) % b == 0):
                if(b in accellerate.keys()):
                    if(ts_max_bus - accellerate[b] > step):
                        step = ts_max_bus - accellerate[b]
                accellerate[b] = ts_max_bus
                continue
            
            found = False
            break
        if(found):
            break
        ts_max_bus += step

    ts = ts_max_bus - bus_idx[max_bus] + bus_idx[bus[0]]

    print("PART B: First timestamp with consecutive departure times:", ts)
    print("        step:", step)    

    # print("PART B: combinations: {}".format(2 ** one_gaps))
    

    # # determine the combinations of adapters that convert the source jolts (0)
    # # to the highest adapter in the collection (3 jolts lower than our device)
    # # given the gap between adapters must be 1, 2, or 3.


    


if __name__ == "__main__":
    main()