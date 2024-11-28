#include "nreinas.h"
#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include <graphics.h> // Incluimos la librería gráfica

using namespace std;

// Definición de variables globales
Movimiento** movimientosPorSolucion = nullptr; // Arreglo de arreglos para almacenar movimientos por solución
int* numMovimientosPorSolucion = nullptr; // Arreglo para almacenar el número de movimientos por solución 
int capacidadSoluciones = 0;
int numSoluciones = 0;
int** soluciones = nullptr; // Arreglo de arreglos para almacenar todas las soluciones

// Función para añadir un movimiento al arreglo
void agregarMovimiento(int fila, int columna, const char* accion, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos) {
    if (numMovimientos >= capacidadMovimientos) {
        int nuevaCapacidad = capacidadMovimientos == 0 ? 10 : capacidadMovimientos * 2;
        movimientos = (Movimiento*)realloc(movimientos, nuevaCapacidad * sizeof(Movimiento));
        capacidadMovimientos = nuevaCapacidad;
    }
    Movimiento mov;
    mov.fila = fila;
    mov.columna = columna;
    strcpy(mov.accion, accion);
    movimientos[numMovimientos] = mov;
    ++numMovimientos;
}

// Función para guardar los movimientos en un archivo
void guardarMovimientosEnArchivo(const char* nombreArchivo, Movimiento* movimientos, int numMovimientos) {
    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    for (int i = 0; i < numMovimientos; ++i) {
        archivo << "Fila: " << movimientos[i].fila 
                << ", Columna: " << movimientos[i].columna 
                << ", Accion: " << movimientos[i].accion << '\n';
    }

    archivo << "Total de movimientos: " << numMovimientos << '\n';

    archivo.close();
}

// Función recursiva para inicializar el arreglo de posiciones de reinas
void inicializarPosicionesReinas(int* posicionReinas, int n, int indice) {
    if (indice >= n) return;
    posicionReinas[indice] = -1;
    inicializarPosicionesReinas(posicionReinas, n, indice + 1);
}

// Función recursiva para verificar si una reina puede ser colocada en la fila actual
bool esSeguroColocarReina(int* posicionReinas, int filaActual, int columna) {
    for (int i = 0; i < filaActual; ++i) {
        int otraColumna = posicionReinas[i];
        if (otraColumna == columna || abs(otraColumna - columna) == abs(i - filaActual)) {
            return false;
        }
    }
    return true;
}

// Función recursiva para encontrar todas las soluciones del problema de las N-Reinas
void encontrarTodasLasSoluciones(int* posicionReinas, int filaActual, int n, Movimiento*& movimientos, int& capacidadMovimientos, int& numMovimientos) {
    if (filaActual == n) {
        if (numSoluciones >= capacidadSoluciones) {
            // Aumentar la capacidad de las soluciones y movimientos
            int nuevaCapacidad = capacidadSoluciones == 0 ? 10 : capacidadSoluciones * 2;
            soluciones = (int**)realloc(soluciones, nuevaCapacidad * sizeof(int*));
            movimientosPorSolucion = (Movimiento**)realloc(movimientosPorSolucion, nuevaCapacidad * sizeof(Movimiento*));
            numMovimientosPorSolucion = (int*)realloc(numMovimientosPorSolucion, nuevaCapacidad * sizeof(int));
            capacidadSoluciones = nuevaCapacidad;
        }

        soluciones[numSoluciones] = (int*)malloc(n * sizeof(int));
        memcpy(soluciones[numSoluciones], posicionReinas, n * sizeof(int));
        
        movimientosPorSolucion[numSoluciones] = (Movimiento*)malloc(numMovimientos * sizeof(Movimiento));
        memcpy(movimientosPorSolucion[numSoluciones], movimientos, numMovimientos * sizeof(Movimiento));
        
        numMovimientosPorSolucion[numSoluciones] = numMovimientos;
        
        ++numSoluciones;
        return;
    }

    for (int columna = 0; columna < n; ++columna) {
        if (esSeguroColocarReina(posicionReinas, filaActual, columna)) {
            posicionReinas[filaActual] = columna;
            agregarMovimiento(filaActual, columna, "Colocar", movimientos, capacidadMovimientos, numMovimientos);
            encontrarTodasLasSoluciones(posicionReinas, filaActual + 1, n, movimientos, capacidadMovimientos, numMovimientos);
            agregarMovimiento(filaActual, columna, "Eliminar", movimientos, capacidadMovimientos, numMovimientos);
            posicionReinas[filaActual] = -1;
        }
    }
}

