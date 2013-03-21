import os
import sys
import timeit

#global variable of filenames?
filename = 'input.txt'

def main():
	NONSAT_HELPER()
	SAT_HELPER()

def NONSAT_HELPER():
	arg = 'NONSAT_RUN(\'%s\')' % filename
	t = timeit.Timer(arg, 'from __main__ import NONSAT_RUN')
	times = []
	iterations = 20
	for i in range(0, iterations):
		elapsed = (1000000 * t.timeit(number=1))
		times.append(elapsed)
	times.sort()
	print "NONSAT takes %0.3f microseconds/pass" % times[0]
	

def NONSAT_RUN(filename):
	command = 'python non-sat-solver.py %s' % filename
	os.system(command)

def SAT_HELPER():
	command = 'python app.py %s min' % filename
	os.system(command) 

	output = 'output.cnf'
	arg = 'SAT_RUN(\'%s\')' % output
	t = timeit.Timer(arg, 'from __main__ import SAT_RUN')
	times = []
	iterations = 20
	for i in range(0, iterations):
		elapsed = (1000000 * t.timeit(number=1))
		times.append(elapsed)
	times.sort()
	print "SAT takes %0.3f microseconds/pass" % elapsed
	

def SAT_RUN(output):
	pass
	#something like this
	#command = 'python sat-solver.py %s' % output
	#os.system(command)

if __name__ == "__main__":
	main()


