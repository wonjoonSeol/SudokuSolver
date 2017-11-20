#include "Sudoku.h"
#include "BestFirstSearch.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

#include <iostream>

using std::cout;
using std::endl;

bool fillBoard(Sudoku * board, const vector<string> & fillWith) {
    
    for (size_t row = 0; row < fillWith.size(); ++row) {
        for (size_t col = 0; col < fillWith.size(); ++col) {
            if (fillWith[row][col] != ' ') {
                const int setTo = std::stoi(fillWith[row].substr(col,1), nullptr, 16);
                if (!board->setSquare(row, col, setTo + 1)) {
                    cout << "Error: setSquare returned false after setting square[" << row << "][" << col << "] to " << setTo << " - this should happen as the example boards are solvable\n";
                    return false;
                }
            }
        }
    }
    
    return true;
}



bool checkAnswer(Sudoku * board, const vector<string> & answer) {
    
    for (size_t row = 0; row < answer.size(); ++row) {
        for (size_t col = 0; col < answer.size(); ++col) {
            const int setTo = std::stoi(answer[row].substr(col,1), nullptr, 16);
            if ((board->getSquare(row,col)) != setTo + 1) {
                cout << "Error: wrong answer in square[" << row << "][" << col << "]: should be " << setTo << " but is " << board->getSquare(row,col) << endl;
                return false;
            }
        }
    }
    
    return true;
}

int main() {
	clock_t tStart = clock();

    
    {
        vector<string> hardBoard{
			" 1 40   C9      ",
            "   2  9 8    5A0",
            "    F A51    C  ",
            "   FE 6 20 A D19",

            " 82    3  BC  5 ",
            "  E157 8        ",
			"D 3 C E 4 9     ",
            "       4  D  E9 ",

            " 57 90   D23   4",
			"C         1  96 ",
			" 3B61   0  E    ",
			" F80B   5    2E ",

			" 0 9 FCD  6 47 3",
			"  C3  0      B E",
			"7B 54     C   8 ",
			"     A 9 2      "};

        vector<string> answer{  
			"B1A40872C95DE3F6",
            "3762DC9184EFB5A0",
            "0D9EF3A51B768C42",
            "8C5FE46B203A7D19",

            "4827A913FEBC605D",
            "F9E157D8A602C43B",
            "DA3BC6E04195287F",
            "560C2BF438D7AE91",
			
            "E57A908C6D231FB4",
			"C24D7E3ABF180965",
			"93B6125F074EDAC8",
			"1F80BD465CA932E7",
			
			"A0198FCDE56B4723",
			"24C365079A81FBDE",
			"7BF5412ED3C0968A",
			"6ED83AB972F4510C"}; 

        unique_ptr<Sudoku> board(new Sudoku(16));
        if (!fillBoard(board.get(), hardBoard)) {
            cout << "Failed: When filling the board, setSquare() returned false\n";
            return 1;
        }
        cout << "Trying to solve hard board:\n";
        board->write(cout);
        
        BestFirstSearch search(std::move(board));
        
        Searchable * solution = search.solve();
        
        if (solution == nullptr) {
            cout << "\nFailed: Couldn't be solved\n";
            return 1;
        }
        
        Sudoku * solvedBoard = static_cast<Sudoku*>(solution);
        
        if (checkAnswer(solvedBoard, answer)) {
            cout << "\nPassed: Solution was:\n";
            solvedBoard->write(cout);
            cout << "\nNodes expanded: " << search.getNodesExpanded() << std::endl;
			//time
			printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
            return 0;
        } else {
            cout << "Failed: Solution was returned, but it was the wrong answer\n";
            return 1;
        }
    }
    
    
}