// Función para seleccionar una solución aleatoria de las soluciones encontradas
int seleccionarIndiceSolucionAleatoria() {
    srand(time(nullptr));
    return rand() % numSoluciones;
}

// Función para dibujar la reina en la posición especificada
void dibujarReina(int x, int y, int tamanoCuadro) {
    int margen = tamanoCuadro * 0.1;  // Margen de la reina
    string path = "images/ReinaBlanca1.jpg";  // Utilizar la imagen de la reina blanca
    readimagefile(path.c_str(), x + margen, y + margen, x + tamanoCuadro - margen, y + tamanoCuadro - margen);
}

// Función para ejecutar el problema de N-Reinas
void ejecutarNReinas(int n) {
    if (n <= 0) {
        cout << "El numero de reinas debe ser mayor que 0.\n";
        return;
    }

    int* posicionReinas = (int*)malloc(n * sizeof(int));
    if (posicionReinas == nullptr) {
        cout << "Error al asignar memoria.\n";
        return;
    }
    inicializarPosicionesReinas(posicionReinas, n, 0);

    // Limpiar el número de soluciones
    numSoluciones = 0;
    capacidadSoluciones = 10;
    soluciones = (int**)malloc(capacidadSoluciones * sizeof(int*));
    movimientosPorSolucion = (Movimiento**)malloc(capacidadSoluciones * sizeof(Movimiento*));
    numMovimientosPorSolucion = (int*)malloc(capacidadSoluciones * sizeof(int));

    // Arreglo para almacenar los movimientos actuales durante la búsqueda de soluciones
    Movimiento* movimientosActuales = (Movimiento*)malloc(n * n * 2 * sizeof(Movimiento));
    int capacidadMovimientosActuales = n * n * 2;
    int numMovimientosActuales = 0;

    // Encontrar todas las soluciones
    encontrarTodasLasSoluciones(posicionReinas, 0, n, movimientosActuales, capacidadMovimientosActuales, numMovimientosActuales);

    // Imprimir el número total de soluciones encontradas
    cout << "Numero total de soluciones encontradas: " << numSoluciones << endl;

    // Seleccionar una solución aleatoria
    int indiceSolucionAleatoria = seleccionarIndiceSolucionAleatoria();
    int* solucionAleatoria = soluciones[indiceSolucionAleatoria];
    Movimiento* movimientosSolucionAleatoria = movimientosPorSolucion[indiceSolucionAleatoria];
    int numMovimientosSolucionAleatoria = numMovimientosPorSolucion[indiceSolucionAleatoria];

    for (int i = 0; i < n; ++i) {
        posicionReinas[i] = solucionAleatoria[i];
    }

    // Ajustar el tamaño del cuadro para números menores a 7
    int tamanoCuadro = (n < 7) ? 70 : 50; // Ajuste del tamaño de cuadro
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;

    // Cerrar cualquier ventana gráfica abierta antes de inicializar una nueva
    closegraph();

    // Inicializar una nueva ventana con el tamaño ajustado
    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de N-Reinas");

    // Ajustar las posiciones iniciales para centrar el tablero
    int inicioX = 20;
    int inicioY = 20;

    // Configurar los parámetros del tablero de ajedrez
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };

    // Configurar el color de fondo para que el tablero sea más visible
    setbkcolor(DARKGRAY);
    cleardevice(); // Limpia la pantalla con el nuevo color de fondo

    // Dibujar el tablero de N x N sin piezas iniciales
    for (int fila = 0; fila < n; ++fila) {
        for (int columna = 0; columna < n; ++columna) {
            dibujarCuadroConPieza(tablero, fila, columna, nullptr);
        }
    }
    // Dibujar la notación del tablero
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    // Dibujar las reinas en sus posiciones
    for (int fila = 0; fila < n; ++fila) {
        int columna = posicionReinas[fila];
        int x = tablero.inicioX + columna * tablero.tamanoCuadro;
        int y = tablero.inicioY + fila * tablero.tamanoCuadro;
        dibujarReina(x, y, tablero.tamanoCuadro);
    }

    // Esperar a que el usuario presione una tecla
    getch();
    
    // Cerrar el modo gráfico
    closegraph();

    // Guardar los movimientos de la solución seleccionada en un archivo
    guardarMovimientosEnArchivo("movimientos.txt", movimientosSolucionAleatoria, numMovimientosSolucionAleatoria);

    // Liberar memoria
    free(posicionReinas);
    free(movimientosActuales);
    for (int i = 0; i < numSoluciones; ++i) {
        free(soluciones[i]);
        free(movimientosPorSolucion[i]);
    }
    free(soluciones);
    free(movimientosPorSolucion);
    free(numMovimientosPorSolucion);
}
