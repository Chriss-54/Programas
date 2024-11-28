#ifndef NREINAS_H
#define NREINAS_H

struct Movimiento {
    int fila;
    int columna;
    char accion[10];
};

void agregarMovimiento(int fila, int columna, const char* accion, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos);
void guardarMovimientosEnArchivo(const char* nombreArchivo, Movimiento* movimientos, int numMovimientos);
void inicializarPosicionesReinas(int* posicionReinas, int n, int indice);
bool esSeguroColocarReina(int* posicionReinas, int filaActual, int columna);
void encontrarTodasLasSoluciones(int* posicionReinas, int filaActual, int n, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos);
int seleccionarIndiceSolucionAleatoria();
void dibujarReina(int x, int y, int tamanoCuadro);
void ejecutarNReinas(int n);

#endif // NREINAS_H
