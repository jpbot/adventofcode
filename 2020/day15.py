#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 10  given a buffer, valid next values are the sum of
#           2 numbers from the most recent 25 values after a 25
#           value preamble
#
#           A: what is the first number not following the pattern
#           B: what is the Accumulator when the book code
#              exits correctly (at end of program) after changing
#              one nop to jmp or one jmp to nop
# ===============================================================
INPUT = [9,3,1,0,8,4]
# INPUT = [0,3,6]        # TEST 0 : --
# INPUT = [1,3,2]        # TEST 1 : 1
# INPUT = [2,1,3]        # TEST 2 : 10
# INPUT = [1,2,3]        # TEST 3 : 27
# INPUT = [2,3,1]        # TEST 4 : 78
# INPUT = [3,2,1]        # TEST 5 : 438
# INPUT = [3,1,2]        # TEST 6 : 1836

def solver(stop=2020):
    memory = {}
    scratch = []
    turn = 1
    last = 0
    i = 0

    # could use a single tuple, but here we are, dictionary of lists of numbers (turn number)
    for i in INPUT:
        if(i in memory.keys()):
            memory[i].append(turn)
        else:
            memory[i] = [turn]
        
        turn += 1
        last = i

    while(not turn > stop):
        scratch = memory[last]
        # print()
        # print("{:>5}:: LAST = {} :: {}".format(turn, last, scratch))
        if(len(scratch) < 2):
            i = 0
            # print("{:>5}:: {}".format(turn, i))
        else:
            i = scratch[-1] - scratch[-2]
            # print("{:>5}:: s[-1]: {} - s[-2]: {} = {}".format(turn, scratch[-1], scratch[-2], i))

        if(i in memory.keys()):
            memory[i].append(turn)
        else:
            memory[i] = [turn]
        
        turn += 1
        last = i
    
    return last

def main():
    a = solver()
    b = solver(stop = 30000000)

    print("PART A: given input: {}, the {} spoken number is {}".format(INPUT, 2020, a))
    print("PART B: given input: {}, the {} spoken number is {}".format(INPUT, 30000000, b))
   
    


if __name__ == "__main__":
    main()