#include "sudoku.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string>

Sudoku::Sudoku() {
    grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    fixed.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
}

void Sudoku::initializeGraphics() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(WINDOW_SIZE / 2 - 50, 10, "Sudoku 9x9");
}

void Sudoku::drawGrid() {
    setbkcolor(WHITE); // Fondo blanco
    cleardevice(); // Limpiar pantalla con color de fondo

    setcolor(BLACK); // Líneas de la cuadrícula en negro
    for (int i = 0; i <= GRID_SIZE; i++) {
        int thickness = (i % SUB_GRID_SIZE == 0) ? 3 : 1;
        setlinestyle(SOLID_LINE, 0, thickness);
        line(i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_SIZE);
        line(0, i * CELL_SIZE, WINDOW_SIZE, i * CELL_SIZE);
    }
}

void Sudoku::drawNumbers() {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != 0) {
                char num[2];
                sprintf(num, "%d", grid[row][col]);
                setcolor(fixed[row][col] ? DARKGRAY : BLACK); // Números fijos en gris oscuro, otros en negro
                outtextxy(col * CELL_SIZE + CELL_SIZE / 2 - 5, row * CELL_SIZE + CELL_SIZE / 2 - 5, num);
            }
        }
    }
}

bool Sudoku::isValid(int row, int col, int num) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }
    int boxRow = row - row % SUB_GRID_SIZE;
    int boxCol = col - col % SUB_GRID_SIZE;
    for (int i = 0; i < SUB_GRID_SIZE; i++) {
        for (int j = 0; j < SUB_GRID_SIZE; j++) {
            if (grid[boxRow + i][boxCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solveSudoku() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= GRID_SIZE; num++) {
                    if (isValid(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku()) {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::generatePuzzle() {
    srand(time(0));
    solveSudoku();

    int clues = 30; // Número de pistas iniciales
    while (clues > 0) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        if (grid[row][col] != 0 && !fixed[row][col]) {
            fixed[row][col] = true;
            clues--;
        }
    }
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (!fixed[i][j]) {
                grid[i][j] = 0;
            }
        }
    }
}

void Sudoku::playGame() {
    int x, y, num;
    bool gameOver = false;

    generatePuzzle();

    while (!gameOver) {
        cleardevice();
        drawGrid();
        drawNumbers();

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            int col = x / CELL_SIZE;
            int row = y / CELL_SIZE;

            if (col < GRID_SIZE && row < GRID_SIZE && !fixed[row][col]) {
                char input;
                do {
                    input = getch(); // Captura la entrada del teclado
                } while (input < '0' || input > '9'); // Asegura que la entrada sea un número válido

                num = input - '0';

                if (num == 0 || isValid(row, col, num)) {
                    grid[row][col] = num;
                }
            }
        }

        gameOver = true;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (grid[i][j] == 0) {
                    gameOver = false;
                    break;
                }
            }
            if (!gameOver) break;
        }

        delay(50);
    }

    outtextxy(WINDOW_SIZE / 2 - 100, WINDOW_SIZE + 10, "¡Felicidades! Has ganado.");
    getch();
}

