# --- Day 4: Secure Container ---
# 
# You arrive at the Venus fuel depot only to discover it's protected by a
# password. The Elves had written the password on a sticky note, but
# someone threw it out.
# 
# However, they do remember a few key facts about the password:
# 
# It is a six-digit number. The value is within the range given in your
# puzzle input. Two adjacent digits are the same (like 22 in 122345).
# Going from left to right, the digits never decrease; they only ever
# increase or stay the same (like 111123 or 135679). Other than the range
# rule, the following are true:
# 
# - 111111 meets these criteria (double 11, never decreases).
# - 223450 does not meet these criteria (decreasing pair of digits 50). 
# - 123789 does not meet these criteria (no double).
#
# How many different passwords within the range given in your puzzle input meet these
# criteria?

--- Part Two ---

# An Elf just remembered one more important detail: the two adjacent
# matching digits are not part of a larger group of matching digits.
# 
# Given this additional criterion, but still ignoring the range rule, the
# following are now true:
# 
# - 112233 meets these criteria because the digits never decrease and all
#   repeated digits are exactly two digits long.
# - 123444 no longer meets the criteria (the repeated 44 is part of a larger
#   group of 444).
# - 111122 meets the criteria (even though 1 is repeated more than twice, it
#   still contains a double 22).

# How many different passwords within the range given in your puzzle input
# meet all of the criteria?
# 

# Your puzzle input is 245318-765747.

MINPASS = 245318
MAXPASS = 765747
DIGITS = 6

def in_range(p, min = MINPASS, max = MAXPASS):
	if(p >= min and p <= max):
		return True
	return False


def check_digit_count(p):
	min = int('1' * DIGITS)
	max = int('9' * DIGITS)
	return in_range(p, min, max)


def check_adjacent_pair(p):
	# check for adjacent pair, must be atomic and not a subset of a larger grouping
	s = str(p)
	d = s[0]
	c = 0

	for i in range(len(s)):
		if(s[i] == d):
			c = c + 1
		else:
			if(c == 2):			# had an adjacent pair
				return True
			d = s[i]
			c = 1

	if(c == 2):
		# adjacent pair at the end
		return True
	return False
	

def check_LR_GTEQ(p):
	# Check that digits in the pass number given do not decrease Left to Right
	s = str(p)
	min = 0
	
	# take advantage that characters are ascending, don't convert back to numbers
	for i in range(len(s)):
		d = int(s[i])
		if(d >= min):
			min = d
		else:
			return False	
	return True


# Rule Checking PW input p
def validate(p):
	return(check_adjacent_pair(p) and check_LR_GTEQ(p))
	

def pn_fix_ascend(p):
	# Change pass number so no digit decreases Left to Right
	s = str(p)
	p = 0
	min = int(s[0])
	incr = False

	for i in range(len(s)):
		d = int(s[i])
		if(d >= min and not incr):
			min = d
			p = p + d * 10 ** (len(s) - 1 - i)
		else:
			incr = True
			p = p + min * 10 ** (len(s) - 1 - i)
	return p
	
def pn_min_incr(p):
	p = p + 1
	p = pn_fix_ascend(p)
	if(not check_adjacent_pair(p)):
		return pn_min_incr(p)
	return p
	

print("Min guess : {}".format(MINPASS))
print("Max guess : {}".format(MAXPASS))
print("Test count: {}".format(MAXPASS - MINPASS + 1))

i = MINPASS
if(validate(i)):
	pwcount = 1
else:
	pwcount = 0

while True:
	i = pn_min_incr(i)
	if i < MAXPASS:
		pwcount = pwcount + 1
	else:
		break

print("Found {} possible passnums.".format(pwcount))
