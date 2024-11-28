#include <iostream>
#include "Frac.h"

using namespace std; // Aquí se corrigió el error de sintaxis

void Frac::in() {
    cout << "Ingrese el numerador: ";
    cin >> a;

    cout << "Ingrese el denominador: ";
    cin >> b;
}

// Sobrecarga del operador *
Frac Frac::operator*(const Frac &obj) {
    Frac temporal;
    temporal.a = a * obj.a;
    temporal.b = b * obj.b;
    return temporal;
}

void Frac::out() {
    cout << "La multiplicacion de la fraccion es: " << a << "/" << b << endl;
}
