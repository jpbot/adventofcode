#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 18  New Math (who needs order of operations)
#
#           A: sum of all expressions
#           B: sum of all expressions, now + before *
# ===============================================================
input_file = "day18.input"

def exp_split(s):
    s1 = 0
    p_count = 0

    while(s1 < len(s)):
        if(s[s1] == '('):
            p_count += 1
        elif(s[s1] == ')'):
            p_count -= 1
        elif(s[s1] == ' '):
            if(p_count == 0):
                break
        s1 += 1

    if(p_count == 0):
        return s[:s1], s[s1 + 1:]

    raise ValueError('Missing Parenthesis')

def build_stack(s2):
    stack = []
    op = []
    cc = 0
    while(len(s2) > 0):
        cc += 1
        s1, s2 = exp_split(s2)
        if(s1 in ['+', '*']):
            op.append(s1)
        else:
            if(s1[0] == '(' and s1[-1] == ')'):
                stack.extend(build_stack(s1[1:-1]))
            else:
                stack.append(s1)
            if(len(op) > 0):
                stack.append(op.pop(-1))
    return stack[:]

def rpn_calc(stack):
    debug = False
    s = []
    c = 0
    for n in stack:
        c += 1
        w = None
        if(n == '+'):
            w = s.pop(-1) + s.pop(-1)
            s.append(w)
        elif(n == '*'):
            w = s.pop(-1) * s.pop(-1)
            s.append(w)
        else:
            s.append(int(n))
        
        if(debug == True and w == None):
            print("{:>4} | {:>4}:        ::: s = {}".format(n, c, s))
        elif(debug == True):
            print("{:>4} | {:>4}: w = {} ::: s = {}".format(n, c, w, s))

    return s[-1]

def split_parenthesis(s):
    if(len(s) <= 0):
        return []

    stack = []
    while(s[0] == '('):
        stack.append('(')
        s = s[1:]
    
    if(s[-1] == ')'):
        s2 = s[s.find(')'):]
        s = s[:s.find(')')]
        stack.append(s)
        while(len(s2) > 0):
            s2 = s2[:-1]
            stack.append(')')
    else:
        stack.append(s)

    return stack[:]

def build_stack_ordered_ops(s2):
    op = []
    s = []
    stack = []

    # turn string into list
    while(True):
        if(s2.find(' ') == -1):
            s.extend(split_parenthesis(s2))
            break
        else:
            s1, s2 = s2.split(' ', 1)
            s.extend(split_parenthesis(s1))

    for n in s:
        if(n in ['(', '+']):
            op.append(n)
        elif(n == ')'):
            while(len(op) > 0 and not op[-1] == '('):
                stack.append(op.pop(-1))
            op.pop(-1)
        elif(n == '*'):
            while(len(op) > 0 and op[-1] == '+'):
                stack.append(op.pop(-1))
            op.append(n)
        else:
            stack.append(n)
        # print("n",n, "   op",op,"   stack",stack)

    while(len(op) > 0):
        stack.append(op.pop(-1))

    # print(s)
    # print(stack)
    return stack[:]

def main():
    debug = False
    verbose = True

    sum = 0
    input = open(input_file, 'r')
    c = 0
    for line in input:
        c += 1
        if(line.strip()==''):
            if(debug):
                print()
            continue

        stack = build_stack(line.rstrip())
        a = rpn_calc(stack)

        if(debug and verbose):
            print(line.strip())
            print("{:>4}| ANSWER: {}  stack: {}".format(c, a, stack))
        elif(debug):
            print("{:>4}| ANSWER: {}".format(c, a))

        sum += a
    input.close()

    print("PART A: sum of expressions: {}".format(sum))

    # PART B
    if(debug):
        print("PART B")
    
    sum = 0
    input = open(input_file, 'r')
    for line in input:
        line = line.strip()

        if(line == ''):
            if(debug):
                print()
            continue

        stack = build_stack_ordered_ops(line)
        a = rpn_calc(stack)
        sum += a

        if(debug and verbose):
            print(line)
            print("stack:",stack)
            print("{:>4}| ANSWER: {}  stack: {}".format(c, a, stack))
        elif(debug):
            print("{:>4}| ANSWER: {}".format(c, a))
        
    print("PART B: sum of expressions: {}".format(sum))
   
    


if __name__ == "__main__":
    main()