#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "nreinas.h"
#include "tablero.h"

using namespace std;

// Función para mostrar el menú principal
void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    cout << "MENU PRINCIPAL\n";
    for (int i = 1; i <= 4; ++i) {
        if (i == opcionSeleccionada) {
            cout << "-> ";
        } else {
            cout << "   ";
        }
        switch (i) {
            case 1:
                cout << "Mostrar tablero de ajedrez sin piezas\n";
                break;
            case 2:
                cout << "Mostrar tablero de ajedrez con piezas\n";
                break;
            case 3:
                cout << "Resolver el problema de N-Reinas\n";
                break;
            case 4:
                cout << "Salir\n";
                break;
        }
    }
}

// Función para obtener un número del usuario
int obtenerNumero() {
    string entrada;
    char tecla;
    cout << "Ingrese el numero de reinas: ";
    while (true) {
        tecla = _getch();
        if (tecla == 13 && !entrada.empty()) { // Si presiona Enter y no está vacío
            int numero = stoi(entrada);
            if (numero > 3) {
                cout << endl;
                return numero;
            } else {
                cout << "\nEl numero debe ser mayor que 3. Intente de nuevo: ";
                entrada.clear();
            }
        }
        if (isdigit(tecla)) {
            entrada += tecla;
            cout << tecla;
        } else if (tecla == 8 && !entrada.empty()) { // Si presiona Backspace y no está vacío
            entrada.pop_back();
            cout << "\b \b"; // Retrocede, elimina el carácter y retrocede de nuevo
        }
    }
}

// Función para ejecutar el menú
void ejecutarMenu() {
    int opcionSeleccionada = 1;
    int tecla;

    while (true) {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();

        if (tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case 72:
                    if (opcionSeleccionada > 1) {
                        opcionSeleccionada--;
                    }
                    break;
                case 80:
                    if (opcionSeleccionada < 4) {
                        opcionSeleccionada++;
                    }
                    break;
            }
        } else if (tecla == 13) { // Si presiona Enter
            switch (opcionSeleccionada) {
                case 1:
                    mostrarTableroSinPiezas();
                    break;
                case 2:
                    mostrarTableroConPiezas();
                    break;
                case 3: {
                    int n = obtenerNumero();
                    ejecutarNReinas(n);
                    break;
                }
                case 4:
                    cout << "Saliendo del programa.\n";
                    return;
            }
        }
    }
}

int main() {
    ejecutarMenu();
    return 0;
}
