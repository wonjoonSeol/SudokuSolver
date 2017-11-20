**SudokuSolver**

Here is an automated test report for your work so far on assignment 5. Please note that this is not the mark for your work; it is provided only in the hope that it is useful in developing your solution. Passing these tests does not guarantee your code is free from bugs: after the deadline, your code will be marked against a different, more thorough set of test cases.

Part a and b: Sudoku board

Sudoku.h compiled, running tests.

getSquare() return -1 for all squares in an empty board: passed
Can solve the easy example puzzle test case you were given, by repeatedly calling setSquare: passed
Can solve https://www.theguardian.com/lifeandstyle/2013/may/06/sudoku-2491-easy, by repeatedly calling setSquare: passed

Total tests passed for parts a and b:
3 out of 3

Part c: Searching for a solution

Sudoku inherits Searchable; and isSolution() returns true for a solved board: passed
The initial board for the given hard problem test has some successors: passed
The given hard problem test could be solved, and had the right solution: passed

Total tests passed for part c:
3 out of 3

Part d: Advanced

The following is a benchmarking result to give you an idea of the efficiency of your solution so far. Note it doesn't check for uninitialised values -- you must run these tests yourself, as the server load would otherwise be excessive.

How many hard sudoku puzzles can be solved in 10 seconds?: 95 out of 95
