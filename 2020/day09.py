#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 9   given a buffer, valid next values are the sum of
#           2 numbers from the most recent 25 values after a 25
#           value preamble
#
#           A: what is the first number not following the pattern
#           B: what is the Accumulator when the book code
#              exits correctly (at end of program) after changing
#              one nop to jmp or one jmp to nop
# ===============================================================
INPUTFILE = "day09.input"
XMAS = []

def check4sum(z, set):
    last = len(set) -1
    for i, x in enumerate(set):
        if(not i == last):
            y = z - x
            if(y in set[(i+1):]):
                return True

def find_contig_sum(v):
    # x1 = -1
    # x2 = -1
    last = len(XMAS) - 2
    
    for i, x in enumerate(XMAS):
        if(not i == last):
            sum = x
            for j, y in enumerate(XMAS[(i+1):]):
                sum += y
                if sum > v:
                    break
                if sum == v:
                    return  i, j + i + 1
    return -1, -1

def sum_range(x1, x2):
    sum = 0
    for x in XMAS[x1:x2+1]:
        print(" >>", x)
        sum += x
    
    return sum

def main():
    input = open(INPUTFILE, 'r')
    
    # read values
    for line in input:
        line = line.rstrip()
        XMAS.append(int(line))

    # PART A
    c = 25
    part_a = -1
    while(c < len(XMAS)):
        if(not check4sum(XMAS[c], XMAS[c-25:c])):
            part_a = c
            break
        c += 1
    
    if(part_a > -1):
        print("PART A: Value not the sum of 2 previous values: ({}) {}".format(part_a, XMAS[part_a]))
    else:
        print("PART A: Value not the sum of 2 previous values: NOT FOUND")
        return


    # PART B
    x1, x2 = find_contig_sum(XMAS[part_a])
    if(x1 == x2):
        print("PART B: first and last value for contiguous range equal sum to part A: NOT FOUND")
    else:
        print("PART B: first and last value for contiguous range equal sum to part A: ({}-{}): {}".format(
            x1, x2, min(XMAS[x1:x2+1]) + max(XMAS[x1:x2+1])
        ))
    
    


if __name__ == "__main__":
    main()