#include "tablero.h"
#include <graphics.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// Función recursiva para vaciar todas las posiciones del arreglo de piezas
void vaciarPiezas(string* piezas, int n, int indice) {
    if (indice >= n * n) return;
    piezas[indice] = "";
    vaciarPiezas(piezas, n, indice + 1);
}

// Función recursiva para colocar las piezas negras en el arreglo de piezas
void colocarPiezasNegras(string* piezas, int indice) {
    if (indice >= 8) return;

    string piezasNegras[8] = {"TorreNegra1", "CaballoNegro1", "AlfilNegro1", "ReinaNegra1", "ReyNegro1", "AlfilNegro1", "CaballoNegro1", "TorreNegra1"};

    // Colocar piezas en la fila de atrás (fila 0)
    piezas[indice] = piezasNegras[indice];

    // Colocar peones en la fila 1
    piezas[indice + 8] = "PeonNegro1";

    colocarPiezasNegras(piezas, indice + 1);
}

// Función recursiva para colocar las piezas blancas en el arreglo de piezas
void colocarPiezasBlancas(string* piezas, int indice) {
    if (indice >= 8) return;

    string piezasBlancas[8] = {"TorreBlanca1", "CaballoBlanco1", "AlfilBlanco1", "ReinaBlanca1", "ReyBlanco1", "AlfilBlanco1", "CaballoBlanco1", "TorreBlanca1"};

    // Colocar peones en la fila 6
    piezas[indice + 48] = "PeonBlanco1";

    // Colocar piezas en la fila de atrás (fila 7)
    piezas[indice + 56] = piezasBlancas[indice];

    colocarPiezasBlancas(piezas, indice + 1);
}

// Función para inicializar las piezas en el tablero de ajedrez estándar usando recursividad
void inicializarPiezasAjedrezEstandar(string* piezas, int n) {
    vaciarPiezas(piezas, n, 0);
    colocarPiezasNegras(piezas, 0);
    colocarPiezasBlancas(piezas, 0);
}

// Función recursiva para dibujar cada cuadro del tablero de ajedrez
void dibujarCuadroConPieza(Tablero tablero, int fila, int columna, string* piezas) {
    // Verificar si hemos terminado de dibujar todas las filas
    if (fila >= tablero.n) return;

    // Calcular las coordenadas de la esquina superior izquierda del cuadro actual
    int x = tablero.inicioX + columna * tablero.tamanoCuadro;
    int y = tablero.inicioY + fila * tablero.tamanoCuadro;

    // Alternar colores: si la suma de la fila y la columna es par, el cuadro es blanco; de lo contrario, es negro
    int colorCuadro;
    if ((fila + columna) % 2 == 0) {
        setfillstyle(SOLID_FILL, WHITE);  // Color blanco
        colorCuadro = WHITE;
    } else {
        setfillstyle(SOLID_FILL, BLACK);  // Color negro
        colorCuadro = BLACK;
    }

    // Dibujar el cuadro
    bar(x, y, x + tablero.tamanoCuadro, y + tablero.tamanoCuadro);

    // Determinar la pieza en la posición inicial de ajedrez
    if (piezas != nullptr) { // Verificar si el puntero piezas no es nulo
        string pieza = piezas[fila * tablero.n + columna];

        // Si hay una pieza, cargar la imagen correspondiente
        if (!pieza.empty()) {
            // Reducir el tamaño de la pieza al 80% del cuadro
            int margen = tablero.tamanoCuadro * 0.1;  // Dejar un margen del 10% alrededor de la pieza
            string path = "images/" + pieza + ".jpg";
            readimagefile(path.c_str(), x + margen, y + margen, x + tablero.tamanoCuadro - margen, y + tablero.tamanoCuadro - margen);
        }
    }

    // Llamada recursiva para el siguiente cuadro
    if (columna < tablero.n - 1) {
        dibujarCuadroConPieza(tablero, fila, columna + 1, piezas);
    } else {
        // Moverse a la siguiente fila
        dibujarCuadroConPieza(tablero, fila + 1, 0, piezas);
    }
}

