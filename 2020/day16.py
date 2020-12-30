#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 16  WAITING SEATING
#
#           A: 
#           B: 
# ===============================================================
from collections import namedtuple

INPUTFILE = "day16.input"
debug = False
tickets = {}
rules = {}
rules_value_valid = {}
Rule = namedtuple('Rule', ['id', 'min', 'max'])



def validate(v):
    if v in rules_value_valid.keys():
        return rules_value_valid[v]
    
    for r in rules:
        for rr in rules[r]:
            if v >= rr.min and v <= rr.max:
                rules_value_valid[v] = True
                return True
    rules_value_valid[v] = False
    return False

def valid_rules(v):
    valid = []

    if v not in rules_value_valid.keys() or rules_value_valid[v] == False:
        return -1

    for r in rules:
        for rr in rules[r]:
            if v >= rr.min and v <= rr.max:
                # print(" valid <<<<<",r)
                valid.append(r)
                break

    return valid[:]

def list_and_inplace(l1, l2):
    l1 = list_and(l1, l2)
    return l1

def list_and(l1, l2):
    s = []
    for i in l1:
        if i in l2:
            s.append(i)
    return s
    
def print_field_counts(fields):
    for f in fields:
        print("{:3}".format(len(f)), end = '')
    print()

def list_field_counts(fields):
    l = []
    for f in fields:
        l.append(len(f))
    return l[:]

def main():
    global debug
    global rules
    global rules_memo

    input = open(INPUTFILE, 'r')

    # READ RULES
    for i, row in enumerate(input):
        details = []
        row = row.rstrip()
        if row == '':
            break

        rule, rule_detail = row.split(": ")
        
        for r in rule_detail.split(" or "):
            min, max = r.split("-")
            details.append(Rule(id = i, min = int(min), max = int(max)))
        
        rules[rule] = details[:]

    # READ TICKETS
    ticket_collection = []
    for row in input:
        row = row.rstrip()
        if row == '':
            continue
        if row[-1] == ':':
            # set collection
            ticket_collection = []
            tickets[row[:-1]] = ticket_collection

            continue
        ticket_collection.append(list(map(int, row.split(','))))
       
    input.close()
    
    ##
    ## PART A
    ## 
    ## find sum of values invalid for any field (ticket scanning error rate)

    valid_tickets = []
    error_rate = 0
    for t in tickets["nearby tickets"]:
        valid = True
        for v in t:
            if not validate(v):
                error_rate += v
                valid = False
        if valid:
            valid_tickets.append(t)
    
    print("PART A:             error_rate =", error_rate)
    print("        nearby tickets scanned =", len(tickets["nearby tickets"]))
    print("          valid nearby tickets =", len(valid_tickets))

    ##
    ## PART B
    ## 
    ## find correct fields and multiply all departure* fields from your ticket

    # add our ticket into the valid ticket list
    valid_tickets.append(tickets["your ticket"][0])

    # Simple algorithm (would be great if this solves).
    # Might need to go more advanced.
    # For each ticket:
    #       Evaluate all values for each field.
    #       Lock in fields with only one positional value.
    #       Continue to next ticket but ignore fields that are locked in.
    # Doesn't work...just in dev...

    # fields = {}
    # scratch_fields = []

    # for t in valid_tickets:
    #     scratch_fields.clear()
    #     for i, f in enumerate(t):
    #         v_count = len(valid_rules(f))
    #         if v_count == 1:
    #             print(i, f, "::", v_count)


    list_of_fields = list(rules.keys())
    fields = []

    # put all fields in the fields list
    for i in range(len(list_of_fields)):
        fields.append(list_of_fields[:])

    # remove fields from fields list that aren't found
    for t_num, t in enumerate(valid_tickets):
        for i, f in enumerate(t):
            if len(fields[i]) > 1:
                scratch = valid_rules(f)
                if len(scratch) < 20:
                    fields[i] = list_and(fields[i], scratch)
                    if(debug):
                        print("ticket {:3} ({:2}) :: ".format(t_num, i), end='')
                        print_field_counts(fields)

    # show progress (debug)
    # debug = True
    if debug:
        print(list_field_counts(fields))
        for i, f in enumerate(fields):
            print(i,f)
    
    last_count = []
    while(not last_count == list_field_counts(fields)):
        last_count = list_field_counts(fields)
        for i, c in enumerate(last_count):
            if c == 1:
                field = fields[i][0]
                for pos, f in enumerate(fields):
                    if not pos == i and field in f:
                        f.remove(field)

    # check if we determined single field for each position
    valid_field_defs = True
    for c in list_field_counts(fields):
        if not c == 1:
            valid_field_defs = False
            break
    
    if not valid_field_defs:
        print("Could not determine fields")
        exit()

    startswith = "departure"
    product_of_departure_fields = 0
    for i, f in enumerate(fields):
        fields[i] = f[0]
        if debug:
            print(i,f[0])

        if f[0][0:len(startswith)] == startswith:
            if product_of_departure_fields == 0:
                product_of_departure_fields = int(tickets["your ticket"][0][i])
            else:
                product_of_departure_fields *= int(tickets["your ticket"][0][i])
            if debug:
                print(i,f[0])
    
    print("PART B: product of fields from 'your ticket' that begin with '{}': {}".format(startswith, product_of_departure_fields))
    
    

    
    

if __name__ == "__main__":
    main()