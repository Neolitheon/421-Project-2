#written by Michael Heavenor

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
			if char_count > 81:
				print "Greater than 81 characters"
				break
		line_count += 1 
		if char_count > 81:
			break
	if char_count < 81:
		print "not enough data"
		exit(1)
	print "returning puzzle"
	printPuzzle(puzzle)
	return puzzle

def validate(row):
	for element in ['1','2','3','4','5','6','7','8','9']:
		if element not in row:
			return False
	return True

def puzzle_valid(puzzle):
	for i in range(0,9):
		row = puzzle.get_row(i)
		column = puzzle.get_column(i)
		square = array_to_string(return_square(i, (i%3)*3, puzzle.rows))
		if not validate(row) or not validate(column) or not validate(square):
			return False
	return True

def puzzle_complete(puzzle):
	for i in range(0,9):
		row_split = puzzle.get_row(i).split(',')
		for element in row_split:
			if len(element) != 1:
				return False
	return True

def s1_in_s2(s1, s2):
	for element in s1:
		if element not in s2:
			return False
	return True

def remove_restrictions(row, thresholds):
	new_row = row
	for threshold in thresholds:
		restrictions = element_restrictions(row, threshold)
		if restrictions:
			row_split = row.split(',')
			removal_list = []
			for element in restrictions[0]:
				removal_list.append(element)
			for to_remove in removal_list:
				for i in range(0,9):
					element = row_split[i]
					if element in restrictions[1]:
						continue
					if to_remove in element:
						removed_element = element.split(to_remove)
						row_split[i] = removed_element[0] + removed_element[1]
			
			new_row = array_to_string(row_split)
			break
	return new_row
					

def element_restrictions(row, threshold):
	row_split = row.split(',')
	below_thresh = []
	at_thresh = []
	for element in row_split:
		if len(element) in range(1, threshold+1):
			below_thresh.append(element)
			if len(element) == threshold:
				at_thresh.append(element)
	
	#for each in the at_thresh, check to see if there are 'threshold' number of elements in below_thresh which only contain elements from the element in at_thresh
	for s2 in at_thresh:
		match = []
		for s1 in below_thresh:
			if s1_in_s2(s1, s2):
				match.append(s1)
		if len(match) > threshold:
			print "Problem, matched more than possible"
			return False
		if len(match) < threshold:
			continue
		if len(match) == threshold:
			return (s2, match)
	return False

def array_to_string(array):
	string = ''
	for element in array:
		string = string + element + ','
	string = string[:-1]
	return string

class Puzzle(object):
	def __init__ (self, rows):
		self.rows = []
		for row in rows:
			self.rows.append(row)

	def get_row(self, row_index):
		return self.rows[row_index]

	def get_column(self, column_index):
		column = []
		for row in self.rows:
			column.append(row.split(',')[column_index])
		return array_to_string(column)

	def set_row(self, row_index, row):
		self.rows[row_index] = row

	def set_column(self, column_index, column):
		column_split = column.split(',')
		for y in range(0, 9):
			row = self.rows[y]
			row_split = row.split(',')
			row_split[column_index] = column_split[y]
			self.set_row(y, array_to_string(row_split))
	
	def set_square(self, index, square):
		square_split = square.split(',')
		for i in range(0,3):
			row = self.get_row(i+index/3*3)
			row_split = row.split(',')
			for j in range(0,3):
				row_split[(index%3)*3+j] = square_split[i*3+j]
			self.set_row(i+index/3*3, array_to_string(row_split))
		
			 

def make_full(row):
	row_string = ''
	for element in row:
		if 'x' == element:
			row_string += '123456789'
		else:
			row_string += '%s' % (element)
		row_string += ','
	return row_string[:-1]

#return all determined numbers in a string
def find_in_string(row):
	numbers = []
	for element in row.split(','):
		if len(element) == 1 and element not in numbers:
			numbers.append(element)
	return numbers

#return all possibilities within a square
def return_square(row_index, index, rows):
	numbers = []
	index_list = []
	if index in [0,1,2]:
		index_list = [0,1,2]
	if index in [3,4,5]:
		index_list = [3,4,5]
	if index in [6,7,8]:
		index_list = [6,7,8]
	row_index_list = []
	if row_index in [0,1,2]:
		row_index_list = [0,1,2]
	if row_index in [3,4,5]:
		row_index_list = [3,4,5]
	if row_index in [6,7,8]:
		row_index_list = [6,7,8]

	for row_index in row_index_list:
		row = rows[row_index]
		for index_inner in index_list:
			element = row.split(',')[index_inner]
			numbers.append(element)
	return numbers

#checks if a boxes possible values contain a unique value in the string
def possible_in_string(row, possible):
	for element in possible:
		if str(row).count(element) == 1 and element in possible:
			return element
	return possible

def find_restrictions(row_index, index, possible, rows):
	row = row_index % 3
	column = index % 3
	in_square = return_square(row_index, index, rows)
	return_list = []
	for element in possible:
		same_row = True
		same_column = True
		square_index = 0
		for square_possibility in in_square:
			if element in square_possibility:
				if square_index % 3 != column:
					same_column = False 		
				if square_index / 3 != row:
					same_row = False
			square_index += 1
		if same_row or same_column:
			return_list.append([same_row, same_column, element])
	return return_list
					

