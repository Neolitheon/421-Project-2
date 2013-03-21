import os
import sys
import timeit

def main():
	NONSAT_HELPER()

def NONSAT_HELPER():
	filename = 'input.txt'
	arg = 'NONSAT_RUN(\'%s\')' % filename
	t = timeit.Timer(arg, 'from __main__ import NONSAT_RUN')
	elapsed = (1000000 * t.timeit(number=20)/20)
	print "NONSAT takes %0.3f microseconds/pass" % elapsed
	

def NONSAT_RUN(filename):
	command = 'python non-sat-solver.py %s' % filename
	os.system(command)

if __name__ == "__main__":
	main()


