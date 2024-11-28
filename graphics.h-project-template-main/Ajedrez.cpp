#include <graphics.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8; // Tamaño del tablero

void drawBoard();
void drawQueen(int row, int col);
bool isSafe(int board[BOARD_SIZE][BOARD_SIZE], int row, int col);
bool solveNQueens(int board[BOARD_SIZE][BOARD_SIZE], int col, vector<string>& moves);
void saveMovesToFile(const vector<string>& moves);

int main() {
    initwindow(600, 600); // Inicializar la ventana gráfica
    
    drawBoard();

    int board[BOARD_SIZE][BOARD_SIZE] = {0}; // Inicializar el tablero
    vector<string> moves;
    
    if (solveNQueens(board, 0, moves)) {
        saveMovesToFile(moves);
    } else {
        cout << "No se encontró una solución" << endl;
    }
    
    getch(); // Esperar a que el usuario presione una tecla
    closegraph(); // Cerrar la ventana gráfica
    return 0;
}

void drawBoard() {
    int cellSize = 60;
    setcolor(WHITE);
    for (int i = 0; i <= BOARD_SIZE; ++i) {
        line(i * cellSize, 0, i * cellSize, BOARD_SIZE * cellSize);
        line(0, i * cellSize, BOARD_SIZE * cellSize, i * cellSize);
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if ((i + j) % 2 == 0) {
                setfillstyle(SOLID_FILL, WHITE);
            } else {
                setfillstyle(SOLID_FILL, DARKGRAY); // Usa DARKGRAY en lugar de BLACK para mejor visibilidad
            }
            floodfill((i * cellSize) + cellSize / 2, (j * cellSize) + cellSize / 2, WHITE);
        }
    }
}

void drawQueen(int row, int col) {
    int cellSize = 60;
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    floodfill((col * cellSize) + cellSize / 2, (row * cellSize) + cellSize / 2, RED);
}

bool isSafe(int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    for (int i = row, j = col; j >= 0 && i < BOARD_SIZE; i++, j--) {
        if (board[i][j]) return false;
    }
    return true;
}

bool solveNQueens(int board[BOARD_SIZE][BOARD_SIZE], int col, vector<string>& moves) {
    if (col >= BOARD_SIZE) {
        return true;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            drawQueen(i, col);
            moves.push_back("Queen placed at row " + to_string(i) + " and column " + to_string(col));
            if (solveNQueens(board, col + 1, moves)) {
                return true;
            }
            board[i][col] = 0; // Backtrack
        }
    }
    return false;
}

void saveMovesToFile(const vector<string>& moves) {
    ofstream outFile("moves.txt");
    for (const auto& move : moves) {
        outFile << move << endl;
    }
    outFile.close();
}
