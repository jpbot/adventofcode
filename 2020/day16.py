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
    valid_tickets.append(tickets["your ticket"])


if __name__ == "__main__":
    main()