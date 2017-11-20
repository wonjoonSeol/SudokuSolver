#include "Sudoku.h"
#include "BestFirstSearch.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

#include <iostream>

using std::cout;
using std::endl;


#include <set>
using std::set;

bool fillBoard(Sudoku * board, const vector<vector<int> > & fillWith, ostream & diagnostic) {
    
    for (size_t row = 0; row < fillWith.size(); ++row) {
        for (size_t col = 0; col < fillWith.size(); ++col) {
            if (fillWith[row][col] != 0) {
                const int setTo = fillWith[row][col];
                if (!board->setSquare(row, col, setTo)) {
                    diagnostic << ", setSquare returned false after setting square[" << row << "][" << col << "] to " << setTo << " - this should not happen as the example boards are solvable\n";
                    return false;
                }
            }
        }
    }
        
    return true;
}


bool checkAnswer(Sudoku * board, const vector<string> & answer, ostream & diagnostic) {
    
    for (size_t row = 0; row < answer.size(); ++row) {
        for (size_t col = 0; col < answer.size(); ++col) {
            const int setTo = std::stoi(answer[row].substr(col,1));
            if (board->getSquare(row,col) != setTo) {
                diagnostic << ", wrong answer in square[" << row << "][" << col << "]: should be " << setTo << " but is " << board->getSquare(row,col) << endl;
                return false;
            }
        }
    }
        
    return true;
}

bool consistent(Sudoku * board, const int boardSize, const int boxSize) {
    for (int i = 0; i < boardSize; ++i) {
        set<int> onRow;
        for (int j = 0; j < boardSize; ++j) {
            onRow.insert(board->getSquare(i,j));
        }
        if (onRow.size() != 9) {
            return false;
        }
    }
    
    for (int i = 0; i < boardSize; ++i) {
        set<int> onRow;
        for (int j = 0; j < boardSize; ++j) {
            onRow.insert(board->getSquare(j,i));
        }
        if (onRow.size() != 9) {
            return false;
        }
    }
    for (int masteri = 0; masteri < boardSize; masteri += boxSize) {
        for (int masterj = 0; masterj < boardSize; masterj += boxSize) {
            set<int> onRow;
            for (int i = masteri; i < masteri + boxSize; ++i) {
                for (int j = masterj; j < masterj + boxSize; ++j) {
                    onRow.insert(board->getSquare(i,j));
                }
            }
            if (onRow.size() != 9) {
                return false;
            }
        }
    }
    return true;
}