// Función recursiva para dibujar la notación de columnas
void dibujarNotacionColumnas(Tablero tablero, int i) {
    if (i >= tablero.n) return;

    char columna[2];
    sprintf(columna, "%c", 'a' + i);  // Convertir entero a carácter
    outtextxy(tablero.inicioX + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, 
              tablero.inicioY - tablero.tamanoCuadro / 4, columna);  // Parte superior
    outtextxy(tablero.inicioX + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, 
              tablero.inicioY + tablero.n * tablero.tamanoCuadro + tablero.tamanoCuadro / 4, columna);  // Parte inferior

    dibujarNotacionColumnas(tablero, i + 1);
}

// Función recursiva para dibujar la notación de filas
void dibujarNotacionFilas(Tablero tablero, int i) {
    if (i >= tablero.n) return;

    char fila[2];
    sprintf(fila, "%d", 8 - i);  // Convertir entero a cadena
    outtextxy(tablero.inicioX - tablero.tamanoCuadro / 4, 
              tablero.inicioY + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, fila);  // Lado izquierdo
    outtextxy(tablero.inicioX + tablero.n * tablero.tamanoCuadro + tablero.tamanoCuadro / 4, 
              tablero.inicioY + i * tablero.tamanoCuadro + tablero.tamanoCuadro / 2 - 5, fila);  // Lado derecho

    dibujarNotacionFilas(tablero, i + 1);
}

// Función para mostrar el tablero inicial de ajedrez sin piezas
void mostrarTableroSinPiezas() {
    int n = 8;  // Tamaño del tablero de ajedrez estándar

    // Calcular el tamaño de cada cuadro en función del tamaño de la ventana
    int tamanoCuadro = 50; // Fijamos un tamaño de cuadro razonable
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;

    // Inicializar una nueva ventana con el tamaño ajustado
    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Ajedrez");

    // Ajustar las posiciones iniciales para centrar el tablero
    int inicioX = 20;
    int inicioY = 20;

    // Configurar los parámetros del tablero
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };

    // Configurar el color de fondo para que el tablero sea más visible
    setbkcolor(DARKGRAY);
    cleardevice(); // Limpia la pantalla con el nuevo color de fondo

    // Dibujar el tablero de ajedrez sin piezas
    dibujarCuadroConPieza(tablero, 0, 0, nullptr);
    // Dibujar la notación del tablero
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    // Esperar a que el usuario presione una tecla
    getch();

    // Cerrar el modo gráfico
    closegraph();
}

// Función para mostrar el tablero inicial de ajedrez con piezas
void mostrarTableroConPiezas() {
    int n = 8;  // Tamaño del tablero de ajedrez estándar

    // Calcular el tamaño de cada cuadro en función del tamaño de la ventana
    int tamanoCuadro = 50; // Fijamos un tamaño de cuadro razonable
    int anchoTotal = tamanoCuadro * n + 40;
    int altoTotal = tamanoCuadro * n + 40;

    // Inicializar una nueva ventana con el tamaño ajustado
    int gd = DETECT, gm;
    initwindow(anchoTotal, altoTotal, "Tablero de Ajedrez");

    // Ajustar las posiciones iniciales para centrar el tablero
    int inicioX = 20;
    int inicioY = 20;

    // Configurar los parámetros del tablero
    Tablero tablero = { n, tamanoCuadro, inicioX, inicioY };

    // Inicializar las piezas
    string* piezas = new string[n * n];
    inicializarPiezasAjedrezEstandar(piezas, n);

    // Configurar el color de fondo para que el tablero sea más visible
    setbkcolor(DARKGRAY);
    cleardevice(); // Limpia la pantalla con el nuevo color de fondo

    // Dibujar el tablero de ajedrez con piezas
    dibujarCuadroConPieza(tablero, 0, 0, piezas);
    // Dibujar la notación del tablero
    dibujarNotacionColumnas(tablero, 0);
    dibujarNotacionFilas(tablero, 0);

    // Esperar a que el usuario presione una tecla
    getch();

    // Cerrar el modo gráfico
    closegraph();

    // Liberar memoria
    delete[] piezas;
}
