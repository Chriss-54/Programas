#include <iostream>
#include "Frac.h" // Incluye el archivo de encabezado, no el de implementación

using namespace std;

int main() {
    Frac F1, F2, result; // Corrige la declaración de F2 y result

    system("cls"); // Limpia la pantalla

    cout << "Ingrese la primera fracción: " << endl;
    F1.in();

    cout << "Ingrese la segunda fracción: " << endl;
    F2.in();

    result = F1 * F2; // Realiza la operación de multiplicación
    result.out();

    return 0;
}
