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

bool provjera(table sudoku, int p, int k, int a, int b, int number){
    std::vector<int> provjera;
    provjera.push_back(number);
    for(int i = p; i < a; i++){
        for(int j = k; j < b; j++){
            if(sudoku.at(i).at(j) != 0)
                provjera.push_back(sudoku.at(i).at(j));
        }
    }
    std::sort(provjera.begin(), provjera.end());
    for(int i = 0; i < provjera.size() - 1; i++)
        if(provjera.at(i) == provjera.at(i + 1)) return false;
    return true;
}

bool check(table sudoku, int rowPosition, int columnPosition, int number){
    for(int i = 0; i < sudoku.size(); i++)
        if(i != columnPosition)
            if(number == sudoku[rowPosition][i]) return false;

    for(int i = 0; i < sudoku.size(); i++)
        if(i != rowPosition)
            if(number == sudoku[i][columnPosition]) return false;

    //devet 3x3 matrice provjerit
    if(rowPosition < 3 && columnPosition < 3){
        return provjera(sudoku, 0, 0, 3, 3, number);
    } else if(rowPosition < 3 && (columnPosition > 2 && columnPosition < 6)){
        return provjera(sudoku, 0, 3, 3, 6, number);
    } else if(rowPosition < 3 && (columnPosition > 5 && columnPosition < 10)){
        return provjera(sudoku, 0, 6, 3, 9, number);
    } else if((rowPosition > 2 && rowPosition < 6) && columnPosition < 3){
        return provjera(sudoku, 3, 0, 6, 3, number);
    } else if((rowPosition > 2 && rowPosition < 6) && (columnPosition > 2 && columnPosition < 6)){
        return provjera(sudoku, 3, 3, 6, 6, number);
    } else if((rowPosition > 2 && rowPosition < 6) && (columnPosition > 5 && columnPosition < 9)){
        return provjera(sudoku, 3, 6, 6, 9, number);
    } else if((rowPosition > 5 && rowPosition < 9) && columnPosition < 3){
        return provjera(sudoku, 6, 0, 9, 3, number);
    } else if((rowPosition > 5 && rowPosition < 9) && (columnPosition > 2 && columnPosition < 6)){
        return provjera(sudoku, 6, 3, 9, 6, number);
    } else if((rowPosition > 5 && rowPosition < 9) && (columnPosition > 5 && columnPosition < 9)){
        return provjera(sudoku, 6, 6, 9, 9, number);
    }
    return true;
}
bool fullSudokuCheck(table sudoku){
    for(int i = 0; i < sudoku.size(); i++)
        for(int j = 0; j < sudoku.size(); j++)
            if(sudoku[i][j] == 0) return false;
    return true;
}

void Solver(table &sudoku, std::vector<std::pair<int, int>> slots, int position){
    if(fullSudokuCheck(sudoku)) exit;//return sudoku;
    while(position < slots.size()){
        if(sudoku[slots[position].first][slots[position].second] == 9){
            sudoku[slots[position].first][slots[position].second] = 0;
            position--; continue;
        }
        for(int i = sudoku[slots[position].first][slots[position].second] + 1; i < 10; i++){
            if(check(sudoku, slots[position].first, slots[position].second, i)){
                sudoku[slots[position].first][slots[position].second] = i;
                break;
            } else if (i == 9) {
                sudoku[slots[position].first][slots[position].second] = 0;
                position-=2;
            }
        }
        position++;
    }
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
    try{
        Solver(probniSudoku, emptySlots, 0);
    } catch(...){
        return 0;
    }
    Print(probniSudoku);
    return 0;
}
