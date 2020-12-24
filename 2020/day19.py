#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 11  Shuttle Search: find the shuttle bus you wait the
#           shortest time for. Buses depart at timestamp 0 and
#           every <busid> timestamps.
# 
#           A: busid * time to wait
#
#           B: 
# ===============================================================
INPUTFILE = "day19.input"

def read_rules(rules, i):
    c = 0
    for r in i:
        r = r.strip()
        if(r == ''):
            break
        c += 1
        r_num, rule = r.split(': ')
        rules[int(r_num)] = rule
    return c

def main():
    rules = {}

    input = open(INPUTFILE, 'r')
    print("Read {} rules from {}.".format(read_rules(rules, input), INPUTFILE))

    # Process messages
    i = 0
    for m in input:
        i += 1
        m = m.strip()
        print("Processing message {} ({}).".format(i, m))
    
    input.close()

    l_keys = []
    for key in rules.keys():
        l_keys.append(key)
    l_keys.sort()
    for key in l_keys:
        print("{:>4}: {}".format(key, rules[key]))

if __name__ == "__main__":
    main()