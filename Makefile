basic: Sudoku.h BasicSudoku.cpp
	g++ -Wall -g -std=c++11 -o BasicSudoku BasicSudoku.cpp

best: Sudoku.h BestFirstSearch.h BestFSSudoku.cpp
	g++ -Wall -g -std=c++11 -o BestFSSudoku BestFSSudoku.cpp

breadth: Sudoku.h BreadthFSSudoku.cpp
	g++ -Wall -g -std=c++11 -o BreadthFSSudoku BreadthFSSudoku.cpp

tenboard: Sudoku.h TenBoards.cpp
	g++ -Wall -g -std=c++11 -o TenBoards TenBoards.cpp

16x16: Sudoku.h	TenBoards.cpp
	g++ -Wall -g -std=c++11 -o 16x16BestFSHard 16x16BestFSHard.cpp

all: basic best breadth tenboard
