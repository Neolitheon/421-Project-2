import sys

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
	char_count = 0
	numList = []
	for line in lines:
		for char in line:
			char = char.strip()
			if char == "":
				continue
			if char in blank:
				char = '0'
			try:
				verify = int(char)
				numList.append(verify)
				char_count += 1
			except:
				print "fail"
				exit(1)
			if len(numList) == 9:
				puzzle.append(numList)
				numList = []
		line_count += 1 
	if char_count < 81:
		print "not enough data"
		exit(1)
	return puzzle

def writeToCNFFile(puzzle, min_or_ext):
	ext = False
	if min_or_ext == 'ext':
		ext = True

	f = open('output.cnf', 'w')
	sum = 0
	for x in range (1,10):
		for y in range (1,10):
			if puzzle[x-1][y-1] != 0:
				sum += 1
	sum += 8748
	if ext:
		sum += 2916
	f.write("p cnf 729 %d\n" % sum)
	#Minimum
	#VARIABLES
	for x in range (1,10):
		for y in range (1,10):
			if puzzle[x-1][y-1] != 0:
				cnf_clause = "%d%d%d 0\n" % (x,y,puzzle[x-1][y-1]) 
				f.write(cnf_clause)
				
	#AT LEAST ONE NUMBER
	f.write("c There is at least one number in each entry\n")
	for x in range (1, 10):
		for y in range (1, 10):
			cnf_clause = ""
			for z in range (1, 10):
				cnf_clause += "%d%d%d " % (x,y,z) 
			cnf_clause += "0\n"
			f.write(cnf_clause)

	f.write("c At most once in each column\n")
	#At most once in each column
	for y in range(1,10):
		for z in range(1,10):
			for x in range(1,9):
				for i in range(1+x,10):
					cnf_clause = "-%d%d%d -%d%d%d 0\n" % (x,y,z,i,y,z) 
					f.write(cnf_clause)

	f.write("c At most once in each row\n")
	#at most once in each row
	for x in range(1,10):
	    for z in range(1,10):
	        for y in range(1,9):
				for i in range(1+y,10):
					cnf_clause = "-%d%d%d -%d%d%d 0\n" % (x,y,z,x,i,z) 
					f.write(cnf_clause)

	f.write("c At most once in each 3x3 grid\n")
	sum = 0	#at most once in each box
	for z in range(1,10):
		for i in range(0,3):
			for j in range(0,3):
				for x in range(1,4):
					for y in range(1,4):
						for k in range(1+y,4):
							cnf_clause = "-"+str(3*i+x)+str(3*j+y)+str(z)+" -"+str(3*i+x)+str(3*j+k)+str(z)+" 0\n"
							f.write(cnf_clause)
	for z in range(1,10):
	    for i in range(0,3):
	        for j in range(0,3):
	            for y in range(1,4):
	                for x in range(1,4):
	                    for k in range(1+x,4):
	                        for l in range(1,4):
								cnf_clause = "-"+str(3*i+x)+str(3*j+y)+str(z)+" -"+str(3*i+k)+str(3*j+l)+str(z)+" 0\n"
								f.write(cnf_clause)  

	#Extended
	if ext:
		#AT MOST ONE NUMBER
		f.write("c There is at most one number in each entry\n")
		for x in range (1, 10):
			for y in range (1, 10):
				for z in range (1, 9):
					for i in range (z, 10):
						cnf_clause = "-%d%d%d -%d%d%d 0\n" % (x,y,z,x,y,i)
						f.write(cnf_clause)
						
		#AT LEAST ONE IN EACH ROW
		f.write("c A number appears at least once in each row\n")
		for y in range (1, 10):
			for z in range (1, 10):
				cnf_clause = ""
				for x in range (1, 10):
						cnf_clause += "%d%d%d " % (x,y,z) 
				cnf_clause += "0\n"
				f.write(cnf_clause)
				
		#AT LEAST ONE IN EACH COLUMN
		f.write("c A number appears at least once in each column\n")
		for x in range (1, 10):
			for z in range (1, 10):
				cnf_clause = ""
				for y in range (1, 10):
						cnf_clause += "%d%d%d " % (x,y,z) 
				cnf_clause += "0\n"
				f.write(cnf_clause)
		
		#AT LEAST ONE NUMBER PER 3x3 	
		f.write("c Each number appears at least once in each 3x3 grid\n")
		for z in range(1,10):
			for i in range(0,3):
				for j in range(0,3):
					cnf_clause = ""
					for x in range(1,4):
						for y in range(1,4):
							cnf_clause += "%d%d%d " %((3*i+x),(3*j+y),(z))
					cnf_clause += "0\n"
					f.write(cnf_clause)
	f.close()
			
def main():
	min_or_ext_list = ['min', 'ext']
	if len(sys.argv) != 3:
		print("Please put in the correct arguments: <filename> <min/ext>")
		exit(1)
	if sys.argv[2] not in min_or_ext_list:
		print("Please make second argument 'min' or 'ext'")
	
	input_file = sys.argv[1]
	min_or_ext = sys.argv[2]

	puzzle = initPuzzle(input_file)
	printPuzzle(puzzle)
	writeToCNFFile(puzzle, min_or_ext)

if __name__ == "__main__":
	main()
