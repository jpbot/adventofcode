#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 8   given boot code for a video game console that's
#           corrupted
#
#           A: what is the Accumulator value prior to where
#              the boot code begins looping
#           B: what is the Accumulator when the book code
#              exits correctly (at end of program) after changing
#              one nop to jmp or one jmp to nop
# ===============================================================
INPUTFILE = "day08.input"
instruction = []
backup = []
bSP = 0
bAC = 0
AC = 0
SP = 0

def backup_vm():
    global bAC
    global bSP
    global backup
    bAC = AC
    bSP = SP
    backup = instruction[:]

def restore_vm():
    global AC
    global SP
    global instruction
    AC = bAC
    SP = bSP
    instruction = backup[:]

def reset_vm():
    global AC
    global SP
    AC = 0
    SP = 0

    for i, val, witness in instruction:
        instruction[SP] = [i, val, 0]
        SP += 1

    SP = 0

def run_vm(verbose = False):
    global AC
    global SP
    PSP = 0

    image_size = len(instruction)
    c = 0
    while(SP < image_size):
        i, val, witness = instruction[SP]
        witness += 1
        instruction[SP] = [i, val, witness]
        sp = SP
        
        if(witness > 1):
            return -1, PSP

        if(i == 'acc'):
            AC += val
            PSP = SP
            SP += 1
        if(i == 'nop'):
            PSP = SP
            SP += 1
        if(i == 'jmp'):
            PSP = SP
            SP += val

        if(verbose):
            print(f"{c:6}| {sp:5}/{image_size:<5}:: {i} {val:<5}   RC: {witness:<2}  SP: {SP:<5}  AC: {AC:<5}")
            c += 1

    return 0, SP

def patch_inst(verbose = False):
    changed = patch_inst_jpm_to_nop(verbose)
    if(not changed == -1):
        return changed

    return patch_inst_nop_to_jmp(verbose)


def patch_inst_jpm_to_nop(verbose = False):
    if(verbose):
        p = 0 # count possible options
        for i, val, witness in instruction:
            if(i == 'jmp'):
                p += 1
        print("{:10} possible jmp's to change to nop".format(p))

    # Try them all until we fix it
    reset_vm()
    backup_vm()
    c = 0
    for i, val, witness in instruction:
        if(i == 'jmp'):
            restore_vm()
            instruction[c] = ['nop', val, 0]
            err, sp = run_vm()
            if(not err):
                reset_vm()
                return c
        c += 1
    
    restore_vm()
    return -1

def patch_inst_nop_to_jmp(verbose = False):
    if(verbose):
        p = 0 # count possible options
        for i, val, witness in instruction:
            if(i == 'nop' and not val == 0):
                p += 1    
        print("{:10} possible nop's with value".format(p))

    # Try them all until we fix it
    c = 0
    reset_vm()
    backup_vm()
    for i, val, witness in instruction:
        if(i == 'nop' and not val == 0):
            restore_vm()
            instruction[c] = ['jmp', val, 0]
            err, sp = run_vm()
            if(not err):
                reset_vm()
                return c
        c += 1

    restore_vm()
    return -1

def main():
    input = open(INPUTFILE, 'r')
    
    # read instructions
    for line in input:
        line = line.rstrip()
        inst, val = line.split(" ")
        instruction.append([inst, int(val), 0])
        
    # PART A
    reset_vm()
    result = run_vm()
    print("PART A: Accumulator prior to execution retrace begin: {:<5}          {}".format(AC, result))

    # PART B
    reset_vm()
    patch_inst()
    result = run_vm()
    print("PART B: Accumulator at execution end:                 {:<5}          {}".format(AC, result))

    


if __name__ == "__main__":
    main()