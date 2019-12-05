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
	s = str(p)
	
	# must be 2 digits to have a repeated pair of digits
	if(len(s) > 1):
		for i in range(len(s) - 1):
			if(s[i] == s[i+1]):
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
	
	
# Brut-force is too slow
def brutforce():
	i = MINPASS
	pwcount = 0
	while i < MAXPASS:
		if(validate(i)):
			pwcount = pwcount + 1
		else:
			i = i + 1

	print("Found {} possible passnums.".format(pwcount))


print("Min guess : {}".format(MINPASS))
print("Max guess : {}".format(MAXPASS))
print("Test count: {}".format(MAXPASS - MINPASS + 1))

# brut force
#brutforce()

# smart increment
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
