import csv

INPUT = 'data/advent06test.txt'
i = 0


with open(INPUT, 'r') as input:
	csv_read = csv.reader(input, delimiter = ')')
	for row in csv_read:
		print(i, row, row[0], row[1])
		i = i + 1