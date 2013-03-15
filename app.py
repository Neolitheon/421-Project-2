blank = ['.', '?', '*']

def readFile(filename):
	lines = []
	f = open(filename)
	for line in f:
		lines.append(line)
	f.close()
	return lines

def printPuzzle(puzzle):
	line_count = 0
	print ""
	for line in puzzle:
		print "%d%d%d " % (line[0], line[1], line[2]),
		print "%d%d%d " % (line[3], line[4], line[5]),
		print "%d%d%d " % (line[6], line[7], line[8])
		line_count += 1
		if line_count % 3 == 0:
			print ""

def initPuzzle(filename): 
	lines = readFile(filename)
	puzzle = []
	line_count = 1
	for line in lines:
		numList = []
		for char in line:
			char = char.strip()
			if char == "":
				continue
			if char in blank:
				char = '0'
			try:
				verify = int(char)
				numList.append(verify)
			except:
				print "fail"
				exit(1)
		if len(numList) != 9:
			print "line %d not long enough" % (line_count)
			exit(1)
		puzzle.append(numList)
		line_count += 1 
	return puzzle

def main():
	puzzle = initPuzzle('input.cnf')
	printPuzzle(puzzle)

if __name__ == "__main__":
	main()
