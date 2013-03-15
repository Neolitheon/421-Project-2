421-Project-2
=============

Suduko SAT solver

FIRST PART:

    creating a program that takes the input, converts it into SAT readable format.

Input:

    9x9 = 81 characters. 1-9, and a "wild card", which maybe anything from A-Z or !-)
    May have arbitrary whitespace.

Output:

Standard SAT-challenge formula

    c This is a Comment
    p cnf <# variables> <# clauses>
    <list of clauses>

SECOND PART:

Take the output of the FIRST PART, run performance on is vs these three things:
 A comparison of performance for

    1. Different encodings  
    2. Different SAT solvers
    3. Non-SAT approaches


1) Encodings:
  Minimal:
  
    -There is at least one number in each entry
    -Each number appears at most once in each row
    -Each number appears at most once in each column
    -Each number appears at most once in each 3x3 sub-grid
    
  Extended:
    
    -There is at most one number in each entry
    -Each number appears at least once in each row
    -Each number appears at least once in each column
    -Each number appears at least once in each 33 sub-grid
  
  Are there any other Encodings?
    
2) SAT Solvers:

    List of them here: 
      http://www.cs.ubc.ca/~hoos/SATLIB/index-ubc.html

3) Non-Sat Sovlers:

    At very least, http://norvig.com/sudoku.html
    Any other suduko solvers we can find.
    
Performance: Bassed off Average Speed & Number of trials completed. So just a normal table...? Check out nodvigs analysis. Mean Time, Avg Time, STD deviation.
