#ifndef SUDOKU_H
#define SUDOKU_H

#include <graphics.h>
#include <vector>

const int GRID_SIZE = 9;
const int SUB_GRID_SIZE = 3;
const int CELL_SIZE = 50;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

class Sudoku {
private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> fixed;

    void drawGrid();
    void drawNumbers();
    bool isValid(int row, int col, int num);
    bool solveSudoku();

public:
    Sudoku();
    void initializeGraphics();
    void playGame();
    void generatePuzzle();
};

#endif // SUDOKU_H