def main():

	if len(sys.argv) != 2:
		print "\nPlease specify an input file as the first argument\n"
		exit(1)
	filename = sys.argv[1]

	#convert to my specified data structure for puzzle	
	rows_input = initPuzzle(filename)
	rows = []
	for row in rows_input:
		rows.append(make_full(row))

	puzzle = Puzzle(rows)
	last_puzzle = []
	for row in puzzle.rows:
		last_puzzle.append(row)
	
	puzzle_stack = []

	solved = False
	itCount = 0
	while not solved:
	#	print "\t\t%s\n" % str(puzzle_stack)
		itCount += 1
	#	for i in range(0,9):
	#		print puzzle.get_row(i)
	#	print "\nStarting Iteration %d\n" % (itCount)
		for i in range(0,9):
			row_count = i
			for j in range(0,9):
				index_count = j
				row_split = puzzle.get_row(row_count).split(',')
				element = row_split[j]
	
				if len(element) != 1:
					
					#find all determined numbers in the row, column, and square
					numbers_line = find_in_string(puzzle.get_row(row_count))
					numbers_column = find_in_string(puzzle.get_column(index_count))
					numbers_square = find_in_string(array_to_string(return_square(row_count, index_count, puzzle.rows)))


					all_numbers = numbers_line
					for element in numbers_column:
						if element not in all_numbers:
							all_numbers.append(element)
					for element in numbers_square:
						if element not in all_numbers:
							all_numbers.append(element)
	
					#remove all the known determined numbers to give possibilities for current box
					old_possibilities = puzzle.get_row(i).split(',')[j]
					NUMBERS = []
					for number in old_possibilities:
						NUMBERS.append(number)
					for element in all_numbers:
						if element in NUMBERS:
							NUMBERS.remove(element)
	
					#turn array into a string
					NUMBERS_STRING = ''
					for element in NUMBERS:
						NUMBERS_STRING += element

		
					#check to see if there are any unique values in the row, column, or square
					NUMBERS_STRING = possible_in_string(array_to_string(return_square(row_count, index_count, puzzle.rows)), NUMBERS_STRING)
					NUMBERS_STRING = possible_in_string(puzzle.get_row(row_count), NUMBERS_STRING)
					NUMBERS_STRING = possible_in_string(puzzle.get_column(index_count), NUMBERS_STRING)
			
					row_split[index_count] = NUMBERS_STRING
					puzzle.set_row(row_count, array_to_string(row_split))
					
					list_restrictions = find_restrictions(row_count, index_count, NUMBERS_STRING, puzzle.rows)
					if list_restrictions != []:
						for restrictions in list_restrictions:
							element_to_remove = restrictions[2]

							if restrictions[0]:
								row_split = puzzle.get_row(row_count).split(',')	
								#eleminate all in row
								for x in range(0,9):
									if element_to_remove in row_split[x] and x/3 != index_count/3:
										removed_element = row_split[x].split(element_to_remove)
										row_split[x] = removed_element[0] + removed_element[1]
										puzzle.set_row(row_count, array_to_string(row_split))
							if restrictions[1]:
								#eliminate all in column
								column = puzzle.get_column(index_count).split(',')
								for y in range(0, 9):
									if element_to_remove in column[y] and y/3 != row_count/3:
										removed_element = column[y].split(element_to_remove)
										column[y] = removed_element[0] + removed_element[1]
								puzzle.set_column(index_count, array_to_string(column))
				
		
		for i in range(0,9):
			row = puzzle.get_row(i)
			new_row = remove_restrictions(row, [2,3,4,5])
			if row != new_row:
				puzzle.set_row(i, new_row)
		for i in range(0,9):
			column = puzzle.get_column(i)
			new_column = remove_restrictions(column, [2,3,4,5])
			if column != new_column:
				puzzle.set_column(i, new_column)
		for i in range(0,9):
			square = array_to_string(return_square(i, (i%3)*3, puzzle.rows))
			new_square = remove_restrictions(square, [2,3,4,5])
			if square != new_square:
				puzzle.set_square(i, new_square)
		
		if not puzzle_valid(puzzle):
			need_to_pop = True
			while need_to_pop:
				if puzzle_stack == []:
	#				print "not a valid puzzle"
					solved = True
	#			print "not valid, backtracking\n"
				popped = puzzle_stack.pop()
				pop_args = popped[0]
				pop_puzzle = popped[1]
				row_index = pop_args[0]
				column_index = pop_args[1]
				element_index = pop_args[2]
			
				row_split = pop_puzzle[row_index].split(',')
				if len(row_split[column_index]) > (element_index+1):
					need_to_pop = False
					row_split[column_index] = row_split[column_index][element_index+1]
					puzzle_stack.append([[row_index,column_index,element_index+1], pop_puzzle])
					
					for i in range(0,9):
						puzzle.set_row(i, pop_puzzle[i])
					puzzle.set_row(row_index, array_to_string(row_split))

					last_puzzle = []
					for row in puzzle.rows:
						last_puzzle.append(row)
		else:			

			if puzzle_complete(puzzle):
				solved = True
	#			print "Solved after %d iterations" % (itCount)
			
			if last_puzzle == puzzle.rows:
				changed = False
				#print "\t***adding to stack***\n"
				for i in range(0,9):
					if changed:
						break
					row = puzzle.get_row(i)
					row_split = row.split(',')
					for j in range (0,9):
						element = row_split[j]
						if len(element) != 1:
							row_split[j] = element[0]
							puzzle.set_row(i, array_to_string(row_split))
							puzzle_stack.append([[i,j,0], last_puzzle])
							changed = True
							last_puzzle = []
							for row in puzzle.rows:
								last_puzzle.append(row)
							break
							
			else:
				last_puzzle = []
				for row in puzzle.rows:
					last_puzzle.append(row)
	
	#for row in puzzle.rows:
	#	print row

if __name__ == "__main__":
	main()
