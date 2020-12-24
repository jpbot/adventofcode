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
INPUTFILE = "day10.input"

def count_gaps(joltdapters, gap_size):
    last = 0
    gaps = 0
    for j in joltdapters:
        if(j - last == gap_size):
            gaps += 1
        last = j
    return gaps

def test_valid(joltdapters, max_gap = 3):
    last = 0
    for j in joltdapters:
        if(j - last > max_gap):
            return False
        last = j
    return True

def main():
    input = open(INPUTFILE, 'r')

    joltdapters = []
    
    # read values
    for line in input:
        joltdapters.append(int(line.rstrip()))

    # sort the joltdapters
    joltdapters.sort()

    if(not test_valid(joltdapters)):
        print("Missing joltdapter")
        exit()
    
    
    #
    # PART A
    #

    # count gaps
    # add one to the 3 difference for the jolt adapter to device internal adapter
    one_gaps = count_gaps(joltdapters, 1)
    three_gaps = count_gaps(joltdapters, 3) + 1

    print("PART A: Using all adapters: there are {} differences of 1 jolt".format(one_gaps))
    print("                            there are {} differences of 3 jolt".format(three_gaps))
    print("                            puzzle answer product of 1 and 3 differences: {}".format(
        one_gaps * three_gaps))

    #     
    # PART B
    #

    # determine the combinations of adapters that convert the source jolts (0)
    # to the highest adapter in the collection (3 jolts lower than our device)
    # given the gap between adapters must be 1, 2, or 3.
    
    memo = {}
    joltdapters.sort(reverse=True)
    # important to follow path to the source in case two adapters can attach to the source
    joltdapters.append(0)
    
    # print(joltdapters, len(joltdapters))
    combos = all_combos(joltdapters, memo)

    print("PART B: combinations: {}".format(combos))

def all_combos(joltdapters, memo):
    return find_combos(0, joltdapters, memo)

def find_combos(j, joltdapters, memo):
    # memoized reverse order recursive search, memoization enables long searches in reasonable time
    if(j == len(joltdapters) - 1):
        return 1
    
    if(not j in memo.keys()):
        if(j+3 < len(joltdapters)):
            if(joltdapters[j] - 3 <= joltdapters[j + 3]):
                memo[j] = find_combos(j + 3, joltdapters, memo) + find_combos(j + 2, joltdapters, memo) + find_combos(j + 1, joltdapters, memo)
                return memo[j]
        if(j+2 < len(joltdapters)):
            if(joltdapters[j] - 3 <= joltdapters[j + 2]):
                memo[j] = find_combos(j + 2, joltdapters, memo) + find_combos(j + 1, joltdapters, memo)
                return memo[j]

        memo[j] = find_combos(j + 1, joltdapters, memo)
    return memo[j]






    


if __name__ == "__main__":
    main()