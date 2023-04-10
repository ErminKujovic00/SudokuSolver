/*          Sudoku Solver       */

#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm>

using table = std::vector<std::vector<int>>;

void Print(table sudoku){
    for(int i = 0; i < sudoku.size(); i++){
        if(i % 3 == 0)
            for(int k = 0; k < 43; k++) std::cout << "-";
        std::cout << std::endl;
        for(int j = 0; j < sudoku.size(); j++){
            if(j % 3 == 0) std::cout << "| " << std::setw(2) << sudoku[i][j] << std::setw(2) << " ";
            else std::cout << std::setw(2) << sudoku[i][j] << std::setw(2) << " ";
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    for(int k = 0; k < 43; k++) std::cout << "-";
    std::cout << std::endl;
}

int main(){
    table probniSudoku(9, std::vector<int> (9, 0));
    std::vector<std::pair<int, int>> emptySlots;
    std::cout << "Input sudoku 9x9 (zero for empty space): " << std::endl;
    for(int i = 0; i < probniSudoku.size(); i++){
        std::cout << "Row " << i + 1 << ": ";
        for(int j = 0; j < probniSudoku.size(); j++){
            int number;
            std::cin >> number;
            if(number < 0 || number > 9){
                std::cout << "Number must be between 0 - 9 (zero for empty space). Input again: ";
                j--;
            } else {
                probniSudoku[i][j] = number;
            }
        }
    }
    for(int i = 0; i < probniSudoku.size(); i++){
        for(int j = 0; j < probniSudoku.size(); j++){
            if(probniSudoku[i][j] == 0) emptySlots.push_back(std::make_pair(i, j));
        }
    }
    Print(probniSudoku);
    return 0;
}
