#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 14  masked memory entries
#
#           A: sum of all memory after load
#           B: sum of all memory where mask is applied to addr
# ===============================================================
INPUTFILE = "day14.input"

MASKA = '0'*36
MASKB = '0'*36
MASKC = '0'*36


def update_mem(mem, mem_c, addr, val):
    # PART B
    #  ADDR range = (addr OR MASKB) AND MASKC
    #       through (addr OR MASKB) AND MASKA
    #               (but only with MASKA bits changed)
    if(addr not in mem_c.keys()):
        a = (int(addr) | int(MASKB, 2))
        a = a & int(MASKC, 2)
        a2 = a | int(MASKA, 2)
        a_list = []

        a_list.append(a)
        mem[a] = val

        while(a < a2):
            a = increment_by_mask(a, MASKA)
            a_list.append(a)
            mem[a] = val

def increment_by_mask(addr, mask, bits = 36):
    a = format(addr, "036b")
    i = bits
    carry = 1

    while(carry == 1):
        i = mask.rfind("1", 0, i)
        if(i == -1):
            return -1
        if(a[i] == '1'):
            carry = 1
            a = a[:i] + '0' + a[i+1:]
        else:
            carry = 0
            a = a[:i] + '1' + a[i+1:]
    
    return int(a,2)
        
def update_mask(val):
    global MASKA
    global MASKB
    global MASKC

    MASKA = val.replace("1", "0")
    MASKA = MASKA.replace("X", "1")
    MASKB = val.replace("X", "0")
    MASKC = val.replace("0", "1")
    MASKC = MASKC.replace("X", "0")

def apply_mask(val):
    val = val & int(MASKA, 2)
    val = val | int(MASKB, 2)
    return val

def main():
    input = open(INPUTFILE, 'r')

    mem_a = {}
    mem_b = {}
    mem_c = {}
    
    # read values
    for line in input:
        line = line.rstrip()
        op, val = line.split("=")
        op=op.rstrip()
        val=val.lstrip()

        if(op == 'mask'):
            update_mask(val)
        
        if(op[:4] == 'mem['):
            addr = int(op[4:-1])
            val = int(val)

            mem_a[addr] = apply_mask(val)
            update_mem(mem_b, mem_c, addr, val)

    total_a = 0
    for k in mem_a:
        total_a += mem_a[k]

    total_b = 0
    for k in mem_b:
        total_b += mem_b[k]

    print("PART A: sum of memory: {}".format(total_a))
    print("PART B: sum of memory: {}".format(total_b))
        
    


if __name__ == "__main__":
    main()