int main() {
	clock_t tStart = clock();
    
    auto & diagnostic = std::cout;
    int solvedCount = 0;
    {        
        vector<vector<vector<int> > > boards{
            {
                {4,0,0,0,0,0,8,0,5},
                {0,3,0,0,0,0,0,0,0},
                {0,0,0,7,0,0,0,0,0},
                {0,2,0,0,0,0,0,6,0},
                {0,0,0,0,8,0,4,0,0},
                {0,0,0,0,1,0,0,0,0},
                {0,0,0,6,0,3,0,7,0},
                {5,0,0,2,0,0,0,0,0},
                {1,0,4,0,0,0,0,0,0}
            },{
                {5,2,0,0,0,6,0,0,0},
                {0,0,0,0,0,0,7,0,1},
                {3,0,0,0,0,0,0,0,0},
                {0,0,0,4,0,0,8,0,0},
                {6,0,0,0,0,0,0,5,0},
                {0,0,0,0,0,0,0,0,0},
                {0,4,1,8,0,0,0,0,0},
                {0,0,0,0,3,0,0,2,0},
                {0,0,8,7,0,0,0,0,0}
            },{
                {6,0,0,0,0,0,8,0,3},
                {0,4,0,7,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,5,0,4,0,7,0},
                {3,0,0,2,0,0,0,0,0},
                {1,0,6,0,0,0,0,0,0},
                {0,2,0,0,0,0,0,5,0},
                {0,0,0,0,8,0,6,0,0},
                {0,0,0,0,1,0,0,0,0}
            },{
                {4,8,0,3,0,0,0,0,0},
                {0,0,0,0,0,0,0,7,1},
                {0,2,0,0,0,0,0,0,0},
                {7,0,5,0,0,0,0,6,0},
                {0,0,0,2,0,0,8,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,1,0,7,6,0,0,0},
                {3,0,0,0,0,0,4,0,0},
                {0,0,0,0,5,0,0,0,0}
            },{
                {0,0,0,0,1,4,0,0,0},
                {0,3,0,0,0,0,2,0,0},
                {0,7,0,0,0,0,0,0,0},
                {0,0,0,9,0,0,0,3,0},
                {6,0,1,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,8,0},
                {2,0,0,0,0,0,1,0,4},
                {0,0,0,0,5,0,6,0,0},
                {0,0,0,7,0,8,0,0,0}
            },{
                {0,0,0,0,0,0,5,2,0},
                {0,8,0,4,0,0,0,0,0},
                {0,3,0,0,0,9,0,0,0},
                {5,0,1,0,0,0,6,0,0},
                {2,0,0,7,0,0,0,0,0},
                {0,0,0,3,0,0,0,0,0},
                {6,0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,7,0,4},
                {0,0,0,0,0,0,0,3,0}
            },{
                {6,0,2,0,5,0,0,0,0},
                {0,0,0,0,0,3,0,4,0},
                {0,0,0,0,0,0,0,0,0},
                {4,3,0,0,0,8,0,0,0},
                {0,1,0,0,0,0,2,0,0},
                {0,0,0,0,0,0,7,0,0},
                {5,0,0,2,7,0,0,0,0},
                {0,0,0,0,0,0,0,8,1},
                {0,0,0,6,0,0,0,0,0}
            },{
                {0,5,2,4,0,0,0,0,0},
                {0,0,0,0,7,0,1,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,8,0,2,0,0,0},
                {3,0,0,0,0,0,6,0,0},
                {0,9,0,5,0,0,0,0,0},
                {1,0,6,0,3,0,0,0,0},
                {0,0,0,0,0,0,0,8,9},
                {7,0,0,0,0,0,0,0,0}
            },{
                {6,0,2,0,5,0,0,0,0},
                {0,0,0,0,0,4,0,3,0},
                {0,0,0,0,0,0,0,0,0},
                {4,3,0,0,0,8,0,0,0},
                {0,1,0,0,0,0,2,0,0},
                {0,0,0,0,0,0,7,0,0},
                {5,0,0,2,7,0,0,0,0},
                {0,0,0,0,0,0,0,8,1},
                {0,0,0,6,0,0,0,0,0}
            },{
                {0,9,2,3,0,0,0,0,0},
                {0,0,0,0,8,0,1,0,0},
                {0,0,0,0,0,0,0,0,0},
                {1,0,7,0,4,0,0,0,0},
                {0,0,0,0,0,0,0,6,5},
                {8,0,0,0,0,0,0,0,0},
                {0,6,0,5,0,2,0,0,0},
                {4,0,0,0,0,0,7,0,0},
                {0,0,0,9,0,0,0,0,0}
            }            
        };
        
        for (const auto & currBoard : boards) {
            unique_ptr<Sudoku> board(new Sudoku(9));

            
            if (!fillBoard(board.get(), currBoard, diagnostic)) {
                return 1;
            }

            Searchable *sCheck = board.get();
            if (sCheck->isSolution()) {
                
                if (!consistent(board.get(),9,3)) {
                    diagnostic << ", an invalid solution was returned for a board\n";
                    bool comma = false;
                    diagnostic << "  {";
                    for (auto & r : currBoard) {
                        if (comma) {
                            diagnostic << ",\n   ";
                        }
                        diagnostic << "  \"";
                        for (auto & c : r) {
                            if (c == 0) {
                                diagnostic << " ";
                            } else {
                                diagnostic << c;
                            }
                        }
                        diagnostic << "\"";
                        comma = true;
                    }
                    diagnostic << "}\n";
                    return 1;
                }   
            } else {
                
                BestFirstSearch search(std::move(board));
                
                Searchable * solution = search.solve();
                
                if (solution == nullptr) {
                    diagnostic << ", a board couldn't be solved -- solution was nullptr\n";
                    bool comma = false;
                    diagnostic << "  {";
                    for (auto & r : currBoard) {
                        if (comma) {
                            diagnostic << ",\n   ";
                        }
                        diagnostic << "  \"";
                        for (auto & c : r) {
                            if (c == 0) {
                                diagnostic << " ";
                            } else {
                                diagnostic << c;
                            }
                        }
                        diagnostic << "\"";
                        comma = true;
                    }
                    diagnostic << "}\n";
                    return 1;
                }
                
                Sudoku * solvedBoard = static_cast<Sudoku*>(solution);
                
                if (!consistent(solvedBoard,9,3)) {
                    diagnostic << ", an invalid solution was returned for a board\n";
                    bool comma = false;
                    diagnostic << "  {";
                    for (auto & r : currBoard) {
                        if (comma) {
                            diagnostic << ",\n   ";
                        }
                        diagnostic << "  \"";
                        for (auto & c : r) {
                            if (c == 0) {
                                diagnostic << " ";
                            } else {
                                diagnostic << c;
                            }
                        }
                        diagnostic << "\"";
                        comma = true;
                    }
                    diagnostic << "}\n";
                    return 1;
                }
                
                /*if (!checkAnswer(solvedBoard, answer, diagnostic)) {
                    return 1;
                }*/
            }
                        
            ++solvedCount;
            diagnostic << solvedCount << " out of 10\n";
            diagnostic.flush();
            
            cout << "Solved\n";
        }
 			printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }    
    return 0;
}
