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

def writeToCNFFile(puzzle, extended):
	f = open('output.cnf', 'w')
	
	#Minimum
	#AT LEAST ONE NUMBER
	for x in range (1, 10):
		for y in range (1, 10):
			cnf_clause = ""
			if puzzle[x-1][y-1] == 0:
				for z in range (1, 10):
					cnf_clause += "%d%d%d " % (x,y,z) 
				cnf_clause += "0\n"
			else:
				cnf_clause ="%d%d%d 0\n" % (x,y,puzzle[x-1][y-1]) 
			f.write(cnf_clause)


	#Extended
	if extended == 1:
		#AT MOST ONE NUMBER
		for x in range (1, 10):
			for y in range (1, 10):
				for z in range (1, 10):
					cnf_clause = ""
					if m[x-1][y-1] == z:
						for i in range (z, 10):
							cnf_clause += "-%d%d%d " % (x,y,i) 
						cnf_clause += "0\n"
						f.write(cnf_clause)
					else if m[x-1][y-1] == 0:
						for i in range (z, 10):
							cnf_clause += "-%d%d%d -%d%d%d 0\n" % (x,y,z,x,y,i)
							f.write(cnf_clause)
					else:
						cnf_clause += "-%d%d%d 0\n" % (x,y,z) 
						f.write(cnf_clause)
						
		#AT LEAST ONE IN EACH ROW	
	f.close()
			
def main():
	puzzle = initPuzzle('input.txt')
	printPuzzle(puzzle)
	writeToCNFFile(puzzle)

if __name__ == "__main__":
	main()
