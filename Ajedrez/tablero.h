#ifndef TABLERO_H
#define TABLERO_H

#include <string>

struct Tablero {
    int n;
    int tamanoCuadro;
    int inicioX;
    int inicioY;
};

void vaciarPiezas(std::string* piezas, int n, int indice);
void colocarPiezasNegras(std::string* piezas, int indice);
void colocarPiezasBlancas(std::string* piezas, int indice);
void inicializarPiezasAjedrezEstandar(std::string* piezas, int n);
void dibujarCuadroConPieza(Tablero tablero, int fila, int columna, std::string* piezas);
void dibujarNotacionColumnas(Tablero tablero, int i);
void dibujarNotacionFilas(Tablero tablero, int i);
void mostrarTableroSinPiezas();
void mostrarTableroConPiezas();

#endif // TABLERO_H
