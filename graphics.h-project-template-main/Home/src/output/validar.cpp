#include "validar.h"
#include "Nodo.h"

#include <iostream>
#include <conio.h>
#include <cctype>

using namespace std;

template<typename T>
bool validarCedula(T cedula) {
    int i, A[10], res, mul, sumapares = 0, sumaimpares = 0, digito, sumatotal;
    long int cos;
    for (i = 9; i >= 0; i--) {
        cos = cedula / 10;
        res = cedula % 10;
        A[i] = res;
        cedula = cos;
    }
    for (i = 0; i < 9; i += 2) {
        mul = A[i] * 2;
        if (mul > 9)
            mul -= 9;
        sumapares += mul;
    }
    for (i = 1; i < 8; i += 2)
        sumaimpares += A[i];

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    digito = 10 - res;

    if (digito == 10)
        digito = 0;
    return digito == A[9];
}

template<typename T>
bool esNumeroCedulaValido(const string &numCedula) {
    if (numCedula.length() != 10) return false;
    for (char c : numCedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

template<typename T>
string ingresarCedula(const string &msj) {
    string dato = "";
    cout << msj << ": ";
    char c;
    while (true) {
        c = _getch(); 
        if (isdigit(c)) {
            if (dato.length() < 10) {
                dato += c;
                cout << c;
            }
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b"; 
            }
        } else if (c == 13) { 
            if (dato.length() == 10) {
                cout << endl;
                break;
            } else {
                cout << "\n>> Debe ingresar exactamente 10 numeros. Intente nuevamente." << endl;
                dato = "";
                cout << msj << ": ";
            }
        }
    }
    return dato;
}

template<typename T>
bool cedulaRepetida(Nodo<T>* raiz, const string &numCedula) {
    Nodo<T>* nodo = raiz;
    while (nodo != nullptr) {
        if (nodo->getCedula() == numCedula) {
            return true;
        } else if (numCedula < nodo->getCedula()) {
            nodo = nodo->getIzquierdo();
        } else {
            nodo = nodo->getDerecho();
        }
    }
    return false;
}

template<typename T>
string ingresarLetras(const string &msj, bool opcional) {
    string dato = "";
    cout << msj << ": ";
    char c;
    while ((c = _getch()) != 13 || (!opcional && dato.empty())) {
        if (isalpha(c)) {
            dato += c;
            cout << c;
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b"; 
            }
        } else if (c == 13 && !dato.empty()) {
            break;
        }
    }
    cout << endl;
    return dato;
}

template<typename T>
string convertirMayusculas(string str) {
    if (str.empty()) return str;
    *str.begin() = toupper(*str.begin());
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        *it = tolower(*it);
    }
    return str;
}
